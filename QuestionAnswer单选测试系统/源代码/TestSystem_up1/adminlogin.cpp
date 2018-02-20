#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "questionlist.h"
#include <QMessageBox>
#include <QPushButton>
#include "core.h"

QString ACCOUNTFILE = "datas/AD.dat";

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_buttonBox_accepted()
{
    Account a(ui->account_line->text(), ui->password_line->text());
    Output out;
    if(out.matchAccount(ACCOUNTFILE,a)){
        QuestionList *ql = new QuestionList;
        ql->show();
    }else{
        //创建需要的Dialog窗体，总布局，文字布局，按钮布局，Label，pushbutton
        QDialog *qd = new QDialog;
        QVBoxLayout *mainl = new QVBoxLayout;
        QVBoxLayout *qvb = new QVBoxLayout;
        QVBoxLayout *qvbb = new QVBoxLayout;
        QLabel *qlbel = new QLabel(QWidget::tr("账号或密码错误!请重新输入"), qd);
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
        qd->show();
    }
}
