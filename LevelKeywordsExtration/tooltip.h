#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QGroupBox>
class ToolTip : public QWidget
{
    Q_OBJECT
public:
    explicit ToolTip(QWidget *parent = nullptr);
    void showMessage(QString name, QString info, QPoint point);
    void showMessage(QPoint point);
signals:

public slots:

private:
    QLabel *labelName;
    QLabel *labelInfo;

    QHBoxLayout *horLayout;
    QVBoxLayout *verlayout;

protected:
    void hoverEvent(QHoverEvent *);
};

#endif // TOOLTIP_H
