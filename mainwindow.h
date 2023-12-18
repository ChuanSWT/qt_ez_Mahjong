#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QVector>
#include <QMainWindow>
#include "form.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton1_clicked();


    void on_checkWidget_clicked();

    void on_pushButton_clicked();
    void on_pushButton2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_label5_linkActivated(const QString &link);

    void on_pushButton5_clicked();

    void on_pushButton6_clicked();

    void on_pushButton7_clicked();

    void on_pushButton8_clicked();

    void on_pushButton9_clicked();

    void on_pushButton10_clicked();

    void on_pushButton11_clicked();

    void on_pushButton12_clicked();

    void on_pushButton13_clicked();

    void on_pushButton14_clicked();

    void on_SuperCheat_clicked();

    void on_pushButton_3_clicked();

private:
void sort();//排序手牌
    void refresh();//玩家打牌后，刷新场上落牌的状态，关联到其他检测方法；
void checkThrow();//检测-是否可以对下家吃碰杠，并触发checkThrow
    void checkThrow2();//对checkThrow检测的补充，检测上家
    void reload();//重新跟据currentHold数组，为每个label覆上图片
void check_LONG();//检测-是否和牌
    void display_warn(QVector<QString> warn);//检测到事件后，通过ui提示玩家
void clear_warn_display();//放弃某事件时，清空事件提示
    bool static lambda(QString a,QString b);//对QString的字典比较 可调用模块
    int holds;//当前持牌数
    QVector<int> x;//牌堆
    QVector<int> currentHold;//当前手牌
    int position=0;//牌堆轮牌
    QVector<QString> warn;//发现可以：吃碰杠的牌
    QVector<QVector<QString>> checked;//一轮检查中玩家已经放弃的吃碰杠
    bool DROP;//吃碰后需要丢掉一张牌   
    int pre_hold;//上家打出的牌
    int next_hold;//下家打出的牌
    Form s;//存储和牌的窗口
    int debug_int=0;//debug用途
 Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
