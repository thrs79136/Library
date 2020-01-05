// Theresa Schüttig, s79136, 18/041/61

#ifndef CD_H
#define CD_H
#include <QTime>
#include <QDebug>
#include "medium.h"

class CD:public Medium{
public:
    CD(QString name, QString creator, int year, int minutes);
    CD(QString name, QString creator, int year, int minutes, long borrowerID);

    void setMinutes(int m);
    int getMinutes(){return minutes;}
    void showCD(){qDebug("%s %s %d %d", name.toStdString().c_str(), creator.toStdString().c_str(), year, minutes);}
private:
    int minutes;
};

#endif // CD_H
