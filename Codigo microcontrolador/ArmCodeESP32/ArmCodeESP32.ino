/**  @author Erick Abimael Rodriguez Hernandez
 *   @date Febrary 2022
 *   Tesis: Diseño y construccion de un brazo robotico controlado por seguimiento ocular
 *   Univerdidad veracruzana
 * 
 *  Arduino code for Robotic Arm Control with ESP32 microcontroller. 
 * Controls robot servomotors via serial commands and implements 
 * different positioning modes,  
 *  
 */
#include <ESP32Servo.h>

#define PIN_M0 15   //Servomotor Pin
#define PIN_M1 2    //Servomotor Pin
#define PIN_M2 4    //Servomotor Pin
#define PIN_M3 5    //Servomotor Pin
#define PIN_M4 18   //Servomotor Pin
#define PIN_M5 19   //Servomotor Pin
#define PIN_M6 21   //Servomotor Pin

#define minUs 500   // microseconds lower limit 
#define maxUs 2500  // microseconds upper limit 
#define minDeg 0
#define maxDeg 180

#define T_HOME_SPEED 8333  //delay time in microseconds to home movement (60Deg/s)
#define SPEED60 8333       //delay time in microseconds to movement at 60Deg/s 
#define SPEED30 16666      //delay time in microseconds to movement at 30Deg/s 
#define Step 0.5           //step to movement in deg

#define Home_Q0  90     //default home value       
#define Home_Q1  90     //default home value         
#define Home_Q2  90     //default home value    
#define Home_Q3  90     //default home value    
#define Home_Q4  90     //default home value   
#define Home_Q5  90     //default home value  
#define Home_Q6  160    //default home value  

enum ArmCtrlCodes{
    INSTANT_MOVEMENT,
    GRIPPER_MOVEMENT,
    PTP_MOVEMENT_30,
    PTP_MOVEMENT_60,
    COODINATED_MOVEMENT_30,
    COODINATED_MOVEMENT_60,
    GET_POSITION,
    SET_HOME,
    GO_HOME,
};


ESP32PWM pwm;

//servo objects definitions:
Servo servoM0;
Servo servoM1;
Servo servoM2;
Servo servoM3;
Servo servoM4;
Servo servoM5;
Servo servoM6;


byte Data_to_be_received[14];
byte dataToSend[15];
byte headFinder = 0;

float Home[7]={Home_Q0,Home_Q1,Home_Q2,Home_Q3,Home_Q4,Home_Q5,Home_Q6};
float AngAct[6]={Home_Q0,Home_Q1,Home_Q2,Home_Q3,Home_Q4,Home_Q5};
float Ang[6]={Home_Q0,Home_Q1,Home_Q2,Home_Q3,Home_Q4,Home_Q5};
int Gripper=Home_Q6;
boolean move=false;



void setSerialArray();       //set motor values to dataToSend array
void instant_Movement();     //move motors instantly
bool notValidPosition();     //verify new position, if its not valid, return true
void go_Home();              // set motors to home
void move_Gripper(int value);  //move gripper in percent values 
void Coordinado( int Twait);   //coordinated movement from AngAct array to Ang array
void puntopunto(int Twait);    //point to point movement from AngAct array to Ang array

void setup() {
   Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);

    // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  servoM0.setPeriodHertz(50);
  servoM1.setPeriodHertz(50);
  servoM2.setPeriodHertz(50);
  servoM3.setPeriodHertz(50);
  servoM4.setPeriodHertz(50);
  servoM5.setPeriodHertz(50);
  servoM6.setPeriodHertz(50);


  servoM0.attach(PIN_M0, minUs, maxUs);
  servoM1.attach(PIN_M1, minUs, maxUs);
  servoM2.attach(PIN_M2, minUs, maxUs);
  servoM3.attach(PIN_M3, minUs, maxUs);
  servoM4.attach(PIN_M4, minUs, maxUs);
  servoM5.attach(PIN_M5, minUs, maxUs);
  servoM6.attach(PIN_M6, minUs, maxUs);

  servoM0.write(Home_Q0);
  servoM1.write(Home_Q1);
  servoM2.write(Home_Q2);
  servoM3.write(Home_Q3);
  servoM4.write(Home_Q4);
  servoM5.write(Home_Q5);
  servoM6.write(Home_Q6);
}


// data array is recibed in byte format, this array contains  a controll value and 6 float values. 
// each float value is divided into two bytes, the first containing the whole value and the second containing the centesimal value.
//  array command structute:
//          [  253,ctl,Aux0_i,Aux0_f,Aux1_i,Aux1_f,Aux2_i,Aux2_f,Aux3_i,Aux3_f,Aux4_i,Aux4_f,Aux5_i,Aux5_f,254 ]

void loop() {

    if ( move==false && (Serial.available() > 0)) {
        headFinder = Serial.read(); 
        if (headFinder == 253) {
            Serial.readBytes(Data_to_be_received,14);         
            if (Data_to_be_received[13] == 254){                 

                int ctrl= Data_to_be_received[0];
                int aux[2];

                switch (ctrl){
                    case INSTANT_MOVEMENT:
                        for (int i=0;i<6;i++){
                            aux[0] = Data_to_be_received[(i*2)+1];    // get whole part
                            aux[1] = Data_to_be_received[(i*2)+2];    // get centesimal value
                            Ang[i] = aux[0]+(aux[1]*0.01);            // set float value.
                        } 
                        instant_Movement();  
                    break;

                    case GRIPPER_MOVEMENT: 
                        move_Gripper(constrain(Data_to_be_received[1], 0, 100));     //for gripper value is only used Aux0_i to get percent value
                    break;

                    case PTP_MOVEMENT_30:
                        for (int i=0;i<6;i++){
                            aux[0] = Data_to_be_received[(i*2)+1];
                            aux[1] = Data_to_be_received[(i*2)+2]; 
                            Ang[i] =  aux[0]+(aux[1]*0.01) ;  
                        }     
                        puntopunto(SPEED30); 
                    break;

                    case PTP_MOVEMENT_60:
                        for (int i=0;i<6;i++){
                            aux[0] = Data_to_be_received[(i*2)+1];
                            aux[1] = Data_to_be_received[(i*2)+2]; 
                            Ang[i] = aux[0]+(aux[1]*0.01) ;  
                        }   
                        puntopunto(SPEED60); 
                    break;

                    case COODINATED_MOVEMENT_30:
                        for (int i=0;i<6;i++){
                            aux[0] = Data_to_be_received[(i*2)+1];
                            aux[1] = Data_to_be_received[(i*2)+2]; 
                            Ang[i] = aux[0]+(aux[1]*0.01) ;  
                        }   
                        Coordinado(SPEED30); 
                    break;

                    case COODINATED_MOVEMENT_60:
                        for (int i=0;i<6;i++){
                            aux[0] = Data_to_be_received[(i*2)+1];
                            aux[1] = Data_to_be_received[(i*2)+2]; 
                            Ang[i] = aux[0]+(aux[1]*0.01) ;  
                        }  
                        Coordinado(SPEED60); 
                    break;

                    case GET_POSITION:
                        setSerialArray();
                        Serial.write(dataToSend,116);
                    break;

                    case SET_HOME:
                        for (int i=0;i<6;i++){
                            aux[0] = Data_to_be_received[(i*2)+1];
                            aux[1] = Data_to_be_received[(i*2)+2]; 
                            Home[i] = constrain((aux[0]+(aux[1]*0.01)), 0, 180);  
                        }   
                    break;

                    case GO_HOME:
                        go_Home();
                    break;

                    default:
                    break;
                }

            }
        }
    }

}

void setSerialArray(){
    dataToSend[0]=253;
    for(int i=0;i<6;i++){
        dataToSend[(i*2)+1]=(int)AngAct[i]; 
        dataToSend[(i*2)+2]=(int)( (AngAct[i]-dataToSend[(i*2)+1])*100 );
    } 
    dataToSend[15]=Gripper;
    dataToSend[16]=254; 
}


void instant_Movement(){

    if (notValidPosition())  return;  

    // if the movement is greater than 5 degrees for any motor, use the point-to-point movement.
    for(int i=0;i<6;i++){
        if (5<AngAct[i]-Ang[i]||-5>AngAct[i]-Ang[i]  ){ 
            puntopunto(SPEED60); 
            return;
        }
    }

        // update actual motor values 
        AngAct[0]=Ang[0];
        AngAct[1]=Ang[1];
        AngAct[2]=Ang[2];
        AngAct[3]=Ang[3];
        AngAct[4]=Ang[4];
        AngAct[5]=Ang[5];

        servoM0.writeMicroseconds(map(AngAct[0],minDeg,maxDeg,minUs,maxUs));
        servoM1.writeMicroseconds(map(AngAct[1],minDeg,maxDeg,minUs,maxUs));
        servoM2.writeMicroseconds(map(AngAct[2],minDeg,maxDeg,minUs,maxUs));
        servoM3.writeMicroseconds(map(AngAct[3],minDeg,maxDeg,minUs,maxUs));
        servoM4.writeMicroseconds(map(AngAct[4],minDeg,maxDeg,minUs,maxUs));
        servoM5.writeMicroseconds(map(AngAct[5],minDeg,maxDeg,minUs,maxUs));
 
}

bool notValidPosition(){
    if(0>Ang[0]  ||   Ang[0]>180) return true;
    if(0>Ang[1]  ||   Ang[1]>180) return true;
    int aux= Ang[2]-Ang[1]+73;
    if(0>aux     ||      aux>145) return true;
    if(0>Ang[3]  ||   Ang[3]>180) return true;
    if(0>Ang[4]  ||   Ang[4]>180) return true;
    if(0>Ang[5]  ||   Ang[5]>180) return true; 
    
    return false;
}

void go_Home(){

    for(int i=0;i<6;i++){
        Ang[i]=Home[i];
    }  
    Coordinado(T_HOME_SPEED);
}


void move_Gripper(int value){
   
    Gripper=map(value,0,100,180,115);
    servoM6.write(Gripper);
}


void Coordinado( int Twait){
    if (notValidPosition())  return; 

    move=true;

    float diferencia[7];
    float Saltos[7];
    float  Max;
    
    // get the position difference for each motor
    for (int i=0;i<6;i++){
        diferencia[i]=Ang[i]-AngAct[i];
    }
    
    // find de higest diference 
    if(diferencia[0]<0) Max=diferencia[0]*-1;  //get the absolute value of the differences
    else Max=diferencia[0];
    for (int i=1;i<6;i++){
        if(diferencia[i]<0){
            if(diferencia[i]*-1>Max) 
                Max=diferencia[i]*-1;    
        }else{
            if(diferencia[i]>Max)Max=diferencia[i];
        }
    }

    int Steps=Max/Step;                  //  steps required for the greatest movement
    for (int i=0;i<6;i++){             
        Saltos[i]= diferencia[i]/Steps;  //  size of steps for each motor. 
    }

    for (int i=1;i<=Steps;i++){
        
        servoM1.writeMicroseconds(map(AngAct[1]+(i*Saltos[1]),minDeg,maxDeg,minUs,maxUs));
        servoM2.writeMicroseconds(map(AngAct[2]+(i*Saltos[2]),minDeg,maxDeg,minUs,maxUs));
        servoM3.writeMicroseconds(map(AngAct[3]+(i*Saltos[3]),minDeg,maxDeg,minUs,maxUs));
        servoM0.writeMicroseconds(map(AngAct[0]+(i*Saltos[0]),minDeg,maxDeg,minUs,maxUs));
        servoM4.writeMicroseconds(map(AngAct[4]+(i*Saltos[4]),minDeg,maxDeg,minUs,maxUs));
        servoM5.writeMicroseconds(map(AngAct[5]+(i*Saltos[5]),minDeg,maxDeg,minUs,maxUs)); 
         delayMicroseconds(Twait);
    }

    servoM0.writeMicroseconds(map(Ang[0],minDeg,maxDeg,minUs,maxUs));
    servoM1.writeMicroseconds(map(Ang[1],minDeg,maxDeg,minUs,maxUs));
    servoM2.writeMicroseconds(map(Ang[2],minDeg,maxDeg,minUs,maxUs));
    servoM3.writeMicroseconds(map(Ang[3],minDeg,maxDeg,minUs,maxUs));
    servoM4.writeMicroseconds(map(Ang[4],minDeg,maxDeg,minUs,maxUs));
    servoM5.writeMicroseconds(map(Ang[5],minDeg,maxDeg,minUs,maxUs));

    AngAct[0]=Ang[0];
    AngAct[1]=Ang[1];
    AngAct[2]=Ang[2];
    AngAct[3]=Ang[3];
    AngAct[4]=Ang[4];
    AngAct[5]=Ang[5];

    move=false;
}


void puntopunto(int Twait){
    if (notValidPosition())  return; 

    move=true;
        bool bandera=true;
        while (bandera)
        {
            bandera=false;
            if(AngAct[0]-Ang[0]>Step){ 
                AngAct[0]-=Step;
                bandera=true;
                }
            if(Ang[0]-AngAct[0]>Step){ 
                AngAct[0]+=Step;
                bandera=true;
                }
            if(AngAct[1]-Ang[1]>Step){ 
                AngAct[1]-=Step;
                bandera=true;
                }
            if(Ang[1]-AngAct[1]>Step){ 
                AngAct[1]+=Step;
                bandera=true;
                }
            if(AngAct[2]-Ang[2]>Step){ 
                AngAct[2]-=Step;
                bandera=true;
                }
            if(Ang[2]-AngAct[2]>Step){ 
                AngAct[2]+=Step;
                bandera=true;
                }
            if(AngAct[3]-Ang[3]>Step){ 
                AngAct[3]-=Step;
                bandera=true;
                }
            if(Ang[3]-AngAct[3]>Step){ 
                AngAct[3]+=Step;
                bandera=true;
                }
            if(AngAct[4]-Ang[4]>Step){ 
                AngAct[4]-=Step;
                bandera=true;
                }
            if(Ang[4]-AngAct[4]>Step){ 
                AngAct[4]+=Step;
                bandera=true;
                }
            if(AngAct[5]-Ang[5]>Step){ 
                AngAct[5]-=Step;
                bandera=true;
                }
            if(Ang[5]-AngAct[5]>Step){ 
                AngAct[5]+=Step;
                bandera=true;
                }
        servoM0.writeMicroseconds(map(AngAct[0],minDeg,maxDeg,minUs,maxUs));
        servoM1.writeMicroseconds(map(AngAct[1],minDeg,maxDeg,minUs,maxUs));
        servoM2.writeMicroseconds(map(AngAct[2],minDeg,maxDeg,minUs,maxUs));
        servoM3.writeMicroseconds(map(AngAct[3],minDeg,maxDeg,minUs,maxUs));
        servoM4.writeMicroseconds(map(AngAct[4],minDeg,maxDeg,minUs,maxUs));
        servoM5.writeMicroseconds(map(AngAct[5],minDeg,maxDeg,minUs,maxUs));  
        delayMicroseconds(Twait);
        }

        servoM0.writeMicroseconds(map(Ang[0],minDeg,maxDeg,minUs,maxUs));
        servoM1.writeMicroseconds(map(Ang[1],minDeg,maxDeg,minUs,maxUs));
        servoM2.writeMicroseconds(map(Ang[2],minDeg,maxDeg,minUs,maxUs));
        servoM3.writeMicroseconds(map(Ang[3],minDeg,maxDeg,minUs,maxUs));
        servoM4.writeMicroseconds(map(Ang[4],minDeg,maxDeg,minUs,maxUs));
        servoM5.writeMicroseconds(map(Ang[5],minDeg,maxDeg,minUs,maxUs));

        AngAct[0]=Ang[0];
        AngAct[1]=Ang[1];
        AngAct[2]=Ang[2];
        AngAct[3]=Ang[3];
        AngAct[4]=Ang[4];
        AngAct[5]=Ang[5];

        move=false;   
}
