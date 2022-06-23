#include "cinematica.h"
#include <math.h>
//#include <QDebug>

bool directKinematic(vector<float> &articularPosition, vector<float> &rectangularPosition)
{
    vector<float> articularPositionRad{0,0,0,0,0,0};

    for (size_t i=0; i<articularPosition.size();i++){
        articularPositionRad.at(i)=articularPosition.at(i)*DEG_RAD_FACTOR;
    }
    // Calculo de senos y cosenos correspondientes para cada angulo
    // de las articlulaciones de brazo
    float sin0=sin(articularPositionRad.at(0));
    float sin1=sin(articularPositionRad.at(1));
    float sin2=sin(articularPositionRad.at(2));
    float sin3=sin(articularPositionRad.at(3));
    float sin4=sin(articularPositionRad.at(4));
    float sin5=sin(articularPositionRad.at(5));
    float cos0=cos(articularPositionRad.at(0));
    float cos1=cos(articularPositionRad.at(1));
    float cos2=cos(articularPositionRad.at(2));
    float cos3=cos(articularPositionRad.at(3));
    float cos4=cos(articularPositionRad.at(4));
    float cos5=cos(articularPositionRad.at(5));
    float sin12=sin(articularPositionRad.at(1)+articularPositionRad.at(2));
    float cos12=cos(articularPositionRad.at(1)+articularPositionRad.at(2));

        // calculos recurrentes constantes en la matriz de transformacion,
    float aux12=cos1*sin0*sin2+cos2*sin0*sin1;
    float aux11=cos0*cos1*sin2+cos0*cos2*sin1;
    float aux10=sin0*sin1*sin2-cos1*cos2*sin0;
    float aux9=cos0*sin3+cos3*aux12;
    float aux8=cos0*sin1*sin2-cos0*cos1*cos2;
    float aux7=sin0*sin3-cos3*aux11;
    float aux6=cos3*sin0+sin3*aux11;
    float aux5=cos0*cos3-sin3*aux12;
    float aux4=sin4*aux9+cos4*aux10;
    float aux3=cos4*aux9-sin4*aux10;
    float aux2=sin4*aux7+sin4*aux8;
    float aux1=sin12*sin4-cos12*cos3*cos4;

    // elementos de la matriz de transformacion necesarios para el calculo
    // de RPY
    float DH11=-sin5*aux6+cos5*aux2;
    float DH21=sin5*aux5-cos5*aux3;
    float DH31=-cos5*aux1+cos12*sin3*sin5;
    float DH32=sin5*aux1+cos12*cos5*sin3;
    float DH33=-sin12*cos4-cos12*cos3*sin4;


    rectangularPosition.at(0)=L3*(sin4*aux7-cos4*aux8)+L1*cos0*cos1+L2*cos0*cos1*cos2-L2*cos0*sin1*sin2;
    rectangularPosition.at(1)=L1*cos1*sin0-L3*aux4+L2*cos1*cos2*sin0-L2*sin0*sin1*sin2;
    rectangularPosition.at(2)=L0+L2*sin12+L1*sin1+(( L3*cos12*sin(articularPositionRad.at(3)+articularPositionRad.at(4)) )/2)+     //x DH34
                    L3*sin12*cos4-( (L3*sin(articularPositionRad.at(3)-articularPositionRad.at(4) )*cos12) /2);

    rectangularPosition.at(3)=atan2(DH21,DH11) *RAD_DEG_FACTOR;                                              //ROW  transformado en grados
    rectangularPosition.at(4)=atan2(-DH31,sqrt((DH11*DH11)+(DH21*DH21)))*RAD_DEG_FACTOR;                     //PITCH  transformado en grados
    rectangularPosition.at(5)=(atan2(DH32,DH33))*RAD_DEG_FACTOR;                                               //YAW  transformado en grados

    return true;
}






bool inverseKinematic(vector<float> &rectangularPosition, vector<float> &articularPosition)
{
    // transformacion de rpy de angulos a radianes
    float phi=rectangularPosition.at(3)*DEG_RAD_FACTOR;
    float theta=rectangularPosition.at(4)*DEG_RAD_FACTOR;
    float psi=(rectangularPosition.at(5)*DEG_RAD_FACTOR); // ajuste de rotacion en x para coincidir con el modelo fisico

        // razones trigonomietricas  de rpw para calculo de la matriz de rotacion Rnn.
    float cosPhi=cos(phi);
    float sinPhi=sin(phi);
    float cosTheta=cos(theta);
    float sinTheta=sin(theta);
    float cosPsi=cos(psi);
    float sinPsi=sin(psi);

    //elementos de Rnn necesarios para calculo de centro de muñeca.
    float R13=sinPhi*sinPsi+cosPhi*cosPsi*sinTheta;
    float R23=cosPsi*sinPhi*sinTheta-cosPhi*sinPsi;
    float R33=cosPsi*cosTheta;

        // centro de muñeca
    float Xw= rectangularPosition.at(0)+(L3*R13);
    float Yw= rectangularPosition.at(1)+(L3*R23);
    float Zw= rectangularPosition.at(2)+(L3*R33);


        // Maximum extension es la separacion maxima alcanzable desde la base
        //  a la muñeca, de exederse elta longitud se cancela el calculo.
    if (sqrt(Xw*Xw+(Zw-L0)*(Zw-L0))>MAXIMUM_EXTENSION) return false;

        // resto de elementos de Rnn
        float R11=cosPhi*cosTheta;
        float R12=cosPhi*sinPsi*sinTheta-cosPsi*sinPhi;
        float R21=sinPhi*cosTheta;
        float R22=cosPhi*cosPsi+sinPsi*sinPhi*sinTheta;
        float R31=-sinTheta;
        float R32=cosTheta*sinPsi;


        // Metodo geometrico  para calculo de Q0, Q1 y Q2
        //  a partir del centro de la muñeca.
        float H_xy=sqrt(Yw*Yw+Xw*Xw);       //  segmento (0,0)-(Xw,Yw)
        articularPosition.at(0)=atan2(Yw,Xw);                                                                           //Q0
        float cos2=(  (H_xy*H_xy) + ((Zw-L0)*(Zw-L0)) - L1*L1 - L2*L2   )/(2*L1*L2);
        articularPosition.at(2)=atan2(sqrt(1-(cos2*cos2)),cos2);                                                         //-Q2
        articularPosition.at(1)=  pi/2- (atan2(H_xy,(Zw-L0))-atan2( (L2*sin(articularPosition.at(2))),(L1+L2*cos(articularPosition.at(2))) ));//Q1
        articularPosition.at(2)=-articularPosition.at(2);                                                   // ajuste de rotacion de Q2



        // H36=H03'*H06
        // generacion de matriz de euler para el calculo de angulos Q3,Q4 y Q5
        // a partir de la matriz de rotacion R (H06) y H03 generada a partir de los angulos Q0, Q1 y Q2
        float sin12=sin(articularPosition.at(1)+articularPosition.at(2));
        float cos12=cos(articularPosition.at(1)+articularPosition.at(2));
        float sin0=sin(articularPosition.at(0));
        float cos0=cos(articularPosition.at(0));



        articularPosition.at(3)=atan2((R13*sin0-R23*cos0)  ,   ( R33*cos12- R13*sin12*cos0- R23*sin12*sin0 ) );
        float cos4=R33*sin12+R13*cos12*cos0+R23*cos12*sin0;
        articularPosition.at(4)=-atan2((sqrt(1-cos4*cos4)),(-cos4));
        articularPosition.at(5)=atan2(-(R32*sin12+R12*cos12*cos0+R22*cos12*sin0 )  ,   (R31*sin12+R11*cos12*cos0+R21*cos12*sin0) );

//        printVec(articularPosition);

        for (size_t i=0; i<articularPosition.size();i++){
            articularPosition.at(i)=round( articularPosition.at(i)*RAD_DEG_FACTOR);
        }


        return true;


}

bool isValidArticularPosition(vector<float> &angles)
{
//    if(!(-90<angles.at(0)&&angles.at(0)<90)  ) return false;
//    if(!(0<angles.at(1)&&angles.at(1)<180)   ) return false;
//    if(!(-150<angles.at(2)&&angles.at(2)<-40)) return false;
//    if(!(-90<angles.at(3)&&angles.at(3)<90)  ) return false;
//    if(!(-145<angles.at(4)&&angles.at(4)<35) ) return false;
//    if(!(-92<angles.at(5)&&angles.at(5)<88)  ) return false;
    return true;
}

void setArmAngles(vector<float> &angles, vector<float> &modelAngles)
{
    angles.at(0)=modelAngles.at(0)+Q0_REFERENCE;
    angles.at(1)=(REC_ANGLE+Q1_REFERENCE)-modelAngles.at(1);
    angles.at(2)=modelAngles.at(1)+modelAngles.at(2)+Q2_REFERENCE;
    angles.at(3)=modelAngles.at(3)+Q3_REFERENCE;
    angles.at(4)=(Q4_REFERENCE-REC_ANGLE)-modelAngles.at(4);
    angles.at(5)=modelAngles.at(5)+Q5_REFERENCE;
}

void arm2ModelAngles(vector<float> &angles)
{
    angles.at(0)=angles.at(0)-Q0_REFERENCE;
    angles.at(1)=(REC_ANGLE+Q1_REFERENCE)-angles.at(1);
    angles.at(2)=angles.at(2)-Q2_REFERENCE-angles.at(1);
    angles.at(3)=angles.at(3)-Q3_REFERENCE;
    angles.at(4)=(Q4_REFERENCE-REC_ANGLE)-angles.at(4);
    angles.at(5)=angles.at(5)-Q5_REFERENCE;
}

void model2ArmAngles(vector<float> &angles)
{
    angles.at(0)+=Q0_REFERENCE;
    int aux=angles.at(1);
    angles.at(1)=(REC_ANGLE+Q1_REFERENCE)-angles.at(1);
    angles.at(2)=aux+angles.at(2)+Q2_REFERENCE;
    angles.at(3)=angles.at(3)+Q3_REFERENCE;
    angles.at(4)=(Q4_REFERENCE-REC_ANGLE)-angles.at(4);
    angles.at(5)=angles.at(5)+Q5_REFERENCE;
}
