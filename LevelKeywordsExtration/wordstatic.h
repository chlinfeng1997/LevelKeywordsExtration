#ifndef WORDSTATIC_H
#define WORDSTATIC_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QMap>
struct Record
{
    QString word;
    int freq;
};

class WordStatic : public QWidget
{
    Q_OBJECT
public:
//    explicit WordStatic(QWidget *parent = nullptr);
      WordStatic(QString filename);
      void readStopWord(QString filename);
      void readFile(QString filename);
      void writeFile(QString  filename);
      bool isNum(QString str);
      QVector<Record> vec; //记录所有除停止词以外的(单词 词频)
//      QMap<QString, int> topWord; //保存top10单词
      QVector<QString> stopWord; //记录停止词

signals:

};

#endif // WORDSTATIC_H
