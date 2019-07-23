// Theresa Schüttig, 45600, s79136, 18/041/61

#ifndef LIBRARY_H
#define LIBRARY_H

#include <QList>
#include <QString>

class User;
class Medium;
class Book;
class CD;

class Library
{
public:
    Library();
    ~Library();
    void addMedium(Medium*);
    void addUser(User*);
    bool selectUser(long UID);
    bool selectMedium(long MID);
    void addLending();
    void returnMedium();
    User *getSelectedUser(){return selectedUser;}
    Medium *getSelectedMedium(){return selectedMedium;}
    void setNoUserSelected(){selectedUser=nullptr;}
    void setNoMediumSelected(){selectedMedium=nullptr;}
    QList<Medium*> *getMediumList(){return &mediumList;}
    QList<User*> *getUserList(){return &userList;}
    bool deleteMedium(long);
    bool deleteUser(long);
    void showUsers();
    void showMedia();
private:
    bool readUsers();
    bool readMedia();
    void addBorrowedMediaLists();
    bool saveUsers();
    bool saveMedia();
    User *selectedUser = nullptr;
    Medium *selectedMedium = nullptr;
    QList<Medium*> mediumList;
    QList<User*> userList;
    QString userFile = "users.csv";
    QString mediaFile = "media.csv";
};

#endif // LIBRARY_H
