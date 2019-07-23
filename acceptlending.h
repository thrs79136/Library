#ifndef ACCEPTLENDING_H
#define ACCEPTLENDING_H

#include <QDialog>

class MainWindow;
class Library;
class User;
class Medium;

namespace Ui {
class acceptLending;
}

class acceptLending : public QDialog
{
    Q_OBJECT

public:
    explicit acceptLending(Library *lib, MainWindow *mainWindow, QWidget *parent = nullptr);
    void setMediumLabel(Medium *pM);
    void setUserLabel(User *pU);
    ~acceptLending();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::acceptLending *ui;
    MainWindow *mainWindow;
    Library *lib;
};

#endif // ACCEPTLENDING_H
