#include "showmedia.h"
#include "ui_showmedia.h"
#include "medium.h"
#include "user.h"

showMedia::showMedia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showMedia)
{
    ui->setupUi(this);
}

// zeigt die ausgeliehenen Medien eines Nutzers an
void showMedia::printList(User *pU, QList<Medium *> mediumList){
    ui->mediaTextBrowser->setText("");
    if (mediumList.empty())
        ui->mediaTextBrowser->setText("Der Nutzer besitzt derzeit keine entliehenen Medien.");
    for (Medium *pM: mediumList)
        ui->mediaTextBrowser->append(pM->getMediumData() + "\n");
    ui->userLabel->setText(pU->getUserData());
}

showMedia::~showMedia()
{
    delete ui;
}
