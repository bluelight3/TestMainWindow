#include "myitemwidget.h"
#include "ui_myitemwidget.h"

MyItemWidget::MyItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyItemWidget)
{
    ui->setupUi(this);
}

MyItemWidget::~MyItemWidget()
{
    delete ui;
}
