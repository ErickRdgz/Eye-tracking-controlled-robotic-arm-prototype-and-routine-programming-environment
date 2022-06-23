#ifndef CONSTANTS_H
#define CONSTANTS_H

#define COORDINATED_TRAJECTORY_STEP 1
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

#endif // CONSTANTS_H
