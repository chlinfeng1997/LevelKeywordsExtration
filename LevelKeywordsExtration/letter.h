#ifndef LETTER_H
#define LETTER_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QMap>

class Letter : public QWidget
{
    Q_OBJECT
public:
//    explicit Letter(QWidget *parent = nullptr);
      Letter(QString letterPath, int letterIndex);

      int letterIndex = 0; //保存该letter的索引
      int modifyTimes = 0; //记录修改路径的次数
      QString previousLetterPath; //保存之前letter的路径
      QString currentLetterPath; //保存当前letter的路径
//      QMap<QString, int> letterWord; //保存top10单词
//      int wordAll = 0; //保存letter总字数
      void mousePressEvent(QMouseEvent *e);
      QLabel *isloadLabel;


signals:
    void modifyLetter(QString previousLetterPath, QString currentLetterPath);
    void deleteLetter(QString deletePath);
//    void wordToShow(QMap<QString, int> letterWord);
    void currentIndex(int letterIndex, QString currentLetterPath);
};

#endif // LETTER_H
