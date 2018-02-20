#include "questioninput.h"
#include "ui_questioninput.h"
#include "core.h"

QString FILEPATH = "datas/QBK.dat";

QuestionInput::QuestionInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionInput)
{
    ui->setupUi(this);
}

QuestionInput::~QuestionInput()
{
    delete ui;
}

void QuestionInput::on_buttonBox_accepted()
{
    Input in;
    Question *q = new Question;
    q->setQuestion(ui->question_line->text(),ui->standard_line->text(),ui->key1_line->text(),ui->key2_line->text(),ui->key3_line->text());
    in.add(FILEPATH,*q);
}
