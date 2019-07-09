<<<<<<< HEAD
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

signals:
    void filePath(const QString &str);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_path_textChanged();

private:
    Ui::SelectPath *ui;
};

#endif // SELECTPATH_H
=======
#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDir>

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
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::SelectPath *ui;
    QFileSystemModel *model;
};

#endif // SELECTPATH_H
>>>>>>> Network/master
