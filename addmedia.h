// Theresa Schüttig, 45600, s79136, 18/041/61

#ifndef ADDMEDIA_H
#define ADDMEDIA_H

#include "library.h"
#include <QDialog>
#include <QAbstractButton>

class MainWindow;

namespace Ui {
class addMedia;
}

class addMedia : public QDialog
{
    Q_OBJECT

public:
    explicit addMedia(Library *lib, MainWindow *mainWindow, QDialog *parent = nullptr);
    ~addMedia();

private slots:
    void resetEdits();
    void on_mediumTypeBox_currentIndexChanged(const QString &arg1);
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addMedia *ui;
    Library *library;
    MainWindow *mainWindow;
};

#endif // ADDMEDIA_H
