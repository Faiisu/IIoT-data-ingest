#ifndef STREAMINGAO_H
#define STREAMINGAO_H

#include <QDialog>
#include "ui_streamingao.h"
#include "configuredialog.h"
#include "../common/WaveformGenerator.h"

class StreamingAO : public QDialog
{
    Q_OBJECT
public:
    StreamingAO(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~StreamingAO();
    void Initialize();
    void ConfigureDevice();
    void CheckError(ErrorCode errorCode);
    void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
    void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
    void ConfigurePanel();
    void InitialButtons();

    static void BDAQCALL OnStoppedEvent(void *, BfdAoEventArgs *, void * userParam);
    static void BDAQCALL OnUnderrunEvent(void *, BfdAoEventArgs *, void * userParam);
signals:
     void stophandle();
     void underrunhandle();

private:
    Ui::StreamingAOClass ui;
    ConfigureDialog* configDialog;
    ConfigureParameter configure;
    BufferedAoCtrl* bfdAoCtrl;

    double* dataScaled;
    WaveformParameter m_waveParam[2];
    WaveformGenerator *waveformGenerator;
    bool m_waveSeled[2];
    QPushButton* buttons[6];

    QString strs[6];
    QButtonGroup* buttonGroup1;

private slots:
    void ButtonConfigureClicked();
    void ButtonStartClicked();
    void WaveButtonClicked(QAbstractButton *btn);
    void stopped();
    void underrunned();

};

#endif // STREAMINGAO_H
