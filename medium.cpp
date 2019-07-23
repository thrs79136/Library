// Theresa Schüttig, 45600, s79136, 18/041/61

#include "medium.h"
#include "user.h"
#include "book.h"
#include "cd.h"

long Medium::id = 0;

Medium::Medium(QString name, QString creator, int year){
    this->year = year;
    this->name = name;
    this->creator = creator;
    m_id=id;
    id++;
}

Medium::Medium(QString name, QString creator, int year, long borrowerID):Medium(name, creator, year){
    this->borrowerID = borrowerID;
}

void Medium::setBorrower(User *pUser){
    if (!pUser) borrowerID=-1;
    else borrowerID = pUser->getID();
    borrower=pUser;
}

QString Medium::getMediumData(){
    return name + ", " + creator + ", " + QString::number(year);
}

QString Medium::saveRecord(){
    int minutesOrPages;
    QString mediumtype;
    if (dynamic_cast<Book*>(this)){
        minutesOrPages = static_cast<Book*>(this)->getPages();
        mediumtype ="0";
    }
    else{
        minutesOrPages = static_cast<CD*>(this)->getMinutes();
        mediumtype="1";
    }
    return QString("%1,%2,%3,%4,%5,%6").arg(mediumtype,name,creator,QString::number(year),QString::number(minutesOrPages), QString::number(borrowerID));
}
