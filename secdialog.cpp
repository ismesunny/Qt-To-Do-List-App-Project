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
#include <QFileDialog>

secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this); 
    QString openFileName = ("/home/sunny/QT ALL Project/ToDoListApp-Project/taskJsData.json");

    QFileInfo fileInfo(openFileName);
    QDir::setCurrent(fileInfo.path());

    QFile jsonFile(openFileName);
    if (jsonFile.open(QIODevice::ReadOnly))
    {
    QByteArray saveData = jsonFile.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    m_currentJsonObject = jsonDocument.object();
}
    QFile filereadtask("/home/sunny/QT ALL Project/ToDoListApp-Project/taskData.json");
    if(filereadtask.open(QIODevice::WriteOnly | QIODevice::Text)){
     }
    QJsonArray taskJsArray = m_currentJsonObject["Todo"].toArray();

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
    QString saveFileName = ("/home/sunny/QT ALL Project/ToDoListApp-Project/taskJsData.json");
    QFileInfo fileInfo(saveFileName);
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    QJsonObject textObject;
    textObject.insert("Completed","false");
    textObject["Deadline"] = ui->lineEdit->text();
    textObject["Task"] = ui->plainTextEdit->toPlainText();

    QJsonArray textsArray = m_currentJsonObject["Todo"].toArray();
    textsArray.append(textObject);
    m_currentJsonObject["Todo"] = textsArray;
    jsonFile.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    jsonFile.close();

   emit on_dialogTextAdded(ui->plainTextEdit->toPlainText());
  this->close();
    ui->plainTextEdit->clear();
}

