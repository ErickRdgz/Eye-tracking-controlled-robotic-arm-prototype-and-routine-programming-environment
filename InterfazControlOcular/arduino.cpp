#include "arduino.h"
#include "QDebug"
#include "constants.h"
#include <QBitArray>

Arduino::Arduino()
{

}


Arduino::Arduino(QString port, int baudRate)
{
    this->port=port;
    this->baudRate=baudRate;
}

bool Arduino::arduinoConected()
{
    this->setPortName(this->port);
    if(this->baudRate==9600)
        this->setBaudRate(QSerialPort::Baud9600);
    if(this->baudRate==19200)
        this->setBaudRate(QSerialPort::Baud19200);
    if(this->baudRate==38400)
        this->setBaudRate(QSerialPort::Baud38400);
    if(this->baudRate==57600)
        this->setBaudRate(QSerialPort::Baud57600);
    if(this->baudRate==115200)
        this->setBaudRate(QSerialPort::Baud115200);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);

    if (this->open(QIODevice::ReadWrite)){
        this->status=true;
        return true;
    }else{
        this->status=false;
        return false;
    }
}

bool Arduino::arduinoDisconected()
{
    try {
        this->close();
        this->status=false;
        return true;
    } catch (...) {
        return false;
        this->status=true;
    }
}



bool Arduino::writeMessage(vector<float> &data)
{
//    qDebug()<<"escribiendo arduino";
//    qDebug()<<data;

    QByteArray messageBytes;
    messageBytes.append((char)253);
    messageBytes.append(data.at(0));
    for(size_t i=1;i<=DoF;i++){
        appendFloat2QBArray(messageBytes,data.at(i) );

    }
    messageBytes.append((char)254);

//    for(int i=0;i<messageBytes.size();i++){
//        qDebug()<<i<<" "<<(int)messageBytes.at(i);
//    }

    if(this->write(messageBytes)>0)
        return true;
    else return false;
}




bool Arduino::newMessage(vector<int>& data, int size)
{
    QByteArray aux;
    if(this->bytesAvailable()){
        aux=this->read(1);
        if(aux.size()!=1)
            return false;

        this->message.at(9)=this->message.at(8);
        this->message.at(8)=this->message.at(7);
        this->message.at(7)=this->message.at(6);
        this->message.at(6)=this->message.at(5);
        this->message.at(5)=this->message.at(4);
        this->message.at(4)=this->message.at(3);
        this->message.at(3)=this->message.at(2);
        this->message.at(2)=this->message.at(1);
        this->message.at(1)=this->message.at(0);
        this->message.at(0)=(aux.at(0) & 0xFF);

       if(this->message.at(0)==253 && this->message.at(9)==254){
       data=this->message;
       this->message={0,0,0,0,0,0,0,0,0,0};
       return true;
       }

    }
    return false;
}

bool Arduino::isConnected()
{
    return this->status;
}

void Arduino::appendFloat2QBArray(QByteArray &array, const float value)
{
    int aux =(int)value;
    array.append(aux);
    aux=(int)((value-aux)*100 ) ;
    array.append(aux);
}
