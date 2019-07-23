// Theresa Schüttig, 45600, s79136, 18/041/61

#include "mainwindow.h"
#include "addmedia.h"
#include "book.h"
#include "cd.h"
#include "ui_addmedia.h"
#include <QDebug>

addMedia::addMedia(Library *lib, MainWindow *mainWindow, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::addMedia)
{
    ui->setupUi(this);

   library = lib;
   this->mainWindow = mainWindow;
}

addMedia::~addMedia()
{
    delete ui;
}

void addMedia::on_mediumTypeBox_currentIndexChanged(const QString &arg1)
{
    if (arg1=="Buch"){
        ui->addInformationLabel->setText("Seitenanzahl");
        ui->creatorLabel->setText("Autor");
    }
    else if (arg1=="CD"){
        ui->addInformationLabel->setText("Dauer");
        ui->creatorLabel->setText("Interpret");
    }
    else{
        ui->addInformationLabel->setText("Sonstiges");
        ui->creatorLabel->setText("Urheber");
    }
}

void addMedia::resetEdits(){
    ui->nameEdit->setText("");
    ui->creatorEdit->setText("");
    ui->yearEdit->setDate(QDate::fromString("01.01.19"));
    ui->additionalInfoEdit->setText("");
    ui->mediumTypeBox->setCurrentIndex(0);
}

void addMedia::on_buttonBox_accepted()
{
    // extrahiert Daten aus Edits
    QString name = ui->nameEdit->text();
    QString creator = ui->creatorEdit->text();
    int year = ui->yearEdit->date().year();
    int additionalInfo = ui->additionalInfoEdit->text().toInt();

    Medium *pMedium;
    if (ui->mediumTypeBox->currentText()=="Buch"){
        pMedium = new Book(name, creator, year, additionalInfo);
        library->addMedium(pMedium);
    } else {
        pMedium = new CD(name, creator, year, additionalInfo);
        library->addMedium(pMedium);
    }
    mainWindow->addMediumEntry(pMedium);
    resetEdits();
}



void addMedia::on_buttonBox_rejected()
{
    resetEdits();
}
