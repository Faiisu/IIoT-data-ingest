#include "configuredialog.h"
#include <QMessageBox>
#include <QtDebug>
#include <QProcess>
#include <QFileDialog>
#include <QButtonGroup>

#define LOCAL_EDGE "Local"

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    //Set the minimum and close button of the main frame.
    this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint |
                                         Qt::WindowCloseButtonHint));

    this->buttonGroup0 = new QButtonGroup();
    this->buttonGroup0->addButton(ui.btn00, 0);
    this->buttonGroup0->addButton(ui.btn01, 1);
    this->buttonGroup0->addButton(ui.btn02, 2);
    this->buttonGroup0->addButton(ui.btn03, 3);
    this->buttonGroup0->addButton(ui.btn04, 4);
    this->buttonGroup0->addButton(ui.btn05, 5);
    this->buttonGroup0->addButton(ui.btn06, 6);
    this->buttonGroup0->addButton(ui.btn07, 7);
    this->buttonGroup0->setExclusive(false);

    buttons[0] = ui.btn00;
    buttons[1] = ui.btn01;
    buttons[2] = ui.btn02;
    buttons[3] = ui.btn03;
    buttons[4] = ui.btn04;
    buttons[5] = ui.btn05;
    buttons[6] = ui.btn06;
    buttons[7] = ui.btn07;

    strs[0] = "background:url(:/DIStatusChangeInterrupt/Resources/ButtonUp.png)";
    strs[1] = "background:url(:/DIStatusChangeInterrupt/Resources/ButtonDown.png)";

    connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged(int)));
    connect(ui.cmbDIport, SIGNAL(currentIndexChanged(int)), this, SLOT(cmbDIportChanged(int)));
    connect(buttonGroup0, SIGNAL(buttonPressed(QAbstractButton *)), this, SLOT(ButtonsClicked(QAbstractButton *)));
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

            Array<DiCosintPort>* diCosintPorts = instantDiCtrl->getDiCosintPorts();
            if (diCosintPorts == NULL) {
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
    ui.cmbDIport->clear();

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
    ErrorCode errorCode = Success;
    errorCode = instantDiCtrl->setSelectedDevice(selected);
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

    //set the DI port
    Array<DiCosintPort>* diCosintPorts = instantDiCtrl->getDiCosintPorts();
    int PmPortCount = diCosintPorts->getCount();
    int portNumber = 0;
    for (int i = 0; i < PmPortCount; i++) {
        portNumber = diCosintPorts->getItem(i).getPort();
        ui.cmbDIport->addItem(QString("%1").arg(portNumber));
     }
    ui.cmbDIport->setCurrentIndex(0);
    //Logout the edge
    instantDiCtrl->Logout();
    instantDiCtrl->Dispose();
    InitializePortState();
}

void ConfigureDialog::cmbDIportChanged(int)
{
    InitializePortState();
}

void ConfigureDialog::InitializePortState()
{
    enableChannels = 0;

    ui.txtenableChan->setText(QString::number(enableChannels, 16).toUpper());

    for (int i = 0; i < 8; i++) {
        buttons[i]->setStyleSheet(strs[0]);
        buttonsTags[i] = 0;
    }
}

void ConfigureDialog::ButtonsClicked(QAbstractButton *btn)
{
    int i = 0, data = 1, bitValue;
    int id = buttonGroup0->id(btn);
    bitValue = buttonsTags[id];

    while (i < id) {
        data = data * 2;
        i++;
    }

    if (bitValue == 0) {
        enableChannels = enableChannels + data;
        buttons[id]->setStyleSheet(strs[1]);
        buttonsTags[id] = 1;
    } else {
        enableChannels = enableChannels - data;
        buttons[id]->setStyleSheet(strs[0]);
        buttonsTags[id] = 0;
    }

    ui.txtenableChan->setText(QString::number(enableChannels, 16).toUpper());
}

void ConfigureDialog::ButtonOKClicked()
{
    if (this->enableChannels == 0) {
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

    configure.selectedPort = ui.cmbDIport->currentText().toInt();
    configure.enabledChannels = this->enableChannels;
    configure.deviceName = ui.cmbDevice->currentText();

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
