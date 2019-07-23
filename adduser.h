// Theresa Schüttig, 45600, s79136, 18/041/61

#ifndef ADDPERSON_H
#define ADDPERSON_H

#include "library.h"
#include <QDialog>

class MainWindow;

namespace Ui {
class addUser;
}

class addUser : public QDialog
{
    Q_OBJECT

public:
    explicit addUser(Library *lib, MainWindow *mainWindow, QDialog *parent = nullptr);
    ~addUser();

private slots:
    void resetEdits();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::addUser *ui;
    Library *library;
    MainWindow *mainWindow;
};

#endif // ADDPERSON_H
