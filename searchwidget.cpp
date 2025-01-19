#include "searchwidget.h"
#include "ui_searchwidget.h"
#include "global.h"
#include "MyHelper.h"

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
{
    ui->setupUi(this);
    FormHelper::FormOnlyCloseButton(this);
    FormHelper::FormNotResize(this);

}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::on_txt_search_returnPressed()
{
    emit search(ui->txt_search->text());
}
