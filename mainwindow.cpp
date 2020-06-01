#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog.h"
#include "dialog.h"
#include <QSize>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QListView>
#include <QAction>
#include <QToolBar>
#include <QApplication>
#include <QMenuBar>
#include <QListWidget>
#include <QList>
#include <QDialog>
#include <QString>
#include <QListWidgetItem>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(QDir::homePath().append("/.config/todo.json"));
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();
    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    QJsonObject json = doc.object();
     foreach(const QJsonValue &value ,json) {
         QJsonObject obj = value.toObject();
        // using namespace std;
        QJsonArray todo = json["todo"].toArray();
        for(int i = 0 ; i < todo.size() ; i++){
            if (todo[i].toObject()["completed"].toBool() == false){
                ui->listWidget->addItem(todo[i].toObject()["task"].toString());
            }
     }
    }
     if(!file.open(QIODevice::ReadOnly))
     {
             return;
     }
       QByteArray rawdata = file.readAll();
       QJsonDocument Doc(QJsonDocument::fromJson(rawdata));
       QJsonObject Json = Doc.object();
       foreach (const QJsonValue &value ,Json) {
           QJsonObject Obj = value.toObject();
         QJsonArray Todo = Json["todo"].toArray();
         for (int i = 0; i<Todo.size(); i++){
             if(Todo[i].toObject()["completed"].toBool() == true){
                 ui->listWidget2->addItem(Todo[i].toObject()["task"].toString());
             }
         }
       }

    setWindowTitle("Koompi Todo x List");

//ui->listWidget->setStyleSheet("background-color:pink");
//ui->listView->setStyleSheet("background-color:pink");
//ui->pushButton->setStyleSheet("background-color:white");

    QPixmap pix(":/rec/img/Todo-iCon.png");
 //QPixmap pix(":/rec/img/download.png");
    int h = ui->picLabel->height();
    int w = ui->picLabel->width();
ui->picLabel->setPixmap(pix.scaled(w,h));
//setStyleSheet("background-color: RGB(68, 184, 172);");
addTextDialog = new secDialog(this);
connect(addTextDialog, &secDialog::on_dialogTextAdded, this,
        &MainWindow::on_recieveData);
//Drag and Drop Item In List Widget
ui->listWidget->setDragEnabled(true);
ui->listWidget->setAcceptDrops(true);
ui->listWidget->setDropIndicatorShown(true);
ui->listWidget->setDefaultDropAction(Qt::MoveAction);

ui->listWidget2->setDragEnabled(true);
ui->listWidget2->setDropIndicatorShown(true);
ui->listWidget2->setAcceptDrops(true);

ui->listWidget2->setDefaultDropAction(Qt::MoveAction);
    }
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setLabelText(QString str)
{
    ui->label->setText(str);//it is label dialog
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAdd_triggered()
{
addTextDialog->show();
//Dialog dialog;
//dialog.exec();

 //dlg->show();
}

void MainWindow::on_actionRemove_triggered()
{
   QFile del("/home/sunny/QT ALL Project/ToDoListApp-Project/taskJsData.json");
   del.remove();
ui->listWidget->takeItem(ui->listWidget->currentRow());
ui->listWidget2->takeItem(ui->listWidget2->currentRow());
QJsonObject textObject;
//remove Data
QFile fileData(QDir::homePath().append("/.config/Data.json"));
m_currentJsonObject = QJsonObject();
if (ui->listWidget->currentItem()->isSelected()){

}
}

void MainWindow::update(QString txt)
{
   ui->label->setText(txt);
}

void MainWindow::on_finishButton_clicked()
{
    //move location file
    QString taskItem = ui->listWidget->currentItem()->text();
     QFile filecpitem("/home/sunny/QT ALL Project/ToDoListApp-Project/CompletedData.json");
     // QString saveText = ui->plainTextEdit->toPlainText();
      if(filecpitem.open(QIODevice::Append | QIODevice::Text))
      {
          QTextStream text(&filecpitem);
          QJsonObject jsonobj;
          jsonobj.insert("item",taskItem);
          QJsonDocument jsondoc;
          jsondoc.setObject(jsonobj);
         filecpitem.write(jsondoc.toJson());
           filecpitem.flush();
             filecpitem.close();
      }
    //remove textData file
   QFile file("/home/sunny/QT ALL Project/ToDoListApp-Project/TaskData.json");
   file.remove();
    widget = ui->listWidget->currentItem();
    int currentRow = ui->listWidget2->currentRow();
    ui->listWidget2->addItem(widget->text());
   ui->listWidget->takeItem(ui->listWidget->currentRow());
//move text in widget one to wideget
   // cp = complet
   // QByteArray itemWidget = ui->listWidget->currentRow();


}

void MainWindow::on_recieveData(QString readData)
{
    QListWidgetItem *item = new QListWidgetItem(readData);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
    widget = ui->listWidget->currentItem();
    int currentRow = ui->listWidget2->currentRow();
    ui->listWidget2->addItem(widget->text());
   ui->listWidget->takeItem(ui->listWidget->currentRow());
}
