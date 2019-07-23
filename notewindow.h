#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QDialog>

namespace Ui {
class NoteWindow;
}

class NoteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NoteWindow(QWidget *parent = nullptr);
    void changeLabel(QString text);
    ~NoteWindow();

private:
    Ui::NoteWindow *ui;
};

#endif // NOTEWINDOW_H
