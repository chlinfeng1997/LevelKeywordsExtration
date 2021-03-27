#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QMap>
#include <tooltip.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void modifyLetter(QString previousLetterPath, QString currentLetterPath);
    void deleteLetter(QString deletePath);
//    void wordToShow(QMap<QString, int> letterWord, QStackedWidget * stackedWidget);
    void currentIndex(int letterIndex);
    void changeLetter(int letterIndex, QStackedWidget * stackedWidget);
    QVector<QString> letterOrder; //记录listWidget里的文件路径
    QMap<QString, int> letterCorrespondIndex; //保存在StackedWidget中letter路径与索引的对应关系
    int index = 0; //记录letter当前索引
    int stackedWidgetIndex = 0; //记录stackedWidget当前窗口索引
    bool isRepeatedLetter = false;
    QStackedWidget * stackedWidget = NULL; //管理StackedWidget窗口
    QVector<QColor> colorVec;
    QString previousMethod = "饼状图";
    QMap<QString, int> seriesPie;


private:
    Ui::Widget *ui;

signals:
    void wordLoadFinish();

};
#endif // WIDGET_H
