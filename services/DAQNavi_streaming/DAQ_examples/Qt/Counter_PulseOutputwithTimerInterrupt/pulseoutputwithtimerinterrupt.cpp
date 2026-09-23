#include <QPalette>
#include <QMessageBox>
#include "pulseoutputwithtimerinterrupt.h"

#define LOCAL_EDGE "Local"

PulseOutputwithTimerInterrupt::PulseOutputwithTimerInterrupt(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    ui.setupUi(this);
    //Set the minimum and close button of the main frame.
    this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint |
                                         Qt::WindowCloseButtonHint));

    //Set the background image for the main frame.
    ui.bkgrndImage->setAutoFillBackground(true);
    QPixmap pixMap(":/PulseOutputwithTimerInterrupt/Resources/Background.png");
    QPalette backPalette;
    backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
    ui.bkgrndImage->setPalette(backPalette);

    movie = new QMovie(":/PulseOutputwithTimerInterrupt/Resources/TimerPulseStatus.gif");
    ui.ExecutionStatus->setMovie(movie);
    movie->start();
    movie->stop();

    timerPulseCtrl = TimerPulseCtrl::Create();
    timerPulseCtrl->addTimerTickHandler(OnCounterEvent, this);

    eventCount = 0;
    ui.userFreqEditor->setText(tr("50"));
    ui.btnStop->setEnabled(false);

    connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
    connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
    connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
}

PulseOutputwithTimerInterrupt::~PulseOutputwithTimerInterrupt()
{
    if (timerPulseCtrl != NULL)
    {
       //Logout the edge
       timerPulseCtrl->Logout();
       timerPulseCtrl->Dispose();
       timerPulseCtrl = NULL;
    }
}

void PulseOutputwithTimerInterrupt::Initialize()
{
    //set the title of the form.
    this->setWindowTitle(tr("Pulse Output with Timer Interrupt - Run(") + configure.deviceName + tr(")"));

    ConfigureDevice();
}

void PulseOutputwithTimerInterrupt::ConfigureDevice()
{
    //Logout the edge
    ErrorCode errorCode = timerPulseCtrl->Logout();
    CheckError(errorCode);

    if (configure.hostName != LOCAL_EDGE) {
        //Login the edge by hostName
        std::wstring hostName = configure.hostName.toStdWString();
        if (Success != timerPulseCtrl->Login(hostName.c_str())) {
            QMessageBox::information(this, tr("Warning Information"),
                                     tr("Login failed! Please make sure the host name is valid."));
            return;
        }
    }

    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

    selected.ModuleIndex = configure.moduleIndex;
    errorCode = Success;
    errorCode = timerPulseCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    std::wstring profile = configure.profilePath.toStdWString();
    errorCode = timerPulseCtrl->LoadProfile(profile.c_str());
    CheckError(errorCode);

    errorCode = timerPulseCtrl->setChannelCount(1);
    CheckError(errorCode);
    errorCode =timerPulseCtrl->setChannelStart(configure.channel);
    CheckError(errorCode);
}

void PulseOutputwithTimerInterrupt::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
    {
        QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
            QString::number(errorCode, 16).right(8).toUpper();
        QMessageBox::information(this, "Warning Information", message);
    }
}

void PulseOutputwithTimerInterrupt::OnCounterEvent(void *, CntrEventArgs *, void * userParam)
{
   PulseOutputwithTimerInterrupt * uParam = (PulseOutputwithTimerInterrupt *) userParam;
   uParam->eventCount++;
   uParam->ui.evtCountEditor->setText(QString("%1").arg(uParam->eventCount));
}

void PulseOutputwithTimerInterrupt::ButtonStartClicked()
{
    this->eventCount = 0;
    ui.evtCountEditor->setText(tr(""));

    double frequence = ui.userFreqEditor->text().toDouble();

    ErrorCode errorCode = Success;
    for (int i = timerPulseCtrl->getChannelStart(); i < timerPulseCtrl->getChannelStart() +
         timerPulseCtrl->getChannelCount(); i++)
    {
      errorCode = timerPulseCtrl->getChannels()->getItem(i).setFrequency(frequence);
    }
    CheckError(errorCode);
    errorCode = timerPulseCtrl->setEnabled(true);
    CheckError(errorCode);
    for (int i = timerPulseCtrl->getChannelStart(); i < timerPulseCtrl->getChannelStart() +
         timerPulseCtrl->getChannelCount(); i++)
   {
      ui.devFreqEditor->setText(QString("%1").arg(timerPulseCtrl->getChannels()->getItem(i).getFrequency()));
   }
    movie->start();

    ui.userFreqEditor->setEnabled(false);
    ui.btnStart->setEnabled(false);
    ui.btnStop->setEnabled(true);
    ui.btnConfig->setEnabled(false);
}

void PulseOutputwithTimerInterrupt::ButtonStopClicked()
{
    ErrorCode errorCode = Success;
    errorCode = timerPulseCtrl->setEnabled(false);
    CheckError(errorCode);

    movie->stop();

    ui.userFreqEditor->setEnabled(true);
    ui.btnStart->setEnabled(true);
    ui.btnStop->setEnabled(false);
    ui.btnConfig->setEnabled(true);
}

void PulseOutputwithTimerInterrupt::ButtonConfigureClicked()
{
    int dialogResult = configDialog->exec();
    if (dialogResult == QDialog::Accepted)
    {
        configure = configDialog->GetConfigureParameter();
        Initialize();
    }
}
