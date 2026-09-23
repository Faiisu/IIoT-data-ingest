#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

#define BUF_SIZE_MAX   2048
struct ConfigureParameter 
{
    QString deviceName;
    uint32  slnIdx;
    QString slnName;
    QString hostName;
};

class ConfigureDialog : public QDialog
{
Q_OBJECT

public:
    ConfigureDialog(QWidget *parent = 0);
    ~ConfigureDialog();

    ConfigureParameter GetConfigureParameter(){return configure;}

private:
    void InitailizationManagedEdgeList();
    void Initailization();
    void CheckError(ErrorCode errorCode);
    void EnableSettings(bool is_enable);

private:
    Ui::ConfigureDialog ui;
    ConfigureParameter configure;

private slots:
    void DeviceChanged();
    void ButtonOKClicked();
    void ButtonCancelClicked();
    void ButtonLoginClicked();
    void ComboBoxHostNameEditTextChanged(const QString &arg1);
};

#endif // CONFIGUREDIALOG_H
