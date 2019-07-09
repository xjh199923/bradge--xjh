#include "adddeflectsensor.h"
#include "ui_adddeflectsensor.h"
#include"deflectpoint.h"
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>  //表头视图类

#include <QFileDialog>      //打开或保存文件对话框
#include <QFile>            //文件类
#include <QTextStream>      //文本流输入输出

adddeflectsensor::adddeflectsensor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adddeflectsensor)
{
    ui->setupUi(this);

    ui->deflectpointnumlineEdit->setPlaceholderText("输入将要设置的测点编号");
    ui->deflectsensornumlineEdit->setPlaceholderText("输入将要设置的传感器编号");
}

adddeflectsensor::~adddeflectsensor()
{
    delete ui;
}

void adddeflectsensor::on_setsavepushButton_clicked()
{
    int temp1=1,temp2=1;
    QString point,sensor;
    point=ui->deflectpointnumlineEdit->text().trimmed();
    sensor=ui->deflectsensornumlineEdit->text().trimmed();
    if(point.isEmpty()||sensor.isEmpty())
    {
        QMessageBox::warning(this, tr("设置传感器"), tr("请先填好几项数据再设置！"));
    }
    QFile fyingbian("/Users/xjh/Desktop/Qt/Bradge_xjh/txt/挠度传感器数据.txt");
    if(!fyingbian.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return ;
    }

    QTextStream txtInput(&fyingbian);
    QString lineStr[201];
    int k=1;
    while(!txtInput.atEnd())
    {

        lineStr[k] = txtInput.readLine();
                k++;
    }
    fyingbian.close();
    int num;
    num=k/8;
    qDebug()<<"kkkk"<<k;
      int m1=0,m2=0,m3=0,m4=0;
      int i=0;
   for(i=0;i<num;i++)
   {
       if(lineStr[i*8+6]==sensor)
       {
           temp1=i*8+6;
           m1=1;break;
       }
   }

   if(lineStr[i*8+5]=="空闲")
   {
       m2=1;
   }
   QFile fstrainpoint("/Users/xjh/Desktop/Qt/Bradge_xjh/txt/deflectpoint.txt");
   if(!fstrainpoint.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       return ;
   }

   QTextStream txtInput1(&fstrainpoint);
   QString lineStr1[201];
   int k1=1;
   while(!txtInput1.atEnd())
   {

       lineStr1[k1] = txtInput1.readLine();
               k1++;
   }
   int num1;
   num1=k1/3;

   fstrainpoint.close();
     int j;
     for(j=0;j<k1;j++)
     {
         if(lineStr1[j*3+2]==point)
         {
             temp2=j*3+2;
             m3=1;break;
         }
     }
     qDebug()<<"m3"<<m3<<"测点编号"<<lineStr1[j*3+2]<<endl;
     if(lineStr1[j*3+3]=="否")
     {
         m4=1;
     }
qDebug()<<"m4"<<m4<<"测点状态"<<lineStr1[j*3+3]<<endl;

     if(m1==1&&m2==1&&m3==1&&m4==1)
     {
         QMessageBox::warning(this, tr("设置传感器"), tr("设置成功！"));



         //设置成功，修改传感器相关信息，

         QString strFileSave = QFileDialog::getSaveFileName(
                     this,
                     tr("保存文件"),
                     tr("/Users/xjh/Desktop/Qt/Bradge_xjh/txt/挠度传感器数据.txt"),
                     tr("Text Files(*.txt)")
                     );
         if(strFileSave.isEmpty())
         {
             return;
         }
         //打开输出文件
         QFile fileOut(strFileSave);
         if( ! fileOut.open(QIODevice::WriteOnly))
         {
             QMessageBox::warning(this, tr("保存文件"), tr("打开保存文件失败：") + fileOut.errorString());
             return;
         }
         //定义输出文本流
         int sen=sensor.toInt();
         QTextStream tsOut( & fileOut);
         lineStr[temp1-1]="已用";
         for(i=1;i<k;i++)
         {
                 QString strCurAll = lineStr[i];
                 tsOut<<strCurAll<<endl;
         }




         //设置成功，修改监测点相关信息，

         QString strFileSave1 = QFileDialog::getSaveFileName(
                     this,
                     tr("保存文件"),
                     tr("/Users/xjh/Desktop/Qt/Bradge_xjh/txt/deflectpoint.txt"),
                     tr("Text Files(*.txt)")
                     );
         if(strFileSave1.isEmpty())
         {
             return;
         }
         //打开输出文件
         QFile fileOut1(strFileSave1);
         if( ! fileOut1.open(QIODevice::WriteOnly))
         {
             QMessageBox::warning(this, tr("保存文件"), tr("打开保存文件失败：") + fileOut.errorString());
             return;
         }
         //定义输出文本流
         QTextStream tsOut1( & fileOut1);
         lineStr1[temp2+1]="是";
         for(i=1;i<k1;i++)
         {
                 QString strCurAll1 = lineStr1[i];
                 tsOut1<<strCurAll1<<endl;
         }

     }

     else if(m1==0&&m2==1&&m3==1&&m4==1)
     {
         QMessageBox::warning(this, tr("设置传感器"), tr("该传感器不存在！"));
     }
     else if(m1==1&&m2==0&&m3==1&&m4==1)
     {
         QMessageBox::warning(this, tr("设置传感器"), tr("该传感器已用！"));
     }
     else if(m1==1&&m2==1&&m3==0&&m4==1)
     {
         QMessageBox::warning(this, tr("设置传感器"), tr("该测点不存在！"));
     }
     else if(m1==1&&m2==1&&m3==1&&m4==0)
     {
         QMessageBox::warning(this, tr("设置传感器"), tr("该测点已设置传感器！"));
     }
     this->close();
   deflectpoint* a =new deflectpoint;
     a->show();
     emit close();
}
