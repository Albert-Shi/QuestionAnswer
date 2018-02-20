#include "questionlist.h"
#include "ui_questionlist.h"
#include "core.h"
#include "questioninput.h"

#define SIZE 200

QString TESTFILE = "datas/QBK.dat";
Question qb[SIZE];
int n;
int position;

QuestionList::QuestionList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionList)
{
    Output out;
    n = out.getQustionBank(TESTFILE, qb);
    ui->setupUi(this);
    for(int i = 0; i < n; i++) {
        ui->listWidget->addItem(QString::number(i + 1) + ". " + qb[i].getQuestion());
    }
}

QuestionList::~QuestionList()
{
    delete ui;
}

void QuestionList::on_pushButton_clicked()
{
    this->close();
}

void QuestionList::on_add_button_clicked()
{
    QuestionInput *qi = new QuestionInput;
    qi->exec();
    Output out;
    ui->listWidget->clear();
    n = out.getQustionBank(TESTFILE, qb);
    for(int i = 0; i < n; i++) {
        ui->listWidget->addItem(QString::number(i + 1) + ". " + qb[i].getQuestion());
    }
}

void QuestionList::on_delete_button_clicked()
{
    Input in;
    int p = ui->listWidget->currentRow();
    qb[p].standard = -1;
//    if(p != 0)
        in.create(TESTFILE);
    for(int j = 0; j  < n; j++) {
        if(qb[j].standard != -1) {
            in.add(TESTFILE, qb[j]);
        }
    }
    ui->listWidget->clear();
    for(int k = 0; k < n; k++) {
        ui->listWidget->addItem(QString::number(k + 1) + ". " + qb[k].getQuestion());
    }
    this->close();
    QuestionList *ql = new QuestionList;
    ql->show();
}
