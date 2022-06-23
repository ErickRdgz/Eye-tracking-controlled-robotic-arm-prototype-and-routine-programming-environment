#include "interfazestandar.h"
#include "ui_interfazestandar.h"
#include "settingsform.h"
#include <QDebug>
#include <QFileDialog>
#include <QDir>


void InterfazEstandar::initPointPage()
{
    ui->in_PointName->setText("P1");

    ui->PointList->setColumnCount(7);
//    QStringList titles;
//    titles<<"Punto"<<"X"<<"Y"<<"Z"<<"ROW"<<"PITCH"<<"YAW";
    ui->PointList->setHorizontalHeaderLabels({"Punto","X","Y","Z","ROW","PITCH","YAW"});
    ui->PointList->setLineWidth(435);
    ui->PointList->setColumnWidth(0,110);
    ui->PointList->setColumnWidth(1,50);
    ui->PointList->setColumnWidth(2,50);
    ui->PointList->setColumnWidth(3,50);
    ui->PointList->setColumnWidth(4,50);
    ui->PointList->setColumnWidth(5,50);
    ui->PointList->setColumnWidth(6,50);
    ui->PointList->insertRow(0);

    ui->CBox_Movement->addItem("Punto-Punto");
    ui->CBox_Movement->addItem("Coordinado");

    connect(ui->Btn_GoHome,&QPushButton::clicked,[=](){
        arm->goHome();
        updateAngularValues();
        updateRectangularValues();
    });

    //    //Arm coordinates;
    connect(ui->Btn_RecMovement,&QPushButton::clicked,this,&InterfazEstandar::rectangularArmMovement);

    //Griper
    connect(ui->Btn_Gripper,&QPushButton::clicked,this,&InterfazEstandar::setGripperPosition);

    //Arm free movement
    connect(ui->Btn_AngMovement,&QPushButton::clicked,this,&InterfazEstandar::angularArmMovement);

    connect(ui->Slider_Q1,&QSlider::valueChanged,[=](){
        ui->in_Q1->setValue(ui->Slider_Q1->value());  });
    connect(ui->in_Q1, &QDoubleSpinBox::textChanged, [=](){
        ui->Slider_Q1->setValue(ui->in_Q1->value());  });

    connect(ui->Slider_Q2,&QSlider::sliderReleased,[=](){
        ui->in_Q2->setValue(ui->Slider_Q2->value());  });
    connect(ui->in_Q2, &QDoubleSpinBox::textChanged, [=](){
        ui->Slider_Q2->setValue(ui->in_Q2->value());  });

    connect(ui->Slider_Q3,&QSlider::sliderReleased,[=](){
        ui->in_Q3->setValue(ui->Slider_Q3->value());  });
    connect(ui->in_Q3, &QDoubleSpinBox::textChanged, [=](){
        ui->Slider_Q3->setValue(ui->in_Q3->value());  });

    connect(ui->Slider_Q4,&QSlider::sliderReleased,[=](){
        ui->in_Q4->setValue(ui->Slider_Q4->value()); });
    connect(ui->in_Q4, &QDoubleSpinBox::textChanged, [=](){
        ui->Slider_Q4->setValue(ui->in_Q4->value()); });

    connect(ui->Slider_Q5,&QSlider::sliderReleased,[=](){
        ui->in_Q5->setValue(ui->Slider_Q5->value()); });
    connect(ui->in_Q5, &QDoubleSpinBox::textChanged, [=](){
        ui->Slider_Q5->setValue(ui->in_Q5->value());  });

    connect(ui->Slider_Q6,&QSlider::sliderReleased,[=](){
        ui->in_Q6->setValue(ui->Slider_Q6->value());  });
    connect(ui->in_Q6, &QDoubleSpinBox::textChanged, [=](){
        ui->Slider_Q6->setValue(ui->in_Q6->value());  });

    //##########################################################################################################
    //##########################################################################################################

    connect(ui->Btn_ListPoint,     &QPushButton::clicked,this, &InterfazEstandar::addPointToList);
    connect(ui->Btn_GoPoint,       &QPushButton::clicked,[=](){                   setArmInPoint(ui->PointList);      });    //    connect(ui->Btn_GoPoint,&QPushButton::clicked,this,&Interfaz::setArmInPoint);
    connect(ui->Btn_SavePointList, &QPushButton::clicked,this, &InterfazEstandar::savePointList);
    connect(ui->Btn_DeletPoint,    &QPushButton::clicked,this, &InterfazEstandar::deletPoint);
    connect(ui->Btn_CleanPointList,&QPushButton::clicked,this, &InterfazEstandar::clearPointList);
    connect(ui->Btn_LoadPointList, &QPushButton::clicked,this, &InterfazEstandar::loadPointList);

}

void InterfazEstandar::enablePointPage(bool enable)
{
    ui->CBox_Movement->setEnabled(enable);
    ui->SBox_Speed->setEnabled(enable);
    ui->Btn_GoHome->setEnabled(enable);

    ui->in_X->setEnabled(enable);
    ui->in_Y->setEnabled(enable);
    ui->in_Z->setEnabled(enable);
    ui->in_Row->setEnabled(enable);
    ui->in_Pitch->setEnabled(enable);
    ui->in_Yaw->setEnabled(enable);
    ui->Btn_RecMovement->setEnabled(enable);

    ui->Slider_Gripper->setEnabled(enable);

    ui->in_Q1->setEnabled(enable);
    ui->in_Q2->setEnabled(enable);
    ui->in_Q3->setEnabled(enable);
    ui->in_Q4->setEnabled(enable);
    ui->in_Q5->setEnabled(enable);
    ui->in_Q6->setEnabled(enable);
    ui->Slider_Q1->setEnabled(enable);
    ui->Slider_Q2->setEnabled(enable);
    ui->Slider_Q3->setEnabled(enable);
    ui->Slider_Q4->setEnabled(enable);
    ui->Slider_Q5->setEnabled(enable);
    ui->Slider_Q6->setEnabled(enable);
    ui->Btn_AngMovement->setEnabled(enable);

    ui->Btn_GoPoint->setEnabled(enable);
    ui->Btn_SavePointList->setEnabled(enable);
    ui->Btn_CleanPointList->setEnabled(enable);
    ui->Btn_DeletPoint->setEnabled(enable);
    ui->Btn_ListPoint->setEnabled(enable);
    ui->in_PointName->setEnabled(enable);
    ui->Btn_LoadPointList->setEnabled(enable);
    ui->PointList->setEnabled(enable);
    ui->PointList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void InterfazEstandar::updateAngularValues()
{
    ui->in_Q1->setValue(arm->getAngle(0));
    ui->in_Q2->setValue(arm->getAngle(1));
    ui->in_Q3->setValue(arm->getAngle(2));
    ui->in_Q4->setValue(arm->getAngle(3));
    ui->in_Q5->setValue(arm->getAngle(4));
    ui->in_Q6->setValue(arm->getAngle(5));
    ui->Slider_Q1->setValue(arm->getAngle(0));
    ui->Slider_Q2->setValue(arm->getAngle(1));
    ui->Slider_Q3->setValue(arm->getAngle(2));
    ui->Slider_Q4->setValue(arm->getAngle(3));
    ui->Slider_Q5->setValue(arm->getAngle(4));
    ui->Slider_Q6->setValue(arm->getAngle(5));
}

void InterfazEstandar::updateRectangularValues()
{
    ui->in_X->    setValue(arm->getRectangularValue(Rectangular::X));
    ui->in_Y->    setValue(arm->getRectangularValue(Rectangular::Y));
    ui->in_Z->    setValue(arm->getRectangularValue(Rectangular::Z));
    ui->in_Row->  setValue(arm->getRectangularValue(Rectangular::ROW));
    ui->in_Pitch->setValue(arm->getRectangularValue(Rectangular::PITCH));
    ui->in_Yaw->  setValue(arm->getRectangularValue(Rectangular::YAW));
}

void InterfazEstandar::rectangularArmMovement()
{
    vector<float> auxRectangular={ZEROS};
    enablePointPage(false);
    enableProgramPage(false);
    auxRectangular.at(Rectangular::X)    =ui->in_X     ->value();
    auxRectangular.at(Rectangular::Y)    =ui->in_Y     ->value();
    auxRectangular.at(Rectangular::Z)    =ui->in_Z     ->value();
    auxRectangular.at(Rectangular::ROW)  =ui->in_Row   ->value();
    auxRectangular.at(Rectangular::PITCH)=ui->in_Pitch ->value();
    auxRectangular.at(Rectangular::YAW)  =ui->in_Yaw   ->value();

    try {                      //new Position    speed(Deg/s)            movement
        arm->rectangularMovement(auxRectangular,ui->SBox_Speed->value(),ui->CBox_Movement->currentIndex());
    } catch (ArmException &e) {
        updateRectangularValues();
        QMessageBox alert;
        alert.setIcon(QMessageBox::Critical);
        alert.setText("Error de ejecucion");
        alert.setInformativeText(e.what());
        alert.exec();
    }


    updateAngularValues();
    enablePointPage(true);
    enableProgramPage(true);
    ui->statusbar->showMessage("Movimiento exitoso ",5000);
}

void InterfazEstandar::angularArmMovement()
{
    vector<float> auxAngles={ZEROS};
    enablePointPage(false);
    enableProgramPage(false);
    auxAngles.at(0)=ui->in_Q1->value();
    auxAngles.at(1)=ui->in_Q2->value();
    auxAngles.at(2)=ui->in_Q3->value();
    auxAngles.at(3)=ui->in_Q4->value();
    auxAngles.at(4)=ui->in_Q5->value();
    auxAngles.at(5)=ui->in_Q6->value();

    try {                  //new Position   speed(Deg/s)        movement
        arm->articularMovement(auxAngles,ui->SBox_Speed->value(),ui->CBox_Movement->currentIndex());
        updateRectangularValues();
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

void InterfazEstandar::setGripperPosition()
{
    arm->setGripper(ui->Slider_Gripper->value());
}

void InterfazEstandar::addPointToList()
{
    int rowIndex=ui->PointList->rowCount()-1;
    ui->PointList->insertRow(rowIndex+1);
    ui->PointList->setItem(rowIndex,PointListTitles::NAME,      new QTableWidgetItem(ui->in_PointName->text()));
    ui->PointList->setItem(rowIndex,PointListTitles::TabX,      new QTableWidgetItem(ui->in_X       ->text()));
    ui->PointList->setItem(rowIndex,PointListTitles::TabY,      new QTableWidgetItem(ui->in_Y       ->text()));
    ui->PointList->setItem(rowIndex,PointListTitles::TabZ,      new QTableWidgetItem(ui->in_Z       ->text()));
    ui->PointList->setItem(rowIndex,PointListTitles::TabROW,    new QTableWidgetItem(ui->in_Row     ->text()));
    ui->PointList->setItem(rowIndex,PointListTitles::TabPITCH,  new QTableWidgetItem(ui->in_Pitch   ->text()));
    ui->PointList->setItem(rowIndex,PointListTitles::TabYAW,    new QTableWidgetItem(ui->in_Yaw     ->text()));

    rowIndex=ui->PointList_2->rowCount()-1;
    ui->PointList_2->insertRow(rowIndex+1);
    ui->PointList_2->setItem(rowIndex,PointListTitles::NAME,    new QTableWidgetItem(ui->in_PointName->text()));
    ui->PointList_2->setItem(rowIndex,PointListTitles::TabX,    new QTableWidgetItem(ui->in_X       ->text()));
    ui->PointList_2->setItem(rowIndex,PointListTitles::TabY,    new QTableWidgetItem(ui->in_Y       ->text()));
    ui->PointList_2->setItem(rowIndex,PointListTitles::TabZ,    new QTableWidgetItem(ui->in_Z       ->text()));
    ui->PointList_2->setItem(rowIndex,PointListTitles::TabROW,  new QTableWidgetItem(ui->in_Row     ->text()));
    ui->PointList_2->setItem(rowIndex,PointListTitles::TabPITCH,new QTableWidgetItem(ui->in_Pitch   ->text()));
    ui->PointList_2->setItem(rowIndex,PointListTitles::TabYAW,  new QTableWidgetItem(ui->in_Yaw     ->text()));

    Point auxPoint=Point();
    auxPoint.setName(ui->in_PointName->text());
    auxPoint.setRectangular(ui->in_X    ->value(),
                            ui->in_Y    ->value(),
                            ui->in_Z    ->value(),
                            ui->in_Row  ->value(),
                            ui->in_Pitch->value(),
                            ui->in_Yaw  ->value());

    auxPoint.setAngular(ui->in_Q1->value(),
                        ui->in_Q2->value(),
                        ui->in_Q3->value(),
                        ui->in_Q4->value(),
                        ui->in_Q5->value(),
                        ui->in_Q6->value());

    pointList->push_back(auxPoint);

    ui->in_PointName->setText("P"+QString::number(rowIndex+2));
    ui->statusbar->showMessage("Agregado a lista ",3000);
}

void InterfazEstandar::deletPoint()
{
    int index=ui->PointList->currentRow();
    if (index<0){
        ui->statusbar->showMessage("Selecciona un punto valido ",4000);
        return;
    }
    ui->PointList->removeRow(index);
    ui->PointList_2->removeRow(index);
    ui->statusbar->showMessage("Elminado de la lista ",2500);
}

void InterfazEstandar::clearPointList()
{
    ui->PointList->clearContents();
    ui->PointList->setRowCount(1);
    ui->in_PointName->setText("P1");

    ui->PointList_2->clearContents();
    ui->PointList_2->setRowCount(1);
    pointList->clear();
    ui->statusbar->showMessage("Lista descartada",4000);
}

void InterfazEstandar::savePointList()
{
    QDir dir;
    if(this->filesPath.absolutePath()=="")              //if no directory opened, get aplication path
        dir.currentPath();
    else dir.setPath(this->filesPath.absolutePath());

    QString path=QFileDialog::getSaveFileName(this, "Guardar", dir.absolutePath()+"/pontList",tr("PointFiles(*.arm.pnt)"));

    if(path=="") return;

    dir.setPath(path);
    QString fullFileName=dir.dirName();      //get file name with extension
    QStringList auxList =fullFileName.split(".");
    if(auxList.size()>3)
          fullFileName=auxList.at(0)+"."+auxList.at(1)+"."+auxList.at(2);   //fix extension (the dialog has a bug and adds extension twice)
    QString fileName=auxList.at(0);   //get the file name without extension

    dir.cdUp();                             //move dir up to remove filename.
    auxList=dir.absolutePath().split("/");  // split path
    if(auxList.at(auxList.size()-1)!=fileName){        // get current directory and if not equivalent to filename then create the directory
        dir.mkdir(dir.absolutePath()+"/"+fileName);
        dir.cd(fileName);                               // move in
    }

    path=dir.absolutePath()+"/"+fullFileName;       // add the file name to path

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
    Point auxPoint;
    for(int i=0;i<pointList->getSize();i++){
        auxPoint=pointList->at(i);

        out<<auxPoint.getName()<<',';
        for(int j=0;j<6;j++){
            out<<auxPoint.getRectangular(j)<<',';
        }
        for(int j=0;j<6;j++){
            out<<auxPoint.getAngular(j);
            if(j<5) out<<',';
        }

        out<<'\n';

    }
    file.close();
    ui->statusbar->showMessage("Guardado ",4000);

    this->filesPath.setPath(dir.absolutePath());
    this->pointsFileName=fileName;
}

void InterfazEstandar::loadPointList()
{
    QDir dir;
    if(this->filesPath.absolutePath()=="")
        dir.currentPath();
    else dir.setPath(this->filesPath.absolutePath());


    QString path=QFileDialog::getOpenFileName(this, "Abrir", dir.absolutePath(),tr("PointFiles(*.arm.pnt)"));
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
    pointList->clear();
    clearPointList();

    Point auxPoint=Point();
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        auxPoint.setName(fields.at(0));

        auxPoint.setRectangular(fields.at(1).toFloat(),
                                fields.at(2).toFloat(),
                                fields.at(3).toFloat(),
                                fields.at(4).toFloat(),
                                fields.at(5).toFloat(),
                                fields.at(6).toFloat());
        auxPoint.setAngular(fields.at(7).toFloat(),
                            fields.at(8).toFloat(),
                            fields.at(9).toFloat(),
                            fields.at(10).toFloat(),
                            fields.at(11).toFloat(),
                            fields.at(12).toFloat());

        int rowIndex=ui->PointList->rowCount()-1;
        ui->PointList->insertRow(rowIndex+1);
        ui->PointList->setItem(rowIndex,PointListTitles::NAME,      new QTableWidgetItem(fields.at(0)));
        ui->PointList->setItem(rowIndex,PointListTitles::TabX,      new QTableWidgetItem(fields.at(1)));
        ui->PointList->setItem(rowIndex,PointListTitles::TabY,      new QTableWidgetItem(fields.at(2)));
        ui->PointList->setItem(rowIndex,PointListTitles::TabZ,      new QTableWidgetItem(fields.at(3)));
        ui->PointList->setItem(rowIndex,PointListTitles::TabROW,    new QTableWidgetItem(fields.at(4)));
        ui->PointList->setItem(rowIndex,PointListTitles::TabPITCH,  new QTableWidgetItem(fields.at(5)));
        ui->PointList->setItem(rowIndex,PointListTitles::TabYAW,    new QTableWidgetItem(fields.at(6)));


        rowIndex=ui->PointList_2->rowCount()-1;
        ui->PointList_2->insertRow(rowIndex+1);
        ui->PointList_2->setItem(rowIndex,PointListTitles::NAME,    new QTableWidgetItem(fields.at(0)));
        ui->PointList_2->setItem(rowIndex,PointListTitles::TabX,    new QTableWidgetItem(fields.at(1)));
        ui->PointList_2->setItem(rowIndex,PointListTitles::TabY,    new QTableWidgetItem(fields.at(2)));
        ui->PointList_2->setItem(rowIndex,PointListTitles::TabZ,    new QTableWidgetItem(fields.at(3)));
        ui->PointList_2->setItem(rowIndex,PointListTitles::TabROW,  new QTableWidgetItem(fields.at(4)));
        ui->PointList_2->setItem(rowIndex,PointListTitles::TabPITCH,new QTableWidgetItem(fields.at(5)));
        ui->PointList_2->setItem(rowIndex,PointListTitles::TabYAW,  new QTableWidgetItem(fields.at(6)));

        pointList->push_back(auxPoint);
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
    this->pointsFileName=fileName;

    dir.cdUp();
    this->filesPath.setPath(dir.absolutePath());
}

