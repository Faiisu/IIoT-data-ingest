#include "configuredialog.h"
#include <QtWidgets/QMessageBox>
#include <QtDebug>
#include <QProcess>
#include <QFileDialog>

#define LOCAL_EDGE "Local"

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    //Set the minimum and close button of the main frame.
    this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint
                                         | Qt::WindowCloseButtonHint));

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
    InstantAiCtrl *instantAiCtrl = InstantAiCtrl::Create();

    if (configure.hostName != LOCAL_EDGE) {
        std::wstring hostName = configure.hostName.toStdWString();
        //Login the edge by hostName
        if (Success == instantAiCtrl->Login(hostName.c_str())) {
            EnableSettings(true);
        }
        else {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            instantAiCtrl->Dispose();
            return;
        }
    }

    Array<DeviceTreeNode>* supportedDevices = instantAiCtrl->getSupportedDevices();

    ui.cmbDevice->blockSignals(true);
    ui.cmbDevice->clear();
    ui.cmbDevice->blockSignals(false);

    if (supportedDevices->getCount() == 0)
    {
        QMessageBox::information(this, tr("Warning Information"),
            tr("No device to support the currently demonstrated function!"));
        EnableSettings(false);
    }
    else
    {
        for (int i = 0; i < supportedDevices->getCount(); i++)
        {
            DeviceTreeNode const &node = supportedDevices->getItem(i);
            qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
            ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
        }
        ui.cmbDevice->setCurrentIndex(0);
    }

    //Logout the edge
    instantAiCtrl->Logout();
    instantAiCtrl->Dispose();
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
    ui.cmbChannelCount->clear();
    ui.cmbChannelStart->clear();
    ui.cmbValueRange->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    InstantAiCtrl *instantAiCtrl = InstantAiCtrl::Create();

    if (configure.hostName != LOCAL_EDGE) {
        std::wstring hostName = configure.hostName.toStdWString();
        //Login the edge by hostName
        if (Success != instantAiCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            instantAiCtrl->Dispose();
            return;
        }
    }

    ErrorCode errorCode = instantAiCtrl->setSelectedDevice(selected);
    ui.btnOK->setEnabled(true);
    if (errorCode != 0){
        QString des = QString::fromStdWString(description);
        QString str = QString("Error:the error code is 0x%1\n\
                      The %2 is busy or not exit in computer now.\n\
                      Select other device please!").arg(errorCode, 0, 16).arg(des);
        QMessageBox::information(this, "Warning Information", str);
        ui.btnOK->setEnabled(false);
        instantAiCtrl->Dispose();
        return;
    }

    int channelCount = (instantAiCtrl->getChannelCount() < 16) ?
        instantAiCtrl->getChannelCount() : 16;
    int logicChannelCount = instantAiCtrl->getChannelCount();

    for (int i = 0; i < logicChannelCount; i++)
    {
        ui.cmbChannelStart->addItem(QString("%1").arg(i));
    }

    for (int i = 0; i < channelCount; i++)
    {
        ui.cmbChannelCount->addItem(QString("%1").arg(i + 1));
    }

    Array<ValueRange>* ValueRanges = instantAiCtrl->getFeatures()->getValueRanges();
    wchar_t         vrgDescription[128];
    MathInterval ranges;
    for (int i = 0; i < ValueRanges->getCount(); i++)
    {
        errorCode = AdxGetValueRangeInformation(ValueRanges->getItem(i),
            sizeof(vrgDescription), vrgDescription, &ranges, NULL);
        CheckError(errorCode);
        QString str = QString::fromWCharArray(vrgDescription);
        ui.cmbValueRange->addItem(str);
    }

    //Logout the edge
    instantAiCtrl->Logout();
    instantAiCtrl->Dispose();

    //Set the default value.
    ui.cmbChannelStart->setCurrentIndex(0);
    ui.cmbChannelCount->setCurrentIndex(1);
    ui.cmbValueRange->setCurrentIndex(0);
}

void ConfigureDialog::ButtonOKClicked()
{
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    InstantAiCtrl* instantAiCtrl = InstantAiCtrl::Create();
    if (configure.hostName != LOCAL_EDGE) {
        std::wstring hostName = configure.hostName.toStdWString();
        //Login the edge by hostName
        if (Success != instantAiCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            instantAiCtrl->Dispose();
            return;
        }
    }

    ErrorCode errorCode = instantAiCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    Array<ValueRange>* valueRanges = instantAiCtrl->getFeatures()->getValueRanges();
    configure.deviceName = ui.cmbDevice->currentText();
    configure.channelStart = ui.cmbChannelStart->currentText().toInt();
    configure.channelCount = ui.cmbChannelCount->currentText().toInt();
    configure.valueRange = valueRanges->getItem(ui.cmbValueRange->currentIndex());

    //Logout the edge
    instantAiCtrl->Logout();
    instantAiCtrl->Dispose();
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

