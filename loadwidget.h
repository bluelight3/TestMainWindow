#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QWidget>

namespace Ui {
class LoadWidget;
}

class LoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadWidget(QWidget *parent = nullptr);
    ~LoadWidget();
    void closeWindow();

private:
    Ui::LoadWidget *ui;
};

#endif // LOADWIDGET_H
