#ifndef ABOUT_PROGRAM_FORM_H
#define ABOUT_PROGRAM_FORM_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class about_program_Form;
}

class about_program_Form : public QWidget
{
    Q_OBJECT

public:
    explicit about_program_Form(QWidget *parent = nullptr);
    ~about_program_Form();

private:
    Ui::about_program_Form *ui;
    friend class mainwindow;
public slots:
    void aboutShow();
    void on_languagesBox_currentIndexChanged(int index);
};

#endif // ABOUT_PROGRAM_FORM_H
