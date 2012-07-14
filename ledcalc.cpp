#include "ledcalc.h"
#include "ui_ledcalc.h"
#include <QPushButton>
#include <QButtonGroup>
#include <math.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
int x_count;
int y_count;
int count;
int first_time=1;
QString out;
int values[8][8];
int calc_x(int c)
{
    int a=0;
    for (int i=0;i<x_count;i++)
        a=a+(values[i][c]*pow(2,i));
    return a;
}
int calc_y(int c)
{
    int a=0;
    for (int i=0;i<y_count;i++)
        a=a+(values[c][y_count-i-1]*pow(2,i));
    return a;
}
float calc_x(float c)
{
    float a=0;
    int cc=c;
    for (int i=0;i<x_count;i++)
        a=a+values[i][cc];
    return a;
}
float calc_y(float c)
{
    float a=0;
    int cc=c;
    for (int i=0;i<x_count;i++)
        a=a+values[cc][i];
    return a;
}

ledcalc::ledcalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ledcalc)
{
    ui->setupUi(this);
    QList <QPushButton *> widgets=this->findChildren<QPushButton *>();
    foreach (QPushButton * widget, widgets) {
        widget->setCheckable(1);
        connect(widget,SIGNAL(clicked()),this,SLOT(update_value()));
    }
  this->on_spn_x_valueChanged(0);
}

ledcalc::~ledcalc()
{
    delete ui;
}
void ledcalc::on_spn_x_valueChanged(int i)
{
x_count=ui->spn_x->value();
y_count=ui->spn_y->value();
this->update_widget();
}
void ledcalc::on_spn_y_valueChanged(int i)
{
    x_count=ui->spn_x->value();
    y_count=ui->spn_y->value();
    this->update_widget();
}
void ledcalc::update_value()
{
    QList <QPushButton *> widgets=this->findChildren<QPushButton *>();
    foreach (QPushButton * widget, widgets) {
        if(widget->isChecked())
            widget->setStyleSheet("background-color: rgb(40, 240, 40)");
        else
            widget->setStyleSheet("background-color: rgb(0, 0, 0)");
    }
    foreach (QPushButton * widget, widgets) {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if( widget->objectName() == "btn_"+QString::number(i)+'_'+QString::number(j))
                {
                    values[i][j]=widget->isChecked();
                }
            }
        }
    }
    QString char1="";
    QString char2="";
    QList <QLineEdit *> widgets1=this->findChildren<QLineEdit *>();
    foreach (QLineEdit * widget, widgets1) {
        for(int i=0;i<8;i++)
        {
                if( widget->objectName() == "ln_1_"+QString::number(i))
                {
                    if(i<y_count)
                    {
                        widget->setText("0x"+QString::number(calc_x(i),16));
                        char2=char2+" "+widget->text()+" ";
                    }
                }
        }
        for(int i=0;i<8;i++)
        {
                if( widget->objectName() == "ln_0_"+QString::number(i))
                {
                    if(i<x_count)
                    {
                        widget->setText("0x"+QString::number(calc_y(i),16));
                        char1=char1+" "+widget->text()+" ";
                    }
                }
        }
    }
    out="int char1["+QString::number(x_count)+"]={"+char1+"}"
            +"\n"+"int char2["+QString::number(y_count)+"]={"+char2+"}";

ui->plainTextEdit->setPlainText(out);
}
void ledcalc::update_widget()
{
    QList <QPushButton *> widgets=this->findChildren<QPushButton *>();
    foreach (QPushButton * widget, widgets) {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if( widget->objectName() == "btn_"+QString::number(i)+'_'+QString::number(j))
                {
                    if(i<x_count&&j<y_count)
                    {
                        widget->setVisible(1);
                    }
                    else
                    {
                        widget->setVisible(0);
                        widget->setChecked(0);
                    }
                }
            }
        }
    }
    QList <QLineEdit *> widgets1=this->findChildren<QLineEdit *>();
    foreach (QLineEdit * widget, widgets1) {
        for(int i=0;i<8;i++)
        {
                if( widget->objectName() == "ln_1_"+QString::number(i))
                {
                    if(i<y_count)
                        widget->setVisible(1);
                    else
                        widget->setVisible(0);
                }
        }
        for(int i=0;i<8;i++)
        {
                if( widget->objectName() == "ln_0_"+QString::number(i))
                {
                    if(i<x_count)
                        widget->setVisible(1);
                    else
                        widget->setVisible(0);
                }
        }
        this->update_value();
    }
}
void ledcalc::on_btn_clear_clicked()
{
    QList <QPushButton *> widgets=this->findChildren<QPushButton *>();
    foreach (QPushButton * widget, widgets) {
        widget->setChecked(0);
    }
    this->update_widget();
}
void ledcalc::on_btn_invert_clicked()
{
    QList <QPushButton *> widgets=this->findChildren<QPushButton *>();
    foreach (QPushButton * widget, widgets) {
        if(widget->isChecked())
            widget->setChecked(0);
        else
            widget->setChecked(1);
    }

    this->update_widget();
}
void ledcalc::on_btn_save_clicked()
{
    QString filename=QFileDialog::getSaveFileName(this,"save file","");
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream out_d(&file);
    out_d<<out;
    file.close();
}

