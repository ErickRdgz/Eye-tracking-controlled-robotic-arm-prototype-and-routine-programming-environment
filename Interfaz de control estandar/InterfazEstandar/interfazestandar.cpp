#include "interfazestandar.h"
#include "ui_interfazestandar.h"
#include "settingsform.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include "sequencecontrolform.h"


void InterfazEstandar::moveArm(std::vector<float> msg)
{
    arm->getArduino()->writeMessage(msg);
}

void InterfazEstandar::responseSetArmToHome()
{
    arm->goHome();
}

void InterfazEstandar::responseSetArmPosition(std::vector<float> msg)
{
    arm->setArticularPosition(msg);
}

InterfazEstandar::InterfazEstandar(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazEstandar)
{
    qRegisterMetaType<std::vector <float>>("std::vector <float>");
    ui->setupUi(this);

    ui->setupUi(this);

    arm             = new RevoluteArm;
    pointList       =new Lista<Point>();
    programList     = new Lista<Point>();
    CommandList     =new Lista<Command>();
    serialDataFinder=new QTimer(this);
    permanentMgs    =new QLabel(this);

    arm->setSequencer(this->CommandList,this);

    ui->Btn_Settings->setIcon(QIcon(QPixmap("./media/Config.png")));
    ui->statusbar-> addPermanentWidget(permanentMgs,0);
    initSettings();

    // Settings Button
    connect(ui->Btn_Settings,&QPushButton::clicked,[=](){
        if(arm->getArduino()->isConnected()){
            arm->disconnectArm();
            serialDataFinder->stop();
            ui->Btn_SerialConnect->setText("Conectar");
            permanentMgs->setText("Desconectado: "+arm->getArduino()->getPort());
        }
        ui->statusbar->showMessage("Modificando Configuraciones...");
        SettingsForm settingsForm;
        settingsForm.setModal(true);
        if (! settingsForm.exec()){
            ui->statusbar->showMessage("Configuracion cancelada! ",5000);
        }else{
            setSettings();
            ui->statusbar->showMessage("Configuraciones guardadas! ",5000);
        }
    });

        // Connect or Disconnect Serial Port
    connect(ui->Btn_SerialConnect,&QPushButton::clicked,[=](){
        if (!arm->getArduino()->isConnected()){
            if(arm->connectArm()){
//                arm->getArduino()->writeMessage(nextAngles);
                arm->goHome();
                connect(arm->getArduino(),&QSerialPort::readyRead,[=](){
                    serialDataFinder->start(10);
                });
//                arm->goHome();
                ui->Btn_SerialConnect->setText("Desconectar");
                permanentMgs->setText("Conectado: "+arm->getArduino()->getPort());
                ui->statusbar->showMessage("Conectado! ",1700);
                enablePointPage(true);
                enableProgramPage(true);
            }else{
                ui->statusbar->showMessage("Error, Verifica tus conexiones! ",5000);
            }
        }else{
            enablePointPage(false);
            enableProgramPage(false);
            arm->disconnectArm();
            serialDataFinder->stop();
            ui->Btn_SerialConnect->setText("Conectar");
            ui->statusbar->showMessage("Desconectado! ",1700);
            permanentMgs->setText("Desconectado: "+arm->getArduino()->getPort());
        }
    });



    enablePointPage(false);
    enableProgramPage(false);

    connect(serialDataFinder,&QTimer::timeout,[=](){
        newArduinoMessage();
    });

    initPointPage();
    initProgramPage();

    connect(arm->getSequencer(),SIGNAL(sendToSerial(std::vector <float>)) ,this,SLOT(moveArm(std::vector <float>)));

}

InterfazEstandar::~InterfazEstandar()
{
    delete ui;
}

void InterfazEstandar::initSettings()
{
    setSettings();

    try {
        arm->setArmToHome();
    } catch (ArmException &e) {
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setText("El home por defecto es invalido");
        alert.setInformativeText(e.what());
        alert.exec();

    }

    updateRectangularValues();
    updateAngularValues();

    ui->Slider_Gripper->setValue(arm->getGripper());
}

void InterfazEstandar::setSettings()
{
    QString aux;
    int auxInt;

    auxInt=SettingsForm::getSetting("Settings","BaudRate",QString::number(DEFAULT_BAUD_RATE)).toInt();
    aux=SettingsForm::getSetting("Settings","Port",DEFAULT_PORT);
    arm->setArduino(aux,auxInt);

    permanentMgs->setText("Desconectado: "+aux);

    aux=SettingsForm::getSetting("Settings","XHome",    QString::number(DEFAULT_X_HOME));
    arm->setHomeValue(Rectangular::X,aux.toInt());

    aux=SettingsForm::getSetting("Settings","YHome",    QString::number(DEFAULT_Y_HOME));
    arm->setHomeValue(Rectangular::Y,aux.toInt());

    aux=SettingsForm::getSetting("Settings","ZHome",    QString::number(DEFAULT_Z_HOME));
    arm->setHomeValue(Rectangular::Z,aux.toInt());

    aux=SettingsForm::getSetting("Settings","RowHome",   QString::number(DEFAULT_ROW_HOME));
    arm->setHomeValue(Rectangular::ROW,aux.toInt());

    aux=SettingsForm::getSetting("Settings","PitchHome", QString::number(DEFAULT_PITCH_HOME));
    arm->setHomeValue(Rectangular::PITCH,aux.toInt());

    aux=SettingsForm::getSetting("Settings","YawHome",   QString::number(DEFAULT_YAW_HOME));
    arm->setHomeValue(Rectangular::YAW,aux.toInt());

    aux=SettingsForm::getSetting("Settings","Gripper",   QString::number(DEFAULT_GRIPPER));
    arm->setHomeValue(Rectangular::GRIPPER,aux.toInt());

    aux=SettingsForm::getSetting("Settings","MaxSpeed",   QString::number(DEFAULT_GRIPPER));
    ui->SBox_Speed->setMaximum(aux.toInt());
    ui->SBox_Speed_2->setMaximum(aux.toInt());
}

void InterfazEstandar::newArduinoMessage()
{
    vector <int> dataIn;
//    qDebug()<<"timer active";
    if(arm->getArduino()->newMessage(dataIn,10)){
        QDebug print=qDebug();
        for(size_t i=0;i<dataIn.size();i++){
            print<<dataIn.at(i)<<"|";
        }
    }
    if(!arm->getArduino()->bytesAvailable())
        serialDataFinder->stop();
}

void InterfazEstandar::setArmInPoint(QTableWidget *table)
{
    vector<float> auxAngles={ZEROS};
  int index=table->currentRow();

  enablePointPage(false);
  Point aux;
  try{
    aux=pointList->at(index);
  }catch(...){
      QMessageBox alert;
      alert.setWindowTitle("Error");
      alert.setIcon(QMessageBox::Critical);
      alert.setText("Selecciona una posicion valida");
      alert.exec();
      enablePointPage(true);
      enableProgramPage(true);
      return;
  }

//    qDebug()<<Point::printPoint(aux);
  auxAngles.at(0)=aux.getAngular(0);
  auxAngles.at(1)=aux.getAngular(1);
  auxAngles.at(2)=aux.getAngular(2);
  auxAngles.at(3)=aux.getAngular(3);
  auxAngles.at(4)=aux.getAngular(4);
  auxAngles.at(5)=aux.getAngular(5);

  try {                  //new Position   speed(Deg/s)        movement
      arm->articularMovement(auxAngles,ui->SBox_Speed->value(),ui->CBox_Movement->currentIndex());
      updateRectangularValues();
      updateAngularValues();
  } catch (ArmException &e) {
      QMessageBox alert;
      alert.setIcon(QMessageBox::Critical);
      alert.setText("Error de ejecucion");
      alert.setInformativeText(e.what());
      alert.exec();
  }

  enablePointPage(true);
  enableProgramPage(true);
  ui->statusbar->showMessage("Movimiento exitoso ",5000);
}



