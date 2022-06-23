#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QDialog>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

    void setSavedSettings();
    void saveSettings();
    static void saveSetting(const QString &gpo,const QString &key,const QString &value);
    static QString getSetting(const QString &gpo,const QString &key,const QString defaultValue);


private:
    Ui::SettingsForm *ui;
};



#endif // SETTINGSFORM_H
