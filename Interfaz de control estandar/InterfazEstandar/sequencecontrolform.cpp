#include "sequencecontrolform.h"
#include "ui_sequencecontrolform.h"

SequenceControlForm::SequenceControlForm(Lista<Command> *CommandList,Lista<Point> *SequenceList,RevoluteArm *arm,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SequenceControlForm)
{
    ui->setupUi(this);
    this->arm=arm;
    this->SequenceList=SequenceList;
    this->CommandList=CommandList;
    arm->getSequencer()->setSequenceList(CommandList);

    ui->Btn_CancelExecution->setEnabled (false);
    ui->Btn_StopAndPlay->setEnabled(false);

    ui->Out_info->setText("Ejecutar secuencia");

    //Execution controls
    connect(ui->Btn_Execution,&QPushButton::clicked,[=](){
        ui->Btn_CancelExecution->setEnabled (true);
        ui->Btn_StopAndPlay->setEnabled(true);
        ui->SBox_N_Executions->setEnabled(false);
        ui->Btn_Execution->setEnabled(false);

        arm->getSequencer()->setExecutionCounter(ui->SBox_N_Executions->value());

        ui->Btn_Execution->setText("Detener");
        this->arm->getSequencer()->start(QThread::TimeCriticalPriority);
        this->stopFlag=false;
        this->commandCounter=0;
        this->executionCounter=1;
        ui->Out_ExecutionCounter->setText(QString::number(this->executionCounter));
        updateExecutionInfo();
    });




    connect(ui->Btn_CancelExecution,&QPushButton::clicked,[=](){
        this->arm->getSequencer()->cancelExecution(CancellationOptions::STOP);
//        this->arm->getSequencer()->wait();
        ui->Btn_CancelExecution->setEnabled (false);
        ui->Btn_StopAndPlay->setEnabled(false);
        ui->SBox_N_Executions->setEnabled(true);
        ui->Btn_Execution->setEnabled(true);
        ui->Out_info->setText("Ejecutar cancelada");
        this->stopFlag=true;
    } );




    connect(ui->Btn_StopAndPlay,&QPushButton::clicked,[=](){
        if (this->stopFlag){
            ui->Btn_StopAndPlay->setText("Pausar");
            this->arm->getSequencer()->continueExecution();
            this->stopFlag=false;

        }else{
            ui->Btn_StopAndPlay->setText("Continuar");
             this->arm->getSequencer()->stopExecution();
            this->stopFlag=true;
        }
    } );



    connect(this->arm->getSequencer(),&Sequencer::newSequenseLine,[=](){
        this->commandCounter++;
        updateExecutionInfo();
    });



    connect(this->arm->getSequencer(),&Sequencer::finished,[=](){
//        qDebug()<<"hilo terminado";
        ui->Btn_Execution->setText("Ejecutar");
        ui->Btn_CancelExecution->setEnabled (false);
        ui->Btn_StopAndPlay->setEnabled(false);
        ui->SBox_N_Executions->setEnabled(true);
        ui->Btn_Execution->setEnabled(true);


        this->stopFlag=true;
        ui->Out_info->setText("Ejecutar finalizada");
        this->commandCounter=0;
    });


    connect(this->arm->getSequencer(),&Sequencer::sequenceFinished,[=](){
        if(this->executionCounter<ui->SBox_N_Executions->value()){
        this->executionCounter++;
        ui->Out_ExecutionCounter->setText(QString::number(this->executionCounter));
        }
        commandCounter=0;
        updateExecutionInfo();

    });




    connect(this->arm->getSequencer(),&Sequencer::executionCancelled,[=](){
        qDebug()<<"ejecucion finalizada";
        ui->Out_info->setText("Ejecutar Cancelada");
    });




}

SequenceControlForm::~SequenceControlForm()
{
    delete ui;
}

void SequenceControlForm::updateExecutionInfo()
{
    try{
    ui->Out_info->setText(Point::printSequencePoint(SequenceList->at(this->commandCounter)));
    }catch(...){

    }
}

void SequenceControlForm::closeEvent(QCloseEvent *)
{
    this->arm->getSequencer()->terminate();
}
