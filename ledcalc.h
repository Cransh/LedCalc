#ifndef LEDCALC_H
#define LEDCALC_H

#include <QMainWindow>

namespace Ui {
class ledcalc;
}

class ledcalc : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ledcalc(QWidget *parent = 0);
    ~ledcalc();
public slots:
    void update_value();
    void update_widget();
    void on_spn_x_valueChanged(int i);
    void on_spn_y_valueChanged(int i);
    void on_btn_clear_clicked();
    void on_btn_invert_clicked();
    void on_btn_save_clicked();
private:
    Ui::ledcalc *ui;
};

#endif // LEDCALC_H
