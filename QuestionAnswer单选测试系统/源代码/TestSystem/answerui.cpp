#include "answerui.h"
#include "ui_answerui.h"
#include "core.h"

#define SIZE 200

int SELECT;
//extern int STANDARD[SIZE];
extern int CRRECT;
extern bool STOP;
extern Output out;
extern Question qbd[SIZE];
extern int POSITION;
extern int QUANTITY;
extern int EXIST;

AnswerUI::AnswerUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerUI)
{
    ui->setupUi(this);

    SELECT = -1;
    fillquestion(POSITION);
}

AnswerUI::~AnswerUI()
{
    delete ui;
}

void AnswerUI::on_radioButton_clicked()
{
    SELECT = 0;
}

void AnswerUI::on_radioButton_2_clicked()
{
    SELECT = 1;
}

void AnswerUI::on_radioButton_3_clicked()
{
    SELECT = 2;
}

void AnswerUI::on_radioButton_4_clicked()
{
    SELECT = 3;
}

void AnswerUI::on_next_button_clicked()
{
    qDebug()<<"SELECT : "<<SELECT;
    if(SELECT == -1) {
        //创建需要的Dialog窗体，总布局，文字布局，按钮布局，Label，pushbutton
        QDialog *qd = new QDialog;
        QVBoxLayout *mainl = new QVBoxLayout;
        QVBoxLayout *qvb = new QVBoxLayout;
        QVBoxLayout *qvbb = new QVBoxLayout;
        QLabel *qlbel = new QLabel(QWidget::tr("没有选择任何选项，请重新选择!"), qd);
        QPushButton *qpb = new QPushButton(QWidget::tr("确定"), qd);

        //设置信号跟槽
        connect(qpb, SIGNAL(clicked(bool)), qd, SLOT(close()));
        connect(qpb, SIGNAL(clicked(bool)), this, SLOT(show()));

        //设置基本参数(Dialog大小，标题，添加布局),show
        qpb->setDefault(true);
        qd->setWindowTitle("错误");
        qd->resize(QSize(150,100));
        qvbb->addWidget(qpb);
        qvb->addWidget(qlbel);
        mainl->addLayout(qvb);
        mainl->addLayout(qvbb);
        qd->setLayout(mainl);
        qd->exec();
    }else{
        if(POSITION < QUANTITY - 1) {
            if(qbd[out.qustionOrder[POSITION]].standard == SELECT)
                CRRECT++;
            POSITION++;
            AnswerUI *n = new AnswerUI;
            n->show();
            this->close();
        }else{
            //创建需要的Dialog窗体，总布局，文字布局，按钮布局，Label，pushbutton
            QDialog *qd = new QDialog;
            QVBoxLayout *mainl = new QVBoxLayout;
            QVBoxLayout *qvb = new QVBoxLayout;
            QVBoxLayout *qvbb = new QVBoxLayout;
            QString grade = QString::number((100.0/QUANTITY)*CRRECT);
            QString text ="共:" + QString::number(QUANTITY) + "题, 答对:" + QString::number(CRRECT) + "题\n" +  "总分: " +  grade;
            QLabel *qlbel = new QLabel(text, qd);
            QPushButton *qpb = new QPushButton(QWidget::tr("确定"), qd);

            //设置信号跟槽
            connect(qpb, SIGNAL(clicked(bool)), qd, SLOT(close()));
            connect(qpb, SIGNAL(clicked(bool)), this, SLOT(close()));

            //设置基本参数(Dialog大小，标题，添加布局),show
            qpb->setDefault(true);
            qd->setWindowTitle("成绩");
            qd->resize(QSize(150,100));
            qvbb->addWidget(qpb);
            qvb->addWidget(qlbel);
            mainl->addLayout(qvb);
            mainl->addLayout(qvbb);
            qd->setLayout(mainl);
            qd->exec();
        }
    }
}

void AnswerUI::on_pushButton_clicked()
{
    STOP = true;
    this->close();
}

void AnswerUI::on_pushButton_2_clicked()
{
    if(POSITION > 0) {
        POSITION--;
        AnswerUI *l = new AnswerUI;
        l->show();
        this->close();
    }
}

void AnswerUI::fillquestion (int p) {
    ui->question_textbrowser->setText(qbd[out.qustionOrder[p]].getQuestion());
    ui->A_textBrowser->setText(qbd[out.qustionOrder[p]].getKey(qbd[out.qustionOrder[p]].optionOrder[0]));
    ui->B_textbrowser->setText(qbd[out.qustionOrder[p]].getKey(qbd[out.qustionOrder[p]].optionOrder[1]));
    ui->C_textbrowser->setText(qbd[out.qustionOrder[p]].getKey(qbd[out.qustionOrder[p]].optionOrder[2]));
    ui->D_textbrowser->setText(qbd[out.qustionOrder[p]].getKey(qbd[out.qustionOrder[p]].optionOrder[3]));
}
