#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QObject>
#include<QThread>
#include<QString>
#include<QByteArray>
#include<QDebug>
#include "lista.h"
#include "arduino.h"
#include "constants.h"
#include <vector>



class Sequencer: public QThread
{
    Q_OBJECT

private:
    Lista<Command> *CommandList;
    std::vector <float> auxmsg={MSG_ZEROS};

     bool stoped=false;
     bool cancelled=false;
     int CancellationOption;
     int executionCounter=1;

     void stopThread();

public:
    explicit Sequencer(QObject *parent = nullptr);
    void setSequenceList(Lista<Command> *CommandList);

    void stopExecution(){
        this->stoped=true;
    }

    void continueExecution(){
        this->stoped=false;
    }

    void cancelExecution(int option){
        this->CancellationOption=option;
        this->cancelled=true;
    }
    void setExecutionCounter(int value){
        this->executionCounter=value;
    }

signals:
    void sendToSerial(std::vector <float>);
    void setArmPosition(std::vector <float>);

    void setArmToHome();
    void newSequenseLine();
    void sequenceFinished();
    void executionCancelled();

protected:
    void run() override;

};

#endif // SEQUENCER_H
