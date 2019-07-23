#ifndef SELECTUANDM_H
#define SELECTUANDM_H

#include <QDialog>

namespace Ui {
class Note;
}

class Note : public QDialog
{
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
 //   QPushButton* getOKButton(){}
    ~Note();

private:
    Ui::Note *ui;
};

#endif // SELECTUANDM_H
