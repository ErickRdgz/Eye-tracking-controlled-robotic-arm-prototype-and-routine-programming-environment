#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QBitArray>
#include <vector>

#define MESSAGE_SIZE 9
using namespace std;

/** @brief The Arduino class.
 *  control comunication with microcontrollers.
 *  @author Erick A. Rodriguez Hernandez
 *  @date Febrary 2022
 */
class Arduino: public QSerialPort
{
public:

    Arduino();
    /** Arduino constructo. Inicializes Arduino with parameters
     */
    Arduino(QString port,int baudRate);
    /**
     * @brief arduinoConnected
     * connect serial port
     * @return true if its a succesful conecction
     */
    bool arduinoConected();
    /**
     * @brief arduinoDisconected
     * @return true if its disconnected
     */
    bool arduinoDisconected();
    /**
     * @brief writeMessage
     * send data structure by serial port.
     * @param data individual values
     * @return true if the data is sent succesfully
     */
    bool writeMessage(vector<int>& data);
    /**
     * @brief writeMessage
     * send data structure by serial port.
     * @param data individual values
     * @return true if the data is sent succesfully
     */
    bool writeMessage(vector<float>& data);
    /**
     * @brief newMessage
     * Get and decode serial data
     * @param data data container
     * @param size expected data size
     * @return true if the data is complete
     */
    bool newMessage(vector<int>& data, int size);

    /**
     * @brief isConnected
     * @return  return connnection status
     */
    bool isConnected();

    /**
     * @brief getPort
     * @return serial port
     */
    QString getPort(){
        return  this->port;
    }



private:
    bool status=false;
    QString port;
    int baudRate;
    vector<int> message={0,0,0,0,0,0,0,0,0,0};
//    int messageRecived[MESSAGE_SIZE];


};

#endif // ARDUINO_H
