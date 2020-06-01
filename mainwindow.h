#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "secdialog.h"
#include <secdialog.h>

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QDialog>
#include <QJsonObject>
#include <QListWidget>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 void setLabelText(QString str);

    //void textChanged(const QString &text);
signals:
    void textChanged(const QString &text);

private slots:


    void on_actionQuit_triggered();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_pushButton_clicked();
    void update(QString txt);

    void on_finishButton_clicked();
    void on_recieveData(QString readData);
    void on_addButton_clicked();


private:
    Ui::MainWindow *ui;
     QMenuBar *addmenubar;
     QMenuBar *removemenubar;
     QMenuBar *quitmenubar;
     secDialog *addTextDialog;
      QListWidgetItem *widget;
      // QDialog * addtextDialog;
     //secDialog    *dlg;
      QListWidget *listwidget;
      QListWidget *listwidget2;
      QJsonObject m_currentJsonObject;
};
#endif // MAINWINDOW_H
