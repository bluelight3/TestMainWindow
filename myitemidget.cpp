#include "myitemidget.h"
#include "ui_myitemidget.h"


MyItemidget::MyItemidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyItemidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

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

void MyItemidget::setTitleName(QString titleName)
{
    ui->lbl_title->setText("图元"+titleName);
}

void MyItemidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap(":/images/shadow.png");
    qDrawBorderPixmap(&painter,event->rect(),QMargins(23, 12, 23, 3),pixmap);
}

// 鼠标按下时记录此时鼠标的全局坐标和窗口左上角的坐标
void MyItemidget::mousePressEvent(QMouseEvent *event)
{
    mousePressedPosition = event->globalPos();
    windowPositionBeforeMoving = frameGeometry().topLeft();
}

// 鼠标放开时设置 mousePressedPosition 为空坐标
void MyItemidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressedPosition = QPoint();
}

// 鼠标移动时如果 mousePressedPosition 不为空，则说明需要移动窗口
// 鼠标移动的位移差，就是窗口移动的位移差
void MyItemidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!mousePressedPosition.isNull()) {
        QPoint delta = event->globalPos() - mousePressedPosition;
        QPoint newPosition = windowPositionBeforeMoving + delta;
        move(newPosition);
    }
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

void MyItemidget::on_btn_close_clicked()
{
    this->close();
}
