#include "answerui.h"
#include "ui_answerui.h"
#include "core.h"

#define SIZE 200

int SELECT = -1;
extern Question G_QUESTION;
//extern int STANDARD[SIZE];
extern int CRRECT;
extern bool STOP;

AnswerUI::AnswerUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerUI)
{
    ui->setupUi(this);

    G_QUESTION.getQustionOptionOrder((unsigned)time(NULL));
    ui->question_textbrowser->setText(G_QUESTION.getQuestion());
    ui->A_textBrowser->setText(G_QUESTION.getKey(G_QUESTION.optionOrder[0]));
    ui->B_textbrowser->setText(G_QUESTION.getKey(G_QUESTION.optionOrder[1]));
    ui->C_textbrowser->setText(G_QUESTION.getKey(G_QUESTION.optionOrder[2]));
    ui->D_textbrowser->setText(G_QUESTION.getKey(G_QUESTION.optionOrder[3]));
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
        if(G_QUESTION.standard == SELECT) {
            CRRECT++;
        }
        this->close();
    }
}

void AnswerUI::on_pushButton_clicked()
{
    STOP = true;
    this->close();
}
