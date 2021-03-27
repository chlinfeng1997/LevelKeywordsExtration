#include "letter.h"
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <QFont>
#include <wordstatic.h>
#include <QTime>
#include <QTimer>
#include <QDebug>
//Letter::Letter(QWidget *parent) : QWidget(parent)
//{

//}

Letter::Letter(QString letterPath, int letterIndex)
{
    this->letterIndex = letterIndex;
    this->previousLetterPath = letterPath;
    this->currentLetterPath = letterPath;
    QFileInfo info(letterPath);
    QString suffix = info.suffix();
    this->setStyleSheet("background:transparent;");
//    qDebug() << suffix;
    QLabel *TypeLabel = new QLabel(this);
    QPixmap myPix;
    if(suffix == "txt")
    {
        myPix.load(":/res/txtNone.png");
    }
    else if (suffix == "doc")
    {
        myPix.load(":/res/docNone.png");
    }
    TypeLabel->setFixedSize(58, 56);
    TypeLabel->setPixmap(myPix);
//    TypeLabel->setScaledContents(true);
    TypeLabel->setStyleSheet("QLabel{padding-left:5px;padding-right:5px;padding-top:5px;padding-bottom:5px}");

    QWidget *frontArea = new QWidget(this);
    frontArea->setFixedSize(180, 56);

    QLabel *letterPathLabel = new QLabel(frontArea);
    letterPathLabel->setFont(QFont("微软雅黑"));
    if(suffix == "txt")
    {
        letterPathLabel->setText("文件名: " + info.fileName().remove(".txt"));
    }
    else if (suffix == "doc")
    {
        letterPathLabel->setText("文件名: " + info.fileName().remove(".doc"));
    }

    QLabel *letterSizeLabel = new QLabel(frontArea);
    letterSizeLabel->setFont(QFont("微软雅黑"));
    letterSizeLabel->setText("大小: " + QString::number(info.size() / 1024) + "KB");

    QWidget *backArea = new QWidget(this);
    backArea->setFixedSize(80, 56);

//    QProgressBar *ProgressBar = new QProgressBar(backArea);
//    ProgressBar->setOrientation(Qt::Horizontal);
//    ProgressBar->setMinimum(0);
//    ProgressBar->setMaximum(0);
//    ProgressBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
////    ProgressBar->setTextVisible(false);
//    ProgressBar->setFixedHeight(20);
    isloadLabel = new QLabel(backArea);
    isloadLabel->setPixmap(QPixmap(":/res/noloadnone.png"));

    QWidget *lastArea = new QWidget(this);
    lastArea->setFixedSize(38, 56);

    QPushButton *modifyFileButton = new QPushButton(lastArea);
    modifyFileButton->setToolTip(QStringLiteral("修改文件"));
    modifyFileButton->setFixedSize(38, 28);
    QIcon icon3(":/res/modifyFile.png");
    modifyFileButton->setIcon(icon3);
    modifyFileButton->setIconSize(QSize(20, 20));
    connect(modifyFileButton, &QPushButton::clicked, [=](){
        QString modifyPath = QFileDialog::getOpenFileName(this, "打开文件", "D:\\QTproject\\test", "(*.doc *.txt)");
        if (modifyPath != "")
        {
            this->modifyTimes++;
            QFileInfo modifyInfo(modifyPath);
            if(this->modifyTimes == 1)
            {
                this->currentLetterPath = modifyPath;
            }
            else
            {
                this->previousLetterPath = this->currentLetterPath;
                this->currentLetterPath = modifyPath;
            }
            QFileInfo modifyPathInfo(modifyPath);
            QPixmap modifyPix;
            if(modifyPathInfo.suffix() == "txt")
            {
                modifyPix.load(":/res/txtNone.png");
                letterPathLabel->setText("文件名: " + modifyInfo.fileName().remove(".txt"));
            }
            else if (modifyPathInfo.suffix() == "doc")
            {
                modifyPix.load(":/res/docNone.png");
                letterPathLabel->setText("文件名: " + modifyInfo.fileName().remove(".doc"));
            }
            TypeLabel->setPixmap(modifyPix);
            letterPathLabel->setText("文件名: " + modifyInfo.fileName().remove(".txt"));
            letterSizeLabel->setText("大小: " + QString::number(modifyInfo.size() / 1024) + "KB");
//            ProgressBar->setMinimum(0);
//            ProgressBar->setMaximum(0);
            emit this->modifyLetter(this->previousLetterPath, this->currentLetterPath);
        }
    });

    QPushButton *deleteFileButton = new QPushButton(lastArea);
    deleteFileButton->setToolTip(QStringLiteral("删除文件"));
    deleteFileButton->setFixedSize(38, 28);
    QIcon icon4(":/res/deleteFile.png");
    deleteFileButton->setIcon(icon4);
    deleteFileButton->setIconSize(QSize(20, 20));
    connect(deleteFileButton, &QPushButton::clicked, [=](){
        emit this->deleteLetter(this->currentLetterPath);
    });

    QVBoxLayout *verLayout = new QVBoxLayout;
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setMargin(0);
    verLayout->setSpacing(0);
    verLayout->addWidget(letterPathLabel);
    verLayout->addWidget(letterSizeLabel);
    frontArea->setLayout(verLayout);

    QHBoxLayout *verLayout2 = new QHBoxLayout;
    verLayout2->setContentsMargins(0, 0, 0, 0);
    verLayout2->setMargin(0);
    verLayout2->setSpacing(0);
    verLayout2->addWidget(isloadLabel);
//    verLayout2->addWidget(SpeedLabel);
    backArea->setLayout(verLayout2);

    QVBoxLayout *verLayout3 = new QVBoxLayout;
    verLayout3->setContentsMargins(0, 0, 0, 0);
    verLayout3->setMargin(0);
    verLayout3->setSpacing(0);
    verLayout3->addWidget(modifyFileButton);
    verLayout3->addWidget(deleteFileButton);
    lastArea->setLayout(verLayout3);

    QHBoxLayout *horLayout = new QHBoxLayout;
    horLayout->setContentsMargins(0, 0, 0, 0);
    horLayout->setMargin(0);
    horLayout->setSpacing(0);
    horLayout->addWidget(TypeLabel);
    horLayout->addWidget(frontArea);
    horLayout->addWidget(backArea);
    horLayout->addWidget(lastArea);
    this->setLayout(horLayout);
}

void Letter::mousePressEvent(QMouseEvent *e)
{
//    qDebug() << "222";
//    qDebug() << this->letterIndex;
    emit this->currentIndex(this->letterIndex, this->currentLetterPath);
    QWidget::mousePressEvent(e);
}
