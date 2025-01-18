#include "myitemwidget.h"
#include "ui_myitemwidget.h"
#include "mainwindow.h"



MyItemWidget::MyItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyItemWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(ui->btn_close,&QPushButton::clicked,this,&MyItemWidget::closeWindow);

}

MyItemWidget::~MyItemWidget()
{
    delete ui;
}

void MyItemWidget::setItemName(QString myItemName)
{
    ui->txt_ItemName->setText(myItemName);
}

void MyItemWidget::setItemToggle(QString myToggle)
{
    ui->txt_ItemToggle->setText(myToggle);
}

void MyItemWidget::setItemType(int myType)
{
    ui->comboBox_itemMyType->setCurrentIndex(myType);
}

void MyItemWidget::setItemPixMap(QPixmap myPixmap)
{
    ui->lbl_itemPicture->setPixmap(myPixmap);
}

void MyItemWidget::setTitleName(QString myTitleName)
{
    ui->lbl_title->setText(myTitleName);
}

void MyItemWidget::mousePressEvent(QMouseEvent *event)
{
    mousePressedPosition = event->globalPos();
    windowPositionBeforeMoving = frameGeometry().topLeft(); // 记录窗口左上角坐标
}

void MyItemWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 当按下按钮的位置不为空 表明窗口需要移动
    if (!mousePressedPosition.isNull()){
        QPoint delta = event->globalPos() - mousePressedPosition;
        QPoint newPosition = windowPositionBeforeMoving + delta;
        move(newPosition);
    }
}

void MyItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressedPosition = QPoint();
}

void MyItemWidget::on_btn_ok_clicked()
{
    //  相关参数传给MainWindow类 / 未来的Control类
    QString newToggle = ui->txt_ItemToggle->text();
    if (newToggle == "defaultToggle") return;
    emit setToggle(newToggle);

    QString newName = ui->txt_ItemName->text();
//    if (newName == "defaultName") return;
    emit setName(newName);

    //  关闭窗口
    closeWindow();
}

void MyItemWidget::on_btn_cancel_clicked()
{
    closeWindow();
}

void MyItemWidget::closeWindow()
{
    this->close();
}
