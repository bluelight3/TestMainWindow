#ifndef GENERATEPROJECTFORM_H
#define GENERATEPROJECTFORM_H

#include <QWidget>

namespace Ui {
class GenerateProjectForm;
}

class GenerateProjectForm : public QWidget
{
    Q_OBJECT

public:
    explicit GenerateProjectForm(QWidget *parent = nullptr);
    ~GenerateProjectForm();

private:
    Ui::GenerateProjectForm *ui;
public slots:
    void updateProgress(int progress);
};

#endif // GENERATEPROJECTFORM_H
