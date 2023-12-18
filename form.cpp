#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QPixmap emoji("D:/Projects/Qt/mahjong/img/win.png");
    ui->label_2->setPixmap(emoji.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Form::~Form()
{
    delete ui;
}
