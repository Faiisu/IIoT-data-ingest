#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

struct ConfigureParameter 
{
    QString deviceName;
    int channelCount;
    int channelStart;
    ValueRange valueRange;
    double clockRatePerChan;
    int32 sectionLength;
    QString profilePath;
    QString hostName;

    //for trigger
    TriggerAction triggerAction;
    SignalDrop triggerSource;
    ActiveSignal triggerEdge;
    int delayCount;
    double triggerLevel;

    //for trigger1
    TriggerAction trigger1Action;
    SignalDrop trigger1Source;
    ActiveSignal trigger1Edge;
    int delayCount1;
    double trigger1Level;
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
    void ButtonBrowseClicked();
    void ButtonLoginClicked();
    void ComboBoxHostNameEditTextChanged(const QString &arg1);
};

#endif // CONFIGUREDIALOG_H
