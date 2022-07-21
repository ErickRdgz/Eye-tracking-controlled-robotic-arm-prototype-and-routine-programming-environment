#include "revolutearm.h"
#include "cinematica.h"

RevoluteArm::RevoluteArm()
{

}

bool RevoluteArm::connectArm()
{
    vector<float>auxmsg={MSG_ZEROS};

    if(this->arduino->arduinoConected()){
        this->setArmToHome();
        setArmAngles(armAngles,this->articularPosition);

        auxmsg.at(0)=ArmCtrlCodes::SET_HOME;
        auxmsg.at(1)=this->armAngles.at(0);
        auxmsg.at(2)=this->armAngles.at(1);
        auxmsg.at(3)=this->armAngles.at(2);
        auxmsg.at(4)=this->armAngles.at(3);
        auxmsg.at(5)=this->armAngles.at(4);
        auxmsg.at(6)=this->armAngles.at(5);

        this->arduino->writeMessage(auxmsg);

        auxmsg.at(0)=ArmCtrlCodes::GO_HOME;
        auxmsg.at(1)=0;
        auxmsg.at(2)=0;
        auxmsg.at(3)=0;
        auxmsg.at(4)=0;
        auxmsg.at(5)=0;
        auxmsg.at(6)=0;
        arduino->writeMessage(auxmsg);
        return true;
    }else return false;
}

bool RevoluteArm::disconnectArm()
{
    if(this->arduino->arduinoDisconected()){
        return true;
    }else return false;
}

Arduino *RevoluteArm::getArduino()
{
     return this->arduino;
}

void RevoluteArm::setArduino(QString port, int baudRate)
{
    this->arduino=new Arduino(port,baudRate);
}

void RevoluteArm::setHomeValue(int position, int value)
{
    rectangularHome.at(position)=value;
}

void RevoluteArm::setGripper(int val)
{
    vector<float>auxmsg={MSG_ZEROS};
    this->gripper=val;
    auxmsg.at(0)=ArmCtrlCodes::GRIPPER_MOVEMENT;
    auxmsg.at(1)=val;
    auxmsg.at(2)=0;
    auxmsg.at(3)=0;
    auxmsg.at(4)=0;
    auxmsg.at(5)=0;
    auxmsg.at(6)=0;
    arduino->writeMessage(auxmsg);
}

bool RevoluteArm::setArticularPosition(vector<float> &newAngles)
{
    int aux[DoF];
    for(size_t i=0;i<DoF;i++)
       aux[i]=rectangularPosition.at(i);

    if (!directKinematic(newAngles,this->rectangularPosition) ){
        for(size_t i=0;i<DoF;i++)
           this->rectangularPosition.at(i)=aux[i];
        throw ArmException(ArmExceptionCodes::OUT_OF_RECTANGULAR_RANGE);
    }

    for(size_t i=0;i<DoF;i++)
        this->articularPosition.at(i)=newAngles.at(i);
    return true;
}

bool RevoluteArm::setRectangularPosition(vector<float> &newRectangularPosition)
{
    int aux[DoF];
    for(size_t i=0;i<DoF;i++)
       aux[i]=this->articularPosition.at(i);

    if (!inverseKinematic(newRectangularPosition,this->articularPosition)){
        for(size_t i=0;i<DoF;i++)
           articularPosition.at(i)=aux[i];
        throw ArmException(ArmExceptionCodes::ANGLES_OUT_OF_RANGE);
    }

    for(size_t i=0;i<DoF;i++)
        this->rectangularPosition.at(i)=newRectangularPosition.at(i);
    return true;
}

float RevoluteArm::getAngle(int position)
{
    return this->armAngles.at(position);
}

float RevoluteArm::getRectangularValue(int position)
{
    return  this->rectangularPosition.at(position);
}

float RevoluteArm::getGripper()
{
    return this->gripper;
}

bool RevoluteArm::setArmToHome()
{
    for(size_t i=0;i<DoF;i++)
        this->rectangularPosition.at(i)=rectangularHome.at(i);

    this->gripper=rectangularHome.at(GRIPPER);

    if (!inverseKinematic(this->rectangularPosition,this->articularPosition))
        throw ArmException(ArmExceptionCodes::ANGLES_OUT_OF_RANGE);

    if (!isValidArticularPosition(this->articularPosition))
        throw ArmException(ArmExceptionCodes::ANGLES_OUT_OF_RANGE);

    setArmAngles(armAngles,this->articularPosition);
    return true;
}

bool RevoluteArm::goHome()
{
    vector<float>auxmsg={MSG_ZEROS};
    this->setArmToHome();
    setArmAngles(armAngles,this->articularPosition);
    auxmsg.at(0)=ArmCtrlCodes::GO_HOME;
    this->arduino->writeMessage(auxmsg);
    return true;
}

bool RevoluteArm::moveGripper(int gripperVal)
{
    this->gripper=gripperVal;
    return true;
}

bool RevoluteArm::articularMovement(vector<float> &nextAngles, const int speed, const int movement)
{
        this->commandList->clear();

        switch (movement) {
        case Movements::POINT_TO_POINT:
            try {
                trajectory_PP(this->armAngles,nextAngles,speed,this->commandList);
            } catch (ArmException &e) {
                    throw e.what();
            }
            break;
        case Movements::COORDINATED:
            try {
                trajectory_Coordinated(this->armAngles,nextAngles,speed,this->commandList);
            } catch (ArmException &e) {
                    throw e.what();
            }
            break;
        default:
            break;
        }
        try {
            executeSecuence();
        } catch (ArmException &e) {
            throw e.what();
        }

        arm2ModelAngles(nextAngles);
        directKinematic(nextAngles,this->rectangularPosition);
        for(size_t i=0;i<DoF;i++){
            this->articularPosition.at(i)=nextAngles.at(i);
        }
        setArmAngles(armAngles,this->articularPosition);
        return true;
}

bool RevoluteArm::rectangularMovement(vector<float> &nextRectangularP, const int speed, const int movement)
{
    float aux[DoF];
    this->commandList->clear();
    vector<float> auxArticularP={ZEROS};

    if (!inverseKinematic(nextRectangularP,auxArticularP)){
        throw ArmException(ArmExceptionCodes::ANGLES_OUT_OF_RANGE);
    }

    if (! isValidArticularPosition(auxArticularP)){
        throw ArmException(ArmExceptionCodes::ANGLES_OUT_OF_RANGE);
    }

    for(size_t i=0;i<DoF;i++){
     aux[i]=auxArticularP.at(i);                            //save model angular values;
    }
    model2ArmAngles(auxArticularP);                         //transform model angles to real arm angles


    switch (movement) {
    case Movements::POINT_TO_POINT:
        try {
            trajectory_PP(this->armAngles,auxArticularP,speed,this->commandList);   //generate commands of trajectory
        } catch (ArmException &e) {
            vector<float>auxmsg={MSG_ZEROS};
            auxmsg.at(0)=ArmCtrlCodes::PTP_MOVEMENT_60;
            for(size_t i=0;i<DoF;i++){
             auxmsg.at(i+1)=this->articularPosition.at(i);                            //save model angular values;
            }
            this->arduino->writeMessage(auxmsg);
                throw e.what();
        }
        break;
    case Movements::COORDINATED:
        try {
            trajectory_Coordinated(this->armAngles,auxArticularP,speed,this->commandList);  //generate commands of trajectory
        } catch (ArmException &e) {
            vector<float>auxmsg={MSG_ZEROS};
            auxmsg.at(0)=ArmCtrlCodes::PTP_MOVEMENT_60;
            for(size_t i=0;i<DoF;i++){
             auxmsg.at(i+1)=this->articularPosition.at(i);                            //save model angular values;
            }
            this->arduino->writeMessage(auxmsg);
                throw e.what();
        }
        break;
    default:
        break;
    }

    try {
        executeSecuence();
    } catch (ArmException &e) {
        throw e.what();
    }

    for(size_t i=0;i<DoF;i++){
         this->armAngles.at(i)=auxArticularP.at(i);         //save new current arm position in real angles
         this->articularPosition.at(i)=aux[i];              //save new current arm position in model angles
         this->rectangularPosition.at(i)=nextRectangularP.at(i); //save new current arm position Rectangular values;
    }
    return true;
}

bool RevoluteArm::generateCommands(Lista<Point> *programList, Lista<Command> *commandList)
{
    vector<float> P1={ZEROS};
    vector<float> P2={ZEROS};
    Point sequenceItem;
    Command  instruction;

    inverseKinematic(this->rectangularHome,P1);       //set the starting point (P1) to home
    model2ArmAngles(P1);

    for(int i=0;i<programList->getSize();i++){
        sequenceItem=programList->at(i);                  //get list item in the temporary object
        switch (sequenceItem.getCtrl()) {
            case CommandCodes::COMMAND_PtP:
                for(int j=0;j<6;j++)
                    P2.at(j)=sequenceItem.getAngular(j);  //copy the new position to temporary vector;
                this->trajectory_PP(P1,P2,sequenceItem.getSpeed(),commandList );    //generate the trajectory from P1 to P2 and save it in commandList
                P1=P2;   // set P1 like new origin point;
                break;
            case CommandCodes::COMMAND_COORDINATED:
                for(int j=0;j<6;j++)
                    P2.at(j)=sequenceItem.getAngular(j);  //copy the new position to temporary vector;
                this->trajectory_Coordinated(P1,P2,sequenceItem.getSpeed(),commandList );    //generate the trajectory from P1 to P2 and save it in commandList
                P1=P2;   // set P1 like new origin point;
                break;
            case CommandCodes::COMMAND_SLEEP:
                instruction.setValues(CommandCodes::COMMAND_SLEEP,(sequenceItem.getSpeed()*1000),0,0,0,0,0,0);
                commandList->push_back(instruction);
                break;
            case CommandCodes::COMMAND_GRIPPER:
                instruction.setValues(CommandCodes::COMMAND_GRIPPER,sequenceItem.getSpeed(),0,0,0,0,0,0);
                commandList->push_back(instruction);
                break;
            default:                                                    // return an error if Ctrl value is invalid
                throw ArmException(ArmExceptionCodes::INVALID_COMMAND);
                break;
        }
    }
    instruction.setValues(CommandCodes::END_FILE,0,0,0,0,0,0,0);
    commandList->push_back(instruction);
    return true;
}



bool RevoluteArm::trajectory_PP(vector<float> &P1, vector<float> &P2, float speed, Lista<Command> *trajectory)
{
    Command instruction=Command();
     float position[DoF];
     float maxMovement=0;
     float aux;
     float step=TRAJECTORY_STEP;

     for(size_t i=0;i<P1.size();i++){
          position[i]=P1.at(i);
          aux= P1.at(i)-P2.at(i);
          if(aux<0)   aux=aux*-1;
          if(aux>maxMovement)
              maxMovement=aux;
     }
     maxMovement/=TRAJECTORY_STEP;

    int sendRate=(1000*TRAJECTORY_STEP)/speed;

    instruction.setValues(CommandCodes::NEW_SEQUENCE,maxMovement,sendRate,0,0,0,0,0);
    trajectory->push_back(instruction);

     for(int i=0;i<maxMovement-1;i++){
         for(size_t i=0;i<P1.size();i++){
             int dif=P2.at(i)-position[i];
             if (dif!=0){
                 if (dif>step)
                     position[i]+=step;
                 else if((dif<0) && (dif*-1)>step)
                     position[i]-=step;
                 else
                     position[i]=P2.at(i);
             }
         }
         instruction.setValues( CommandCodes::MOVE_ARM,
                                position[0],
                                position[1],
                                position[2],
                                position[3],
                                position[4],
                                position[5],
                                0);
         trajectory->push_back(instruction);
     }

     for(size_t i=0;i<P1.size();i++){
      position[i]=P2.at(i);
     }
     instruction.setValues( CommandCodes::MOVE_ARM,
                            position[0],
                            position[1],
                            position[2],
                            position[3],
                            position[4],
                            position[5],
                            0);
     trajectory->push_back(instruction);

     instruction.setValues(CommandCodes::END_SEQUENCE,0,0,0,0,0,0,0);
     trajectory->push_back(instruction);
     return true;
}

bool RevoluteArm::trajectory_Coordinated(vector<float> &P1, vector<float> &P2, float speed, Lista<Command> *trajectory)
{
    Command instruction=Command();
     float position[DoF];
     float maxMovement=0;
     float dif[DoF];
     float aux;
     float steps[DoF];

     for(size_t i=0;i<P1.size();i++){
          position[i]=P1.at(i);
          dif[i]= P2.at(i)-P1.at(i);
          if(dif[i]<0)   aux=dif[i]*-1;
          else aux=dif[i];
          if(aux>maxMovement)
              maxMovement=aux;
     }

     int N_Steps= maxMovement/TRAJECTORY_STEP;

//     qDebug()<<"Numero de pasos: "<<N_Steps;

     for(size_t i=0;i<P1.size();i++){
        steps[i]=dif[i]/N_Steps;
//        qDebug()<<steps[i];
     }

    int sendRate=(1000*TRAJECTORY_STEP)/speed;

    instruction.setValues(CommandCodes::NEW_SEQUENCE,N_Steps,sendRate,0,0,0,0,0);
    trajectory->push_back(instruction);
     for(int i=0;i<N_Steps-1;i++){
         for(size_t i=0;i<P1.size();i++){
            position[i]+=steps[i];
         }
         instruction.setValues( CommandCodes::MOVE_ARM,
                                position[0],
                                position[1],
                                position[2],
                                position[3],
                                position[4],
                                position[5],
                                0);
         trajectory->push_back(instruction);

         qDebug()<<Command::printCommand(instruction);
     }
     for(size_t i=0;i<P1.size();i++){
      position[i]=P2.at(i);
     }
     instruction.setValues( CommandCodes::MOVE_ARM,
                            position[0],
                            position[1],
                            position[2],
                            position[3],
                            position[4],
                            position[5],
                            0);
     trajectory->push_back(instruction);
     instruction.setValues(CommandCodes::END_SEQUENCE,0,0,0,0,0,0,0);
     trajectory->push_back(instruction);

     return true;
}

void RevoluteArm::executeSecuence()
{
    this->sequencer->setSequenceList(this->commandList);
    this->sequencer->start();
}
