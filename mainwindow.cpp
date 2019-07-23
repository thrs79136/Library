// Theresa Schüttig, 45600, s79136, 18/041/61

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include "user.h"
#include "medium.h"
#include "book.h"
#include "cd.h"
#include "adduser.h"
#include "addmedia.h"
#include "acceptlending.h"
#include "notewindow.h"
#include "showmedia.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    library = new Library;
    addPWindow = new addUser(library, this);
    addMWindow = new addMedia(library, this);
    accLendWindow = new acceptLending(library, this);
    noteWindow = new NoteWindow();
    showMediaWindow = new showMedia();
    if (!library || !addPWindow || !addMWindow || !accLendWindow || !noteWindow || !showMediaWindow){} /*dicker fetter Fehler*/

    ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mediaTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->removeButton->setEnabled(false);
    displayMedia();
    displayUsers();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete addPWindow;
    delete addMWindow;
    delete library;
    delete noteWindow;
    delete showMediaWindow;
}

void MainWindow::displayMedia(){
    mediumModel = new QStandardItemModel(this);
    mediumModel->setColumnCount(7);
    mediumModel->setHorizontalHeaderLabels(QStringList() << "Typ" << "Name" << "Urheber" << "Jahr" << "Seitenanzahl/Dauer" << "Verfügbar" << "ID");
    ui->mediaTable->setModel(mediumModel);
    ui->mediaTable->setColumnHidden(6, true);

    // Einfuegen der Mediendaten in die Tabelle
    QList<QStandardItem*> itemList;
    for (Medium *pM : *library->getMediumList()) addMediumEntry(pM);
}

void MainWindow::displayUsers(){
    QList<QStandardItem*> itemList;
    userModel = new QStandardItemModel(this);
    userModel->setColumnCount(4);
    userModel->setHorizontalHeaderLabels(QStringList() << "Bibliotheksnr." << "Name" << "Vorname" << "Geburtsdatum");
    ui->userTable->setModel(userModel);

    // Einfuegen aller Nutzerdaten in Tabelle
    for (User *pU : *library->getUserList()) addUserEntry(pU);
}

void MainWindow::reloadUserTable(){
    userModel->clear();
    displayUsers();
}

void MainWindow::reloadMediaTable(){
    mediumModel->clear();
    displayMedia();
    disableButton();
}

void MainWindow::addMediumEntry(Medium *pM){
    static QList<QStandardItem*> itemList;
    itemList.clear();
    QString type = dynamic_cast<Book*>(pM)? "Buch" : "CD";
    itemList.append(new QStandardItem(type));
    itemList.append(new QStandardItem(pM->getName()));
    itemList.append(new QStandardItem(pM->getCreator()));
    itemList.append(new QStandardItem(QString::number(pM->getYear())));
    QString pagesOrMinutes;
    if (dynamic_cast<Book*>(pM)) pagesOrMinutes = QString::number(static_cast<Book*>(pM)->getPages()) + " Seiten";
    else pagesOrMinutes = QString::number(static_cast<CD*>(pM)->getMinutes()) + " Minuten";
    itemList.append(new QStandardItem(pagesOrMinutes));
    itemList.append(new QStandardItem(pM->available()?"Ja":"Nein"));
    itemList.append(new QStandardItem(QString::number(pM->getId())));
    mediumModel->insertRow(mediumModel->rowCount(),itemList);
}

void MainWindow::addUserEntry(User *pU){
    static QList<QStandardItem*> itemList;
    itemList.clear();
    itemList.append(new QStandardItem(QString::number(pU->getID())));
    itemList.append(new QStandardItem(pU->getSurname()));
    itemList.append(new QStandardItem(pU->getFirstName()));
    itemList.append(new QStandardItem(pU->getBirthDate().toString("dd.MM.yyyy")));
    userModel->insertRow(userModel->rowCount(),itemList);
}

// Button zum Ausleihen oder Zurueckgeben wird gesperrt, je nachdem, ob Medium verfuegbar ist oder nicht
void MainWindow::disableButton(){
    bool borrowButtonEnabled = true;
    bool returnMediumButtonEnabled = true;
    if (!library->getSelectedMedium()){
        borrowButtonEnabled=false;
        returnMediumButtonEnabled=false;
    }
    else if (!library->getSelectedMedium()->available()){
        borrowButtonEnabled = false;
        returnMediumButtonEnabled = true;
    }
    else{
        borrowButtonEnabled = true;
        returnMediumButtonEnabled = false;
    }
    ui->borrowButton->setEnabled(borrowButtonEnabled);
    ui->returnMediumButton->setEnabled(returnMediumButtonEnabled);
}


// oeffnet Fenster, um Nutzer hinzuzufuegen
void MainWindow::on_addPersonButton_clicked()
{
    addPWindow->show();
}

// oeffnet Fenster, um Medium hinzuzufuegen
void MainWindow::on_addMediaButton_clicked()
{
    addMWindow->show();
}

// wird aufgerufen, wenn Nutzer selektiert wurde
void MainWindow::on_userTable_clicked(const QModelIndex &index)
{
    userIndex = index;

    QStandardItem *userID = userModel->itemFromIndex(index.sibling(index.row(), 0));
    library->selectUser(userID->text().toInt());
    ui->selectedUserLabel->setText(library->getSelectedUser()->getUserData());
    ui->removeButton->setEnabled(true);
}

// wird aufgerufen, wenn Medium selektiert wurde
void MainWindow::on_mediaTable_clicked(const QModelIndex &index)
{
    mediumIndex = index;
    QStandardItem *mediumID = mediumModel->itemFromIndex(index.sibling(index.row(),6));
    library->selectMedium(mediumID->text().toInt());
    ui->selectedMediumLabel->setText(library->getSelectedMedium()->getMediumData());
    disableButton();
    ui->removeButton->setEnabled(true);
}

void MainWindow::on_usersTable_currentChanged(int index)
{
    selectedTab = static_cast<Tab>(index);
    bool removeButtonEnabled = false;
    if ((selectedTab==users && library->getSelectedUser()) ||
           (selectedTab==media && library->getSelectedMedium()))
        removeButtonEnabled=true;
    ui->removeButton->setEnabled(removeButtonEnabled);
}

void MainWindow::on_borrowButton_clicked()
{
    if (library->getSelectedUser() && library->getSelectedMedium()){
        accLendWindow->setUserLabel(library->getSelectedUser());
        accLendWindow->setMediumLabel(library->getSelectedMedium());
        accLendWindow->show();
    }
    else{
        noteWindow->show();
        noteWindow->changeLabel("Bitte wählen Sie zum Ausleihen\n einen Nutzer und ein Medium aus");
    }
}

void MainWindow::on_mediaTable_activated(const QModelIndex &index)
{
    on_mediaTable_clicked(index);
}

void MainWindow::on_userTable_activated(const QModelIndex &index)
{
    on_userTable_clicked(index);
}

void MainWindow::on_returnMediumButton_clicked()
{
    library->returnMedium();
    reloadMediaTable();
}


void MainWindow::on_removeButton_clicked()
{
    if (selectedTab==media){
        long ID = library->getSelectedMedium()->getId();
        int rowNumber = mediumModel->rowCount(mediumIndex);
        mediumModel->removeRow(rowNumber,mediumIndex);
        library->deleteMedium(ID);
        library->setNoMediumSelected();
        ui->selectedMediumLabel->setText("Keins");
        reloadMediaTable();
    }
    else {
        // Nutzer hat noch Medien ausgeliehen => kann nicht entfernt werden
        if (!library->getSelectedUser()->getBorrowedMedia().empty()){
            noteWindow->changeLabel("Der Nutzer kann nicht gelöscht werden,\nda er noch verliehene Medien besitzt.\nÜber einen Doppelklick\n auf den Nutzer erfahren Sie,\nwelche dies sind.");
            noteWindow->show();
        } else {
            long ID = library->getSelectedUser()->getID();
            int rowNumber = userModel->rowCount(mediumIndex);
            userModel->removeRow(rowNumber,mediumIndex);
            library->deleteUser(ID);
            library->setNoUserSelected();
            ui->selectedUserLabel->setText("Keiner");
            reloadUserTable();
        }
    }
}

// Doppelklick auf Nutzer zeigt ausgeliehene Medien an
void MainWindow::on_userTable_doubleClicked(const QModelIndex &index)
{
    on_userTable_clicked(index);
    showMediaWindow->printList(library->getSelectedUser(), library->getSelectedUser()->getBorrowedMedia());
    showMediaWindow->show();
}
