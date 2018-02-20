#ifndef CORE
#define CORE

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QtDebug>

#define LINESIZE 50

using namespace std;

class Account{
  QString Name;
  QString Password;
public:
  Account(){}
  Account(QString name, QString passwd){
      setAccount(name, passwd);
  }
  void setAccount(QString name, QString passwd){
      Name = name;
      Password = passwd;
  }

  QString getName(){
      return Name;
  }
  QString getPassword(){
      return Password;
  }

  bool compare(Account &account){
      if(account.getName() == Name && account.getPassword() == Password){
          return true;
      }else{
          return false;
      }
  }
};

class Question{
    QString question;                                                    //题目信息
    QString key_standard;                                                //标准答案
    QString key1;                                                        //备选答案1
    QString key2;                                                        //备选答案2
    QString key3;                                                        //备选答案3
public:
    int standard;                                                       //在随机排序后，标准答案在4个答案中的位置
    int optionOrder[4];                                                 //记录随机排序后4个选项位置

    Question() {}

    Question(Question &q) {
        question = q.getQuestion();
       key_standard = q.get1stKey_standard();
       key1 = q.get2ndKey();
       key2 = q.get3rdKey();
       key3 = q.get4thKey();
    }

    Question(QString q, QString standardkey, QString k1, QString k2, QString k3) {
        setQuestion(q, standardkey, k1, k2, k3);
    }

    Question(char* q, char* standardkey, char* k1, char* k2, char* k3) {
        setQuestion(q, standardkey, k1, k2, k3);
    }

    void setQuestion(QString q, QString standardkey, QString k1, QString k2, QString k3) {   //建立Question对象信息
        question = q;
        key_standard = standardkey;
        key1 = k1;
        key2 = k2;
        key3 = k3;
        getQustionOptionOrder((unsigned)time(NULL));
    }

    void setQuestion(char* q, char* standardkey, char* k1, char* k2, char* k3) {        //建立Question对象信息
        question = QString(q);
        key_standard = QString(standardkey);
        key1 = QString(k1);
        key2 = QString(k2);
        key3 = QString(k3);
        getQustionOptionOrder((unsigned)time(NULL));
    }

    int* getQustionOptionOrder (unsigned t){                                     //将4个选项进行随机排序
        srand(t);
        int i = 0;
        int judge[4];
        while(i < 4) {
            int number = rand() % (3 - 0 + 1) + 0;                    //假设范围是 [a, b];//create random range is from 0 to 4
            if(judge[number] != 1) {                                  //int range = b - a + 1;
                judge[number] = 1;                                    //int val = rand() % range + a;
                if (number == 0)                                      //rand() % range 就是 rand() 生成的数对range取余，数值就会在 [0, range) 之间， 加上 a,就是 [a , a+ range) -> [a, b+1) -> [a, b]
                    standard = i;
                optionOrder[i] = number;
                i++;
            }
        }
        return optionOrder;
    }

    QString getQuestion () {                                         //获取题目
        return question;
    }
    QString get1stKey_standard () {                                  //获取标准答案
        return key_standard;
    }
    QString get2ndKey () {                                           //获取备选答案1
        return key1;
    }
    QString get3rdKey () {                                           //获取备选答案2
        return key2;
    }
    QString get4thKey () {                                           //获取备选答案3
        return key3;
    }

    QString getKey (int i) {
        switch(i) {
            case 0:
                return key_standard;
            case 1:
                return key1;
            case 2:
                return key2;
            case 3:
                return key3;
            default:
                return NULL;
        }
    }
};

class Input{
public:
//    void create(string filePath, string content) {                  //filePath:文件路径，content:题目内容
    void create(QString filePath, QString content) {
//        ofstream fout(filePath, ios::out|ios::binary);
        QFile fout(filePath);
//        if(fout) {                                                                     //c++
        if(fout.open(QFile::WriteOnly)){                                      //Qt
            QTextStream stream(&fout);
//            fout<<"*--question--*\n"<<content<<"\n";
            stream<<"*--question--*\n"<<content<<"\n";
            fout.close();
        }
        else {
            cout<<"Can't open output file!"<<endl;
            exit(1);
        }
    }

    void create(QString filePath, Question q) {
        QString content = q.getQuestion() + "\n" + q.get1stKey_standard() + "\n" + q.get2ndKey() + "\n" + q.get3rdKey() + "\n" + q.get4thKey();
        create(filePath, content);
    }

    void create(QString filePath) {
        QFile fout(filePath);
        if(fout.open(QFile::WriteOnly)){
            QTextStream stream(&fout);
            stream<<"";
            fout.close();
        }
        else {
            cout<<"Can't open output file!"<<endl;
            exit(1);
        }
    }

    void add(QString filePath, QString content) {                     //filePath:文件路径，content:题目内容
//        ofstream fout(filePath, ios::app|ios::binary);
        QFile fout(filePath);
        if(fout.open(QFile::Append)) {
            QTextStream stream(&fout);
            stream<<"*--question--*\n"<<content<<"\n";
            fout.close();
        }
        else {
            cout<<"Can't open output file!"<<endl;
            exit(1);
        }
    }

    void add(QString filePath, Question q) {
        QString content = q.getQuestion() + "\n" + q.get1stKey_standard() + "\n" + q.get2ndKey() + "\n" + q.get3rdKey() + "\n" + q.get4thKey();
        add(filePath, content);
    }
};

class Output {
public:
    int qustionOrder[LINESIZE];                                     //存储随机排序后题目的顺序
    int getQustionBank (QString questionBankPath, Question* qb) {    //从题库中提取 Question/题目 对象,并存入Question数组qb中
        int i = 0;                                                  //当读取一个完整的Question对象，则i++
//        ifstream fin(questionBankPath, ios::in)
        qDebug()<<"First Step is OK";
        QFile fin(questionBankPath);
        if(fin.open(QFile::ReadOnly)) {
            QTextStream stream(&fin);
            QString result;
            while ((result = stream.readLine()) != NULL) {
//                char temp[LINESIZE];
//                fin.getline(temp, LINESIZE);
                if(result == "*--question--*") {                    //以读取的“*--question--*”为标识，下面的5行依次为 题目，标准答案，备选答案1，备选答案2，备选答案3
                    result = "";
                    QString ques = stream.readLine();
//                    string question(temp);
                    QString t0 = stream.readLine();
//                    string k1(temp);
                    QString t1= stream.readLine();
//                    string k2(temp);
                    QString t2 = stream.readLine();
//                    string k3(temp);
                    QString t3 = stream.readLine();
//                    string k4(temp);
                    Question *q = new Question;
                    q->setQuestion(ques, t0, t1, t2, t3);
                    qb[i] = *q;
                    i++;
                    qDebug()<<"The i is:"<<i;
                }
            }
            fin.close();
        }
        else {
            cout<<"Can't open input file!"<<endl;
            return -1;
        }
        return i;                                                   //获取得到 Question/题目 对象的个数
    }

    int* getQustionOrder (int sum, int n){                          //从sum个 题目/Question对象 随机抽选出其中n个(进行随机排序)
        srand((unsigned)time(NULL));
        int i = 0;
        int judge[LINESIZE];                                        //将选中过的序号，在judge中占据相应的位置，方便判断是否取过此数
        while(i < n) {
            int number = rand() % ((sum - 1) - 0 + 1) + 0;          //同上
            if(judge[number] != 1) {
                judge[number] = 1;
                qustionOrder[i] = number;                           //将选中的题号记录到questionOrder的第i位上
                i++;
            }
        }
        return qustionOrder;
    }

    bool matchAccount (QString accountBankPath, Account account) {
//        int i = 0;
        QFile fin(accountBankPath);
        if(fin.open(QFile::ReadOnly)) {
            QTextStream stream(&fin);
            QString result;
            while ((result = stream.readLine()) != NULL) {
                if(result == "*--account--*") {
                    QString name = stream.readLine();
                    QString passwd = stream.readLine();
                    Account *a = new Account(name, passwd);
                    if(a->compare(account)){
                        fin.close();
                        return true;
                    }
//                    i++;
                }
            }
            fin.close();
        }
        else {
            cout<<"Can't open input file!"<<endl;
            exit(1);
        }
        return false;
    }
};


/*
int main() {
    //以下均为测试使用
    int n;
    int op;
    int m;
    Input in;
    Output out;
    Question QB[200];
    Question q;
    n = out.getQustionBank("/home/shishuheng/devkits/test.txt", QB);
    out.getQustionOrder(n,1);
    for(int i = 0; i < 1; i++) {
        QB[i].getQustionOptionOrder();
        cout << QB[i].getQuestion().toStdString() << endl << QB[i].getKey(QB[i].optionOrder[0]).toStdString() << endl;
        cout << QB[i].getKey(QB[i].optionOrder[1]).toStdString() << endl << QB[i].getKey(QB[i].optionOrder[2]).toStdString() << endl;
        cout << QB[i].getKey(QB[i].optionOrder[3]).toStdString() << endl << QB[i].standard << endl << "please Input You answer: " <<
        endl;
        cin >> op;
        if (op == QB[i].standard + 1)
            cout << "You're Right" << endl;
        else
            cout << "You're Wrong" << endl;

    }
    //
    return 0;
}
*/

/*
 * 基本操作
Input类用于输入，添加题目
Output类用于将文本数据转化为Question对象，将Question对象排序
Question类用于生成Question对象，获取对象中的各个元素，将选项排序
(1)创建文件Input类实例化：
 Input in;
 in.create(string filePath, Question q)
   或in.create(string filePath, string content) 其中 content = question + "\n" + 1stKey_standard() + "\n" + 2ndKey() + "\n" + 3rdKey + "\n" + 4thKey;
(2)添加内容
 in.add(string filePath, Question q)
   或in.add(string filePath, string content) 其中 content = question + "\n" + 1stKey_standard() + "\n" + 2ndKey() + "\n" + 3rdKey + "\n" + 4thKey;
(3)获取Question对象
 Output out;
 out.getQustionBank (string questionBankPath, Question* qb)；
(4)将取得的所有数组中总共sum个 题目/Question对象 随机抽选出其中n个(进行随机排序),得到的顺序信息存储在order[LINESIZE]中
 order = out.getQustionOrder (int sum, int n);
(5)创建Question对象
 Question q(string q, string standardkey, string k1, string k2, string k3),依次填入 题目， 标准答案， 备选答案1， 备选答案2， 备选答案3
 或用q.setQuestion(string q, string standardkey, string k1, string k2, string k3),此为相同的功能
(6)将 题目/Question对象 排序, 得到的顺序信息存储在order[4]中
 order = q.getQustionOptionOrder();
 也可通过q.optionOrder[i] i = 0~3;取得答案序号index，即(int) index = q.optionOrder[i];
 其中正确答案序号可通过q.standard取得
 已知答案序号可以通过q.getKey(int index),将会返回string类型的答案数据
(7)判分系统
 还没做，准备弄qt的时候顺带弄，主要就是
 总分 = (100分 / 选取的题目数) * 做对的题目数
 题目数需自己设定（需小于等于题库总题目数），做对的题目用判断记录一下，没难度
就酱紫,啦啦啦~
 160603
 */

#endif // CORE

