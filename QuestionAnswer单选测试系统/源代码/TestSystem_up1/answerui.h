#ifndef ANSWERUI_H
#define ANSWERUI_H

#include <QDialog>

namespace Ui {
class AnswerUI;
}

class AnswerUI : public QDialog
{
    Q_OBJECT

public:
    explicit AnswerUI(QWidget *parent = 0);
    ~AnswerUI();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_next_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::AnswerUI *ui;
};

#endif // ANSWERUI_H
