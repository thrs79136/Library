// Theresa Schüttig, s79136, 18/041/61

#include <QApplication>
#include <QFile>
#include "mainwindow.h"
#include "library.h"
#include "medium.h"
#include "book.h"
#include "cd.h"
#include "user.h"

Library::Library()
{
    this->readMedia();
    this->readUsers();
    this->addBorrowedMediaLists();
}

Library::~Library(){
    this->saveMedia();
    this->saveUsers();
}

void Library::addMedium(Medium *pM){
    mediumList.append(pM);
}

void Library::addUser(User *pU){
    userList.append(pU);
}

bool Library::selectUser(long UID){
    for (User *pU : userList){
        if (pU->getID()==UID){
            selectedUser = pU;
            return true;
        }
    }
    return false;
}

bool Library::selectMedium(long MID){
    for (Medium *pM : mediumList){
        if (pM->getId()==MID){
            selectedMedium = pM;
            return true;
        }
    }
    return false;
}

void Library::addLending(){
    selectedMedium->setBorrower(selectedUser);
    selectedUser->borrowMedium(selectedMedium);
}

void Library::returnMedium(){
    selectedMedium->getBorrower()->returnMedium(selectedMedium->getId());
    selectedMedium->setBorrower(nullptr);
}

bool Library::deleteUser(long uID){
    QList<User*>::iterator it = userList.begin();
    for (;it!=userList.end(); it++){
        User *pU = *it;
        if (pU->getID()==uID){
            userList.erase(it);
            return true;
        }
    }
    return false;
}

bool Library::deleteMedium(long mID){
    QList<Medium*>::iterator it = mediumList.begin();
    for (; it!=mediumList.end(); it++){
        Medium *pM = *it;
        if (pM->getId()==mID){
            if (pM->getBorrower()){
                // Medium wird aus der Liste des Nutzers entfernt, falls es ausgeliehen wurde
                pM->getBorrower()->returnMedium(pM->getId());
            }
            mediumList.erase(it);
            return true;
        }
    }
    return false;
}

void Library::showUsers(){
    for (User *u: userList) u->showUser();
}

void Library::showMedia(){
    for (Medium *m: mediumList){
         if (dynamic_cast<Book*>(m)) static_cast<Book*>(m)->showBook();
         else static_cast<CD*>(m)->showCD();
    }
}

bool Library::readUsers(){
    QFile file(QCoreApplication::applicationDirPath() + "/" + userFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!file.atEnd()){
            QList<QByteArray> tokens = file.readLine().split(',');
            QString surName = tokens[0];
            QString firstName = tokens[1];
            QString bDate = tokens[2];
            long id = tokens[3].toLong();
            userList.push_back(new User(surName, firstName,QDate::fromString(bDate,"dd.MM.yyyy"),id));
        }
    }
    else return false;
    file.close();
    return true;
}

bool Library::readMedia(){
    QFile file(QCoreApplication::applicationDirPath() + "/" + mediaFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!file.atEnd()){
            QList<QByteArray> tokens = file.readLine().split(',');
            QString name = tokens[1];
            QString creator = tokens[2];
            int year = tokens[3].toInt();
            int minutesOrPages = tokens[4].toInt();
            int borrowerID = tokens[5].toInt();
            Medium *pM;
            if (QString::compare(tokens[0],"0", Qt::CaseSensitive)==0){ //ist Buch
                pM = new Book(name,creator,year,minutesOrPages,borrowerID);
                mediumList.push_back(static_cast<Medium*>(pM));
            }
            else{
                pM = new CD(name,creator,year,minutesOrPages, borrowerID);
                mediumList.push_back(pM);
            }
        }
    }
    else return false;
    file.close();
    return true;
}

// fuegt Listen mit geliehenen Medien zu Nutzern, basierend auf IDs in der csv-Datei
void Library::addBorrowedMediaLists(){
    for (Medium *pM: mediumList){
        for (User *pU: userList){
            if (pM->getBorrowerID() == pU->getID()){
                pU->borrowMedium(pM);
                pM->setBorrower(pU);
            }
        }
    }
}

bool Library::saveMedia(){
    QFile file(QCoreApplication::applicationDirPath() + "/" + mediaFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.resize(0);
        for (Medium *m: mediumList){
            QTextStream out(&file);
            out << m->saveRecord() << endl;
        }
        return true;
    }
    return false;
}

bool Library::saveUsers(){
    QFile file(QCoreApplication::applicationDirPath() + "/" + userFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.resize(0);
        for (User *u: userList){
            QTextStream out(&file);
            out << u->saveRecord() << endl;
        }
        return true;
    }
    return false;
}

