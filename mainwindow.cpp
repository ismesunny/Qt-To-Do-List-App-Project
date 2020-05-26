#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   std::cout << "Application created" <<std::endl;
// QString taskItem = ui->listWidget->currentItem()->text();
     QFile filecpitem("/home/sunny/QT ALL Project/ToDoListApp-Project/CompletedData.json");
     // QString saveText = ui->plainTextEdit->toPlainText();
      if(filecpitem.open(QIODevice::ReadOnly | QIODevice::Text))
      {

          QTextStream text(&filecpitem);
           QString taskItem = text.readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(filecpitem.readAll());
            QJsonObject jsonobj;
         // jsonobj.insert("item",taskItem);

          QString data = jsonDoc.object().value("item").toString();
          ui->listWidget->addItem(data);
//         filecpitem.write(jsondoc.toJson());
       ui->listWidget2->addItem(data);

             filecpitem.close();
      }

    setWindowTitle("Koompi Todo x List");

//ui->listWidget->setStyleSheet("background-color:pink");
//ui->listView->setStyleSheet("background-color:pink");
//ui->pushButton->setStyleSheet("background-color:white");

    QPixmap pix(":/rec/icons8-todo-list-96.png");
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

 //dlg->show();
}

void MainWindow::on_actionRemove_triggered()
{
ui->listWidget->takeItem(ui->listWidget->currentRow());
ui->listWidget2->takeItem(ui->listWidget2->currentRow());
//remove task
QFile filecp("/home/sunny/QT ALL Project/ToDoListApp-Project/CompletedData.json");
filecp.remove();
 QFile file("/home/sunny/QT ALL Project/ToDoListApp-Project/TaskData.json");
file.remove();
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
