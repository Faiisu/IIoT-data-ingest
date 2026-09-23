#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

struct ConfigureParameter 
{
    QString deviceName;
    int selectedPort;
    quint8 enabledChannels;
    quint8 pmValue;
    QString profilePath;
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
    void InitializePortState();
    void CheckError(ErrorCode errorCode);
    void EnableSettings(bool is_enable);

private:
    Ui::ConfigureDialog ui;
    ConfigureParameter configure;

    quint8 enableChannels;
   quint8 pmValue;

    QString strs[2];
    QButtonGroup* buttonGroup0;
    QButtonGroup* buttonGroup1;
    QPushButton* buttons[2][8];
    int buttonsTags[2][8];

private slots:
    void DeviceChanged(int);
    void cmbDIportChanged(int);
    void Buttons0Clicked(QAbstractButton *btn);
    void Buttons1Clicked(QAbstractButton *btn);
    void ButtonOKClicked();
    void ButtonCancelClicked();
    void ButtonBrowseClicked();
    void ButtonLoginClicked();
    void ComboBoxHostNameEditTextChanged(const QString &arg1);
};

#endif // CONFIGUREDIALOG_H
