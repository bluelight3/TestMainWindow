#include "cpumemorywidget.h"
#include "ui_cpumemorywidget.h"

CpuMemoryWidget::CpuMemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuMemoryWidget)
{
    ui->setupUi(this);
    FormHelper::FormOnlyCloseButton(this);
    FormHelper::FormNotResize(this);


    initForm();
}

CpuMemoryWidget::~CpuMemoryWidget()
{
    delete ui;
}

void CpuMemoryWidget::initForm()
{
    QFont font;
    font.setPixelSize(16);
    setFont(font);

    QString qss1 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("100,184,255");
//    QString qss2 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("255,107,107");
//    QString qss3 = QString("QLabel{background-color:rgb(0,0,0);color:rgb(%1);}").arg("24,189,155");

    ui->lbl_cpuMemory->setStyleSheet(qss1);
//    ui->label2->setStyleSheet(qss2);
//    ui->label3->setStyleSheet(qss3);

//    connect(ui->label1, SIGNAL(textChanged(QString)), ui->label2, SLOT(setText(QString)));
//    connect(ui->label1, SIGNAL(valueChanged(quint64, quint64, quint64, quint64, quint64)),
//            this, SLOT(valueChanged(quint64, quint64, quint64, quint64, quint64)));
    ui->lbl_cpuMemory->start(1000);
}
