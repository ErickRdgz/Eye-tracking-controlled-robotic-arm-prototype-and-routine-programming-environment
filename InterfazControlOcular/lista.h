#ifndef LISTA_H
#define LISTA_H
#include <QString>
#include "constants.h"
enum ExceptionCodes{
    LISTA_VACIA,
    POSICION_INVALIDA,
    ERROR_MEMORIA,
    NO_EXISTE,
    DESCONOCIDO
};

/**
 * @brief The ListException class
 * controls list class exceptions
 */
class ListException: public std::exception
{
private:
    std::string mensaje;

public:
    ListException(int codigo){
        switch (codigo) {
        case LISTA_VACIA:
            this->mensaje="Error, la lista se encuentra vacia!";
            break;
        case POSICION_INVALIDA:
             this->mensaje="Error, la posicion proporcionada es invalida";
            break;
        case ERROR_MEMORIA:
            this->mensaje="Error, no se ha podido reservar memoria";
            break;
        case NO_EXISTE:
            this->mensaje="Error,  Ese elemento no existe";
            break;
        default:
            this->mensaje="Error de operacion desconocido";
            break;
        }
    }
    const char * what() const throw(){
        return this->mensaje.c_str();
    }
};


//#########################################################################################
//#########################################################################################
//#########################################################################################
//#########################################################################################


template <typename D>
/**
 * @brief The Nodo class
 * Helper class to store data in Lista
 */
class Nodo
{
private:
//    char dato[STRING_CHARACTERS];
    D dato;
    Nodo* next;
public:
    Nodo();
    Nodo(D dato, Nodo<D>* next);

    D getDato(){
        return this->dato;
    }
    void setDato(D dato ){
        this->dato=dato;
    }

    Nodo *getNext(){
        return this->next;
    }

    void setNext(Nodo* next){
        this->next=next;
    }
};


//#########################################################################################
//#########################################################################################
//#########################################################################################
//#########################################################################################


template <typename D>
/**
 * @brief The Lista class
 * Store data with dynamic memory, useful to LIFO and FIFO
 */
class Lista
{
private:
    int size;
    Nodo<D>* head;

    Nodo<D>* getHead();
    void  setHead(Nodo<D>* head);
    Nodo<D>* point_at(int position);
    Nodo<D>* getPointerBack();

public:
    Lista();

    void push_front(D dato);
    bool pop_front();

    void clear();
    bool empty();
    int getSize();

    bool push_back(D data);
    bool pop_back();
    bool insert(D data, int position);
    bool errase(int position);
    bool repleace(D newData,int position);

    D front();
    D back();
    D at(int position);
    D getItem(QString  data,bool (*Search)(D,QString ));

    void PrintList(QString(*imprimeElemento)(D));
};



//#########################################################################################
//#########################################################################################
//#########################################################################################
//#########################################################################################

/**
 * @brief The Point class
 * Store data to points and program commands
 */
class Point{
private:
    int ctrl=0;
    int speed=0;
    QString name;
    float R0;
    float R1;
    float R2;
    float R3;
    float R4;
    float R5;
    float A0;
    float A1;
    float A2;
    float A3;
    float A4;
    float A5;

public:
    Point(){
    }

    void setAsCommand(int ctrl, int data){
        this->ctrl=ctrl;
        this->speed=data;
        this->R0=0;
        this->R1=0;
        this->R2=0;
        this->R3=0;
        this->R4=0;
        this->R5=0;
        this->A0=0;
        this->A1=0;
        this->A2=0;
        this->A3=0;
        this->A4=0;
        this->A5=0;
    }

    void setAll(Point point){
        this->ctrl=point.ctrl;
        this->speed=point.speed;
        this->name= point.name;
        this->R0=point.R0;
        this->R1=point.R1;
        this->R2=point.R2;
        this->R3=point.R3;
        this->R4=point.R4;
        this->R5=point.R5;
        this->A0=point.A0;
        this->A1=point.A1;
        this->A2=point.A2;
        this->A3=point.A3;
        this->A4=point.A4;
        this->A5=point.A5;
    }
    int getCtrl(){
        return  this->ctrl;
    }
    void setCtrl(int ctrl){
        this->ctrl=ctrl;
    }
    int getSpeed(){
        return  this->speed;
    }
    void setSpeed(int speed){
        this->speed=speed;
    }
    void setName(QString name){
        this->name=name;
    }
    void setRectangular( float R0, float R1,float R2,float R3,float R4,float R5){
                        this->R0=R0;
                        this->R1=R1;
                        this->R2=R2;
                        this->R3=R3;
                        this->R4=R4;
                        this->R5=R5;
    }

    void setAngular( float A0, float A1,float A2,float A3,float A4,float A5){
        this->A0=A0;
        this->A1=A1;
        this->A2=A2;
        this->A3=A3;
        this->A4=A4;
        this->A5=A5;
    }

    void setGripper(float val){
        this->R0=0;
        this->R1=0;
        this->R2=0;
        this->A0=val;
    }

    float getRectangular(int at){
        switch (at) {
        case 0:
            return this->R0;
            break;
        case 1:
            return this->R1;
            break;
        case 2:
            return this->R2;
            break;
        case 3:
            return this->R3;
            break;
        case 4:
            return this->R4;
            break;
        case 5:
            return this->R5;
            break;
        default:
            throw ListException(ExceptionCodes::NO_EXISTE);
        }
    }

    float getAngular(int at){
        switch (at) {
        case 0:
            return this->A0;
            break;
        case 1:
            return this->A1;
            break;
        case 2:
            return this->A2;
            break;
        case 3:
            return this->A3;
            break;
        case 4:
            return this->A4;
            break;
        case 5:
            return this->A5;
            break;
        default:
            throw ListException(ExceptionCodes::NO_EXISTE);
        }
    }

    QString getName(){
        return  this->name;
    }

    static bool sameName(Point P1, QString P2){
        if(P1.getName()==P2)
            return true;
        return false;
    }

    static QString printPoint(Point p){
             QString print;
             print+=QString::number(p.getCtrl());
             print+="||";
             print+=QString::number(p.getSpeed());
             print+="||";
             print+=p.getName();
             print+="||";
             print+=QString::number(p.getRectangular(0));
             print+="||";
             print+=QString::number(p.getRectangular(1));
             print+="||";
             print+=QString::number(p.getRectangular(2));
             print+="||";
             print+=QString::number(p.getRectangular(3));
             print+="||";
             print+=QString::number(p.getRectangular(4));
             print+="||";
             print+=QString::number(p.getRectangular(5));
             print+="||";
             print+=QString::number(p.getAngular(0));
             print+="||";
             print+=QString::number(p.getAngular(1));
             print+="||";
             print+=QString::number(p.getAngular(2));
             print+="||";
             print+=QString::number(p.getAngular(3));
             print+="||";
             print+=QString::number(p.getAngular(4));
             print+="||";
             print+=QString::number(p.getAngular(5));
             return print;
    }



    static QString printSequencePoint(Point p){
     QString print;

     if(p.getCtrl()==CommandCodes::COMMAND_PtP ||p.getCtrl()==CommandCodes::COMMAND_COORDINATED){
         if(p.getCtrl()==CommandCodes::COMMAND_PtP)
             print+="Movimiento Punto a punto";
         else
             print+="Movimiento Coordinado   ";

         print+=" (";
         print+=QString::number(p.getRectangular(0));
         print+=" , ";
         print+=QString::number(p.getRectangular(1));
         print+=" , ";
         print+=QString::number(p.getRectangular(2));
         print+=" , ";
         print+=QString::number(p.getRectangular(3));
         print+=" , ";
         print+=QString::number(p.getRectangular(4));
         print+=" , ";
         print+=QString::number(p.getRectangular(5));
         print+=" )";
     }

     else if(p.getCtrl()==CommandCodes::COMMAND_SLEEP ||p.getCtrl()==CommandCodes::COMMAND_GRIPPER){
         if(p.getCtrl()==CommandCodes::COMMAND_SLEEP)
             print+="Delay ";
         else
             print+="Gripper ";
         print+=" (";
         print+=QString::number(p.getSpeed());
         print+=" )";
     }
     else
         print+="-----";
     return print;
    }
};


/**
 * @brief The Command class
 * Stores Sequencer commands
 */
class Command{
private:
    int Ctrl=0;
    float Q0=0;
    float Q1=0;
    float Q2=0;
    float Q3=0;
    float Q4=0;
    float Q5=0;
    float Q6=0;
public:
    Command(){   }

    void setValues(int Ctrl,int Q0,int Q1,int Q2,int Q3, int Q4,int Q5,int Q6){
        this->Ctrl  =Ctrl;
        this->Q0    =Q0;
        this->Q1    =Q1;
        this->Q2    =Q2;
        this->Q3    =Q3;
        this->Q4    =Q4;
        this->Q5    =Q5;
        this->Q6    =Q6;
    }

    int getAngle(int at){
        switch (at) {
        case 0:
            return this->Q0;
            break;
        case 1:
            return this->Q1;
            break;
        case 2:
            return this->Q2;
            break;
        case 3:
            return this->Q3;
            break;
        case 4:
            return this->Q4;
            break;
        case 5:
            return this->Q5;
            break;
        case 6:
            return this->Q6;
            break;
        default:
            return -1;
        }
    }

    int getCtrl(){
        return  this->Ctrl;
    }

    static QString printCommand(Command c){
     QString print;
     print+=QString::number(c.getCtrl());
     print+="||";
     print+=QString::number(c.getAngle(0));
     print+="||";
     print+=QString::number(c.getAngle(1));
     print+="||";
     print+=QString::number(c.getAngle(2));
     print+="||";
     print+=QString::number(c.getAngle(3));
     print+="||";
     print+=QString::number(c.getAngle(4));
     print+="||";
     print+=QString::number(c.getAngle(5));
     print+="||";
     print+=QString::number(c.getAngle(6));
     return print;
    }

};



#endif // LISTA_H
