#include "interfazocular.h"
#include "ui_interfazocular.h"
#include <QDir>
#include <QDebug>
#include "configwindow.h"
#include <QMessageBox>
#include <QIcon>


InterfazOcular::InterfazOcular(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazOcular)
{
    qRegisterMetaType<std::vector <float>>("std::vector <float>");
    ui->setupUi(this);

    LeftSound=new QSound("./media/click.wav");
    RightSound=new QSound("./media/click.wav");
    UpSound=new QSound("./media/button.wav");
    CommandList=new Lista<Command>();

    arm=new RevoluteArm;
    arm->setSequencer(this->CommandList,this);

    eyeTrackingVideo=new EyeTracking(this,"0");
    eyeTrackingVideo->start(QThread::HighestPriority);

    initSettings();
    initStyleObjects();
    loadMenuList();

    armVideo =new ArmVideo(this,getSetting("Settings","IpCam",DEFAULT_CAM_IP));
    armVideo->start();

    serialConection(true);


    connect(ui->Btn_L,&QPushButton::clicked,this,[=](){
        LeftSound->play();
        if (this->menuPosition>0 ){
            menuPosition--;
            updateMenu();
        }
    } );
    connect(ui->Btn_Up,&QPushButton::clicked,this,[=](){
        UpSound->play();
            ExecuteSelection();
    } );
    connect(ui->Btn_R,&QPushButton::clicked,this,[=](){
        RightSound->play();
        if (this->menuPosition<Options.size()-1 ){
            menuPosition++;
            updateMenu();
        }
    } );


    connect(eyeTrackingVideo,&EyeTracking::moveUp ,this,[&](){
         UpSound->play();
         ExecuteSelection();
    });
    connect(eyeTrackingVideo,&EyeTracking::moveLeft,this,[&](){
        LeftSound->play();
        if (this->menuPosition>0 ){
            menuPosition--;
            updateMenu();
        }
    });
    connect(eyeTrackingVideo,&EyeTracking::moveRight,this,[&](){
        RightSound->play();
        if (this->menuPosition<Options.size()-1 ){
            menuPosition++;
            updateMenu();
        }
    });



    connect(armVideo,&ArmVideo::newVideoFrame,this,[&](){
       ui->Box_armVideo->setPixmap(armVideo->getVideoPixMap().scaled(720,480));
    });

    connect(eyeTrackingVideo,&EyeTracking::newVideoFrame ,this,[&](){
       ui->Box_faceVideo->setPixmap(eyeTrackingVideo->getVideoPixMap().scaled(300,200));
    });


    // Settings Button
    connect(ui->Btn_Settings,&QPushButton::clicked,[=](){
        serialConection(false);

        ui->statusbar->showMessage("Modificando Configuraciones...");
        ConfigWindow settingsForm;
        settingsForm.setModal(true);
        if (settingsForm.exec()){
        setSettings();
        ui->statusbar->showMessage("Configuraciones guardadas! ",5000);
        }else{
            ui->statusbar->showMessage("Configuracion cancelada! ",5000);
        }

        serialConection(true);
    });



    connect(arm->getSequencer(),SIGNAL(sendToSerial(std::vector <float>)) ,this,SLOT(moveArm(std::vector <float>)));

    connect(this->arm->getSequencer(),&Sequencer::finished,[=](){
        RunningSequence=false;
        ui->statusbar->showMessage("Ejecutando programa... ",1700);
        updateDisplayedValues();
         for(size_t i=0; i<nextRecPosition.size();i++){
             nextRecPosition.at(i)=arm->getRectangularValue(i);
         }
    });
}

InterfazOcular::~InterfazOcular()
{
    eyeTrackingVideo->terminate();
    armVideo->terminate();
    delete ui;
}

void InterfazOcular::ExecuteSelection()
{
    if (RunningSequence){
        return;
    }

    switch (menuPosition) {
    case UP :
        singleMovement( Rectangular::Z, Direction::POSITIVE);
        break;
    case DOWN:
        singleMovement( Rectangular::Z, Direction::NEGATIVE);
        break;
    case RIGHT:
        singleMovement( Rectangular::Y, Direction::POSITIVE);
        break;
    case LEFT:
        singleMovement( Rectangular::Y, Direction::NEGATIVE);
        break;
    case FORWARD:
        singleMovement( Rectangular::X, Direction::POSITIVE);
        break;
    case BACKWARD:
        singleMovement( Rectangular::X, Direction::NEGATIVE);
        break;
    case OPEN_GRIPPER:
        gripperVal-=DEFAULT_GRIPPER_STEP;
        if (gripperVal<=MIN_GRIPPER_VAL)
            gripperVal=MIN_GRIPPER_VAL;
        arm->setGripper(gripperVal);
        break;
    case CLOSE_GRIPPER:
        gripperVal+=DEFAULT_GRIPPER_STEP;
        if (gripperVal>=MAX_GRIPPER_VAL)
            gripperVal=MAX_GRIPPER_VAL;
        arm->setGripper(gripperVal);
        return;
        break;
    default:
        ExecuteFile();
        return;
        break;
    }
}

void InterfazOcular::ExecuteFile()
{
    if( menuPosition<=MAX_BASIC_OPTION_NUMBER|| menuPosition >= Options.size())
        return;
    QString fileName=filesDirectory->path()+"/"+Options.at(menuPosition);

    qDebug()<<fileName;

    QFile file(fileName);

    if(!file.exists()){
        ui->statusbar->showMessage("Error al abrir archivo...",2000);
        return;
    }
    if(!file.open(QIODevice::ReadOnly)){
        ui->statusbar->showMessage("Error al abrir archivo...",2000);
        return;
    }


    CommandList->clear();
    Command auxCommand=Command();

     QTextStream in(&file);

     while(!in.atEnd()) {
         QString line = in.readLine();
         QStringList fields = line.split(",");

         auxCommand.setValues( fields.at(0).toInt(),
                               fields.at(1).toInt(),
                               fields.at(2).toInt(),
                               fields.at(3).toInt(),
                               fields.at(4).toInt(),
                               fields.at(5).toInt(),
                               fields.at(6).toInt(),
                               fields.at(7).toInt() );

         CommandList->push_back(auxCommand);
     }
    file.close();

    CommandList->PrintList(Command::printCommand);

    arm->getSequencer()->setExecutionCounter(1);
    this->arm->getSequencer()->start(QThread::TimeCriticalPriority);
    RunningSequence=true;
}

void InterfazOcular::initSettings()
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

    nextRecPosition.at(Rectangular::X)    =arm->getRectangularValue(Rectangular::X)    ;
    nextRecPosition.at(Rectangular::Y)    =arm->getRectangularValue(Rectangular::Y)    ;
    nextRecPosition.at(Rectangular::Z)    =arm->getRectangularValue(Rectangular::Z)    ;
    nextRecPosition.at(Rectangular::ROW)  =arm->getRectangularValue(Rectangular::ROW)  ;
    nextRecPosition.at(Rectangular::PITCH)=arm->getRectangularValue(Rectangular::PITCH);
    nextRecPosition.at(Rectangular::YAW)  =arm->getRectangularValue(Rectangular::YAW)  ;


    updateDisplayedValues();
}

void InterfazOcular::setSettings()
{
    QString aux;
    int auxInt;

    aux=getSetting("Settings","Directory",    DEFAULT_DIR);
    filesDirectory =new QDir;
    filesDirectory->setPath(aux);

    auxInt=getSetting("Settings","BaudRate",QString::number(DEFAULT_BAUD_RATE)).toInt();
    aux=getSetting("Settings","Port",DEFAULT_PORT);
    arm->setArduino(aux,auxInt);

    aux=getSetting("Settings","XHome",    QString::number(DEFAULT_X_HOME));
    arm->setHomeValue(Rectangular::X,aux.toInt());

    aux=getSetting("Settings","YHome",    QString::number(DEFAULT_Y_HOME));
    arm->setHomeValue(Rectangular::Y,aux.toInt());

    aux=getSetting("Settings","ZHome",    QString::number(DEFAULT_Z_HOME));
    arm->setHomeValue(Rectangular::Z,aux.toInt());

    aux=getSetting("Settings","RowHome",   QString::number(DEFAULT_ROW_HOME));
    arm->setHomeValue(Rectangular::ROW,aux.toInt());

    aux=getSetting("Settings","PitchHome", QString::number(DEFAULT_PITCH_HOME));
    arm->setHomeValue(Rectangular::PITCH,aux.toInt());

    aux=getSetting("Settings","YawHome",   QString::number(DEFAULT_YAW_HOME));
    arm->setHomeValue(Rectangular::YAW,aux.toInt());

    aux=getSetting("Settings","Gripper",   QString::number(DEFAULT_GRIPPER));
    arm->setHomeValue(Rectangular::GRIPPER,aux.toInt());

    aux=getSetting("Settings","MaxSpeed",   QString::number(DEFAULT_MAX_SPEED));
    armSpeed=aux.toInt();

    aux=getSetting("Settings","ArmStep",   QString::number(DEFAULT_ARM_STEP));
    armStep=aux.toFloat();

    aux=getSetting("Settings","DetectionTime",QString::number(EYE_COMMAND_TIMEOUT));
    eyeTrackingVideo->setCommandTime(aux.toFloat());
    aux=getSetting("Settings","UpperLimit", QString::number(UPPER_LIMIT));
    eyeTrackingVideo->setUpperLimit (aux.toFloat());
    aux=getSetting("Settings","LeftLimit",  QString::number(LEFT_LIMIT ));
    eyeTrackingVideo->setLeftLimit  (aux.toFloat());
    aux=getSetting("Settings","RightLimit", QString::number(RIGHT_LIMIT));
    eyeTrackingVideo->setRightLimit (aux.toFloat());
}

bool InterfazOcular::serialConection(bool status)
{
    if (status){
        if (arm->getArduino()->isConnected())
            return true;
        else{
            if(arm->connectArm()){
                arm->goHome();
                ui->statusbar->showMessage("Conectado! ",1700);
                return true;
            }else{
                ui->statusbar->showMessage("Error, Verifica tus conexiones! ",5000);
                return false;
            }
        }

    }else{
        if (!arm->getArduino()->isConnected())
            return true;
        else{
            if(arm->disconnectArm()){
                return true;
            }else{
                return  false;
            }
        }
    }
}

void InterfazOcular::singleMovement(int axis, direction_t direction)
{
    float aux = nextRecPosition.at(axis);

    if (direction==Direction::POSITIVE){
        nextRecPosition.at(axis)+=armStep;
    }else if (direction==Direction::NEGATIVE){
        nextRecPosition.at(axis)-=armStep;
    }

    try {
        arm->rectangularMovement(nextRecPosition,armSpeed,DEFAULT_MOVEMENT);
        updateDisplayedValues();
        RunningSequence=true;
        ui->statusbar->showMessage("Ejecutando programa...! ",1000);
    } catch (...) {
        nextRecPosition.at(axis)=aux;
        updateDisplayedValues();
        ui->statusbar->showMessage("Movimiento invalido ",5000);
    }

    return;
}
void InterfazOcular::moveArm(std::vector<float> msg)
{
    arm->getArduino()->writeMessage(msg);
    qDebug()<<msg;
}

void InterfazOcular::updateDisplayedValues()
{
    ui->in_X     ->setText(QString::number(arm->getRectangularValue(Rectangular::X)    ));
    ui->in_Y     ->setText(QString::number(arm->getRectangularValue(Rectangular::Y)    ));
    ui->in_Z     ->setText(QString::number(arm->getRectangularValue(Rectangular::Z)    ));
    ui->in_Roll  ->setText(QString::number(arm->getRectangularValue(Rectangular::ROW)  ));
    ui->in_Pitch ->setText(QString::number(arm->getRectangularValue(Rectangular::PITCH)));
    ui->in_Yaw   ->setText(QString::number(arm->getRectangularValue(Rectangular::YAW)  ));
}

void InterfazOcular::loadMenuList()
{
    QStringList fileNames;
    fileNames =filesDirectory->entryList(QStringList()<<"*.arm.cmmd",QDir::Files);

    Options.append(TEXT_UP            );
    Options.append(TEXT_DOWN          );
    Options.append(TEXT_RIGHT         );
    Options.append(TEXT_LEFT          );
    Options.append(TEXT_FORWARD       );
    Options.append(TEXT_BACKWARD      );
    Options.append(TEXT_OPEN_GRIPPER  );
    Options.append(TEXT_CLOSE_GRIPPER );

    foreach(QString i, fileNames){
        Options.append( i );
    }

    updateMenu();
}

void InterfazOcular::updateMenu()
{
    if(Options.at(menuPosition).size()>13){
        ui->Btn_Up->setText(" "+Options.at(menuPosition));
        ui->Btn_Up->setStyleSheet("background-color: rgb(210, 255, 240);   font: 75 18pt 'Arial Narrow'; text-align:left ;");
    }
    else {
        ui->Btn_Up->setText(Options.at(menuPosition));
        ui->Btn_Up->setStyleSheet("background-color: rgb(210, 255, 240);   font: 75 18pt 'Arial Narrow'; text-align:center ;");
    }


    if (menuPosition==0){
        ui->Btn_L->hide();
        ClearOptionStyle(ui->Option_Left1);
        ClearOptionStyle(ui->Option_Left2);
    }else{
        ui->Btn_L->show();
        if (menuPosition-1<0){
            ClearOptionStyle(ui->Option_Left1);
        }else{
            ui->Option_Left1->setText(Options.at(menuPosition-1));
            NormalOptionStyle(ui->Option_Left1);
        }
        if (menuPosition-2<0){
            ClearOptionStyle(ui->Option_Left2);
        }else{
            ui->Option_Left2->setText(Options.at(menuPosition-2));
            NormalOptionStyle(ui->Option_Left2);
        }
    }

    int upperLimit=Options.size()-1;
    if (menuPosition==upperLimit){
        ui->Btn_R->hide();
        ClearOptionStyle(ui->Option_Right1);
        ClearOptionStyle(ui->Option_Right2);
    }else{
        ui->Btn_R->show();
        if (menuPosition+1>upperLimit){
            ClearOptionStyle(ui->Option_Right1);
        }else{
            ui->Option_Right1->setText(Options.at(menuPosition+1));
            NormalOptionStyle(ui->Option_Right1);
        }
        if (menuPosition+2>upperLimit){
            ClearOptionStyle(ui->Option_Right2);
        }else{
            ui->Option_Right2->setText(Options.at(menuPosition+2));
            NormalOptionStyle(ui->Option_Right2);
        }
    }
}

void InterfazOcular::initStyleObjects()
{
    NormalOptionStyle(ui->Option_Left1);
    NormalOptionStyle(ui->Option_Left2);
    NormalOptionStyle(ui->Option_Right1);
    NormalOptionStyle(ui->Option_Right2);

    ui->Btn_R->setText("");
    ui->Btn_R->setIcon(QIcon(QPixmap("./media/R_Arrow.png")));
    ui->Btn_R->setIconSize(QSize(30,70));

    ui->Btn_Up->setDefault(true);
    ui->Btn_Up->setAutoFillBackground(true);
    ui->Btn_Up->setStyleSheet("background-color: rgb(210, 255, 240);   font: 75 18pt 'Arial Narrow'; text-align:center ;");

    ui->Btn_L->setText("");
    ui->Btn_L->setIcon(QIcon(QPixmap("./media/L_Arrow.png")));
    ui->Btn_L->setIconSize(QSize(30,70));

    ui->Btn_Settings ->setText("");
    ui->Btn_Settings->setIcon(QIcon(QPixmap("./media/Config.png")));
    ui->Btn_Settings->setIconSize(QSize(20,20));

    ui->in_X->setEnabled(false);
    ui->in_Y->setEnabled(false);
    ui->in_Z->setEnabled(false);
    ui->in_Roll->setEnabled(false);
    ui->in_Pitch->setEnabled(false);
    ui->in_Yaw->setEnabled(false);
}

void InterfazOcular::ClearOptionStyle(QLabel *label)
{
    label->setText("");
    label->setFrameShape(QFrame::NoFrame);
    label->setAutoFillBackground(true);// # This is important!!
    label->setStyleSheet("");
}

void InterfazOcular::NormalOptionStyle(QLabel *label)
{
    label->setFrameShape(QFrame::Box );
    label->setAutoFillBackground(true);// # This is important!!
    label->setStyleSheet("background-color: rgba(210, 255, 240,60); font: 15pt 'Arial Narrow';");

    if(label->text().size()>14) label->setAlignment(Qt::AlignLeft );
    else label->setAlignment(Qt::AlignCenter );
}

