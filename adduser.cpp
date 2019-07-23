// Theresa Schüttig, 45600, s79136, 18/041/61

#include "mainwindow.h"
#include "adduser.h"
#include "ui_adduser.h"
#include "user.h"
#include <QDebug>
#include <QDate>

addUser::addUser(Library *lib, MainWindow *mainWindow, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::addUser)
{
    ui->setupUi(this);
    library = lib;
    this->mainWindow = mainWindow;
}

addUser::~addUser()
{
    delete ui;
}

void addUser::resetEdits(){
    ui->firstNameEdit->setText("");
    ui->surnameEdit->setText("");
    ui->birthdateEdit->setDate(QDate::fromString("01.01.00"));
}

void addUser::on_buttonBox_accepted()
{
    QString firstName = ui->firstNameEdit->text();
    QString surName = ui->surnameEdit->text();
    QDate birthDate = ui->birthdateEdit->date();

    User *pUser = new User(surName, firstName, birthDate);
    library->getUserList()->append(pUser);
    mainWindow->addUserEntry(pUser);
    resetEdits();
}

void addUser::on_buttonBox_rejected(){
    resetEdits();
}
