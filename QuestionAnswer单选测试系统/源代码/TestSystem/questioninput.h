#ifndef QUESTIONINPUT_H
#define QUESTIONINPUT_H

#include <QDialog>

namespace Ui {
class QuestionInput;
}

class QuestionInput : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionInput(QWidget *parent = 0);
    ~QuestionInput();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::QuestionInput *ui;
};

#endif // QUESTIONINPUT_H
