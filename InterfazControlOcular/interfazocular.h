#ifndef INTERFAZOCULAR_H
#define INTERFAZOCULAR_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QDir>
#include <QTimer>
#include <QFile>
#include "armvideo.h"
#include "eyetracking.h"
#include "lista.h"
#include "revolutearm.h"
#include <QSound>


#define DATA_SIZE 8

QT_BEGIN_NAMESPACE
namespace Ui { class InterfazOcular; }
QT_END_NAMESPACE
class EyeTracking;
class ArmVideo;


enum Basic_Options{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    FORWARD,
    BACKWARD,
    OPEN_GRIPPER,
    CLOSE_GRIPPER
};

typedef enum Direction{
    POSITIVE,
    NEGATIVE
}direction_t;


#define MAX_BASIC_OPTION_NUMBER 7
#define DEFAULT_SELECTED_OPTION_NUMBER 4
#define TEXT_UP               "Subir"
#define TEXT_DOWN             "Bajar"
#define TEXT_RIGHT            "Derecha"
#define TEXT_LEFT             "Izquierda"
#define TEXT_FORWARD          "Adelante"
#define TEXT_BACKWARD         "Atras"
#define TEXT_OPEN_GRIPPER     "Abrir Gripper"
#define TEXT_CLOSE_GRIPPER    "Cerrar Gripper"
#define DEFAULT_MOVEMENT    Movements::COORDINATED
#define DEFAULT_GRIPPER_STEP 10
#define MAX_GRIPPER_VAL 100
#define MIN_GRIPPER_VAL 0




class InterfazOcular : public QMainWindow
{
    Q_OBJECT

public slots:
    void moveArm(std::vector <float> msg);

public:
    InterfazOcular(QWidget *parent = nullptr);
    ~InterfazOcular();

private:
    Ui::InterfazOcular *ui;

    QSound *UpSound;
    QSound *RightSound;
    QSound *LeftSound;

    RevoluteArm *arm;
    ArmVideo *armVideo;
    EyeTracking *eyeTrackingVideo;

    Lista <Command> *CommandList;
    std::vector <float> nextRecPosition{ZEROS};

    QDir *filesDirectory;
    QVector <QString> Options;
    int menuPosition=DEFAULT_SELECTED_OPTION_NUMBER;
    int armSpeed;
    float armStep;
    int gripperVal=0;
    float detectionTime;
    bool RunningSequence=false;

    void ExecuteSelection();
    void ExecuteFile();

    void initSettings();
    void setSettings();

    bool serialConection(bool status);
    void singleMovement(int axis, direction_t direction );

    void updateDisplayedValues();
    void loadMenuList();
    void updateMenu();
    void initStyleObjects();
    void ClearOptionStyle   (QLabel *label);
    void NormalOptionStyle  (QLabel *label);

};
#endif // INTERFAZOCULAR_H
