#ifndef ADDRULE_H
#define ADDRULE_H

#include <QDialog>

namespace Ui {
class AddRule;
}

class AddRule : public QDialog
{
    Q_OBJECT

public:
    explicit AddRule(QWidget *parent = nullptr);
    ~AddRule();

public:
    int getColor_1();
    int getColor_2();
    bool getRule();

private slots:
    void on_listWidget_itemClicked();

    void on_listWidget_2_itemClicked();

    void addRule();

    void on_reject_clicked();

    void on_allow_clicked();

    void on_ban_clicked();

private:
    Ui::AddRule *ui;
    bool listWidget_1_clicked;
    bool listWidget_2_clicked;
    QString color1;
    QString color2;
    bool reject;
    int color_1;
    int color_2;
    bool rule;
};

#endif // ADDRULE_H
