#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QDialog>
#include <QFileSystemModel>
#include <QDir>

namespace Ui {
class SelectPath;
}

/// Класс, описывающий файловый проводник
class SelectPath : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPath(QWidget *parent = nullptr); /// Инициализация диалогового окна
    ~SelectPath(); /// Деструктор класса

    QString getProjectPath(); /// Возврат пути проекта

private slots:
    void on_listView_doubleClicked(const QModelIndex &index); //вход в директорию

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_listView_clicked(const QModelIndex &index); // выделение директории

private:
    Ui::SelectPath *ui;
    QFileSystemModel *model;
    QModelIndex current;
    QString projectPath;
};

#endif // SELECTPATH_H
