#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include<QSerialPortInfo>

// #define DEFAULT_X_HOME     10
// #define DEFAULT_Y_HOME     10
// #define DEFAULT_Z_HOME     10
// #define DEFAULT_ROW_HOME   0
// #define DEFAULT_PITCH_HOME 0
// #define DEFAULT_YAW_HOME   0
// #define DEFAULT_MAX_SPEED  100
// #define DEFAULT_PORT       "COM10"
// #define DEFAULT_BAUD_RATE  115200
// #define DEFAULT_GRIPPER 50
// #define DEFAULT_EYE_D_TIME  2
// #define DEFAULT_DIR "./docs"
// #define DEFAULT_DETECTION_TIME "2"
// #define DEFAULT_ARM_STEP 0.5
// #define DEFAULT_CAM_IP "http://192.168.1.70:8080/video"


namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = nullptr);
    ~ConfigWindow();

    void setSavedSettings();
    void saveSettings();
    void updateDir();


private:
    Ui::ConfigWindow *ui;
};


void saveSetting(const QString &gpo,const QString &key,const QString &value);
QString getSetting(const QString &gpo,const QString &key,const QString defaultValue);


#endif // CONFIGWINDOW_H
