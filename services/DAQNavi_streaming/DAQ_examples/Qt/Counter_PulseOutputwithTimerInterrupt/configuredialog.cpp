#include "configuredialog.h"
#include <QMessageBox>
#include <QtDebug>
#include <QProcess>
#include <QFileDialog>

#define LOCAL_EDGE "Local"

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    //Set the minimum and close button of the main frame.
    this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint |
                                         Qt::WindowCloseButtonHint));

    connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged(int)));
    connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));
    connect(ui.cmbModuleIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(ModuleIndexChanged(int)));
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
    TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        std::wstring hostName = configure.hostName.toStdWString();
        //Login the edge by hostName
        if (Success == timerPulseCtrl->Login(hostName.c_str())) {
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
    Array<DeviceTreeNode> *supportedDevices = timerPulseCtrl->getSupportedDevices();
    //Logout the edge
    timerPulseCtrl->Logout();
    timerPulseCtrl->Dispose();

    if (supportedDevices->getCount() == 0)
    {
        QMessageBox::information(this, tr("Warning Information"),
            tr("No device to support the currently demonstrated function!"));
        EnableSettings(false);
    } else {
        for (int i = 0; i < supportedDevices->getCount(); i++) {
            DeviceTreeNode const &node = supportedDevices->getItem(i);
            ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
        }
        ui.cmbDevice->setCurrentIndex(0);
    }

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
    ui.cmbModuleIndex->blockSignals(true);
    ui.cmbModuleIndex->clear();
    ui.cmbModuleIndex->blockSignals(false);
    TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        //Login the edge by hostName
        std::wstring hostName = configure.hostName.toStdWString();
        if (Success != timerPulseCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }
    Array<DeviceTreeNode> *supportedDevices = timerPulseCtrl->getSupportedDevices();
    //Logout the edge
    timerPulseCtrl->Logout();
    timerPulseCtrl->Dispose();

    // Set ModulesIndex combo box
    DeviceTreeNode devNode = supportedDevices->getItem(ui.cmbDevice->currentIndex());
    int k = 0;
    for (int j = 0; j < 8; j++) {
        k = devNode.ModulesIndex[j];
        if (k != -1) {
            ui.cmbModuleIndex->addItem(QString("%1").arg(k));
        } else {
            break;
        }
    }
    ui.cmbModuleIndex->setCurrentIndex(0);

    supportedDevices->Dispose();
}

void ConfigureDialog::ModuleIndexChanged(int)
{
    ui.cmbCounterChannel->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        //Login the edge by hostName
        std::wstring hostName = configure.hostName.toStdWString();
        if (Success != timerPulseCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }

    ErrorCode errorCode = Success;
    selected.ModuleIndex = ui.cmbModuleIndex->currentIndex();
    errorCode = timerPulseCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    // Set channel start combo box
    int channelCountMax = timerPulseCtrl->getFeatures()->getChannelCountMax();
    Array<CounterCapability> * counterCap;
    int itemCount;

    for (int i = 0; i < channelCountMax; i++) {
           itemCount = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
         counterCap = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i);
        for (int j = 0; j < itemCount; j++) {
               if (TimerPulse == counterCap->getItem(j)) {
                ui.cmbCounterChannel->addItem(QString("%1").arg(i));
            }
        }
    }
    ui.cmbCounterChannel->setCurrentIndex(0);

    //Logout the edge
    timerPulseCtrl->Logout();
    timerPulseCtrl->Dispose();
}

void ConfigureDialog::ButtonOKClicked()
{
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        //Login the edge by hostName
        std::wstring hostName = configure.hostName.toStdWString();
        if (Success != timerPulseCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }

    ErrorCode errorCode = timerPulseCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    configure.deviceName = ui.cmbDevice->currentText();
    configure.channel = ui.cmbCounterChannel->currentText().toInt();
    configure.moduleIndex = ui.cmbModuleIndex->currentText().toInt();

    //Logout the edge
    timerPulseCtrl->Logout();
    timerPulseCtrl->Dispose();
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
