#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>
#include <QLineEdit>
#include<QTextEdit>
#include <QMainWindow>
#include "mainwindow.h"
#include <QListWidgetItem>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QFile>
#include <QJsonArray>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this); 

    QFile filereadtask("/home/sunny/QT ALL Project/ToDoListApp-Project/taskData.json");
    if(filereadtask.open(QIODevice::ReadOnly | QIODevice::Text)){
       // QTextStream filetask;
      //  QByteArray readTaskBack = filereadtask.readAll();
    }
    QByteArray saveData = filereadtask.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    QJsonArray taskJsArray = m_currentJsonObject["Todo"].toArray();


ui->lineEdit->setText("Enter DeadLine");
ui->lineEdit->selectAll();
//ui->plainTextEdit->setPlainText("Please Add Your Task Here!");
//ui->plainTextEdit->selectAll();
    setWindowTitle("Koompi Todo x List.");
    //setStyleSheet->("background-color: rgb(255, 170, 255);");
setStyleSheet("background-color: rgb(170, 255, 255);");
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::on_pushButton_clicked()
{
   /* QFile filereadtask("/home/sunny/QT ALL Project/ToDoListApp-Project/taskData.json");
    if(filereadtask.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream filetask;
        QString readTaskBack = filereadtask.readAll();}
    */
    QFile filetask("/home/sunny/QT ALL Project/ToDoListApp-Project/taskData.json");
    if(filetask.open(QIODevice::WriteOnly | QIODevice::Text)){
        QJsonObject taskjsonobj;
        taskjsonobj["DeadLine"] = ui->lineEdit->text();
        taskjsonobj["Task"] = ui->plainTextEdit->toPlainText();
        taskjsonobj.insert("Completed","false");

        QFile filereadtask("/home/sunny/QT ALL Project/ToDoListApp-Project/taskData.json");
        if(filereadtask.open(QIODevice::ReadOnly | QIODevice::Text)){
           // QTextStream filetask;
          //  QByteArray readTaskBack = filereadtask.readAll();
        }
        QByteArray saveData = filereadtask.readAll();
        QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));

        QJsonArray taskJsArray = m_currentJsonObject["Todo"].toArray();
        taskJsArray.append(taskjsonobj);
        m_currentJsonObject["Todo"] = taskJsArray;
  }


    QString taskText = QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented);
    //QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    filetask.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    ui->lineEdit->clear();
    filetask.close();
    /*
             QFile filecp("/home/sunny/QT ALL Project/ToDoListApp-Project/complettext.txt");
               if(filecp.open(QFile::Append |  QFile::Text))
               {
                   QTextStream writecp(&filecp);
                  QString textcp = ui->plainTextEdit->toPlainText();
                  writecp<<textcp;
                  filecp.flush();
                  file.close();
                  */
//emit on_dialogTextAdded(ui->lineEdit->text());// we cant use textEdit.
   emit on_dialogTextAdded(ui->plainTextEdit->toPlainText());
  this->close();
    ui->plainTextEdit->clear();
}

