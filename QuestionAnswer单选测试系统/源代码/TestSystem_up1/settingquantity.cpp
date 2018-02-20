#include "settingquantity.h"
#include "ui_settingquantity.h"
#include "core.h"
#include "answerui.h"
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QtDebug>

#define SIZE  200

Question G_QUESTION;
QString QBANKPATH = "datas/QBK.dat";
//int ANSWER[SIZE];
//int STANDARD[SIZE];
int CRRECT;
bool STOP;


SettingQuantity::SettingQuantity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingQuantity)
{
    ui->setupUi(this);
    qDebug()<<"setupUi is successful!";
}

SettingQuantity::~SettingQuantity()
{
    delete ui;
}

int judge(int n, int *standard, int *answer) {
    int number = 0;
    for(int j = 0; j < n; j++) {
        if(standard[j] == answer[j])
            number++;
    }
    return number;
}

void SettingQuantity::on_pushButton_clicked()
{
    qDebug()<<"click button and start test!";
    CRRECT = 0;
    STOP = false;
    Question qb[SIZE];
    int number = ui->lineEdit->text().toInt();
    Output out;
    int exist = out.getQustionBank(QBANKPATH, qb);
    qDebug()<<"exist: "<<exist;
    if(exist != -1){
        if(number > exist) {
            number = exist;
        }
        out.getQustionOrder(exist, number);


        for(int i = 0; i < number; i++) {
            if(STOP == true)
                break;
            G_QUESTION = qb[out.qustionOrder[i]];
            qDebug()<<"the: "<<i<<"question";
            AnswerUI *aui = new AnswerUI;
            aui->exec();
        }
        //创建需要的Dialog窗体，总布局，文字布局，按钮布局，Label，pushbutton
        QDialog *qd = new QDialog;
        QVBoxLayout *mainl = new QVBoxLayout;
        QVBoxLayout *qvb = new QVBoxLayout;
        QVBoxLayout *qvbb = new QVBoxLayout;
        QString grade = QString::number((100.0/number)*CRRECT);
        QString text ="共:" + QString::number(number) + "题, 答对:" + QString::number(CRRECT) + "题\n" +  "总分: " +  grade;
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

    /*
    QDialog *paper = new QDialog;
    QVBoxLayout *containerlayot = new QVBoxLayout;
    QVBoxLayout *mainlayout = new QVBoxLayout;
    QVBoxLayout *buttonlayout = new QVBoxLayout;
    QPushButton *postbutton = new QPushButton(QWidget::tr("提交"), paper);
    buttonlayout->addWidget(postbutton);
    containerlayot->addLayout(mainlayout);
    containerlayot->addLayout(buttonlayout);
    for(int i = 0; i < number; i++) {
        Question *position = new Question(qb[out.qustionOrder[i]]);
        position->getQustionOptionOrder((unsigned)time(NULL)+i);    //保证时间种子不同
        STANDARD[i] =  position->standard;
        QVBoxLayout *questionlayout = new QVBoxLayout;
        QHBoxLayout *titlelayout = new QHBoxLayout;
        QHBoxLayout *key1layout = new QHBoxLayout;
        QHBoxLayout *key2layout = new QHBoxLayout;
        QHBoxLayout *key3layout = new QHBoxLayout;
        QHBoxLayout *key4layout = new QHBoxLayout;
        QLabel *tips = new QLabel;
        tips->setText(tr("题目:"));
        QLabel *questiontext = new QLabel;
        QString qstr = position->getQuestion();
        questiontext->setText(qstr);
        titlelayout->addWidget(tips);
        titlelayout->addWidget(questiontext);

        QRadioButton *a = new QRadioButton;
        a->setText("A:");
        QLabel *key1 = new QLabel;
        QString k0str = position->getKey(position->optionOrder[0]);
        key1->setText(k0str);
        key1layout->addWidget(a);
        key1layout->addWidget(key1);

        QRadioButton *b = new QRadioButton;
        b->setText("B:");
        QLabel *key2 = new QLabel;
        QString k1str = position->getKey(position->optionOrder[1]);
        key2->setText(k1str);
        key2layout->addWidget(b);
        key2layout->addWidget(key2);

        QRadioButton *c = new QRadioButton;
        c->setText("C:");
        QLabel *key3 = new QLabel;
        QString k2str = position->getKey(position->optionOrder[2]);
        key3->setText(k2str);
        key3layout->addWidget(c);
        key3layout->addWidget(key3);

        QRadioButton *d = new QRadioButton;
        d->setText("D:");
        QLabel *key4 = new QLabel;
        QString k3str = position->getKey(position->optionOrder[3]);
        key4->setText(k3str);
        key4layout->addWidget(d);
        key4layout->addWidget(key4);

        questionlayout->addLayout(titlelayout);
        questionlayout->addLayout(key1layout);
        questionlayout->addLayout(key2layout);
        questionlayout->addLayout(key3layout);
        questionlayout->addLayout(key4layout);
        mainlayout->addLayout(questionlayout);
    }
    paper->setLayout(containerlayot);

    paper->show();
    */
}

