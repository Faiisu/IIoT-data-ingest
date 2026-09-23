#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <qwidget.h>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

struct ConfigureParameter 
{
    QString deviceName;
    int channelCount;
    int channelStart;
    ValueRange valueRange;
    int32 clockRatePerChan;
    int32 sectionLength;
    QString profilePath;
    QString hostName;
};

class ConfigureDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigureDialog(QDialog *parent = 0);
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

private slots:
    void DeviceChanged(int);
    void ButtonOKClicked();
    void ButtonCancelClicked();
    void ButtonBrowseClicked();
    void ButtonLoginClicked();
    void ComboBoxHostNameEditTextChanged(const QString &arg1);
};

#endif // CONFIGUREDIALOG_H
