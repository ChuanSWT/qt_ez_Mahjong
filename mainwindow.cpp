    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include <QDir>
#include <QVector>
#include <algorithm>
#include <random>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bg("D:/Projects/Qt/mahjong/img/bg.jpg");
    ui->label->setPixmap(bg.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    holds=14;
    for(int i=1;i<4;++i)
    {
        for(int j=1;j<=9;++j)
        {
            for(int count=0;count<4;++count)
            x.push_back(10*i+j);
        }
    }
    for(int count=0;count<4;++count)
    {
        for(int i=1;i<8;++i)
            x.push_back(40+i);
    }
    std::random_device rd;
    std::mt19937 rng(rd());

    // 使用 std::shuffle 来打乱 QVector 中的元素
    std::shuffle(x.begin(), x.end(), rng);

    for(int i=1;i<=holds;++i)
    {
        QString op = "D:/Projects/Qt/mahjong/img/";
        QString ed = ".PNG";
        QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
        currentHold.push_back(x[position]);
        QPixmap icon1(imagePath);
        QString numS=QString::number(i);
        QLabel *foundLabel = findChild<QLabel*>("label"+numS);
            if (!icon1.isNull()) {
            foundLabel->setText(QString::number(x[position]));
            //foundLabel->setFixedSize(icon1.size());

        } else {
            foundLabel->setText(QString::number(x[position]));
            //foundLabel->setText(QString::number(x[position]));
            qDebug() << "Failed to load image: " << imagePath;
        }
        ++position;
    }
    sort();
    refresh();
    DROP=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton1_clicked()
{
    if(DROP)
        {
        currentHold[0]=1099;
        ui->label1->setText("1099");
            DROP=false;
        sort();
        ui->checkWidget->setText("");
        refresh();
            return;
    }
    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path

    // Debug: Print the constructed image path
    qDebug() << "Image Path: " << imagePath;

    QPixmap icon1(imagePath);
    currentHold[0] = x[position];

    if (!icon1.isNull()) {
            qDebug() << "Setting Pixmap to Label";

            ui->label1->setPixmap(icon1);


    } else {
            qDebug() << "Failed to load image: " << imagePath;

            ui->label1->setText(QString::number(x[position]));

            qDebug() << "Setting Label Text: " << QString::number(x[position]);
    }

    sort();
    ++position;
    refresh();
}
void MainWindow::sort()
{

    for(int i=0;i<holds;++i)
    {
        for(int j=0;j<holds;++j)
        {
            if(currentHold[i]<currentHold[j])
            {
            int temp=999;
            QLabel *p1=findChild<QLabel*>("label"+QString::number(i+1));
            QLabel *p2=findChild<QLabel*>("label"+QString::number(j+1));
            temp=currentHold[i];
            currentHold[i]=currentHold[j];
            currentHold[j]=temp;
            //p1->setText(QString::number(currentHold[i]));
            //p2->setText(QString::number(currentHold[j]));
            QString op = "D:/Projects/Qt/mahjong/img/";
            QString ed = ".PNG";
            QString imagePath1 = op + QString::number(currentHold[i]) + ed; // Construct the full file path
            QString imagePath2 = op + QString::number(currentHold[j]) + ed; // Construct the full file path

            QPixmap icon1(imagePath1);
            QPixmap icon2(imagePath2);
                p1->setPixmap(icon1);
                p2->setPixmap(icon2);
                ui->pre->setPixmap(icon1.scaled(ui->label1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                ui->next->setPixmap(icon1.scaled(ui->label1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                 //foundLabel->setPixmap(icon1.scaled(ui->label1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                  //foundLabel->setPixmap(icon1.scaled(ui->label1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


            }
        }
    }
}
void MainWindow::refresh()
{
    clear_warn_display();
    if(position>133)
    {
        qDebug()<<"emptyyy";
        ui->checkWidget->setText("流局/听牌。。。");
        --position;
        return;
    }
    next_hold=x[position];
    ++position;
    pre_hold=x[position];
    ++position;
    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath1 = op + QString::number(next_hold) + ed; // Construct the full file path
    QString imagePath2 = op + QString::number(pre_hold) + ed; // Construct the full file path

    QPixmap icon1(imagePath1);
    QPixmap icon2(imagePath2);
    ui->next->setPixmap(icon1);
    ui->pre->setPixmap(icon2);

    checked.clear();
    ui->checkWidget->setText("");
    check_LONG();

checkThrow();

}
void MainWindow::checkThrow()
{

    int counter=0;
    for(int i:currentHold)
        if(i==next_hold)
        {++counter;}
//ok
    qDebug()<<"checker1";
    if(counter==2)
    {
        warn.clear();
        warn.push_back(QString::number(next_hold));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("碰"+QString::number(next_hold)+"?");
 qDebug()<<"checker11";
        display_warn(warn);
return;
}
    }
     qDebug()<<"checker2";
    if(counter==3)
    {
        warn.clear();
        for(int i=0;i<4;++i)
        warn.push_back(QString::number(next_hold));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("杠"+QString::number(next_hold)+"?");
display_warn(warn);
return;
    }
        }
     qDebug()<<"checker3";
    bool pre_found=false;
    bool next_found=false;
    for(int i:currentHold)
    {
        if(i+1==next_hold)
        pre_found=true;
        if(i-1==next_hold)
        next_found=true;
    }
    if(pre_found&&next_found&&next_hold<40)//风牌元牌不计入吃的范围
    {
        warn.clear();
        int intValue = next_hold;
        warn.push_back(QString::number(next_hold-1));
        warn.push_back(QString::number(next_hold+1));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+QString::number(next_hold-1)+QString::number(next_hold)+QString::number(next_hold+1)+"?");
display_warn(warn);
return;
        }
    }
    pre_found=false;
    next_found=false;
    for(int i:currentHold)
    {
        if(i-1==next_hold)
        pre_found=true;
        if(i-2==next_hold)
        next_found=true;
    }
    if(pre_found&&next_found&&next_hold<40)//风牌元牌不计入吃的范围
    {
        warn.clear();
        int intValue = next_hold;
        warn.push_back(QString::number(next_hold+1));
        warn.push_back(QString::number(next_hold+2));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+QString::number(next_hold)+QString::number(next_hold+1)+QString::number(next_hold+2)+"?");
display_warn(warn);
return;
        }
    }
    pre_found=false;
    next_found=false;
    for(int i:currentHold)
    {
        if(i+1==next_hold)
        pre_found=true;
        if(i+2==next_hold)
        next_found=true;
    }
    if(pre_found&&next_found&&next_hold<40)//风牌元牌不计入吃的范围
    {
        warn.clear();
        int intValue = next_hold;

        warn.push_back(QString::number(next_hold-1));
        warn.push_back(QString::number(next_hold-2));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+QString::number(next_hold-2)+QString::number(next_hold-1)+QString::number(next_hold)+"?");
display_warn(warn);
return;
        }
    }
    checkThrow2();
}
void MainWindow::checkThrow2()
{
    int counter=0;
    for(int i:currentHold)
        if(i==pre_hold)
        {++counter;}

    if(counter==2)
    {
        warn.clear();
        warn.push_back(QString::number(pre_hold));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("碰"+QString::number(pre_hold)+"?");

display_warn(warn);
return;
}
    }
    if(counter==3)
    {
        warn.clear();
        for(int i=0;i<4;++i)
        warn.push_back(QString::number(pre_hold));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("杠"+QString::number(pre_hold)+"?");
display_warn(warn);
return;
    }
        }
    bool pre_found=false;
    bool next_found=false;
    for(int i:currentHold)
    {
        if(i+1==pre_hold)
        pre_found=true;
        if(i-1==pre_hold)
        next_found=true;
    }
    if(pre_found&&next_found&&pre_hold<40)//风牌元牌不计入吃的范围
    {
        warn.clear();
        int intValue = pre_hold;
        warn.push_back(QString::number(pre_hold-1));
        warn.push_back(QString::number(pre_hold+1));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+QString::number(pre_hold-1)+QString::number(pre_hold)+QString::number(pre_hold+1)+"?");
display_warn(warn);
return;
        }
    }
    pre_found=false;
    next_found=false;
    for(int i:currentHold)
    {
        if(i-1==pre_hold)
        pre_found=true;
        if(i-2==pre_hold)
        next_found=true;
    }
    if(pre_found&&next_found&&pre_hold<40)//风牌元牌不计入吃的范围
    {
        warn.clear();
        int intValue = pre_hold;
        warn.push_back(QString::number(pre_hold+1));
        warn.push_back(QString::number(pre_hold+2));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+QString::number(pre_hold)+QString::number(pre_hold+1)+QString::number(pre_hold+2)+"?");
display_warn(warn);
return;
        }
    }
    pre_found=false;
    next_found=false;
    for(int i:currentHold)
    {
        if(i+1==pre_hold)
        pre_found=true;
        if(i+2==pre_hold)
        next_found=true;
    }
    if(pre_found&&next_found&&pre_hold<40)//风牌元牌不计入吃的范围
    {
        warn.clear();
        int intValue = pre_hold;
        warn.push_back(QString::number(pre_hold-1));
        warn.push_back(QString::number(pre_hold-2));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+QString::number(pre_hold-2)+QString::number(pre_hold-1)+QString::number(pre_hold)+"?");
display_warn(warn);
return;
        }
    }
     qDebug()<<"checker4";
    for(int i=0;i<holds-2&&currentHold.size()==14;++i)
     {
        if(currentHold[i]==1099)
break;

        if(currentHold[i]==currentHold[i+1]&&currentHold[i]==currentHold[i+2])
        {
        warn.clear();
        warn.push_back(QString::number(currentHold[i]));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("碰"+QString::number(currentHold[i])+"?");

display_warn(warn);
return;
        }
     }
        if(currentHold[i]==currentHold[i+1]-1&&currentHold[i]==currentHold[i+2]-2&&currentHold[i]<40)
        {
        warn.clear();
        warn.push_back(QString::number(currentHold[i]));
        warn.push_back(QString::number(currentHold[i+1]));
        warn.push_back(QString::number(currentHold[i+2]));
        int FOUND=false;
        for(QVector<QString> vs:checked)
        if(vs==warn)
            FOUND=true;
        if(!FOUND)//没有找到提供的动作
        {
        checked.push_back(warn);
        ui->checkWidget->setText("吃"+warn[0]+warn[1]+warn[2]+"?");

display_warn(warn);
return;
        }
     }
}
    clear_warn_display();
}

void MainWindow::on_checkWidget_clicked()
{
    if(warn.empty())
        return;
    ui->checkWidget->setText("");
    for(QString s:warn)
        qDebug()<<s<<" ";
    if(warn.size()==1)//碰的处理
        {DROP=true;
        ui->checkWidget->setText("~Please DROP one~");
        for(int i=0;i<4;++i)
        for(int &i:currentHold)
        {
        if(QString::number(i)==warn[0])
        {
            i=1099;
        }
        sort();
        }
        int c=std::count(currentHold.begin(),currentHold.end(),1099);
        if(c%3==0)
        {
        DROP=false;
        ui->checkWidget->setText("");
        }
        }
    if(warn.size()==2)//吃的处理
    {DROP=true;
        ui->checkWidget->setText("~Please DROP one~");
        qDebug() << "check1";
        for(QString s:warn)
        {
        for(int &i:currentHold)
        {
        if(QString::number(i)==s)
        {
            i=1099;
            sort();
            break;
        }

        }
    }

    //ui->label1->setText(QString::number(x[position]));//??
    //ui->label1->update();//??
    int c=std::count(currentHold.begin(),currentHold.end(),1099);
    if(c%3==0)
    {
        DROP=false;
        ui->checkWidget->setText("");
    }
    }
    if(warn.size()==3)//自吃的处理
    {DROP=false;
    qDebug() << "check1";
    for(QString s:warn)
    {
        for(int &i:currentHold)
        {
        if(QString::number(i)==s)
        {
            i=1099;
            sort();
            break;
        }

        }
    }

    //ui->label1->setText(QString::number(x[position]));//??
    //ui->label1->update();//??
    int c=std::count(currentHold.begin(),currentHold.end(),1099);
    if(c%3==0)
    {
        DROP=false;
        ui->checkWidget->setText("");
    }
    }
    if(warn.size()==4)//杠的处理
    {
    for(int i=0;i<4;++i)
        for(int &i:currentHold)
        {
        if(QString::number(i)==warn[0])
        {
            i=1099;
        }
        sort();
        }
    }
}



void MainWindow::on_pushButton_clicked()
{
    warn.clear();
       warn.push_back(QString::number(currentHold[0]));
}


void MainWindow::on_pushButton2_clicked()
{
       if(DROP)
       {
    currentHold[1]=1099;
    ui->label2->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[1]=x[position];
       if (!icon1.isNull()) {
    ui->label2->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label2->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton_2_clicked()
{
       ui->checkWidget->setText("");
       warn.clear();
       clear_warn_display();
       checkThrow();

}


void MainWindow::on_pushButton3_clicked()
{
       if(DROP)
       {
    currentHold[2]=1099;
    ui->label3->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[2]=x[position];
       if (!icon1.isNull()) {
    ui->label3->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label3->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton4_clicked()
{
       if(DROP)
       {
    currentHold[3]=1099;
    ui->label4->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[3]=x[position];
       if (!icon1.isNull()) {
    ui->label4->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label4->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_label5_linkActivated(const QString &link)
{
       return;
}



void MainWindow::on_pushButton5_clicked()
{
       if(DROP)
       {
    currentHold[4]=1099;
    ui->label5->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[4]=x[position];
       if (!icon1.isNull()) {
    ui->label5->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label5->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}



void MainWindow::on_pushButton6_clicked()
{
       if(DROP)
       {
    currentHold[5]=1099;
    ui->label6->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[5]=x[position];
       if (!icon1.isNull()) {
    ui->label6->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label6->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton7_clicked()
{
       if(DROP)
       {
    currentHold[6]=1099;
    ui->label7->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[6]=x[position];
       if (!icon1.isNull()) {
    ui->label7->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label7->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton8_clicked()
{    if(DROP)
       {
    currentHold[7]=1099;
    ui->label8->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[7]=x[position];
       if (!icon1.isNull()) {
    ui->label8->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label8->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton9_clicked()
{
       if(DROP)
       {
    currentHold[8]=1099;
    ui->label9->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[8]=x[position];
       if (!icon1.isNull()) {
    ui->label8->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label8->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton10_clicked()
{    if(DROP)
       {
    currentHold[9]=1099;
    ui->label10->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[9]=x[position];
       if (!icon1.isNull()) {
    ui->label10->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label10->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton11_clicked()
{
       if(DROP)
       {
    currentHold[10]=1099;
    ui->label11->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[10]=x[position];
       if (!icon1.isNull()) {
    ui->label11->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label11->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton12_clicked()
{
       if(DROP)
       {
    currentHold[11]=1099;
    ui->label12->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[11]=x[position];
       if (!icon1.isNull()) {
    ui->label12->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label12->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton13_clicked()
{
       if(DROP)
       {
    currentHold[12]=1099;
    ui->label13->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[12]=x[position];
       if (!icon1.isNull()) {
    ui->label13->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label13->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_pushButton14_clicked()
{
       if(DROP)
       {
    currentHold[13]=1099;
    ui->label14->setText("1099");
    DROP=false;
    sort();
    ui->checkWidget->setText("");
    refresh();
    return;
       }
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       QPixmap icon1(imagePath);
       currentHold[13]=x[position];
       if (!icon1.isNull()) {
    ui->label14->setPixmap(icon1);
    // Uncomment the line below if you want to resize the button to match the image size
    // ui->pushButton->setFixedSize(icon1.size());
       } else {
    ui->label14->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       sort();
       ++position;
       refresh();
}


void MainWindow::on_SuperCheat_clicked()
{
       for(int i=2;i<holds;++i)
    currentHold[i]=1099;
       reload();
       sort();
}
void MainWindow::reload()
{
       for(int i=0;i<holds;++i)
       {
    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath = op + QString::number(currentHold[i]) + ed; // Construct the full file path
    QPixmap icon1(imagePath);
    QLabel* label_found=findChild<QLabel*>("label"+QString::number(i+1));
    if (!icon1.isNull()) {
        label_found->setPixmap(icon1);
        // Uncomment the line below if you want to resize the button to match the image size
        // ui->pushButton->setFixedSize(icon1.size());
    } else {
        label_found->setText(QString::number(x[position]));
        qDebug() << "Failed to load image: " << imagePath;
    }
       }
}
void MainWindow::check_LONG()
{

       int count=0;
       for(int i:currentHold)
    if(i!=1099)
        ++count;
       if(count==2)
       {
    bool LONG=false;
    if(currentHold[0]==currentHold[1])
        LONG=true;
    if(currentHold[0]==pre_hold)
        LONG=true;
    if(currentHold[0]==next_hold)
        LONG=true;
    if(currentHold[1]==pre_hold)
        LONG=true;
    if(currentHold[1]==next_hold)
        LONG=true;
    if(LONG)
    {
        ui->checkWidget->setText("恭喜和牌！");
        s.show();
        qDebug() << currentHold[0]<<" "<<currentHold[1]<<" "<<pre_hold<<" "<<next_hold;
    }
       }
}
void MainWindow::display_warn(QVector<QString> warn)
{
       if(warn.size()==1)
       {
    for(int i=0;i<3;++i)
    {
    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath = op + warn[0] + ed; // Construct the full file path
    QPixmap icon1(imagePath);
    QLabel* label_found=findChild<QLabel*>("label_"+QString::number(i+1));
    if (!icon1.isNull()) {
        label_found->setPixmap(icon1);
        // Uncomment the line below if you want to resize the button to match the image size
        // ui->pushButton->setFixedSize(icon1.size());
    } else {
        label_found->setText(QString::number(x[position]));
        qDebug() << "Failed to load image: " << imagePath;
    }
       }
       }
       if(warn.size()==4)
       {
       for(int i=0;i<4;++i)
       {
    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath = op + warn[0] + ed; // Construct the full file path
    QPixmap icon1(imagePath);
    QLabel* label_found=findChild<QLabel*>("label_"+QString::number(i+1));
    if (!icon1.isNull()) {
        label_found->setPixmap(icon1);
        // Uncomment the line below if you want to resize the button to match the image size
        // ui->pushButton->setFixedSize(icon1.size());
    } else {
        label_found->setText(QString::number(x[position]));
        qDebug() << "Failed to load image: " << imagePath;
    }
       }
       }
       if(warn.size()==2)
       {
       QVector<QString> ans=warn;
       if(abs(pre_hold-ans[0].toInt())<3)
    ans.push_back(QString::number(pre_hold));
       if(abs(next_hold-ans[0].toInt())<3)
    ans.push_back(QString::number(next_hold));
       std::sort(ans.begin(),ans.end(),lambda);
       for(int i=0;i<ans.size();++i)
       {

    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath = op + ans[i] + ed; // Construct the full file path
    QPixmap icon1(imagePath);
    QLabel* label_found=findChild<QLabel*>("label_"+QString::number(i+1));
    if (!icon1.isNull()) {
        label_found->setPixmap(icon1);
        // Uncomment the line below if you want to resize the button to match the image size
        // ui->pushButton->setFixedSize(icon1.size());
    } else {
        label_found->setText(QString::number(x[position]));
        qDebug() << "Failed to load image: " << imagePath;
    }
       }
       }
       if(warn.size()==3)
       {
       QVector<QString> ans=warn;
       std::sort(ans.begin(),ans.end(),lambda);
       for(int i=0;i<ans.size();++i)
       {

    QString op = "D:/Projects/Qt/mahjong/img/";
    QString ed = ".PNG";
    QString imagePath = op + ans[i] + ed; // Construct the full file path
    QPixmap icon1(imagePath);
    QLabel* label_found=findChild<QLabel*>("label_"+QString::number(i+1));
    if (!icon1.isNull()) {
        label_found->setPixmap(icon1);
        // Uncomment the line below if you want to resize the button to match the image size
        // ui->pushButton->setFixedSize(icon1.size());
    } else {
        label_found->setText(QString::number(x[position]));
        qDebug() << "Failed to load image: " << imagePath;
    }
       }
       }
}
void MainWindow::clear_warn_display()
{
       ui->label_1->clear();
       ui->label_2->clear();
       ui->label_3->clear();
       ui->label_4->clear();

}
bool MainWindow::lambda(QString a,QString b)
{
       if(a.toInt()<b.toInt())
       return true;
       else
       return false;
}


void MainWindow::on_pushButton_3_clicked()
{
       position=0;
       std::random_device rd;
       std::mt19937 rng(rd());

       // 使用 std::shuffle 来打乱 QVector 中的元素
       std::shuffle(x.begin(), x.end(), rng);
       for(int i=1;i<=holds;++i)
       {
       QString op = "D:/Projects/Qt/mahjong/img/";
       QString ed = ".PNG";
       QString imagePath = op + QString::number(x[position]) + ed; // Construct the full file path
       currentHold.push_back(x[position]);
       QPixmap icon1(imagePath);
       QString numS=QString::number(i);
       QLabel *foundLabel = findChild<QLabel*>("label"+numS);
       if (!icon1.isNull()) {
    foundLabel->setPixmap(icon1);
    //foundLabel->setFixedSize(icon1.size());

       } else {
    foundLabel->setText(QString::number(x[position]));
    //foundLabel->setText(QString::number(x[position]));
    qDebug() << "Failed to load image: " << imagePath;
       }
       ++position;
       }
       sort();
       refresh();
       sort();
       DROP=false;
}

