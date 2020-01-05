// Theresa Schüttig, s79136, 18/041/61

#ifndef USER_H
#define USER_H
#include "QString"
#include <QList>
#include <QDate>

class Medium;

class User{
public:
    User(QString sur, QString first, QDate birth);
    User(QString sur, QString first, QDate birth,long ID);
    QString saveRecord();
    void setName(QString sur, QString first);
    QString getUserData();
    QString getFirstName(){return firstName;}
    QString getSurname(){return surname;}
    QDate getBirthDate(){return birthDate;}
    long getID(){return m_id;}
    QList<Medium*> getBorrowedMedia(){return borrowedMedia;}
    void borrowMedium(Medium *pM){borrowedMedia.push_back(pM);}
    void returnMedium(long mID);
    void showUser();

private:
    QString surname;
    QString firstName;
    QDate birthDate;
    QList<Medium*> borrowedMedia = {};
    long m_id;
    static long id;
};

#endif // USER_H
