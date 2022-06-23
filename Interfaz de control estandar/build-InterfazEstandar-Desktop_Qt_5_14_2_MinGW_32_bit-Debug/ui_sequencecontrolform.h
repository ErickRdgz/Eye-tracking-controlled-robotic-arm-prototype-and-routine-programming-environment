/********************************************************************************
** Form generated from reading UI file 'sequencecontrolform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCECONTROLFORM_H
#define UI_SEQUENCECONTROLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SequenceControlForm
{
public:
    QPushButton *Btn_Execution;
    QLineEdit *Out_ExecutionCounter;
    QLineEdit *Out_info;
    QPushButton *Btn_CancelExecution;
    QLabel *label;
    QPushButton *Btn_StopAndPlay;
    QSpinBox *SBox_N_Executions;

    void setupUi(QDialog *SequenceControlForm)
    {
        if (SequenceControlForm->objectName().isEmpty())
            SequenceControlForm->setObjectName(QString::fromUtf8("SequenceControlForm"));
        SequenceControlForm->resize(431, 150);
        Btn_Execution = new QPushButton(SequenceControlForm);
        Btn_Execution->setObjectName(QString::fromUtf8("Btn_Execution"));
        Btn_Execution->setGeometry(QRect(20, 52, 90, 40));
        Btn_Execution->setAutoDefault(false);
        Out_ExecutionCounter = new QLineEdit(SequenceControlForm);
        Out_ExecutionCounter->setObjectName(QString::fromUtf8("Out_ExecutionCounter"));
        Out_ExecutionCounter->setEnabled(false);
        Out_ExecutionCounter->setGeometry(QRect(20, 122, 41, 20));
        Out_info = new QLineEdit(SequenceControlForm);
        Out_info->setObjectName(QString::fromUtf8("Out_info"));
        Out_info->setEnabled(false);
        Out_info->setGeometry(QRect(70, 122, 341, 20));
        Btn_CancelExecution = new QPushButton(SequenceControlForm);
        Btn_CancelExecution->setObjectName(QString::fromUtf8("Btn_CancelExecution"));
        Btn_CancelExecution->setGeometry(QRect(320, 52, 90, 40));
        label = new QLabel(SequenceControlForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(68, 12, 300, 20));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        Btn_StopAndPlay = new QPushButton(SequenceControlForm);
        Btn_StopAndPlay->setObjectName(QString::fromUtf8("Btn_StopAndPlay"));
        Btn_StopAndPlay->setGeometry(QRect(210, 52, 90, 40));
        SBox_N_Executions = new QSpinBox(SequenceControlForm);
        SBox_N_Executions->setObjectName(QString::fromUtf8("SBox_N_Executions"));
        SBox_N_Executions->setGeometry(QRect(120, 60, 51, 25));
        QFont font1;
        font1.setPointSize(12);
        SBox_N_Executions->setFont(font1);
        SBox_N_Executions->setMaximum(50);
        SBox_N_Executions->setValue(1);

        retranslateUi(SequenceControlForm);

        Btn_Execution->setDefault(true);


        QMetaObject::connectSlotsByName(SequenceControlForm);
    } // setupUi

    void retranslateUi(QDialog *SequenceControlForm)
    {
        SequenceControlForm->setWindowTitle(QCoreApplication::translate("SequenceControlForm", "Dialog", nullptr));
        Btn_Execution->setText(QCoreApplication::translate("SequenceControlForm", "Ejecutar", nullptr));
        Btn_CancelExecution->setText(QCoreApplication::translate("SequenceControlForm", "Cancelar", nullptr));
        label->setText(QCoreApplication::translate("SequenceControlForm", "Control de ejecucion de programas", nullptr));
        Btn_StopAndPlay->setText(QCoreApplication::translate("SequenceControlForm", "Pausar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SequenceControlForm: public Ui_SequenceControlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCECONTROLFORM_H
