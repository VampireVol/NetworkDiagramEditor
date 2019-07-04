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
