#include "configuredialog.h"
#include <QMessageBox>
#include <QtDebug>
#include <QFileDialog>

#define LOCAL_EDGE "Local"

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    //Set the minimum and close button of the main frame.
    this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint |
                                         Qt::WindowCloseButtonHint));

    m_portPanel = NULL;

    images[0] = "background:url(:/DIInterrupt/Resources/ButtonUp.png)";
    images[1] = "background:url(:/DIInterrupt/Resources/ButtonDown.png)";
    images[2] = "background:url(:/DIInterrupt/Resources/ButtonDisabled.png)";

    this->layout = new QVBoxLayout(ui.scrollAreaWidgetContents);

    connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged(int)));
    connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));
    connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(ButtonBrowseClicked()));
    connect(ui.btnLogin, SIGNAL(clicked()), this, SLOT(ButtonLoginClicked()));
    connect(ui.cmbHostName, SIGNAL(editTextChanged(QString)), this,
            SLOT(ComboBoxHostNameEditTextChanged(QString)));

    InitailizationManagedEdgeList();

    configure.hostName = LOCAL_EDGE;
    Initailization();
}

ConfigureDialog::~ConfigureDialog()
{

}

void ConfigureDialog::InitailizationManagedEdgeList()
{
    ui.cmbHostName->blockSignals(true);

    ui.cmbHostName->clear();
    ui.cmbHostName->addItem(LOCAL_EDGE);

    EthManagedEdge* managedEdge;
    int32 count = 0;
    ErrorCode ret = AdxQueryActiveManagedEdge(&count, NULL);
    if (ret == ErrorBufferTooSmall) {
        managedEdge = new EthManagedEdge[count];
        ret = AdxQueryActiveManagedEdge(&count, managedEdge);
        for (int i = 0; i < count; ++i) {
            ui.cmbHostName->addItem(QString::fromWCharArray(managedEdge[i].EdgeName));
        }

        delete[] managedEdge;
    }
    ui.cmbHostName->setCurrentIndex(0);

    ui.cmbHostName->blockSignals(false);
}

void ConfigureDialog::Initailization()
{
    InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        std::wstring hostName = configure.hostName.toStdWString();
        //Login the edge by hostName
        if (Success == instantDiCtrl->Login(hostName.c_str())) {
            EnableSettings(true);
        }
        else {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }

    ui.cmbDevice->blockSignals(true);
    ui.cmbDevice->clear();
    ui.cmbDevice->blockSignals(false);
    Array<DeviceTreeNode> *supportedDevices = instantDiCtrl->getSupportedDevices();

    if (supportedDevices->getCount() > 0)
    {
        for (int i = 0; i < supportedDevices->getCount(); i++) {
            DeviceTreeNode const &node = supportedDevices->getItem(i);
            qDebug("%d, %ls\n", node.DeviceNumber, node.Description);

            DeviceInformation devInfo(node.Description, ModeRead);
            instantDiCtrl->setSelectedDevice(devInfo);

            Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
            if (interruptChans == NULL) {
                continue;
            }
            ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
        }
    }

    if (ui.cmbDevice->count() < 1) {
        QMessageBox::information(this, tr("Warning Information"),
                                 tr("No device to support the currently demonstrated function!"));
        EnableSettings(false);
    }
    else {
        ui.cmbDevice->setCurrentIndex(0);
    }

    //Logout the edge
    instantDiCtrl->Logout();
    instantDiCtrl->Dispose();
    supportedDevices->Dispose();
}

void ConfigureDialog::CheckError(ErrorCode errorCode)
{
    if (errorCode >= 0xE0000000 && errorCode != Success)
    {
        QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
            QString::number(errorCode, 16).right(8).toUpper();
        QMessageBox::information(this, "Warning Information", message);
    }
}

void ConfigureDialog::DeviceChanged(int)
{   
    //remove the old port panel
    if (m_portPanel != NULL) {
        int height = ui.scrollAreaWidgetContents->height();
        for (int i = 0; i < enablePortCount; i++) {
            this->layout->removeWidget(m_portPanel[i]);
            ui.scrollAreaWidgetContents->setGeometry(0, 0, 309, height - (i + 1) * 40);
            if (m_portPanel[i] != NULL) {
                delete m_portPanel[i];
                m_portPanel[i] = NULL;
            }
        }
    }
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        //Login the edge by hostName
        std::wstring hostName = configure.hostName.toStdWString();
        if (Success != instantDiCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }
    ErrorCode errorCode = instantDiCtrl->setSelectedDevice(selected);
    ui.btnOK->setEnabled(true);
    if (errorCode != Success){
        QString des = QString::fromStdWString(description);
        QString str = QString("Error:the error code is 0x%1\n\
                      The %2 is busy or not exit in computer now.\n\
                      Select other device please!").arg(errorCode, 0, 16).arg(des);
        QMessageBox::information(this, "Warning Information", str);
        ui.btnOK->setEnabled(false);
        return;
    }

    Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
    int intPortCount = interruptChans->getCount();
    quint8* ports = new quint8[instantDiCtrl->getFeatures()->getPortCount()];
    for (int i = 0; i < instantDiCtrl->getFeatures()->getPortCount(); i++) {
        ports[i] = 0;
    }

    for (int i = 0; i < intPortCount; i++) {
        int portIndex = interruptChans->getItem(i).getChannel() / 8;
        int chIndex = interruptChans->getItem(i).getChannel() % 8;
        ports[portIndex] |= 0x1 << chIndex;
    }

    enablePortCount = 0;
    for (int i = 0; i < instantDiCtrl->getFeatures()->getPortCount(); i++) {
        if (ports[i] != 0){
                enablePortCount++;
        }
    }

    int* portIndexes = new int[enablePortCount];
    int j = 0;
    for (int i = 0; i < instantDiCtrl->getFeatures()->getPortCount(); i++) {
        if (ports[i] != 0) {
            portIndexes[j++] = i;
        }
    }

     m_portPanel = new DioPortUI*[enablePortCount];
     for (int i = 0; i < enablePortCount; i++) {
        ui.scrollAreaWidgetContents->setGeometry(0, 0, 309, (i + 1) * 40);
        m_portPanel[i] = new DioPortUI(0, Qt::Widget, portIndexes[i], ports[portIndexes[i]], images);
        m_portPanel[i]->setIsEditable(true);
        m_portPanel[i]->setMask(ports[portIndexes[i]]);
        m_portPanel[i]->setState((quint8)1);

        this->layout->addWidget(m_portPanel[i]);
     }
     delete []ports;
     delete []portIndexes;
     //Logout the edge
     instantDiCtrl->Logout();
     instantDiCtrl->Dispose();
}

void ConfigureDialog::ButtonOKClicked()
{
    bool selectedChannel = false;
    for (int i = 0; i < enablePortCount; i++) {
        if (m_portPanel[i]->getState() != 0) {
            selectedChannel = true;
            break;
        }
    }
    if (!selectedChannel) {
        QMessageBox::information(this, "Warning Information", "Please enable at lest one channel!");
        return;
    }

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        //Login the edge by hostName
        std::wstring hostName = configure.hostName.toStdWString();
        if (Success != instantDiCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }
    ErrorCode errorCode = instantDiCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    configure.deviceName = ui.cmbDevice->currentText();
    configure.selectedPortIndex = new int[enablePortCount];
    configure.enableChannel = new int[enablePortCount];
    for (int i = 0; i < enablePortCount; i++) {
        configure.selectedPortIndex[i] = m_portPanel[i]->getKey();
        configure.enableChannel[i] = m_portPanel[i]->getState();
    }

    //Logout the edge
    instantDiCtrl->Logout();
    instantDiCtrl->Dispose();
    this->accept();
}

void ConfigureDialog::ButtonCancelClicked()
{
    this->reject();
}

void ConfigureDialog::ButtonBrowseClicked()
{
    QString str = QFileDialog::getOpenFileName(this, tr("Open Profile"), "../../profile",
                                               tr("Image Files(*.xml)"));
    ui.txtProfilePath->setText(str);
    configure.profilePath = str;
}

void ConfigureDialog::ButtonLoginClicked()
{
    configure.hostName = ui.cmbHostName->currentText();
    Initailization();
}

void ConfigureDialog::EnableSettings(bool is_enable)
{
    ui.frame->setEnabled(is_enable);
    ui.btnOK->setEnabled(is_enable);
}

void ConfigureDialog::ComboBoxHostNameEditTextChanged(const QString &arg1)
{
    bool is_hostName_null = arg1.isNull() || arg1.isEmpty();
    ui.btnLogin->setEnabled(!is_hostName_null);

    bool is_local = arg1 == LOCAL_EDGE;
    EnableSettings(is_local);

    if (is_local) {
        configure.hostName = ui.cmbHostName->currentText();
        Initailization();
    }
}
