#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget();

private:
    Ui::SearchWidget *ui;

signals:
    void search(QString);

private slots:
    void on_txt_search_returnPressed();
};

#endif // SEARCHWIDGET_H
