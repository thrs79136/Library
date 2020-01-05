// Theresa Schüttig, s79136, 18/041/61

#include "user.h"
#include "medium.h"
#include <QDebug>
#include <QDate>

long User::id = 0;

User::User(QString sur, QString first, QDate birth){
    surname=sur;
    firstName=first;
    birthDate = birth;
    m_id=id++;
}

User::User(QString sur, QString first, QDate birth, long ID) : User(sur, first, birth){
    m_id = ID;
    if (ID>=id) id = ID+1;
}

QString User::saveRecord(){
    return QString("%1,%2,%3,%4,").arg(surname,firstName,birthDate.toString("dd.MM.yyyy"),QString::number(m_id));
}

void User::setName(QString sur, QString first){
    if (sur.isEmpty() || first.isEmpty()) throw QString("Name darf nicht leer sein.");
    surname = sur;
    firstName = first;
}

QString User::getUserData(){
    return QString::number(m_id) + ", " + firstName + " " + surname;
}

void User::returnMedium(long mID){
    QList<Medium*>::iterator it = borrowedMedia.begin();
    for (;it!=borrowedMedia.end(); it++){
        if ((*it)->getId() == mID) borrowedMedia.erase(it);
    }
}

void User::showUser(){
    qDebug() << firstName << surname <<  m_id;
}
