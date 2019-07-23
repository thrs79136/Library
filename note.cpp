#include "note.h"
#include "ui_selectuandm.h"

Note::Note(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));
}

Note::~Note()
{
    delete ui;
}
