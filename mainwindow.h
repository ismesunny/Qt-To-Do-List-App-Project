#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secdialog.h"
#include <QSize>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QTextStream>
#include <QStringList>
#include <QListView>
#include <QAction>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include <QMenuBar>
#include <QListWidget>
#include <QComboBox>
#include <QList>
#include <QDialog>
#include <QString>
#include <QClipboard>
#include <QListWidgetItem>
#include <QByteArray>
#include <QJsonArray>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QStringList>

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
       void emitItemToList(QListWidgetItem *item);
       void emitcpItemDel(QListWidgetItem *itemcp);

   public slots:


       void on_actionAdd_triggered();

       void on_actionRemove_triggered();
       void on_recieveData(QListWidgetItem *item);
       void on_checkboxpush_clicked(QListWidgetItem *itemcb);
       void on_checkboxback_clicked(QListWidgetItem *itemcbback);
       void on_listwidget_clicked(QListWidgetItem * getItem);
       void on_listWidget2_itemClicked(QListWidgetItem *itemCPDel);

   private:

       Ui::MainWindow *ui;
       QListWidgetItem *itemcb;
       QListWidgetItem *itemcbback;
       QListWidgetItem *item;
       QListWidgetItem *itemcp;
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
         QJsonObject m_delecttask;
         QJsonObject m_objtodonew;
         int selectedRow;
          int selectedRowCPDel;
         int id;
          int idcpdel;
};
#endif // MAINWINDOW_H
