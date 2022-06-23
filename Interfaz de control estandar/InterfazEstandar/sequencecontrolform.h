#ifndef SEQUENCECONTROLFORM_H
#define SEQUENCECONTROLFORM_H

#include <QDialog>
#include "sequencer.h"
#include <QMessageBox>
#include "lista.h"
#include <QWidget>
#include "revolutearm.h"
#include <vector>

namespace Ui {
class SequenceControlForm;
}

class SequenceControlForm : public QDialog
{
    Q_OBJECT

public:
    explicit SequenceControlForm(Lista<Command> *CommandList,Lista<Point> *SequenceList,RevoluteArm *arm ,QWidget *parent);
    ~SequenceControlForm();

private:
    Ui::SequenceControlForm *ui;
    Lista<Command> *CommandList;
    Lista<Point> *SequenceList;
    RevoluteArm *arm;
    int executionCounter=0;
    int commandCounter=0;
    bool stopFlag=false;
    void updateExecutionInfo();

protected:
    void closeEvent(QCloseEvent *) override;

};

#endif // SEQUENCECONTROLFORM_H
