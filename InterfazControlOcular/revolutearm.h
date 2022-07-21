#ifndef REVOLUTEARM_H
#define REVOLUTEARM_H

#include "arduino.h"
#include "constants.h"
#include "lista.h"
#include "sequencer.h"

enum ArmExceptionCodes{
    OUT_OF_RECTANGULAR_RANGE,
    ANGLES_OUT_OF_RANGE,
    INVALID_COMMAND
};

class RevoluteArm
{
public:
    RevoluteArm();

    // Arduino ------------------------------------------------
    /**
     * @brief connectArm
     * connect the robot microcontroller
     * @return
     */
    bool connectArm();
    /**
     * @brief disconnectArm
     * disconnet the robot microcontroller
     * @return
     */
    bool disconnectArm();
    /**
     * @brief getArduino
     * @return  pointer to robot microcontroller
     */
    Arduino *getArduino();
    /**
     * @brief setArduino
     *  init robot microcontroller
     * @param port     serial port
     * @param baudRate serial baud rate
     */
    void setArduino(QString port,int baudRate);

    // Set values without movement ------------------------------------------------
    /**
     * @brief setHomeValue
     * define home values without movement.
     * @param position
     * @param value
     */
    void setHomeValue(int position,int value);
    /**
     * @brief setArmToHome
     * set arm position values to home without movement
     * @return
     */
    bool setArmToHome();
    /**
     * @brief setGripper
     * set gripper position values without movement
     * @param val
     */
    void setGripper(int val);
    /**
     * @brief setArticularPosition
     * set arm position from an model joint position
     * @param newAngles
     * @return if its successful
     */
    bool setArticularPosition(vector<float>& newAngles);
    /**
     * @brief setRectangularPosition
     * set arm position from an rectangular position
     * @param newRectangularPosition
     * @return if its successful
     */
    bool setRectangularPosition(vector<float>& newRectangularPosition);

    // -------------------------------------------------------
    /**
     * @brief getAngle
     * get an value from arm angles vector
     * @param position position of the angle in the vector
     * @return  angle value
     */
    float getAngle(int position);
    /**
     * @brief getRectangularValue
     * get an value from RectangularPosition.
     * @param position
     * @return  value
     */
    float getRectangularValue(int position);
    /**
     * @brief getGripper
     * @return Actual gripper value
     */
    float getGripper();

    // movements----------------------------------------------
    /**
     * @brief goHome
     * move arm to home position.
     * @return If its successful
     */
    bool goHome();
    /**
     * @brief moveGripper
     * @param gripperVal New gripper value
     * @return If its successful
     */
    bool moveGripper(int gripperVal);
    /**
     * @brief articularMovement
     * move arm to new arm angles values.
     * @param nextAngles
     * @param speed
     * @param movement
     * @return If its successful
     */
    bool articularMovement(vector<float>& nextAngles,const int speed, const int movement);
    /**
     * @brief rectangularMovement
     * move arm to new rectangular position
     * @param nextRectangularP
     * @param speed
     * @param movement
     * @return If its successful
     */
    bool rectangularMovement(vector<float>& nextRectangularP,const int speed, const int movement);

    /**
     * @brief generateCommands
     * generate commands from a program
     * @param programList
     * @param commandList
     * @return If its successful
     */
    bool generateCommands(Lista<Point> *programList, Lista<Command> *commandList);  

    /**
     * @brief setSequencer
     * init  program sequencer
     * @param CommandList
     * @param parent
     */
    void setSequencer(Lista<Command>* CommandList, QObject *parent ){
        this->sequencer =new Sequencer(parent);
        this->commandList= new Lista<Command>;
        sequencer->setSequenceList(CommandList);
    }
    /**
     * @brief getSequencer
     * @return get sequencer pointer
     */
    Sequencer* getSequencer(){
        return this->sequencer;
    }


private:
    Arduino *arduino;
    Sequencer *sequencer;
    Lista<Command> *commandList;
    vector <float> rectangularHome={DEF_HOME};
    vector <float> articularPosition={ZEROS};
    vector <float> rectangularPosition={ZEROS};
    vector <float> armAngles={ZEROS};
    int gripper=DEF_GRIPPER;

    // Program ----------------------------------------------
    bool trajectory_PP(vector<float>& P1,vector<float>& P2, float speed, Lista<Command>*  trajectory);
    bool trajectory_Coordinated(vector<float>& P1,vector<float>& P2, float speed, Lista<Command>*  trajectory);
    bool trajectory_Continuous(vector<float>& P1,vector<float>& P2, float speed, Lista<Command>*  trajectory);
    void executeSecuence();
};




class ArmException:public exception{
private:
    string message;
public:
    ArmException(int exceptionCode){
        switch (exceptionCode) {
        case OUT_OF_RECTANGULAR_RANGE:
            this->message="position is out of Rectangular range!";
            break;
        case ANGLES_OUT_OF_RANGE:
            this->message="angles exceed the limit of the motors";
        default:
            this->message="unidentified error";
            break;

        }
    }

    const char * what() const throw(){
        return  this->message.c_str();
    }

};





//    void hilo(Lista<Command>* sequenceList);



//    SerialDataSequencer *sequencer;

//    void setSequencer(Lista<Command>* CommandList, QObject *parent ){
//        this->sequencer =new SerialDataSequencer(parent);
//        this->commandList= new Lista<Command>;
//        sequencer->setSequenceList(CommandList);
//    }


//    SerialDataSequencer* getSequencer(){
//        return this->sequencer;
//    }





//    vector<float> auxmsg={ZEROS,0};
//    Lista<Command> *commandList;
//    vector<float> nextRectangularPosition={ZEROS};
//    vector<float> nextAngularPosition={ZEROS};
//    bool directKinematic(vector<float>& angles, vector<float>& RectangularPosition);
//    bool inverseKinematic(vector<float>& rectangularPosition,vector<float>& angles);
//    void nomalizeAngles(vector<float>& Angles);
//    void armAngles(vector<float>& Angles);
//    bool validModelAngles(vector<float>& angles);




#endif // REVOLUTEARM_H
