#include "answerui.h"
#include "ui_answerui.h"
#include "core.h"

#define SIZE 200

//int SELECT;
//extern int STANDARD[SIZE];
extern bool STOP;
extern Output out;
extern Question qbd[SIZE];
extern int POSITION;
extern int QUANTITY;
extern int EXIST;

int CORRECT;

AnswerUI::AnswerUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerUI)
{
    ui->setupUi(this);

//    SELECT = -1;
    fillquestion(POSITION);
    if(POSITION == QUANTITY - 1) {
        ui->next_button->setText("交卷!");
    }
    if(qbd[out.qustionOrder[POSITION]].choosed != -1) {
        switch (qbd[out.qustionOrder[POSITION]].choosed) {
        case 0:
            ui->radioButton->setChecked(true);
            break;
        case 1:
            ui->radioButton_2->setChecked(true);
            break;
        case 2:
            ui->radioButton_3->setChecked(true);
            break;
        case 3:
            ui->radioButton_4->setChecked(true);
            break;
        default:
            break;
        }
    }
}

AnswerUI::~AnswerUI()
{
    delete ui;
}

void AnswerUI::on_radioButton_clicked()
{
//    SELECT = 0;
    qbd[out.qustionOrder[POSITION]].choosed = 0;
}

void AnswerUI::on_radioButton_2_clicked()
{
 //   SELECT = 1;
    qbd[out.qustionOrder[POSITION]].choosed = 1;
}

void AnswerUI::on_radioButton_3_clicked()
{
//    SELECT = 2;
    qbd[out.qustionOrder[POSITION]].choosed = 2;
}

void AnswerUI::on_radioButton_4_clicked()
{
//    SELECT = 3;
    qbd[out.qustionOrder[POSITION]].choosed = 3;
}

void AnswerUI::on_next_button_clicked()
{
//    qDebug()<<"SELECT : "<<SELECT;
    if(qbd[out.qustionOrder[POSITION]].choosed == -1) {
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
//            if(qbd[out.qustionOrder[POSITION]].standard == SELECT)
//                CRRECT++;
            POSITION++;
            AnswerUI *n = new AnswerUI;
            n->show();
            this->close();
        }else{
            CORRECT = 0;
            for(int j = 0; j < QUANTITY; j++) {
                if(qbd[out.qustionOrder[j]].choosed == qbd[out.qustionOrder[j]].standard)
                    CORRECT++;
            }

            //创建需要的Dialog窗体，总布局，文字布局，按钮布局，Label，pushbutton
            QDialog *qd = new QDialog;
            QVBoxLayout *mainl = new QVBoxLayout;
            QVBoxLayout *qvb = new QVBoxLayout;
            QVBoxLayout *qvbb = new QVBoxLayout;
            QString grade = QString::number((100.0/QUANTITY)*CORRECT);
            QString text ="共:" + QString::number(QUANTITY) + "题, 答对:" + QString::number(CORRECT) + "题\n" +  "总分: " +  grade;
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
    //创建需要的Dialog窗体，总布局，文字布局，按钮布局，Label，pushbutton
    QDialog *qd = new QDialog;
    QVBoxLayout *mainl = new QVBoxLayout;
    QVBoxLayout *qvb = new QVBoxLayout;
    QVBoxLayout *qvbb = new QVBoxLayout;
    QString text = "题库没有足够的题目，将以最大题量:" + QString::number(EXIST) + "进行测试!";
    QLabel *qlbel = new QLabel(text, qd);
    QPushButton *qpb = new QPushButton(QWidget::tr("确定"), qd);
    QPushButton *qpb2 = new QPushButton(QWidget::tr("cancel"), qd);

    //设置信号跟槽
    connect(qpb, SIGNAL(clicked(bool)), qd, SLOT(close()));
    connect(qpb, SIGNAL(clicked(bool)), this, SLOT(close()));
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
//    STOP = true;
//    this->close();
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
