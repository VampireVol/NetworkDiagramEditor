#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QDialog>

namespace Ui {
class SelectPath;
}

class SelectPath : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPath(QWidget *parent = nullptr);
    ~SelectPath();

 private slots:
    void okClicked();

private:
    Ui::SelectPath *ui;
};

#endif // SELECTPATH_H
