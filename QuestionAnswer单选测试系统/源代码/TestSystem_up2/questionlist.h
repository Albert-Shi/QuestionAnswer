#ifndef QUESTIONLIST_H
#define QUESTIONLIST_H

#include <QDialog>

namespace Ui {
class QuestionList;
}

class QuestionList : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionList(QWidget *parent = 0);
    ~QuestionList();

private slots:
    void on_pushButton_clicked();

    void on_add_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::QuestionList *ui;
};

#endif // QUESTIONLIST_H
