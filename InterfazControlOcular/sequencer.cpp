#include "sequencer.h"
#include <QElapsedTimer>


Sequencer::Sequencer(QObject *parent) : QThread(parent)
{

}

void Sequencer::stopThread()
{
    if(this->CancellationOption==CancellationOptions::HOME){
        emit setArmToHome();
    }
    this->cancelled=false;
    this->stoped=false;
    emit executionCancelled();
//    qDebug()<<"cancelado";
}

void Sequencer::setSequenceList(Lista<Command> *CommandList)
{
    this->CommandList=CommandList;
}

void Sequencer::run()
{

    //    qDebug()<<"iniciando!!!";
        QElapsedTimer timer;
        timer.start();
        int timeOut=0;
        Command command;

        int ctrl;
        bool goNext=false;
        std::vector <float> lastPosition={ZEROS,0,0,0};

//        this->CommandList->PrintList(&Command::printCommand);
        for(int j=0;j<this->executionCounter;j++){
            int commandCount=0;


        while(commandCount<CommandList->getSize() ){
            if(timer.hasExpired(timeOut) || goNext==true){
                goNext=false;
                command=CommandList->at(commandCount);
                ctrl=command.getCtrl();

                switch (ctrl) {
                case CommandCodes::MOVE_ARM :
    //                qDebug()<<"movearm";
                    this->auxmsg.at(0)=ArmCtrlCodes::INSTANT_MOVEMENT;
                    for(int i=0;i<6;i++)
                        this->auxmsg.at(i+1)=command.getAngle(i);

                    emit sendToSerial(this->auxmsg);
                    lastPosition=this->auxmsg;
                    timer.start();
                    commandCount++;
                    break;


                case CommandCodes::NEW_SEQUENCE :
    //                qDebug()<<"new";
                    timeOut=command.getAngle(1);
    //                qDebug()<<timeOut;
                    commandCount++;
                    goNext=true;
                    break;


                case CommandCodes::END_SEQUENCE :
    //                qDebug()<<"end";
                    emit newSequenseLine();
                    commandCount++;
                    goNext=true;
                    break;


                case CommandCodes::COMMAND_SLEEP :
    //                qDebug()<<"sleep";
                    msleep(command.getAngle(0)-timeOut);
                    emit newSequenseLine();
                    commandCount++;
                    goNext=true;
                    break;


                case CommandCodes::COMMAND_GRIPPER :
    //                qDebug()<<"gripper";
                    this->auxmsg.at(0)=ArmCtrlCodes::GRIPPER_MOVEMENT;
                    this->auxmsg.at(1)=command.getAngle(0);
                    this->auxmsg.at(2)=0;
                    this->auxmsg.at(3)=0;
                    this->auxmsg.at(4)=0;
                    this->auxmsg.at(5)=0;
                    this->auxmsg.at(6)=0;

                    emit sendToSerial(this->auxmsg);
                    timer.start();
                    emit newSequenseLine();
                    commandCount++;
                    goNext=true;
                    break;

                case CommandCodes::END_FILE :
    //                qDebug()<<"finalizado";
                    commandCount++;
                    emit sequenceFinished();
    //                return;
                    break;

                default:
                    commandCount++;
                    break;
                }

            }

            if(this->stoped){
               emit setArmPosition(lastPosition);
    //            qDebug()<<"Pausado";
                while (this->stoped) {

                    if(this->cancelled){
                        stopThread();
                        return;
                    }
                }

            }

            if(this->cancelled){
                emit setArmPosition(lastPosition);
                stopThread();
                return;
            }
        }
        }
    return;
}
