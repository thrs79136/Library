// Theresa Schüttig, s79136, 18/041/61

#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <QDebug>
#include "medium.h"

class Book:public Medium{
public:
    Book(QString name, QString creator, int year, int pages);
    Book(QString name, QString creator, int year, int pages, long borrowerID);
    void setPages(int pages);
    int getPages(){return pages;}
    void showBook(){qDebug("%s %s %d %d", name.toStdString().c_str(), creator.toStdString().c_str(), year, pages);}
private:
    int pages;
};

#endif // BOOK_H
