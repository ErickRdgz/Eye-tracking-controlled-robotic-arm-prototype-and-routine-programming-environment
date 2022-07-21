#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TRAJECTORY_STEP 0.5
#define DEF_GRIPPER 50
#define DEF_HOME 10,10,10,0,0,0,50
#define ZEROS 0,0,0,0,0,0
#define MSG_ZEROS 0,0,0,0,0,0,0

#define DEFAULT_X_HOME     10
#define DEFAULT_Y_HOME     10
#define DEFAULT_Z_HOME     10
#define DEFAULT_ROW_HOME   0
#define DEFAULT_PITCH_HOME 0
#define DEFAULT_YAW_HOME   0
#define DEFAULT_MAX_SPEED  100
#define DEFAULT_PORT       "COM10"
#define DEFAULT_BAUD_RATE  115200
#define DEFAULT_GRIPPER 50

#define DEFAULT_EYE_D_TIME  2
#define DEFAULT_DIR "./docs"
#define DEFAULT_ARM_STEP 0.5
#define DEFAULT_CAM_IP "http://192.168.1.68:8080/video"

#define DoF 6  //Grados de libertad

typedef  enum Rectangular{
  X,Y,Z,ROW,PITCH,YAW,GRIPPER
}rec_t;

typedef enum Movements{
    POINT_TO_POINT,
    COORDINATED,
    CONTINUOUS
}mov_t;

enum CancellationOptions{
    HOME,
    STOP,
//    END_POINT
};

typedef enum ArmCtrlCodes{
    INSTANT_MOVEMENT,
    GRIPPER_MOVEMENT,
    PTP_MOVEMENT_30,
    PTP_MOVEMENT_60,
    COODINATED_MOVEMENT_30,
    COODINATED_MOVEMENT_60,
    GET_POSITION,
    SET_HOME,
    GO_HOME,
}ArmCodes_t;

typedef enum CommandCodes{
  /* 0 */      COMMAND_PtP,
  /* 1 */      COMMAND_COORDINATED,
  /* 2 */      COMMAND_SLEEP,
  /* 3 */      COMMAND_GRIPPER,
  /* 4 */      NEW_SEQUENCE,
  /* 5 */      MOVE_ARM,
  /* 6 */      MOVE_GRIPPER,
  /* 7 */      GO_TO_HOME,
  /* 8 */      END_SEQUENCE,
               END_FILE
}cmmd_t;


/*
 ###########################################################################
 ###########################################################################
 ###########################################################################
 Eye Control constants
*/

//// Debugging
const bool kPlotVectorField = false;

// Size constants
const int kEyePercentTop = 25;
const int kEyePercentSide = 13;
const int kEyePercentHeight = 30;
const int kEyePercentWidth = 35;

// Preprocessing
const bool kSmoothFaceImage = false;
const float kSmoothFaceFactor = 0.005;

// Algorithm Parameters
const int kFastEyeWidth = 50;
const int kWeightBlurSize = 5;
const bool kEnableWeight = true;
const float kWeightDivisor = 1.0;
const double kGradientThreshold = 50.0;
#define STABILIZE_WINDOW 7
#define ERROR_RANGE_X 15
#define ERROR_RANGE_Y 10


#define UPPER_LIMIT  7.6  //25
#define RIGHT_LIMIT   2  //28
#define LEFT_LIMIT   0.7  //18
#define EYE_COMMAND_TIMEOUT 1.6


// Postprocessing
const bool kEnablePostProcess = true;
const float kPostProcessThreshold = 0.97;



typedef enum EyePosition{
    EYE_NEUTRAL,
    EYE_UP,
    EYE_RIGHT,
    EYE_LEFT
}Position_t;


#endif // CONSTANTS_H
