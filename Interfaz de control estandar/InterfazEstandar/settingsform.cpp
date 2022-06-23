#include "settingsform.h"
#include "ui_settingsform.h"
#include <QtDebug>
#include <QSettings>
#include <QString>
#include "constants.h"
#include<QSerialPortInfo>

SettingsForm::SettingsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsForm)
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

    connect(ui->buttonBox,&QDialogButtonBox::accepted,[=](){
     saveSettings();
    });
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::setSavedSettings()
{
    QString auxString;

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

}

void SettingsForm::saveSettings()
{
    saveSetting("Settings","Port",ui->CBox_Port->currentText());
    saveSetting("Settings","BaudRate",ui->CBox_BRate->currentText());
    saveSetting("Settings","XHome",QString::number(ui->SBox_XHome->value()));
    saveSetting("Settings","YHome",QString::number(ui->SBox_YHome->value()));
    saveSetting("Settings","ZHome",QString::number(ui->SBox_ZHome->value()));
    saveSetting("Settings","RowHome",QString::number(ui->SBox_RowHome->value()));
    saveSetting("Settings","PitchHome",QString::number(ui->SBox_PitchHome->value()));
    saveSetting("Settings","YawHome",QString::number(ui->SBox_YawHome->value()));
    saveSetting("Settings","MaxSpeed",QString::number(ui->SBox_Vmax->value()));

}

void SettingsForm::saveSetting(const QString &gpo, const QString &key, const QString &value)
{
    QSettings S;
    S.beginGroup(gpo);
    S.setValue(key,value);
    S.endGroup();
}

QString SettingsForm::getSetting(const QString &gpo, const QString &key, const QString defaultValue)
{
    QSettings S;
    S.beginGroup(gpo);
    return S.value(key,defaultValue).toString();
}


