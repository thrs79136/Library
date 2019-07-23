// Theresa Schüttig, 45600, s79136, 18/041/61

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "library.h"
#include <QMainWindow>
#include <QDebug>
#include <QStandardItemModel>

class addUser;
class addMedia;
class acceptLending;
class NoteWindow;
class showMedia;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void displayUsers();
    void displayMedia();
    void reloadMediaTable();
    void reloadUserTable();
    void addUserEntry(User*);
    void addMediumEntry(Medium*);
    void disableButton();
    explicit MainWindow(QWidget *parent = nullptr);
    Library *getLibrary(){return library;}
    ~MainWindow();

private slots:

    void on_addPersonButton_clicked();

    void on_addMediaButton_clicked();

    void on_userTable_clicked(const QModelIndex &index);

    void on_mediaTable_clicked(const QModelIndex &index);

    void on_usersTable_currentChanged(int index);

    void on_borrowButton_clicked();

    void on_mediaTable_activated(const QModelIndex &index);

    void on_userTable_activated(const QModelIndex &index);

    void on_returnMediumButton_clicked();

    void on_removeButton_clicked();

    void on_userTable_doubleClicked(const QModelIndex &index);

private:
    enum Tab{media, users};
    // gibt an, welche Tabelle derzeit angezeigt wird
    Tab selectedTab = media;
    Ui::MainWindow *ui;
    Library *library;
    //Fenster
    addUser *addPWindow;
    addMedia *addMWindow;
    acceptLending *accLendWindow;
    NoteWindow *noteWindow;
    showMedia *showMediaWindow;

    // Model fuer die Tabellen
    QStandardItemModel *mediumModel;
    QStandardItemModel *userModel;

    // Indizes
    QModelIndex mediumIndex;
    QModelIndex userIndex;
};

#endif // MAINWINDOW_H
