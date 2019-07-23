#include "acceptlending.h"
#include "ui_acceptlending.h"
#include "mainwindow.h"
#include "library.h"
#include "user.h"
#include "medium.h"

acceptLending::acceptLending(Library *lib, MainWindow *mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acceptLending)
{
    ui->setupUi(this);
    this->mainWindow = mainWindow;
    this->lib = lib;
}

acceptLending::~acceptLending()
{
    delete ui;
}

void acceptLending::setUserLabel(User *pU){
    ui->userLabel->setText(pU->getUserData());
    ui->userLabel->setAlignment(Qt::AlignCenter);
}

void acceptLending::setMediumLabel(Medium *pM){
    ui->mediumLabel->setText(pM->getMediumData());
    ui->mediumLabel->setAlignment(Qt::AlignCenter);
}

void acceptLending::on_buttonBox_accepted()
{
    lib->addLending();
    mainWindow->reloadMediaTable();
}
