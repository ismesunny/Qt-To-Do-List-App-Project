#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QListWidgetItem>

namespace Ui {
class secDialog;
}

class secDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();

signals:
    void on_dialogTextAdded(QListWidgetItem *);
private slots:
    void on_pushButton_clicked();
private:
    Ui::secDialog *ui;
      QJsonObject m_currentJsonObject;
};

#endif // SECDIALOG_H
