#include "tooltip.h"

ToolTip::ToolTip(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->resize(150, 50);

    this->setObjectName("ToolTip");
    this->setStyleSheet("QWidget#ToolTip {border: 2px solid green; background-color: skyblue;}");

    QWidget *Area = new QWidget(this);
    Area->resize(150,50);
    labelName = new QLabel(this);
    labelName->setFont(QFont("微软雅黑"));
//    labelName->setGeometry(0, 0, 20, 140);
//    labelName->setLineWidth(130);
    labelInfo = new QLabel(this);
    labelInfo->setFont(QFont("微软雅黑"));

    verlayout = new QVBoxLayout();
    verlayout->setContentsMargins(0, 0, 0, 0);
    verlayout->setMargin(0);
    verlayout->setSpacing(0);
    verlayout->addWidget(labelName);
    verlayout->addWidget(labelInfo);
    Area->setLayout(verlayout);

}

// 显示ToolTip消息
void ToolTip::showMessage(QString name, QString info, QPoint point) {
    labelName->setText(name);
    labelInfo->setText(info);

    // 重新定义ToolTip的坐标
    int rectX = point.rx();
    int rectY;
//    if (point.rx() < 200) {
//        rectX = point.rx() + 10;
//    } else {
//        rectX = point.rx() - 240;
//    }
    rectY =  point.ry();
    move(QPoint(rectX, rectY));
    QWidget::show();
}

// 显示ToolTip消息
void ToolTip::showMessage(QPoint point) {
    labelName->setText("自己想办法获取");
    labelInfo->setText("自己动手，丰衣足食");
    // 此处可以作为QToolTip样式进行显示
    move(point);
    QWidget::show();
}

// 当鼠标进入事件时，让界面隐藏掉
void ToolTip::hoverEvent(QHoverEvent *) {
    hide();
}
