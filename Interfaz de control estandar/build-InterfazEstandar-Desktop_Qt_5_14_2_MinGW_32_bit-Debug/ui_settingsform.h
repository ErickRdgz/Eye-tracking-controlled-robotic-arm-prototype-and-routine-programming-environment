/********************************************************************************
** Form generated from reading UI file 'settingsform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSFORM_H
#define UI_SETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsForm
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_10;
    QGridLayout *gridLayout;
    QDoubleSpinBox *SBox_YHome;
    QDoubleSpinBox *SBox_ZHome;
    QLabel *label_7;
    QLabel *label_4;
    QDoubleSpinBox *SBox_PitchHome;
    QDoubleSpinBox *SBox_RowHome;
    QLabel *label_8;
    QDoubleSpinBox *SBox_YawHome;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *SBox_XHome;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSpinBox *SBox_Vmax;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_2;
    QComboBox *CBox_Port;
    QLabel *label_2;
    QComboBox *CBox_BRate;
    QLabel *label;

    void setupUi(QDialog *SettingsForm)
    {
        if (SettingsForm->objectName().isEmpty())
            SettingsForm->setObjectName(QString::fromUtf8("SettingsForm"));
        SettingsForm->resize(320, 240);
        buttonBox = new QDialogButtonBox(SettingsForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-30, 200, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(SettingsForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 131, 222));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_2->addWidget(label_10);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        SBox_YHome = new QDoubleSpinBox(layoutWidget);
        SBox_YHome->setObjectName(QString::fromUtf8("SBox_YHome"));

        gridLayout->addWidget(SBox_YHome, 1, 1, 1, 1);

        SBox_ZHome = new QDoubleSpinBox(layoutWidget);
        SBox_ZHome->setObjectName(QString::fromUtf8("SBox_ZHome"));

        gridLayout->addWidget(SBox_ZHome, 2, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        SBox_PitchHome = new QDoubleSpinBox(layoutWidget);
        SBox_PitchHome->setObjectName(QString::fromUtf8("SBox_PitchHome"));

        gridLayout->addWidget(SBox_PitchHome, 4, 1, 1, 1);

        SBox_RowHome = new QDoubleSpinBox(layoutWidget);
        SBox_RowHome->setObjectName(QString::fromUtf8("SBox_RowHome"));

        gridLayout->addWidget(SBox_RowHome, 3, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 5, 0, 1, 1);

        SBox_YawHome = new QDoubleSpinBox(layoutWidget);
        SBox_YawHome->setObjectName(QString::fromUtf8("SBox_YawHome"));

        gridLayout->addWidget(SBox_YawHome, 5, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        SBox_XHome = new QDoubleSpinBox(layoutWidget);
        SBox_XHome->setObjectName(QString::fromUtf8("SBox_XHome"));

        gridLayout->addWidget(SBox_XHome, 0, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        SBox_Vmax = new QSpinBox(layoutWidget);
        SBox_Vmax->setObjectName(QString::fromUtf8("SBox_Vmax"));
        SBox_Vmax->setMinimum(1);
        SBox_Vmax->setMaximum(400);
        SBox_Vmax->setValue(100);

        horizontalLayout->addWidget(SBox_Vmax);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        layoutWidget_2 = new QWidget(SettingsForm);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(180, 10, 131, 67));
        gridLayout_2 = new QGridLayout(layoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        CBox_Port = new QComboBox(layoutWidget_2);
        CBox_Port->setObjectName(QString::fromUtf8("CBox_Port"));

        gridLayout_2->addWidget(CBox_Port, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1, Qt::AlignRight);

        CBox_BRate = new QComboBox(layoutWidget_2);
        CBox_BRate->setObjectName(QString::fromUtf8("CBox_BRate"));

        gridLayout_2->addWidget(CBox_BRate, 1, 1, 1, 1);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        retranslateUi(SettingsForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsForm);
    } // setupUi

    void retranslateUi(QDialog *SettingsForm)
    {
        SettingsForm->setWindowTitle(QCoreApplication::translate("SettingsForm", "Dialog", nullptr));
        label_10->setText(QCoreApplication::translate("SettingsForm", "Posicion Home:", nullptr));
        label_7->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">PITCH:</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">Y:</p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">YAW:</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">Z:</p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">ROW:</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">X:</p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("SettingsForm", "Velocidad maxima:", nullptr));
        CBox_Port->setCurrentText(QString());
        label_2->setText(QCoreApplication::translate("SettingsForm", "Baud Rate:", nullptr));
        label->setText(QCoreApplication::translate("SettingsForm", "<html><head/><body><p align=\"right\">Port:</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsForm: public Ui_SettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSFORM_H
