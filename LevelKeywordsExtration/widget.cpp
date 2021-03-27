#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include <letter.h>
#include <QList>
#include <QMessageBox>
#include <wordstatic.h>
#include <QTime>
#include <QStackedWidget>
#include <QtCharts>
#include <QMovie>
#include <QBarSet>
#include <tooltip.h>
QT_CHARTS_USE_NAMESPACE
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("英文词频展示系统");
    this->setWindowIcon(QIcon(":/res/Title.ico"));
    this->setFixedSize(1000, 600);
    this->setStyleSheet("background-color: rgb(255,255, 255)");
//    ui->letterList->setStyleSheet("border:1px solid darkgray");
    QStackedWidget * stackedWidget = new QStackedWidget(ui->widget);
    stackedWidget->setGeometry(30, 10, 480, 500);
    ui->addBtn->setFixedSize(150,30);
    ui->addBtn->setStyleSheet("background-color: rgb(230,230, 230)");
    ui->deleteBtn->setFixedSize(150,30);
    ui->deleteBtn->setStyleSheet("background-color: rgb(230,230, 230)");
//    stackedWidget->setStyleSheet("border:1px solid darkgray");
    //请添加文件画面
    QWidget * analyseWidegt = new QWidget(stackedWidget);
    QLabel * analyse = new QLabel(analyseWidegt);
    analyse->setPixmap(QPixmap(":/res/analyse.jpg"));
    QHBoxLayout * analyseHBoxLayout = new QHBoxLayout;
    analyseHBoxLayout->setContentsMargins(0, 0, 0, 0);
    analyseHBoxLayout->setMargin(0);
    analyseHBoxLayout->setSpacing(0);
    analyseHBoxLayout->addWidget(analyse);
    analyseHBoxLayout->setAlignment(analyse, Qt::AlignCenter);
    analyseWidegt->setLayout(analyseHBoxLayout);
    stackedWidget->addWidget(analyseWidegt);
    //数据加载画面
    QWidget * loadWidegt = new QWidget(stackedWidget);
    QLabel * load = new QLabel(loadWidegt);
    QMovie * gif = new QMovie(":/res/load.gif");
    load->setMovie(gif);
    gif->start();
    QHBoxLayout * loadHBoxLayout = new QHBoxLayout;
    loadHBoxLayout->setContentsMargins(0, 0, 0, 0);
    loadHBoxLayout->setMargin(0);
    loadHBoxLayout->setSpacing(0);
    loadHBoxLayout->addWidget(load);
    loadHBoxLayout->setAlignment(load, Qt::AlignCenter);
    loadWidegt->setLayout(loadHBoxLayout);
    stackedWidget->addWidget(loadWidegt);
    ui->letterList->setViewMode(QListWidget::ListMode);
    ui->letterList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    WordStatic * word = new WordStatic("D:\\C++projectwordCount\\stopWord.txt");
    colorVec = {QColor(227,23,13), QColor(255,128,0), QColor(255,215,0), QColor(51,161,201), QColor(0,199,140), QColor(30,144,255), QColor(135,38,87), QColor(255,125,64), QColor(112,128,105), QColor(192,192,192), QColor(128,138,135), QColor(41,36,33)};
//    ui->addBtn->setStyleSheet("background-color: rgb(245,245, 245)");
//    ui->deleteBtn->setStyleSheet("background-color: rgb(245,245, 245)");
    connect(ui->addBtn, &QPushButton::clicked, [=](){
        QStringList path = QFileDialog::getOpenFileNames(this, "打开文件", "D:\\QTproject\\test", "(*.doc *.txt)");
        int countLetter = path.count();
        for(int i = 0 ; i < countLetter; i++)
        {
            if(letterOrder.indexOf(path.at(i)) != -1)
            {
                this->isRepeatedLetter = true;
                break;
            }
        }

        if(!this->isRepeatedLetter)
        {
            for(int i = 0 ; i < countLetter; i++)
            {
                letterOrder.append(path.at(i));
            }

//            for(int i = 0 ; i < letterOrder.size(); i++)
//            {
//                qDebug() << letterOrder.at(i);
//            }

            for(int i = 0 + index ; i < letterOrder.size(); i++)
            {
                stackedWidget->setCurrentIndex(1);
                QListWidgetItem * item = new QListWidgetItem(ui->letterList);
                QSize size = item->sizeHint();
                item->setSizeHint(QSize(300, 70));
                ui->letterList->addItem(item);
                Letter * letter = new Letter(letterOrder.at(i), i);
                letter->setParent(ui->letterList);
                letter->setSizeIncrement(size.width(), 56);
                ui->letterList->setItemWidget(item, letter);
//                item->setBackground(QColor(0, 255, 255));
//                for(int i = 0; i < ui->letterList->count()-1; i++)
//                {
//                    QListWidgetItem * listWidgetItem = ui->letterList->item(i);
//                    listWidgetItem->setBackground(QColor(255, 255, 255));
//                }
//
                connect(letter, &Letter::currentIndex, [=](int letterIndex, QString currentLetterPath){
                    qDebug() << 111;
                    for(int i = 0; i < ui->letterList->count(); i++)
                    {
                        QListWidgetItem * listWidgetItem = ui->letterList->item(i);
                        if( i == letterIndex)
                        {
                            listWidgetItem->setBackground(QColor(240, 255, 255));
                        }
                        else
                        {
                            listWidgetItem->setBackground(QColor(255, 255, 255));
                        }
                    }
                    if(letterCorrespondIndex.size() == 0 || letterCorrespondIndex.find(currentLetterPath) == letterCorrespondIndex.end())
                    {
                        letterCorrespondIndex.insert(currentLetterPath, stackedWidgetIndex + 2);
                        QWidget * topNumber = new QWidget();
                        QLabel * expressMethod = new QLabel();
                        expressMethod->setFixedSize(100,30);
                        expressMethod->setText("选择显示样式：");
                        QComboBox * selectMethod = new QComboBox(topNumber);
                        selectMethod->addItem("饼状图");
                        selectMethod->addItem("柱状图");
                        selectMethod->setFixedSize(80,30);
                        QLabel * expressTopNumber = new QLabel();
                        expressTopNumber->setFixedSize(100,30);
                        expressTopNumber->setText("选择显示数量：");
                        QSpinBox * selectTopNumber = new QSpinBox(topNumber);
                        selectTopNumber->setAlignment(Qt::AlignHCenter);
                        selectTopNumber->setRange(5,12);
                        selectTopNumber->setValue(10);
                        selectTopNumber->setFixedSize(50,30);
                        QPushButton * confirmTopNumber = new QPushButton(topNumber);
                        confirmTopNumber->setFixedSize(80,30);
                        confirmTopNumber->setText("确认");
                        QWidget * chartWidegt = new QWidget(stackedWidget);
                        QChart * m_chart = new QChart();
                        ToolTip * m_tooltip = new ToolTip();
                        m_chart->setAnimationOptions(QChart::SeriesAnimations);//动画显示
                        QBarSeries * seriesBar = new QBarSeries();
                        QPieSeries * series = new QPieSeries();
                        QBarCategoryAxis *axisX = new QBarCategoryAxis();
                        QValueAxis *axisY = new QValueAxis();
                        axisY->setTitleText("词频");
                        axisX->setTitleText("keywords");
//                        axis->setMinorGridLineColor(QColor(109, 109 ,109));
//                        QMap<QString, int>::iterator iter;//定义一个迭代指针iter
                        word->vec.clear();
//                        word->topWord.clear();
                        word->readFile(currentLetterPath);
//                        for(iter = word->topWord.begin(); iter != word->topWord.end(); iter++)
//                        {
//        //                    series->append(QString("%1:%2").arg(iter.key()).arg(iter.value()* 100.0/letter->wordAll), iter.value());
//                            series->append(QString("%1").arg(iter.key()), iter.value());
//                            qDebug() << iter.value();
//                        }
                        for(int i = 0; i < 10; i++)
                        {
                            series->append(QString("%1").arg(word->vec.at(i).word), word->vec.at(i).freq);
                            seriesPie[word->vec.at(i).word] = i + 1;
                        }
        //                series->append("水果:30%",500);     //添加标签"水果:30%" 和 百分值30%
        //                series->append("零食:20%",400);
        //                series->append("主食:50%",100);
                        series->setLabelsVisible(true);
                        series->setUseOpenGL(true);
                        series->slices().at(0)->setColor(QColor(227,23,13));   //设置颜色
                        series->slices().at(0)->setLabelColor(QColor(227,23,13));
                        series->slices().at(0)->setExploded();//切片是否与饼图分离
                        series->slices().at(0)->setLabelVisible(true);
                        series->slices().at(1)->setColor(QColor(255,128,0));
                        series->slices().at(1)->setLabelColor(QColor(255,128,0));
                        series->slices().at(2)->setColor(QColor(255,215,0));
                        series->slices().at(2)->setLabelColor(QColor(255,215,0));
                        series->slices().at(3)->setColor(QColor(51,161,201));
                        series->slices().at(3)->setLabelColor(QColor(51,161,201));
                        series->slices().at(4)->setColor(QColor(30,144,255));
                        series->slices().at(4)->setLabelColor(QColor(30,144,255));
                        series->slices().at(5)->setColor(QColor(135,38,87));
                        series->slices().at(5)->setLabelColor(QColor(135,38,87));
                        series->slices().at(6)->setColor(QColor(255,125,64));
                        series->slices().at(6)->setLabelColor(QColor(255,125,64));
                        series->slices().at(7)->setColor(QColor(192,192,192));
                        series->slices().at(7)->setLabelColor(QColor(192,192,192));
                        series->slices().at(8)->setColor(QColor(128,138,135));
                        series->slices().at(8)->setLabelColor(QColor(128,138,135));
                        series->slices().at(9)->setColor(QColor(41,36,33));
                        series->slices().at(9)->setLabelColor(QColor(41,36,33));
                        m_chart->setTheme(QChart::ChartThemeLight);//设置白色主题
        //                m_chart->setDropShadowEnabled(true);//背景阴影
                        m_chart->addSeries(series);//添加系列到QChart上
//                        m_chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
//                        m_chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
//                        m_chart->setTitle("top10关键字");
                        m_chart->legend()->hide();
                        connect(series, &QPieSeries::hovered, [=](QPieSlice * slice, bool status){
                            if (status) {
                                qDebug() << 111;
                                QPoint pt_pie = QCursor::pos();
                                m_tooltip->showMessage(QString("top%1：%2").arg(seriesPie[slice->label()]).arg(slice->label()), QString("词频：%1").arg(slice->value()), QPoint(pt_pie.rx(),pt_pie.ry()));
                            }
                            else {
                                m_tooltip->hide();
                            }
                        });
                        //修改说明样式
        //                m_chart->legend()->setVisible(true);
        //                m_chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
        //                m_chart->legend()->setBackgroundVisible(true);//设置背景是否可视
        //                m_chart->legend()->setAutoFillBackground(true);//设置背景自动填充
        //                m_chart->legend()->setColor(QColor(222,233,251));//设置颜色
        //                m_chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
        //                m_chart->legend()->setMaximumHeight(50);
                        QChartView *chartView = new QChartView(m_chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        QHBoxLayout *pHLayout = new QHBoxLayout(this);
                        pHLayout->addWidget(expressMethod);
                        pHLayout->addWidget(selectMethod);
                        pHLayout->addWidget(expressTopNumber);
                        pHLayout->addWidget(selectTopNumber);
                        pHLayout->addWidget(confirmTopNumber);
                        topNumber->setLayout(pHLayout);
                        QVBoxLayout *pVLayout = new QVBoxLayout(this);
                        pVLayout->addWidget(topNumber);
                        pVLayout->addWidget(chartView);
                        chartWidegt->setLayout(pVLayout);
                        chartWidegt->setGeometry(20,30,500,500);
                        stackedWidget->addWidget(chartWidegt);
                        stackedWidget->setCurrentIndex(letterCorrespondIndex.value(currentLetterPath));
                        stackedWidgetIndex++;
                        letter->isloadLabel->setPixmap(QPixmap(":/res/isloadnone.png"));
                        connect(confirmTopNumber, &QPushButton::clicked, [=](){
                            int selectValue = selectTopNumber->value();
                            QString selectStyle = selectMethod->currentText();
                            m_chart->removeSeries(series);
                            m_chart->removeSeries(seriesBar);
                            if(previousMethod != "饼状图")
                            {
                                m_chart->removeAxis(m_chart->axisX());
                                m_chart->removeAxis(m_chart->axisY());
                            }
                            if(selectStyle == "饼状图")
                            {
                                seriesPie.clear();
                                series->clear();
                                for(int i = 0; i < selectValue; i++)
                                {
                                    series->append(QString("%1").arg(word->vec.at(i).word), word->vec.at(i).freq);
                                    seriesPie[word->vec.at(i).word] = i + 1;
                                }
                //                series->append("水果:30%",500);     //添加标签"水果:30%" 和 百分值30%
                //                series->append("零食:20%",400);
                //                series->append("主食:50%",100);
                                series->setLabelsVisible(true);
                                series->setUseOpenGL(true);
                                series->slices().at(0)->setColor(QColor(227,23,13));   //设置颜色
                                series->slices().at(0)->setLabelColor(QColor(227,23,13));
                                series->slices().at(0)->setExploded();//切片是否与饼图分离
                                series->slices().at(0)->setLabelVisible(true);
                                for(int j = 1; j < selectValue; j++)
                                {
                                    series->slices().at(j)->setColor(colorVec[j]);
                                    series->slices().at(j)->setLabelColor(colorVec[j]);
                                }
                                m_chart->addSeries(series);
                                previousMethod = "饼状图";
                            }
                            else
                            {
                                seriesBar->clear();
                                QBarSet *set = new QBarSet("Jane");
                                axisX->clear();
                                for(int i = 0; i < selectValue; i++)
                                {
                                    set->append(word->vec.at(i).freq);
                                }
                                seriesBar->append(set);
//                                QStringList categories;
//                                for(int i = 0; i < selectValue; i++)
//                                {
//                                    categories.append(word->vec.at(i).word);
//                                }
//                                axisX->setLabelsAngle(90);
//                                axisX->append(categories);
                                m_chart->addSeries(seriesBar);
                                QStringList categories;
                                for(int i = 0; i < selectValue; i++)
                                {
                                    categories.append(word->vec.at(i).word);
                                }
                                axisX->setLabelsAngle(90);
                                axisX->append(categories);
                                m_chart->addAxis(axisX, Qt::AlignBottom);
                                seriesBar->attachAxis(axisX);
                                axisY->setRange(0,word->vec.at(0).freq);
                                m_chart->addAxis(axisY, Qt::AlignLeft);
                                seriesBar->attachAxis(axisY);
//                                for(int i = 0; i < selectValue; i++)
//                                {
//                                    axisY->append("11", word->vec.at(i).freq);

//                                }
                                QPen axisPen(QColor(51, 161, 201));
                                axisPen.setWidth(2);
                                axisY->setLinePen(axisPen);
                                axisX->setLinePen(axisPen);
//                                axisY->setRange(0, 200);

//                                m_chart->setAxisY(axisY, seriesBar);
//                                /*m_chart->createDefaultAxes();*///创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
//                                m_chart->setAcceptTouchEvents(true);
//                                m_chart->setAxisX(axisX, seriesBar);//设置坐标轴

                                previousMethod = "柱状图";
                                connect(seriesBar, &QBarSeries::hovered, [=](bool status, int index, QBarSet* barset){
                                    if (status) {
                                        qDebug() << 111.1;
                                        QPoint pt = QCursor::pos();
                                        m_tooltip->showMessage(QString("top%1：%2").arg(index+1).arg(categories.at(index)), QString("词频：%1").arg(barset->at(index)), QPoint(pt.rx(),pt.ry()));
                                    }
                                    else {
                                        m_tooltip->hide();
                                    }
                                });

                            }

                        });
                    }
                    else
                    {
                        stackedWidget->setCurrentIndex(letterCorrespondIndex.value(currentLetterPath));
                    }
                });

                connect(letter, &Letter::modifyLetter, this, [=](QString previousLetterPath, QString currentLetterPath){
                    int modifyIndex = this->letterOrder.indexOf(previousLetterPath);
                    this->letterOrder.replace(modifyIndex, currentLetterPath);
                    stackedWidget->setCurrentIndex(1);
                    letter->isloadLabel->setPixmap(QPixmap(":/res/noloadnone.png"));

                });
                connect(letter, &Letter::deleteLetter, [=](QString deletePath){
//                    qDebug() << deletePath;
                    int deleteIndex = this->letterOrder.indexOf(deletePath);
//                    qDebug() << QString::number(deleteIndex);
                    QListWidgetItem *item = ui->letterList->takeItem(deleteIndex);
                    delete item;
                    this->letterOrder.remove(deleteIndex);
                    this->index--;
//                    for(int i = 0 ; i < letterOrder.size(); i++)
//                    {
//                        qDebug() << letterOrder.at(i);
//                    }
//                    QWidget* deleteWidget = stackedWidget->widget(deleteIndex + 2);
//                    stackedWidget->removeWidget(deleteWidget);
//                    deleteWidget->deleteLater();
//                    qDebug() << ui->letterList->count();
                    if(ui->letterList->count() == 0)
                    {
//                        qDebug("111111");
                        stackedWidget->setCurrentIndex(0);
                    }
                    else
                    {
                        stackedWidget->setCurrentIndex(1);
                    }
                });

            }
            index = letterOrder.size();
        }
        else
        {
            QMessageBox::warning(this, "警告", "请勿添加重复文件");
        }
        this->isRepeatedLetter = false;
    });


    connect(ui->deleteBtn, &QPushButton::clicked, [=](){
        letterOrder.clear();
        index = 0;
        int num = ui->letterList->count();  //获取列表项的总数目
//        qDebug() << QString::number(num);
        ui->letterList->setFocus(); //将光标设置到列表框上，若注释该语句，则删除时，要手动将焦点设置到列表框，即点击列表项
        for(int i = 0; i < num; i++)
        {
//            qDebug() << QString::number(ui->letterList->currentRow());
            //逐个获取列表项的指针，并删除
            QListWidgetItem *item = ui->letterList->takeItem(0);
            delete item;
         }

//        for(int i = stackedWidget->count(); i > 0; i--)
//        {
//                QWidget* widget = stackedWidget->widget(i);
//                stackedWidget->removeWidget(widget);
//                widget->deleteLater();
//        }
        stackedWidget->setCurrentIndex(0);
    });

}

Widget::~Widget()
{
    delete ui;
}

