// Theresa Schüttig, 45600, s79136, 18/041/61

#include "cd.h"

//Konstruktor fuer Medium wird aufgerufen
CD::CD(QString name, QString creator, int year, int minutes):Medium(name,creator,year){
    this->minutes = minutes;
}

CD::CD(QString name, QString creator, int year, int minutes, long borrowerID):Medium(name,creator,year, borrowerID){
    this->minutes = minutes;
}

void CD::setMinutes(int m){
    if (m>0) this-> minutes = m;
    else throw QString("Dauer muss größer als 0 sein.");
}
