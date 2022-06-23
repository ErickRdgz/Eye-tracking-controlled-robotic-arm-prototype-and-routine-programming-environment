#ifndef CINEMATICA_H
#define CINEMATICA_H
#include <vector>

#define L0 7
#define L1 16
#define L2 14
#define L3 10
#define pi 3.1415926
#define rad 180
#define DEG_RAD_FACTOR 0.0174533  // = pi/180
#define RAD_DEG_FACTOR 57.2958    // =180/pi
#define MAXIMUM_EXTENSION 27
#define L1L2_ANGLE_CONST 97
#define MAXIMUM_L1L2_ANGLE 140 //     este factor nace de la relacion  180-Q1'-Q2'<140; siendo 140 el angulo maximo entre L1 y L3
#define REC_ANGLE 90

#define Q0_REFERENCE 90
#define Q1_REFERENCE 85
#define Q2_REFERENCE 102
#define Q3_REFERENCE 90
#define Q4_REFERENCE 125
#define Q5_REFERENCE 92

#define DoF 6  //Grados de libertad


using namespace std;

/**
 * @brief directKinematic
 * calculate rectangular position form angles
 * @param articularPosition  input angles values
 * @param rectangularPosition output position
 * @return true if successful
 */
bool directKinematic(vector<float>& articularPosition, vector<float>& rectangularPosition);
/**
 * @brief inverseKinematic
 * calculate articular position form rectangular input values
 * @param rectangularPosition input position
 * @param articularPosition   output angles
 * @return
 */
bool inverseKinematic(vector<float>& rectangularPosition, vector<float>& articularPosition);
/**
 * @brief arm2ModelAngles
 * convert arm angles to model angles
 * @param angles angles to convert
 */
void arm2ModelAngles(vector<float>& angles);
/**
 * @brief model2ArmAngles
 * convert model angles to arm angles
 * @param angles angles to convert
 */
void model2ArmAngles(vector<float>& angles);
/**
 * @brief isValidArticularPosition
 * eval if artiuclar position is robot workspace
 * @param angles
 * @return
 */
bool isValidArticularPosition(vector<float>& angles);

/**
 * @brief setArmAngles
 * conver model angles to arm angles and saves them in diferent positions.
 * @param angles     input data
 * @param modelAngles  output data
 */
void setArmAngles(vector<float>& angles,vector<float>& modelAngles);




#endif // CINEMATICA_H
