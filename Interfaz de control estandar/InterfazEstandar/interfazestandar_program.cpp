#include "interfazestandar.h"
#include "ui_interfazestandar.h"
#include "settingsform.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include "sequencecontrolform.h"



void InterfazEstandar::initProgramPage()
{
    ui->CBox_Movement_2->addItem("Punto-Punto");
    ui->CBox_Movement_2->addItem("Coordinado");

    ui->PointList_2->setColumnCount(7);
    ui->PointList_2->setHorizontalHeaderLabels({"Punto","X","Y","Z","ROW","PITCH","YAW"});
    ui->PointList_2->setLineWidth(435);
    ui->PointList_2->setColumnWidth(0,110);
    ui->PointList_2->setColumnWidth(1,50);
    ui->PointList_2->setColumnWidth(2,50);
    ui->PointList_2->setColumnWidth(3,50);
    ui->PointList_2->setColumnWidth(4,50);
    ui->PointList_2->setColumnWidth(5,50);
    ui->PointList_2->setColumnWidth(6,50);
    ui->PointList_2->insertRow(0);

    ui->SequenceList->setColumnCount(3);
    ui->SequenceList->setHorizontalHeaderLabels({"Orden","1","2"});
    ui->SequenceList->setLineWidth(250);
    ui->SequenceList->setColumnWidth(0,110);
    ui->SequenceList->setColumnWidth(1,60);
    ui->SequenceList->setColumnWidth(2,50);
    ui->SequenceList->insertRow(0);

    // Slots
                // file management
    connect(ui->Btn_LoadPointList_2,&QPushButton::clicked,this,&InterfazEstandar::loadPointList);
    connect(ui->Btn_SaveSequenceList,&QPushButton::clicked,this,&InterfazEstandar::saveProgramList);
    connect(ui->Btn_LoadSequenceList,&QPushButton::clicked,this,&InterfazEstandar::loadProgramList);

                //Execution controls
    connect(ui->Btn_CommandCtrl,&QPushButton::clicked,this,&InterfazEstandar::generateCommands);

                // add items to Sequence list
    connect(ui->Btn_pushPointToSequence,&QPushButton::clicked,this,  &InterfazEstandar::pushPointToProgramList);
    connect(ui->Btn_pushDelayToSequence,&QPushButton::clicked,this,  &InterfazEstandar::pushDelayToProgramList);
    connect(ui->Btn_pushGripperToSequence,&QPushButton::clicked,this,&InterfazEstandar::pushGripperToProgramList);
    connect(ui->Btn_GoPoint_2,&QPushButton::clicked,[=](){                      setArmInPoint(ui->PointList_2);    });
    connect(ui->Btn_RemoveFromSequence,&QPushButton::clicked,this,   &InterfazEstandar::removeFromProgramList);
    connect(ui->Btn_ClearSequenceList,&QPushButton::clicked,this,    &InterfazEstandar::clearProgramList);
    connect(ui->Btn_MoveUp,&QPushButton::clicked,this,&InterfazEstandar::moveProgramItemUp);
    connect(ui->Btn_MoveDown,&QPushButton::clicked,this,&InterfazEstandar::moveProgramItemDown);

}

void InterfazEstandar::enableProgramPage(bool enable)
{
    ui->Btn_LoadPointList_2->setEnabled(enable);
    ui->Btn_CommandCtrl->setEnabled(enable);
    ui->Btn_LoadSequenceList->setEnabled(enable);
    ui->Btn_SaveSequenceList->setEnabled(enable);

    ui->PointList_2->setEnabled(enable);
    ui->PointList_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SequenceList ->setEnabled(enable);
    ui->SequenceList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->SBox_Speed_2->setEnabled(enable);
    ui->CBox_Movement_2->setEnabled(enable);
    ui->Btn_GoPoint_2->setEnabled(enable);
    ui->Btn_pushPointToSequence->setEnabled(enable);
    ui->Btn_pushGripperToSequence->setEnabled(enable);
    ui->Btn_pushDelayToSequence->setEnabled(enable);
    ui->in_Gripper_2->setEnabled(enable);
    ui->in_Delay->setEnabled(enable);
    ui->Btn_MoveUp->setEnabled(enable);
    ui->Btn_MoveDown->setEnabled(enable);
    ui->Btn_RemoveFromSequence->setEnabled(enable);
    ui->Btn_ClearSequenceList->setEnabled(enable);
}

void InterfazEstandar::saveProgramList()
{
    QDir dir;
    if(this->filesPath.absolutePath()=="")          //if no directory opened, get aplication path
        dir.currentPath();
    else dir.setPath(this->filesPath.absolutePath());

    QString auxname="sequenceList";
    if(this->pointsFileName!="")                //get the name of the current point file. if no file is open, set default name
        auxname=this->pointsFileName;

    QString path=QFileDialog::getSaveFileName(this, "Guardar",dir.absolutePath()+"/"+auxname,tr("SequenceFiles(*.arm.pgm)"));

    if(path=="") return;



    dir.setPath(path);
    QString fullFileName=dir.dirName();             //get file name with extension
    QStringList auxList =fullFileName.split(".");
    if(auxList.size()>3)
          fullFileName=auxList.at(0)+"."+auxList.at(1)+"."+auxList.at(2);   //fix extension (the dialog has a bug and adds extension twice)
    QString fileName=auxList.at(0);                         //get the file name without extension

    dir.cdUp();                                     //move dir up to remove filename.
    path=dir.absolutePath()+"/"+fullFileName;       // add the corrected file name to path


    updateProgramListFile(path);


    ui->statusbar->showMessage("Guardado ",4000);

    this->filesPath.setPath(dir.absolutePath());
    this->programFileName=fileName;
}

void InterfazEstandar::loadProgramList()
{
    QDir dir;
    if(this->filesPath.absolutePath()=="")
        dir.currentPath();
    else dir.setPath(this->filesPath.absolutePath());

    QString path=QFileDialog::getOpenFileName(this, "Abrir", dir.absolutePath(),tr("SequenceFiles(*.arm.pgm)"));
    QFile file(path);

    if (path=="") return;  //the process has been canceled

    ui->statusbar->showMessage("Abriendo...");
    if(!file.exists()){
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setText("Error de lectura");
        alert.setInformativeText("El archivo no ha sido encontrado");
        alert.exec();
        ui->statusbar->showMessage("Error al abrir los archivos",2500);
        return;
    }

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setText("Error de lectura");
        alert.setInformativeText("El archivo no se ha podido abrir");
        alert.exec();
        ui->statusbar->showMessage("Error al abrir los archivos",2500);
        return;
    }
    clearProgramList();
    programList->clear();

    Point auxitem=Point();
    QTextStream in(&file);
    int index=0;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");


        auxitem.setCtrl (fields.at(0).toInt());
        auxitem.setSpeed(fields.at(1).toInt());
        auxitem.setName(fields.at(2));

        auxitem.setRectangular( fields.at(3).toFloat(),
                                fields.at(4).toFloat(),
                                fields.at(5).toFloat(),
                                fields.at(6).toFloat(),
                                fields.at(7).toFloat(),
                                fields.at(8).toFloat());
        auxitem.setAngular( fields.at(9).toFloat(),
                            fields.at(10).toFloat(),
                            fields.at(11).toFloat(),
                            fields.at(12).toFloat(),
                            fields.at(13).toFloat(),
                            fields.at(14).toFloat());


        programList->push_back(auxitem);
        setToProgramTable(index,auxitem);
        index++;

    //    qDebug()<<pointList->getSize();
//        pointList->PrintList(&Point::printPoint);
//        qDebug()<<"#####################################";

    }
    file.close();
    ui->statusbar->showMessage("Archivo abierto exitosamente",4000);



    dir.setPath(path);
    QString fileName=dir.dirName();
    QStringList auxList =fileName.split(".");
    fileName=auxList.at(0);
    this->programFileName=fileName;

    dir.cdUp();
    this->filesPath.setPath(dir.absolutePath());
}

void InterfazEstandar::generateCommands()
{
    if(programList->getSize()==0){
        ui->statusbar->showMessage("Lista  de secuencia vacia!! ",5000);
//        QMessageBox alert;
//        alert.setIcon(QMessageBox::Critical);
//        alert.setText("Secuencia no encontrada");
////        alert.setInformativeText("   ");
//        alert.exec();
        return;
    }

    if(this->programFileName==""){
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setWindowTitle("Guarda el programa!!");
//        alert.setText("Guarda el programa!!");
        alert.setInformativeText("Para poder ejecutar el programa\ndebe guardarlo antes");
        alert.exec();
        return;
    }

    updateProgramListFile(this->filesPath.absolutePath()+"/"+this->programFileName+".arm.pgm");

    arm->generateCommands(programList,CommandList);

    saveCommandList(this->filesPath.absolutePath()+"/"+this->programFileName+".arm.cmmd");


    SequenceControlForm SC(CommandList,programList,arm,this);
    SC.setModal(true);
    SC.exec();
}

void InterfazEstandar::saveCommandList(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setText("Error de lectura");
        alert.setInformativeText("El archivo no se ha podido generar");
        alert.exec();
        return;
    }

    QTextStream out(&file);
    ui->statusbar->showMessage("Guardando... ");
    Command auxitem;

    for(int i=0;i<CommandList->getSize();i++){
        auxitem=CommandList->at(i);

        out<<auxitem.getCtrl()<<',';
        for(int j=0;j<7;j++){
            out<<auxitem.getAngle(j);
            if(j<6) out<<',';
        }
        out<<'\n';

    }
    file.close();
}

void InterfazEstandar::pushPointToProgramList()
{
    int movement,speed,pointIndex;
    QString movementText,pointName;

    movementText=ui->CBox_Movement_2->currentText();
    if (movementText=="Punto-Punto")
        movement=CommandCodes::COMMAND_PtP;

    else if(movementText=="Coordinado")
        movement=CommandCodes::COMMAND_COORDINATED;

    speed=ui->SBox_Speed_2->value();

    pointIndex=ui->PointList_2->currentRow();
    if (pointIndex<0){
        ui->statusbar->showMessage("Selecciona un punto valido ",4000);
        return;
    }

    pointName=ui->PointList_2->item(pointIndex,PointListTitles::NAME)->text();

    //getting point data from pointlist  to construct an Sequence item and push it to sequense list
    Point auxPoint=Point();
    Point auxSequenceItem=Point();
    auxPoint=pointList->getItem(pointName,&Point::sameName);    //search by name the point in pointlist

    auxSequenceItem.setAll(auxPoint);
    auxSequenceItem.setCtrl(movement);
    auxSequenceItem.setSpeed(speed);


    programList->push_back(auxSequenceItem);
//    SequenceList->PrintList(&Point::printPoint);

    int rowIndex=ui->SequenceList->rowCount()-1;
    ui->SequenceList->insertRow(rowIndex+1);

    ui->SequenceList->setItem(rowIndex,0,new QTableWidgetItem(movementText));
    ui->SequenceList->setItem(rowIndex,1,new QTableWidgetItem(pointName));
    ui->SequenceList->setItem(rowIndex,2,new QTableWidgetItem(QString::number(speed)));
    ui->statusbar->showMessage("Agregado a lista ",3000);
}

void InterfazEstandar::pushGripperToProgramList()
{
    Point auxSequenceItem=Point();
    auxSequenceItem.setAsCommand(CommandCodes::COMMAND_GRIPPER,  ui->in_Gripper_2->value());

    programList->push_back(auxSequenceItem);
//    SequenceList->PrintList(&Point::printPoint);

    int rowIndex=ui->SequenceList->rowCount()-1;
    ui->SequenceList->insertRow(rowIndex+1);

    ui->SequenceList->setItem(rowIndex,0,new QTableWidgetItem("Gripper"));
    ui->SequenceList->setItem(rowIndex,1,new QTableWidgetItem(QString::number(ui->in_Gripper_2->value())));

    ui->statusbar->showMessage("Agregado a lista ",3000);
}

void InterfazEstandar::pushDelayToProgramList()
{
    Point auxSequenceItem=Point();
    auxSequenceItem.setAsCommand(CommandCodes::COMMAND_SLEEP,  ui->in_Delay->value());

    programList->push_back(auxSequenceItem);
//    SequenceList->PrintList(&Point::printPoint);

    int rowIndex=ui->SequenceList->rowCount()-1;
    ui->SequenceList->insertRow(rowIndex+1);

    ui->SequenceList->setItem(rowIndex,0,new QTableWidgetItem("Delay"));
    ui->SequenceList->setItem(rowIndex,1,new QTableWidgetItem(QString::number(ui->in_Delay->value())));

    ui->statusbar->showMessage("Agregado a lista ",3000);
}



void InterfazEstandar::moveProgramItemUp()
{
    int index=ui->SequenceList->currentRow();

    if(index<1){
        ui->statusbar->showMessage("El elemento ya es el primero de la lista",3000);
        return;}  //if the current item is the first one, do nothing

    Point auxSequenceItem=Point();
    auxSequenceItem=programList->at(index);
    programList->errase(index);

    programList->insert(auxSequenceItem,index-1);
    setToProgramTable(index-1,auxSequenceItem);

    auxSequenceItem=programList->at(index);
    setToProgramTable(index,auxSequenceItem);
    ui->SequenceList->setCurrentCell(index-1,ui->SequenceList->currentColumn());
    ui->statusbar->showMessage("Elemento subido",3000);
}

void InterfazEstandar::moveProgramItemDown()
{
    int index=ui->SequenceList->currentRow();

    if(index>ui->SequenceList->rowCount()-3){
        ui->statusbar->showMessage("El elemento ya es el ultimo de la lista",3000);
        return;} //if the current item is the last one, do nothing

    Point auxSequenceItem=Point();
    auxSequenceItem=programList->at(index);
    programList->errase(index);

    programList->insert(auxSequenceItem,index+1);
    setToProgramTable(index+1,auxSequenceItem);

    auxSequenceItem=programList->at(index);
    setToProgramTable(index,auxSequenceItem);
    ui->SequenceList->setCurrentCell(index+1,ui->SequenceList->currentColumn());
    ui->statusbar->showMessage("Elemento bajado",3000);
}

void InterfazEstandar::removeFromProgramList()
{
    int index=ui->SequenceList->currentRow();
    if (index<0||index>programList->getSize()){
        ui->statusbar->showMessage("Selecciona un punto valido ",4000);
        return;
    }
    ui->SequenceList->removeRow(index);
    ui->statusbar->showMessage("Elminado de la lista ",2500);
    programList->errase(index);
}

void InterfazEstandar::clearProgramList()
{
    ui->SequenceList->clearContents();
    ui->SequenceList->setRowCount(1);
    programList->clear();
    ui->statusbar->showMessage("Lista descartada",4000);
}

void InterfazEstandar::updateProgramListFile(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setText("Error de lectura");
        alert.setInformativeText("El archivo no se ha podido generar");
        alert.exec();
        return;
    }
    QTextStream out(&file);
    ui->statusbar->showMessage("Guardando... ");
    Point auxitem;

    for(int i=0;i<programList->getSize();i++){
        auxitem=programList->at(i);

        out<<auxitem.getCtrl()<<',';
        out<<auxitem.getSpeed()<<',';
        out<<auxitem.getName()<<',';
        for(int j=0;j<6;j++){
            out<<auxitem.getRectangular(j)<<',';
        }
        for(int j=0;j<6;j++){
            out<<auxitem.getAngular(j);
            if(j<5) out<<',';
        }

        out<<'\n';

    }
    file.close();
}

void InterfazEstandar::setToProgramTable(int index, Point item)
{
    QString command;

    if(index>=ui->SequenceList->rowCount()-1){
        index=ui->SequenceList->rowCount()-1;
        ui->SequenceList->insertRow(index+1);
    }

    if(item.getCtrl()==CommandCodes::COMMAND_PtP){
        command="Punto-Punto";
        ui->SequenceList->setItem(index,0,new QTableWidgetItem(command));
        ui->SequenceList->setItem(index,1,new QTableWidgetItem(item.getName()));
        ui->SequenceList->setItem(index,2,new QTableWidgetItem(QString::number(item.getSpeed())));
        return;
    }
    if(item.getCtrl()==CommandCodes::COMMAND_COORDINATED){
        command="Coordinado";
        ui->SequenceList->setItem(index,0,new QTableWidgetItem(command));
        ui->SequenceList->setItem(index,1,new QTableWidgetItem(item.getName()));
        ui->SequenceList->setItem(index,2,new QTableWidgetItem(QString::number(item.getSpeed())));
        return;
    }
    if(item.getCtrl()==CommandCodes::COMMAND_SLEEP){
        command="Delay";
        ui->SequenceList->setItem(index,0,new QTableWidgetItem(command));
        ui->SequenceList->setItem(index,1,new QTableWidgetItem(QString::number(item.getSpeed())));
        ui->SequenceList->setItem(index,2,new QTableWidgetItem(""));
        return;
    }
    if(item.getCtrl()==CommandCodes::COMMAND_GRIPPER){
        command="Gripper";
        ui->SequenceList->setItem(index,0,new QTableWidgetItem(command));
        ui->SequenceList->setItem(index,1,new QTableWidgetItem(QString::number(item.getSpeed())));
        ui->SequenceList->setItem(index,2,new QTableWidgetItem(""));
        return;
    }
}

