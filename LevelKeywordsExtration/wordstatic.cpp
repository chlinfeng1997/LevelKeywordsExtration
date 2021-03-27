#include "wordstatic.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QtDebug>
#include <QtAlgorithms>
#include <QRegularExpression>
#include <QAxWidget>
#include <QAxObject>
//WordStatic::WordStatic(QWidget *parent) : QWidget(parent)
//{

//}
bool cmp(Record a, Record b)
{
    return a.freq > b.freq; //从大到小排序
}

WordStatic::WordStatic(QString filename)
{
    readStopWord(filename);
}

void WordStatic::readFile(QString filename)
{
    //逐行读取，将行读入字符串
//    std::ifstream ifs;
//    ifs.open(filename, std::ios::in);
//    std::string str;

//    if(!ifs.is_open())
//    {
//        std::cout << "open readfile failed" << std::endl;
//        ifs.close();
//        return;
//    }

//    while(getline(ifs,str))
//    {
//        std::stringstream ss(str);
//        std::string word;
//        while(ss >> word)
//        {
//            //std::cout<< word << std::endl;
//            if(!isNum(word) && find(stopWord.begin(), stopWord.end(), word) == stopWord.end())
//            {
//                std::vector<Record>::iterator it;
//                for (it = vec.begin(); it != vec.end(); ++it) {
//                    //string 重载了等号
//                    if (word == (*it).word) {
//                        (*it).freq += 1;
//                        break;
//                    }
//                }
//                if (it == vec.end()) {
//                    Record newRe;
//                    newRe.word = word;
//                    newRe.freq = 1;
//                    vec.push_back(newRe);
//                }
//            }
//        }
//    }
//    ifs.close();
//    sort(vec.begin(), vec.end(), cmp);


//    QFile file(filename);
//    file.open(QIODevice::ReadOnly);
//    QString line;
//    QTextStream in(&file);  //用文件构造流
//    line = in.readLine();//读取一行放到字符串里
//    qDebug() << line;
//    QStringList wordList = line.split(" ");
//    for(int i = 0; i < wordList.size(); i++)
//    {
//        qDebug() << wordList.at(i);
//    }
//    for(int i = 0; i < wordList.size(); i++)
//    {
//        qDebug() << isNum(wordList.at(i));
//        if(!isNum(wordList.at(i)) && this->stopWord.indexOf(wordList.at(i)) == -1)
//        {
//            QVector<Record>::iterator it;
//            for (it = vec.begin(); it != vec.end(); ++it)
//            {
//                //string 重载了等号
//                if (wordList.at(i) == (*it).word)
//                {
//                    (*it).freq += 1;
//                    break;
//                }
//            }
//            if (it == vec.end())
//            {
//                Record newRecord;
//                newRecord.word = wordList.at(i);
//                newRecord.freq = 1;
//                vec.push_back(newRecord);
//            }
//        }
//    }
//   qDebug() << this->vec.size();
//    while(!line.isNull())//字符串有内容
//    {
//        line = in.readLine();//循环读取下行
//        wordList = line.split(" ");

//        for(int i = 0; i < wordList.size(); i++)
//        {
//            if(!isNum(wordList.at(i)) && this->stopWord.indexOf(wordList.at(i)) == -1)
//            {
//                QVector<Record>::iterator it;
//                for (it = vec.begin(); it != vec.end(); ++it)
//                {
//                    //string 重载了等号
//                    if (wordList.at(i) == (*it).word)
//                    {
//                        (*it).freq += 1;
//                        break;
//                    }
//                }
//                if (it == vec.end())
//                {
//                    Record newRecord;
//                    newRecord.word = wordList.at(i);
//                    newRecord.freq = 1;
//                    vec.push_back(newRecord);
//                }
//            }
//        }
//    }
    QFileInfo info(filename);
    QString suffix = info.suffix(); //文件后缀名
    if(suffix == "txt")
    {
        QFile file(filename); //参数就是读取文件的路径
        //设置打开方式
        file.open(QIODevice::ReadOnly);
        QString array;
        QStringList wordList;
        while(!file.atEnd())
        {
            array = file.readLine(); //按行读
    //        qDebug() << array;
            wordList= array.split(QRegularExpression("[\\s\\p{P}]+")); //字符分割
    //        qDebug() << wordList;
            for(int i = 0; i < wordList.size(); i++)
            {
    //            qDebug() << isNum(wordList.at(i));
                if(!isNum(wordList.at(i)) && this->stopWord.indexOf(wordList.at(i)) == -1) //判断字符串是否是数字或停止词
                {
                    QVector<Record>::iterator it;
                    for (it = vec.begin(); it != vec.end(); ++it)
                    {
                        //string 重载了等号
                        if (wordList.at(i) == (*it).word)
                        {
                            (*it).freq += 1;
                            break;
                        }
                    }
                    if (it == vec.end())
                    {
                        Record newRecord;
                        newRecord.word = wordList.at(i);
                        newRecord.freq = 1;
                        vec.push_back(newRecord);
                    }
                }
            }
        }
        file.close();

        qSort(vec.begin(), vec.end(), cmp);

//        for(int i = 0; i < 10; i++)
//        {
//            qDebug() << vec.at(i).word << vec.at(i).freq;
//            topWord.insert(vec.at(i).word, vec.at(i).freq);
//        }
    }
    else if (suffix == "doc")
    {
        //指定要打开文件的路径
            //QString filePath = "D:/doc/local.doc";
            //创建QAxWidget 对象，使其拥有Word的对象
        QStringList wordList;
        qDebug() << filename;
        QAxWidget *word=new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);

        //设置word是否为可见，这里设置为false。这样就不会看到word的程序了
        word->setProperty("Visible", false);

//        connect(word, SIGNAL(exception(int, QString, QString, QString)), this, SLOT(slots_exception()));

        //通过word对象找到它的属性，Document
        QAxObject * documents = word->querySubObject("Documents");

        //通过Document打开要获取文件内容的文件
        documents->dynamicCall("Open(QString)", filename);
        //    documents->dynamicCall("Open(QString)",QString::fromLocal8Bit("D:/doc/local.doc"));

            //获取当前活动的Document
        QAxObject *document = word->querySubObject("ActiveDocument");

        //从当前活动的Document中获取paragraphs
        QAxObject *paragraphs = document->querySubObject("Paragraphs");

        //循环输入每一个paragraph
        qDebug() << paragraphs->property("Count").toInt();
        for (int ipar = 1; ipar <= paragraphs->property("Count").toInt(); ipar++)
        {
            QAxObject *lines = paragraphs->querySubObject("Item(QVariant)", ipar);
            QAxObject *line = lines->querySubObject("Range");
            QString str = line->property("Text").toString();
            str = str.trimmed();
//            qDebug()<<str;
            wordList= str.split(QRegularExpression("[\\s\\p{P}]+"));
    //        qDebug() << wordList;
            for(int i = 0; i < wordList.size(); i++)
            {
    //            qDebug() << isNum(wordList.at(i));
                if(!isNum(wordList.at(i)) && this->stopWord.indexOf(wordList.at(i)) == -1)
                {
                    QVector<Record>::iterator it;
                    for (it = vec.begin(); it != vec.end(); ++it)
                    {
                        //string 重载了等号
                        if (wordList.at(i) == (*it).word)
                        {
                            (*it).freq += 1;
                            break;
                        }
                    }
                    if (it == vec.end())
                    {
                        Record newRecord;
                        newRecord.word = wordList.at(i);
                        newRecord.freq = 1;
                        vec.push_back(newRecord);
                    }
                }
            }
//            line->clear();
            delete line;
//            lines->clear();
            delete lines;
        }
        //关闭Document
        document->dynamicCall("Close (boolean)", false);
    //     document->dynamicCall("Close (boolean)", false);

        //退出word
        word->dynamicCall("Quit()");

        qSort(vec.begin(), vec.end(), cmp);

//        for(int i = 0; i < 10; i++)
//        {
//            topWord.insert(vec.at(i).word, vec.at(i).freq);
//        }
    }
}

void WordStatic::writeFile(QString filename)
{
    //从流中写数据
    QVector<Record>::iterator it;
    QFile file("D:\\QTproject\\LevelKeywordsExtration\\res\\test.txt");
    file.open(QIODevice::WriteOnly);
    for(it = vec.begin(); it != vec.end(); ++it)
    {
        file.write((*it).word.toUtf8() + " ");
        file.write(QString::number((*it).freq).toUtf8());
        file.write("\n");
        //std::cout << (*it).word << " " << (*it).freq << std::endl;
    }
    file.close();
}

void WordStatic::readStopWord(QString filename)
{
//    std::ifstream ifs;
//    ifs.open(filename, std::ios::in);
//    std::string str;

//    if(!ifs.is_open())
//    {
//        std::cout << "open readfile failed" << std::endl;
//        ifs.close();
//        return;
//    }

//    while(getline(ifs,str))
//    {
//        std::stringstream ss(str);
//        std::string word;
//        while(ss >> word)
//        {
//            //std::cout<< word << std::endl;
//            stopWord.push_back(word);
//        }
//    }
//    ifs.close();
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QString line;
    QTextStream in(&file);  //用文件构造流
    line = in.readLine();//读取一行放到字符串里
    this->stopWord.append(line);
    while(!line.isNull())//字符串有内容
    {
        line=in.readLine();//循环读取下行
        this->stopWord.append(line);
    }
//    for(int i = 0; i < this->stopWord.size(); i++)
//    {
//        qDebug() << this->stopWord.at(i);
//    }
}

// 判断字符串是不是数字
bool WordStatic::isNum(QString str)
{
    QByteArray ba = str.toLatin1();
   const char *s = ba.data();
   bool bret = true;
   while(*s)
   {
       if(*s>='0' && *s<='9')
       {

       }
       else
       {
           bret = false;
           break;
       }
       s++;
   }
   return bret;
}
