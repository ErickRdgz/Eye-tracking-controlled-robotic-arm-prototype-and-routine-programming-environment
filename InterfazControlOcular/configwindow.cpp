#include "configwindow.h"
#include "ui_configwindow.h"
#include <QtDebug>
#include <QSettings>
#include <QString>
#include <QFileDialog>
#include "constants.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    foreach(const QSerialPortInfo &serial_Info,QSerialPortInfo::availablePorts()){
                ui->CBox_Port ->addItem(serial_Info.portName());
     }

    ui->CBox_BRate->addItem("9600");
    ui->CBox_BRate->addItem("19200");
    ui->CBox_BRate->addItem("38400");
    ui->CBox_BRate->addItem("57600");
    ui->CBox_BRate->addItem("115200");

    setSavedSettings();

    connect(ui->Btn_Dir,&QPushButton::clicked,[=](){
        updateDir();
    } );

    connect(ui->buttonBox,&QDialogButtonBox::accepted,[=](){
     saveSettings();
     accept();
    });
    connect(ui->buttonBox,&QDialogButtonBox::rejected,[=](){
     reject();
    });

}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}


void ConfigWindow::setSavedSettings()
{
    QString auxString;

    auxString=getSetting("Settings","Directory",    DEFAULT_DIR);
    ui->Dir_Label->setText(auxString);

    auxString=getSetting("Settings","DetectionTime",QString::number(EYE_COMMAND_TIMEOUT));
    ui->SBox_EDT->setValue(auxString.toFloat());

    auxString=getSetting("Settings","Port",DEFAULT_PORT);
    if(ui->CBox_Port->findText(auxString)>=0){
        ui->CBox_Port->setCurrentIndex(ui->CBox_Port->findText(auxString));
    }else{
        ui->CBox_Port ->insertItem(0,auxString);
        ui->CBox_Port->setCurrentIndex(0);
    }

    auxString=getSetting("Settings","BaudRate",QString::number(DEFAULT_BAUD_RATE) );
    if(ui->CBox_BRate->findText(auxString)>=0){
        ui->CBox_BRate->setCurrentIndex(ui->CBox_BRate->findText(auxString));
    }else{
        ui->CBox_BRate ->insertItem(0,auxString);
        ui->CBox_BRate->setCurrentIndex(0);
    }

    auxString=getSetting("Settings","XHome",    QString::number(DEFAULT_X_HOME));
    ui->SBox_XHome->setValue(auxString.toInt());

    auxString=getSetting("Settings","YHome",    QString::number(DEFAULT_Y_HOME));
    ui->SBox_YHome->setValue(auxString.toInt());

    auxString=getSetting("Settings","ZHome",    QString::number(DEFAULT_Z_HOME));
    ui->SBox_ZHome->setValue(auxString.toInt());

    auxString=getSetting("Settings","RowHome",  QString::number(DEFAULT_ROW_HOME));
    ui->SBox_RowHome->setValue(auxString.toInt());

    auxString=getSetting("Settings","PitchHome",QString::number(DEFAULT_PITCH_HOME));
    ui->SBox_PitchHome->setValue(auxString.toInt());

    auxString=getSetting("Settings","YawHome",  QString::number(DEFAULT_YAW_HOME));
    ui->SBox_YawHome->setValue(auxString.toInt());

    auxString=getSetting("Settings","MaxSpeed",  QString::number(DEFAULT_MAX_SPEED));
    ui->SBox_Vmax->setValue(auxString.toInt());

    auxString=getSetting("Settings","ArmStep",   QString::number(DEFAULT_ARM_STEP));
    ui->SBox_ArmStep->setValue(auxString.toFloat());

    auxString=getSetting("Settings","IpCam",   DEFAULT_CAM_IP);
    ui->IPCam->setText(auxString);

    auxString=getSetting("Settings","UpperLimit",   QString::number(UPPER_LIMIT));
    ui->SBox_UpperLimit ->setValue(auxString.toFloat());
    auxString=getSetting("Settings","LeftLimit",   QString::number(LEFT_LIMIT));
    ui->SBox_LeftLimit ->setValue(auxString.toFloat());
    auxString=getSetting("Settings","RightLimit",   QString::number(RIGHT_LIMIT));
    ui->SBox_RightLimit ->setValue(auxString.toFloat());


}

void ConfigWindow::saveSettings()
{
    saveSetting("Settings","DetectionTime",QString::number(ui->SBox_EDT->value()));
    saveSetting("Settings","Directory",ui->Dir_Label->text());
    saveSetting("Settings","Port",ui->CBox_Port->currentText());
    saveSetting("Settings","BaudRate",ui->CBox_BRate->currentText());
    saveSetting("Settings","XHome",QString::number(ui->SBox_XHome->value()));
    saveSetting("Settings","YHome",QString::number(ui->SBox_YHome->value()));
    saveSetting("Settings","ZHome",QString::number(ui->SBox_ZHome->value()));
    saveSetting("Settings","RowHome",QString::number(ui->SBox_RowHome->value()));
    saveSetting("Settings","PitchHome",QString::number(ui->SBox_PitchHome->value()));
    saveSetting("Settings","YawHome",QString::number(ui->SBox_YawHome->value()));
    saveSetting("Settings","MaxSpeed",QString::number(ui->SBox_Vmax->value()));
    saveSetting("Settings","ArmStep",QString::number(ui->SBox_ArmStep->value()));
    saveSetting("Settings","IpCam",ui->IPCam->text());

    saveSetting("Settings","UpperLimit",QString::number(ui->SBox_UpperLimit ->value()));
    saveSetting("Settings","LeftLimit",QString::number(ui->SBox_LeftLimit ->value()));
    saveSetting("Settings","RightLimit",QString::number(ui->SBox_RightLimit ->value()));
}

void ConfigWindow::updateDir()
{
    QString path=QFileDialog::getExistingDirectory(this,"Directorio de trayectorias",ui->Dir_Label->text());
    if(path=="")
        return;
    ui->Dir_Label->setText(path);
}


void saveSetting(const QString &gpo, const QString &key, const QString &value)
{
    QSettings S;
    S.beginGroup(gpo);
    S.setValue(key,value);
    S.endGroup();
}

QString getSetting(const QString &gpo, const QString &key,const QString defaultValue)
{
    QSettings S;
    S.beginGroup(gpo);
    return S.value(key,defaultValue).toString();
}
