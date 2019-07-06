#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QDialog>

namespace Ui {
class ProjectName;
}

class ProjectName : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectName(QWidget *parent = nullptr);
    ~ProjectName();
public:
    QString projectName();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_projectName_textChanged();

private:
    Ui::ProjectName *ui;
};

#endif // SELECTPATH_H
