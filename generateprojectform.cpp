#include "generateprojectform.h"
#include "ui_generateprojectform.h"

GenerateProjectForm::GenerateProjectForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenerateProjectForm)
{
    ui->setupUi(this);
}

GenerateProjectForm::~GenerateProjectForm()
{
    delete ui;
}

void GenerateProjectForm::updateProgress(int progress)
{
    ui->pgs_generate->setValue(progress);
    this->update();
}
