#ifndef ABOUT_OF_AUTHORS_H
#define ABOUT_OF_AUTHORS_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class about_of_authors;
}

class about_of_authors : public QWidget
{
    Q_OBJECT

public:
    explicit about_of_authors(QWidget *parent = nullptr);
    ~about_of_authors();

private:
    Ui::about_of_authors *ui;
    friend class mainwindow;
public slots:
    void aboutAuth();
    void setWindowLanguage(int index);
};

#endif // ABOUT_OF_AUTHORS_H
