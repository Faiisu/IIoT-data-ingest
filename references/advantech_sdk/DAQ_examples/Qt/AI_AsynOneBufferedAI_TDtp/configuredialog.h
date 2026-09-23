#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QtWidgets/QDialog>
//#include <QCore>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

struct ConfigureParameter 
{
    QString deviceName;
    int channelCount;
    int channelStart;
    ValueRange valueRange;
    int32 sectionLength;
    double clockRatePerChan;
    QString profilePath;
    QString hostName;

    //for trigger
    int triggerIndex;
    TriggerAction triggerAction;
    SignalDrop triggerSource;
    ActiveSignal triggerEdge;
    int delayCount;
    double triggerLevel;
  
};

class ConfigureDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigureDialog(QWidget *parent = 0);
    ~ConfigureDialog();

    ConfigureParameter GetConfigureParameter(){return configure;}
    void RefreshConfigureParameter();

private:
    void InitailizationManagedEdgeList();
    void Initailization();
    void CheckError(ErrorCode errorCode);
    void EnableSettings(bool is_enable);

private:
    Ui::ConfigureDialog ui;
    ConfigureParameter configure;
    bool isTriggerSupported;
    bool isTrigger1Supported;

private slots:
    void DeviceChanged(int);
    void ButtonOKClicked();
    void ButtonCancelClicked();
    void TriggerSourceChanged(int);
    void TriggerIndexChanged(int index);
    void ButtonBrowseClicked();
    void ButtonLoginClicked();
    void ComboBoxHostNameEditTextChanged(const QString &arg1);
};

#endif // CONFIGUREDIALOG_H
