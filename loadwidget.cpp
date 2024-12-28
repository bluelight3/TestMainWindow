#include "loadwidget.h"
#include "ui_loadwidget.h"

LoadWidget::LoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWidget)
{
    ui->setupUi(this);


    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    ui->widget->installEventFilter(this);
    ui->widget->setStyleSheet(QString("background-image:url(:/background/%1.png);").arg(1));
}

LoadWidget::~LoadWidget()
{
    delete ui;
}

void LoadWidget::closeWindow()
{
    this->close();
}
