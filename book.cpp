// Theresa Schüttig, s79136, 18/041/61

#include "book.h"

Book::Book(QString name, QString creator, int year, int pages):Medium(name,creator,year){
    this->pages = pages;
}

Book::Book(QString name, QString creator, int year, int pages, long borrowerID) : Medium(name, creator, year, borrowerID){
    this->pages = pages;
}


void Book::setPages(int pages){
    if (pages<1) throw QString("Seitenanzahl muss mindestens 1 sein");
    this->pages = pages;
}

