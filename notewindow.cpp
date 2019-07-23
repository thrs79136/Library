#include "notewindow.h"
#include "ui_notewindow.h"

NoteWindow::NoteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoteWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->habsGerafftButton, SIGNAL(clicked()), this, SLOT(close()));
}

NoteWindow::~NoteWindow()
{
    delete ui;
}

void NoteWindow::changeLabel(QString text){
    ui->noteLabel->setText(text);
    ui->noteLabel->setAlignment(Qt::AlignCenter);
}
