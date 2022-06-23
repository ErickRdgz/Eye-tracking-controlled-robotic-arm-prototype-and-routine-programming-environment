#ifndef INTERFAZESTANDAR_H
#define INTERFAZESTANDAR_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QTableWidget>
#include <QMessageBox>
#include <QDir>
#include <QLabel>
#include "revolutearm.h"
#include "lista.h"

enum PointListTitles{
    NAME,
    TabX,
    TabY,
    TabZ,
    TabROW,
    TabPITCH,
    TabYAW,
    TabGRIPPER
};

QT_BEGIN_NAMESPACE
namespace Ui { class InterfazEstandar; }
QT_END_NAMESPACE

class InterfazEstandar : public QMainWindow
{
    Q_OBJECT

public slots:
    void moveArm(std::vector <float> msg);
    void responseSetArmToHome();
    void responseSetArmPosition(std::vector <float> msg);

public:
    InterfazEstandar(QWidget *parent = nullptr);
    ~InterfazEstandar();

private:
    Ui::InterfazEstandar *ui;

    RevoluteArm *arm;
//    vector <float> nextAngles={ZEROS};//{90,90,90,90,90,90};
//    vector <float> nextRecPosition={ZEROS};//{0,0,0,0,0,0};

    Lista<Point> *pointList;
    Lista<Point> *programList;
    Lista<Command> *CommandList;
    QTimer *serialDataFinder;
    QLabel *permanentMgs;

    //file manager
    QString pointsFileName="";
    QString programFileName="";
    QString commandFileName="";
    bool pointsFileOpen=false;
    bool programFileOpen=false;
    bool commandFileOpen=false;
    QDir filesPath;

    //###############################################################
    // interfazestandar.cpp
    void initSettings();
    void setSettings();
    void newArduinoMessage();
    void setArmInPoint(QTableWidget *table);
//    void setArmInPoint();


    //###############################################################
    // interfazestandar_points.cpp
    void initPointPage();
    void enablePointPage(bool enable);

    void updateAngularValues();
    void updateRectangularValues();
    void rectangularArmMovement();
    void angularArmMovement();
    void setGripperPosition();

    void addPointToList();
    void deletPoint();
    void clearPointList();

    void savePointList();
    void loadPointList();

    //###############################################################
    // interfazestandar_program.cpp

    void initProgramPage();
    void enableProgramPage(bool enable);

    void saveProgramList();
    void loadProgramList();

    void generateCommands();
    void saveCommandList(QString path);

    void pushPointToProgramList();
    void pushGripperToProgramList();
    void pushDelayToProgramList();
//    void pushGripperToProgram();
    void moveProgramItemUp();
    void moveProgramItemDown();
    void removeFromProgramList();
    void clearProgramList();
    void updateProgramListFile(QString path);
    void setToProgramTable(int Index,Point item);

};

#endif // INTERFAZESTANDAR_H
