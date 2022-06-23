/********************************************************************************
** Form generated from reading UI file 'interfazestandar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFAZESTANDAR_H
#define UI_INTERFAZESTANDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfazEstandar
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_4;
    QTableWidget *PointList;
    QPushButton *Btn_GoPoint;
    QPushButton *Btn_SavePointList;
    QPushButton *Btn_CleanPointList;
    QPushButton *Btn_ListPoint;
    QPushButton *Btn_DeletPoint;
    QPushButton *Btn_LoadPointList;
    QLabel *label_14;
    QLineEdit *in_PointName;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *CBox_Movement;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_23;
    QSpinBox *SBox_Speed;
    QPushButton *Btn_GoHome;
    QGroupBox *groupBox;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_5;
    QDoubleSpinBox *in_X;
    QDoubleSpinBox *in_Y;
    QDoubleSpinBox *in_Z;
    QDoubleSpinBox *in_Row;
    QDoubleSpinBox *in_Pitch;
    QDoubleSpinBox *in_Yaw;
    QPushButton *Btn_RecMovement;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout;
    QSlider *Slider_Gripper;
    QPushButton *Btn_Gripper;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget_4;
    QGridLayout *gridLayout_2;
    QSlider *Slider_Q1;
    QSlider *Slider_Q2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_11;
    QDoubleSpinBox *in_Q1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QDoubleSpinBox *in_Q2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSlider *Slider_Q3;
    QSlider *Slider_Q4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QDoubleSpinBox *in_Q3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QDoubleSpinBox *in_Q4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QSlider *Slider_Q5;
    QSlider *Slider_Q6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QDoubleSpinBox *in_Q5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QDoubleSpinBox *in_Q6;
    QPushButton *Btn_AngMovement;
    QWidget *tab_2;
    QTableWidget *PointList_2;
    QTableWidget *SequenceList;
    QGroupBox *fileManager;
    QPushButton *Btn_SaveSequenceList;
    QPushButton *Btn_CommandCtrl;
    QPushButton *Btn_LoadSequenceList;
    QPushButton *Btn_LoadPointList_2;
    QGroupBox *groupBox_7;
    QPushButton *Btn_GoPoint_2;
    QSpinBox *in_Gripper_2;
    QLabel *label_18;
    QPushButton *Btn_pushGripperToSequence;
    QPushButton *Btn_pushPointToSequence;
    QLabel *label_19;
    QPushButton *Btn_pushDelayToSequence;
    QSpinBox *in_Delay;
    QComboBox *CBox_Movement_2;
    QLabel *label_20;
    QPushButton *Btn_ClearSequenceList;
    QLabel *label_21;
    QSpinBox *SBox_Speed_2;
    QPushButton *Btn_RemoveFromSequence;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *Btn_MoveUp;
    QPushButton *Btn_MoveDown;
    QPushButton *Btn_Settings;
    QPushButton *Btn_SerialConnect;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InterfazEstandar)
    {
        if (InterfazEstandar->objectName().isEmpty())
            InterfazEstandar->setObjectName(QString::fromUtf8("InterfazEstandar"));
        InterfazEstandar->resize(874, 668);
        centralwidget = new QWidget(InterfazEstandar);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 70, 855, 571));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(380, 0, 451, 531));
        QFont font;
        font.setPointSize(10);
        groupBox_4->setFont(font);
        PointList = new QTableWidget(groupBox_4);
        PointList->setObjectName(QString::fromUtf8("PointList"));
        PointList->setEnabled(true);
        PointList->setGeometry(QRect(10, 110, 433, 411));
        Btn_GoPoint = new QPushButton(groupBox_4);
        Btn_GoPoint->setObjectName(QString::fromUtf8("Btn_GoPoint"));
        Btn_GoPoint->setGeometry(QRect(10, 30, 81, 71));
        Btn_SavePointList = new QPushButton(groupBox_4);
        Btn_SavePointList->setObjectName(QString::fromUtf8("Btn_SavePointList"));
        Btn_SavePointList->setGeometry(QRect(350, 60, 91, 41));
        Btn_CleanPointList = new QPushButton(groupBox_4);
        Btn_CleanPointList->setObjectName(QString::fromUtf8("Btn_CleanPointList"));
        Btn_CleanPointList->setGeometry(QRect(240, 70, 91, 21));
        Btn_ListPoint = new QPushButton(groupBox_4);
        Btn_ListPoint->setObjectName(QString::fromUtf8("Btn_ListPoint"));
        Btn_ListPoint->setGeometry(QRect(110, 30, 111, 23));
        Btn_DeletPoint = new QPushButton(groupBox_4);
        Btn_DeletPoint->setObjectName(QString::fromUtf8("Btn_DeletPoint"));
        Btn_DeletPoint->setGeometry(QRect(240, 40, 91, 23));
        Btn_LoadPointList = new QPushButton(groupBox_4);
        Btn_LoadPointList->setObjectName(QString::fromUtf8("Btn_LoadPointList"));
        Btn_LoadPointList->setGeometry(QRect(350, 30, 91, 23));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(111, 63, 50, 16));
        in_PointName = new QLineEdit(groupBox_4);
        in_PointName->setObjectName(QString::fromUtf8("in_PointName"));
        in_PointName->setGeometry(QRect(111, 79, 109, 21));
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 1, 341, 60));
        groupBox_5->setFont(font);
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(22, 10, 301, 51));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        CBox_Movement = new QComboBox(layoutWidget);
        CBox_Movement->setObjectName(QString::fromUtf8("CBox_Movement"));
        CBox_Movement->setMinimumSize(QSize(100, 0));
        CBox_Movement->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(CBox_Movement);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_23 = new QLabel(layoutWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_8->addWidget(label_23);

        SBox_Speed = new QSpinBox(layoutWidget);
        SBox_Speed->setObjectName(QString::fromUtf8("SBox_Speed"));
        SBox_Speed->setMinimum(1);
        SBox_Speed->setMaximum(120);
        SBox_Speed->setValue(50);

        horizontalLayout_8->addWidget(SBox_Speed);


        horizontalLayout_9->addLayout(horizontalLayout_8);

        Btn_GoHome = new QPushButton(layoutWidget);
        Btn_GoHome->setObjectName(QString::fromUtf8("Btn_GoHome"));
        Btn_GoHome->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_9->addWidget(Btn_GoHome);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 62, 340, 151));
        groupBox->setMinimumSize(QSize(340, 130));
        groupBox->setFont(font);
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(-10, 20, 301, 89));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(80, 16777215));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 0, 2, 1, 1, Qt::AlignRight);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(80, 16777215));
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 1, 0, 1, 1, Qt::AlignRight);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(80, 16777215));
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1, Qt::AlignRight);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(80, 16777215));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 2, 0, 1, 1, Qt::AlignRight);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(80, 16777215));
        label_6->setFont(font1);

        gridLayout->addWidget(label_6, 2, 2, 1, 1, Qt::AlignRight);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(80, 16777215));
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 1, 2, 1, 1, Qt::AlignRight);

        in_X = new QDoubleSpinBox(layoutWidget_2);
        in_X->setObjectName(QString::fromUtf8("in_X"));
        QFont font2;
        font2.setPointSize(11);
        in_X->setFont(font2);
        in_X->setMinimum(-40.000000000000000);
        in_X->setMaximum(40.000000000000000);

        gridLayout->addWidget(in_X, 0, 1, 1, 1);

        in_Y = new QDoubleSpinBox(layoutWidget_2);
        in_Y->setObjectName(QString::fromUtf8("in_Y"));
        in_Y->setFont(font2);
        in_Y->setMinimum(-40.000000000000000);
        in_Y->setMaximum(40.000000000000000);

        gridLayout->addWidget(in_Y, 1, 1, 1, 1);

        in_Z = new QDoubleSpinBox(layoutWidget_2);
        in_Z->setObjectName(QString::fromUtf8("in_Z"));
        in_Z->setFont(font2);
        in_Z->setMinimum(-2.000000000000000);
        in_Z->setMaximum(40.000000000000000);

        gridLayout->addWidget(in_Z, 2, 1, 1, 1);

        in_Row = new QDoubleSpinBox(layoutWidget_2);
        in_Row->setObjectName(QString::fromUtf8("in_Row"));
        in_Row->setFont(font2);
        in_Row->setMinimum(-270.000000000000000);
        in_Row->setMaximum(270.000000000000000);

        gridLayout->addWidget(in_Row, 0, 3, 1, 1);

        in_Pitch = new QDoubleSpinBox(layoutWidget_2);
        in_Pitch->setObjectName(QString::fromUtf8("in_Pitch"));
        in_Pitch->setFont(font2);
        in_Pitch->setMinimum(-270.000000000000000);
        in_Pitch->setMaximum(270.000000000000000);

        gridLayout->addWidget(in_Pitch, 1, 3, 1, 1);

        in_Yaw = new QDoubleSpinBox(layoutWidget_2);
        in_Yaw->setObjectName(QString::fromUtf8("in_Yaw"));
        in_Yaw->setFont(font2);
        in_Yaw->setMinimum(-360.000000000000000);
        in_Yaw->setMaximum(360.000000000000000);

        gridLayout->addWidget(in_Yaw, 2, 3, 1, 1);

        Btn_RecMovement = new QPushButton(groupBox);
        Btn_RecMovement->setObjectName(QString::fromUtf8("Btn_RecMovement"));
        Btn_RecMovement->setGeometry(QRect(100, 120, 141, 23));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 213, 340, 65));
        groupBox_2->setMinimumSize(QSize(340, 65));
        groupBox_2->setFont(font);
        layoutWidget_3 = new QWidget(groupBox_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(20, 20, 301, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Slider_Gripper = new QSlider(layoutWidget_3);
        Slider_Gripper->setObjectName(QString::fromUtf8("Slider_Gripper"));
        Slider_Gripper->setMaximum(100);
        Slider_Gripper->setTracking(true);
        Slider_Gripper->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(Slider_Gripper);

        Btn_Gripper = new QPushButton(layoutWidget_3);
        Btn_Gripper->setObjectName(QString::fromUtf8("Btn_Gripper"));

        horizontalLayout->addWidget(Btn_Gripper);

        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 280, 340, 251));
        groupBox_3->setMinimumSize(QSize(340, 200));
        groupBox_3->setFont(font);
        layoutWidget_4 = new QWidget(groupBox_3);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 20, 301, 191));
        gridLayout_2 = new QGridLayout(layoutWidget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Slider_Q1 = new QSlider(layoutWidget_4);
        Slider_Q1->setObjectName(QString::fromUtf8("Slider_Q1"));
        Slider_Q1->setMaximum(180);
        Slider_Q1->setTracking(true);
        Slider_Q1->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Slider_Q1, 0, 0, 1, 1);

        Slider_Q2 = new QSlider(layoutWidget_4);
        Slider_Q2->setObjectName(QString::fromUtf8("Slider_Q2"));
        Slider_Q2->setMaximum(180);
        Slider_Q2->setTracking(true);
        Slider_Q2->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Slider_Q2, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_11 = new QLabel(layoutWidget_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font1);

        horizontalLayout_2->addWidget(label_11);

        in_Q1 = new QDoubleSpinBox(layoutWidget_4);
        in_Q1->setObjectName(QString::fromUtf8("in_Q1"));
        in_Q1->setFont(font2);
        in_Q1->setKeyboardTracking(true);
        in_Q1->setDecimals(1);
        in_Q1->setMaximum(180.000000000000000);

        horizontalLayout_2->addWidget(in_Q1);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_12 = new QLabel(layoutWidget_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        horizontalLayout_5->addWidget(label_12, 0, Qt::AlignRight);

        in_Q2 = new QDoubleSpinBox(layoutWidget_4);
        in_Q2->setObjectName(QString::fromUtf8("in_Q2"));
        in_Q2->setFont(font2);
        in_Q2->setDecimals(1);
        in_Q2->setMaximum(180.000000000000000);

        horizontalLayout_5->addWidget(in_Q2);


        gridLayout_2->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);

        Slider_Q3 = new QSlider(layoutWidget_4);
        Slider_Q3->setObjectName(QString::fromUtf8("Slider_Q3"));
        Slider_Q3->setMaximum(180);
        Slider_Q3->setTracking(true);
        Slider_Q3->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Slider_Q3, 3, 0, 1, 1);

        Slider_Q4 = new QSlider(layoutWidget_4);
        Slider_Q4->setObjectName(QString::fromUtf8("Slider_Q4"));
        Slider_Q4->setMaximum(180);
        Slider_Q4->setTracking(true);
        Slider_Q4->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Slider_Q4, 3, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(layoutWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);

        horizontalLayout_3->addWidget(label_8, 0, Qt::AlignRight);

        in_Q3 = new QDoubleSpinBox(layoutWidget_4);
        in_Q3->setObjectName(QString::fromUtf8("in_Q3"));
        in_Q3->setFont(font2);
        in_Q3->setDecimals(1);
        in_Q3->setMaximum(180.000000000000000);

        horizontalLayout_3->addWidget(in_Q3);


        gridLayout_2->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_9 = new QLabel(layoutWidget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);

        horizontalLayout_6->addWidget(label_9, 0, Qt::AlignRight);

        in_Q4 = new QDoubleSpinBox(layoutWidget_4);
        in_Q4->setObjectName(QString::fromUtf8("in_Q4"));
        in_Q4->setFont(font2);
        in_Q4->setDecimals(1);
        in_Q4->setMaximum(180.000000000000000);

        horizontalLayout_6->addWidget(in_Q4);


        gridLayout_2->addLayout(horizontalLayout_6, 4, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 5, 1, 1, 1);

        Slider_Q5 = new QSlider(layoutWidget_4);
        Slider_Q5->setObjectName(QString::fromUtf8("Slider_Q5"));
        Slider_Q5->setMaximum(180);
        Slider_Q5->setTracking(true);
        Slider_Q5->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Slider_Q5, 6, 0, 1, 1);

        Slider_Q6 = new QSlider(layoutWidget_4);
        Slider_Q6->setObjectName(QString::fromUtf8("Slider_Q6"));
        Slider_Q6->setMaximum(180);
        Slider_Q6->setTracking(true);
        Slider_Q6->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(Slider_Q6, 6, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(layoutWidget_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        horizontalLayout_4->addWidget(label_7, 0, Qt::AlignRight);

        in_Q5 = new QDoubleSpinBox(layoutWidget_4);
        in_Q5->setObjectName(QString::fromUtf8("in_Q5"));
        in_Q5->setFont(font2);
        in_Q5->setDecimals(1);
        in_Q5->setMaximum(180.000000000000000);

        horizontalLayout_4->addWidget(in_Q5);


        gridLayout_2->addLayout(horizontalLayout_4, 7, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_10 = new QLabel(layoutWidget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        horizontalLayout_7->addWidget(label_10, 0, Qt::AlignRight);

        in_Q6 = new QDoubleSpinBox(layoutWidget_4);
        in_Q6->setObjectName(QString::fromUtf8("in_Q6"));
        in_Q6->setFont(font2);
        in_Q6->setDecimals(1);
        in_Q6->setMaximum(180.000000000000000);

        horizontalLayout_7->addWidget(in_Q6);


        gridLayout_2->addLayout(horizontalLayout_7, 7, 1, 1, 1);

        Btn_AngMovement = new QPushButton(groupBox_3);
        Btn_AngMovement->setObjectName(QString::fromUtf8("Btn_AngMovement"));
        Btn_AngMovement->setGeometry(QRect(100, 220, 141, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        PointList_2 = new QTableWidget(tab_2);
        PointList_2->setObjectName(QString::fromUtf8("PointList_2"));
        PointList_2->setGeometry(QRect(10, 110, 331, 371));
        SequenceList = new QTableWidget(tab_2);
        SequenceList->setObjectName(QString::fromUtf8("SequenceList"));
        SequenceList->setGeometry(QRect(589, 110, 250, 371));
        fileManager = new QGroupBox(tab_2);
        fileManager->setObjectName(QString::fromUtf8("fileManager"));
        fileManager->setGeometry(QRect(190, 30, 491, 71));
        Btn_SaveSequenceList = new QPushButton(fileManager);
        Btn_SaveSequenceList->setObjectName(QString::fromUtf8("Btn_SaveSequenceList"));
        Btn_SaveSequenceList->setGeometry(QRect(370, 20, 111, 41));
        Btn_CommandCtrl = new QPushButton(fileManager);
        Btn_CommandCtrl->setObjectName(QString::fromUtf8("Btn_CommandCtrl"));
        Btn_CommandCtrl->setGeometry(QRect(130, 20, 111, 41));
        Btn_LoadSequenceList = new QPushButton(fileManager);
        Btn_LoadSequenceList->setObjectName(QString::fromUtf8("Btn_LoadSequenceList"));
        Btn_LoadSequenceList->setGeometry(QRect(250, 20, 111, 41));
        Btn_LoadPointList_2 = new QPushButton(fileManager);
        Btn_LoadPointList_2->setObjectName(QString::fromUtf8("Btn_LoadPointList_2"));
        Btn_LoadPointList_2->setGeometry(QRect(10, 20, 111, 41));
        groupBox_7 = new QGroupBox(tab_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(360, 112, 211, 361));
        Btn_GoPoint_2 = new QPushButton(groupBox_7);
        Btn_GoPoint_2->setObjectName(QString::fromUtf8("Btn_GoPoint_2"));
        Btn_GoPoint_2->setGeometry(QRect(20, 100, 75, 31));
        in_Gripper_2 = new QSpinBox(groupBox_7);
        in_Gripper_2->setObjectName(QString::fromUtf8("in_Gripper_2"));
        in_Gripper_2->setGeometry(QRect(22, 154, 71, 22));
        in_Gripper_2->setMaximum(100);
        in_Gripper_2->setValue(50);
        label_18 = new QLabel(groupBox_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(22, 140, 47, 13));
        Btn_pushGripperToSequence = new QPushButton(groupBox_7);
        Btn_pushGripperToSequence->setObjectName(QString::fromUtf8("Btn_pushGripperToSequence"));
        Btn_pushGripperToSequence->setGeometry(QRect(100, 142, 90, 35));
        Btn_pushPointToSequence = new QPushButton(groupBox_7);
        Btn_pushPointToSequence->setObjectName(QString::fromUtf8("Btn_pushPointToSequence"));
        Btn_pushPointToSequence->setGeometry(QRect(100, 100, 90, 35));
        label_19 = new QLabel(groupBox_7);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 186, 47, 13));
        Btn_pushDelayToSequence = new QPushButton(groupBox_7);
        Btn_pushDelayToSequence->setObjectName(QString::fromUtf8("Btn_pushDelayToSequence"));
        Btn_pushDelayToSequence->setGeometry(QRect(100, 188, 90, 35));
        in_Delay = new QSpinBox(groupBox_7);
        in_Delay->setObjectName(QString::fromUtf8("in_Delay"));
        in_Delay->setGeometry(QRect(22, 200, 71, 22));
        in_Delay->setMaximum(360);
        in_Delay->setValue(2);
        CBox_Movement_2 = new QComboBox(groupBox_7);
        CBox_Movement_2->setObjectName(QString::fromUtf8("CBox_Movement_2"));
        CBox_Movement_2->setGeometry(QRect(100, 30, 90, 22));
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(30, 30, 61, 16));
        Btn_ClearSequenceList = new QPushButton(groupBox_7);
        Btn_ClearSequenceList->setObjectName(QString::fromUtf8("Btn_ClearSequenceList"));
        Btn_ClearSequenceList->setGeometry(QRect(20, 330, 171, 21));
        label_21 = new QLabel(groupBox_7);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(40, 70, 47, 13));
        SBox_Speed_2 = new QSpinBox(groupBox_7);
        SBox_Speed_2->setObjectName(QString::fromUtf8("SBox_Speed_2"));
        SBox_Speed_2->setGeometry(QRect(100, 60, 51, 25));
        SBox_Speed_2->setMinimum(1);
        SBox_Speed_2->setValue(50);
        Btn_RemoveFromSequence = new QPushButton(groupBox_7);
        Btn_RemoveFromSequence->setObjectName(QString::fromUtf8("Btn_RemoveFromSequence"));
        Btn_RemoveFromSequence->setGeometry(QRect(20, 280, 171, 21));
        layoutWidget_5 = new QWidget(groupBox_7);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 244, 171, 32));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        Btn_MoveUp = new QPushButton(layoutWidget_5);
        Btn_MoveUp->setObjectName(QString::fromUtf8("Btn_MoveUp"));
        Btn_MoveUp->setMinimumSize(QSize(0, 30));

        horizontalLayout_10->addWidget(Btn_MoveUp);

        Btn_MoveDown = new QPushButton(layoutWidget_5);
        Btn_MoveDown->setObjectName(QString::fromUtf8("Btn_MoveDown"));
        Btn_MoveDown->setMinimumSize(QSize(0, 30));

        horizontalLayout_10->addWidget(Btn_MoveDown);

        tabWidget->addTab(tab_2, QString());
        Btn_Settings = new QPushButton(centralwidget);
        Btn_Settings->setObjectName(QString::fromUtf8("Btn_Settings"));
        Btn_Settings->setGeometry(QRect(680, 10, 41, 61));
        Btn_SerialConnect = new QPushButton(centralwidget);
        Btn_SerialConnect->setObjectName(QString::fromUtf8("Btn_SerialConnect"));
        Btn_SerialConnect->setGeometry(QRect(720, 10, 141, 61));
        Btn_SerialConnect->setFont(font1);
        InterfazEstandar->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InterfazEstandar);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 874, 21));
        InterfazEstandar->setMenuBar(menubar);
        statusbar = new QStatusBar(InterfazEstandar);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        InterfazEstandar->setStatusBar(statusbar);

        retranslateUi(InterfazEstandar);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InterfazEstandar);
    } // setupUi

    void retranslateUi(QMainWindow *InterfazEstandar)
    {
        InterfazEstandar->setWindowTitle(QCoreApplication::translate("InterfazEstandar", "Interfaz de control estandar", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("InterfazEstandar", "Puntos", nullptr));
        Btn_GoPoint->setText(QCoreApplication::translate("InterfazEstandar", "Posicionar", nullptr));
        Btn_SavePointList->setText(QCoreApplication::translate("InterfazEstandar", "Guardar lista", nullptr));
        Btn_CleanPointList->setText(QCoreApplication::translate("InterfazEstandar", "Borrar lista", nullptr));
        Btn_ListPoint->setText(QCoreApplication::translate("InterfazEstandar", "Guardar Punto", nullptr));
        Btn_DeletPoint->setText(QCoreApplication::translate("InterfazEstandar", "Borrar Punto", nullptr));
        Btn_LoadPointList->setText(QCoreApplication::translate("InterfazEstandar", "Abrir lista", nullptr));
        label_14->setText(QCoreApplication::translate("InterfazEstandar", "Nombre:", nullptr));
#if QT_CONFIG(tooltip)
        in_PointName->setToolTip(QCoreApplication::translate("InterfazEstandar", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        in_PointName->setWhatsThis(QCoreApplication::translate("InterfazEstandar", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        in_PointName->setText(QString());
        groupBox_5->setTitle(QCoreApplication::translate("InterfazEstandar", "Movimiento", nullptr));
        label_23->setText(QCoreApplication::translate("InterfazEstandar", "<html><head/><body><p align=\"right\">Velocidad:</p></body></html>", nullptr));
        Btn_GoHome->setText(QCoreApplication::translate("InterfazEstandar", "Home", nullptr));
        groupBox->setTitle(QCoreApplication::translate("InterfazEstandar", "Posicion rectangular", nullptr));
        label_4->setText(QCoreApplication::translate("InterfazEstandar", "Roll:", nullptr));
        label_2->setText(QCoreApplication::translate("InterfazEstandar", "Y:", nullptr));
        label->setText(QCoreApplication::translate("InterfazEstandar", "X:", nullptr));
        label_3->setText(QCoreApplication::translate("InterfazEstandar", "Z:", nullptr));
        label_6->setText(QCoreApplication::translate("InterfazEstandar", "Yaw:", nullptr));
        label_5->setText(QCoreApplication::translate("InterfazEstandar", "Pitch:", nullptr));
        Btn_RecMovement->setText(QCoreApplication::translate("InterfazEstandar", "Posicionar", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("InterfazEstandar", "Gripper", nullptr));
        Btn_Gripper->setText(QCoreApplication::translate("InterfazEstandar", "Gripper", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("InterfazEstandar", "Posicion Angular", nullptr));
        label_11->setText(QCoreApplication::translate("InterfazEstandar", "<html><head/><body><p align=\"right\">Q0:</p></body></html>", nullptr));
        in_Q1->setSpecialValueText(QString());
        label_12->setText(QCoreApplication::translate("InterfazEstandar", "Q1:", nullptr));
        label_8->setText(QCoreApplication::translate("InterfazEstandar", "Q2:", nullptr));
        label_9->setText(QCoreApplication::translate("InterfazEstandar", "Q3:", nullptr));
        label_7->setText(QCoreApplication::translate("InterfazEstandar", "Q4:", nullptr));
        label_10->setText(QCoreApplication::translate("InterfazEstandar", "Q5:", nullptr));
        Btn_AngMovement->setText(QCoreApplication::translate("InterfazEstandar", "Posicionar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("InterfazEstandar", "Generacion de puntos", nullptr));
        fileManager->setTitle(QCoreApplication::translate("InterfazEstandar", "Trayectorias", nullptr));
        Btn_SaveSequenceList->setText(QCoreApplication::translate("InterfazEstandar", "Guardar", nullptr));
        Btn_CommandCtrl->setText(QCoreApplication::translate("InterfazEstandar", "Ejecutar\n"
"programa", nullptr));
        Btn_LoadSequenceList->setText(QCoreApplication::translate("InterfazEstandar", "Abrir", nullptr));
        Btn_LoadPointList_2->setText(QCoreApplication::translate("InterfazEstandar", "Abrir lista\n"
"de puntos", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("InterfazEstandar", "Modificador de trayectorias", nullptr));
        Btn_GoPoint_2->setText(QCoreApplication::translate("InterfazEstandar", "Posicionar", nullptr));
        label_18->setText(QCoreApplication::translate("InterfazEstandar", "Gripper: ", nullptr));
        Btn_pushGripperToSequence->setText(QCoreApplication::translate("InterfazEstandar", "Agregar Gripper", nullptr));
        Btn_pushPointToSequence->setText(QCoreApplication::translate("InterfazEstandar", "Agregar punto", nullptr));
        label_19->setText(QCoreApplication::translate("InterfazEstandar", "Delay:", nullptr));
        Btn_pushDelayToSequence->setText(QCoreApplication::translate("InterfazEstandar", "Agregar Delay", nullptr));
        label_20->setText(QCoreApplication::translate("InterfazEstandar", "movimiento:", nullptr));
        Btn_ClearSequenceList->setText(QCoreApplication::translate("InterfazEstandar", "Descartar Trayectoria", nullptr));
        label_21->setText(QCoreApplication::translate("InterfazEstandar", "Velocidad:", nullptr));
        Btn_RemoveFromSequence->setText(QCoreApplication::translate("InterfazEstandar", "Eliminar de trayectoria", nullptr));
        Btn_MoveUp->setText(QCoreApplication::translate("InterfazEstandar", "Subir", nullptr));
        Btn_MoveDown->setText(QCoreApplication::translate("InterfazEstandar", "Bajar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("InterfazEstandar", "Generador de programas", nullptr));
        Btn_Settings->setText(QString());
        Btn_SerialConnect->setText(QCoreApplication::translate("InterfazEstandar", "Conectar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InterfazEstandar: public Ui_InterfazEstandar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFAZESTANDAR_H
