// Theresa Schüttig, s79136, 18/041/61

#ifndef MEDIUM_H
#define MEDIUM_H
#include "QString"
#include <QList>

class User;

class Medium{
public:
    Medium(QString name, QString creator, int year);
    Medium(QString name, QString creator, int year, long borrowerID);
    virtual ~Medium(){}
    virtual QString saveRecord();
    void setBorrower(User *pUser);
    QString getMediumData();
    QString getName(){return name;}
    QString getCreator(){return creator;}
    int getYear(){return year;}
    long getBorrowerID(){return borrowerID;}
    User *getBorrower(){return borrower;}
    long getId(){return m_id;}
    bool available(){return borrowerID==-1?1:0;}

    protected:
    QString name;
    QString creator;
    int year;
    long m_id;
    // -1 steht dafür, dass das Medium von keinem Nutzer ausgeliehen wurd
    long borrowerID=-1;
    User *borrower;
    static long id;
};


#endif // MEDIUM_H
