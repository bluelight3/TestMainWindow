#include "myitemidget.h"
#include "ui_myitemidget.h"

MyItemidget::MyItemidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyItemidget)
{
    ui->setupUi(this);
}

MyItemidget::~MyItemidget()
{
    delete ui;
}

void MyItemidget::setItemName(QString itemName)
{
    ui->txt_itemName->setText(itemName);
}

void MyItemidget::setItemToggle(QString itemToggle)
{
    ui->txt_itemToggle->setText(itemToggle);
}

void MyItemidget::setItemMyType(int i)
{
    ui->comboBox_itemMyType->setCurrentIndex(i);
}

void MyItemidget::setItemPixmap(QPixmap pixmap)
{
    ui->lbl_itemPicture->setPixmap(pixmap);
}

void MyItemidget::on_btn_ok_clicked()
{
    // 向主界面 / Control 发送Item更新信号

    // 关闭当前Widget
    this->close();
}

void MyItemidget::on_btn_cancel_clicked()
{
    //  关闭当前Widget
    this->close();
}
