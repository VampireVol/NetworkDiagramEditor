#ifndef ADDDESCRIPTION_H
#define ADDDESCRIPTION_H

#include <QDialog>

namespace Ui {
class AddDescription;
}

class AddDescription : public QDialog
{
    Q_OBJECT

public:
    explicit AddDescription(QWidget *parent = nullptr);
    ~AddDescription();

private slots:
    void on_plainTextEdit_textChanged();

    void on_ok_clicked();

    void on_reject_clicked();

private:
    Ui::AddDescription *ui;
};

#endif // ADDDESCRIPTION_H
