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
#include <iostream>
secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
   QString openData = QDir::homePath().append("/.config/todo.json");
   QFileInfo fileInfo(openData);
   QDir::setCurrent(fileInfo.path());
   QFile readFile(openData);
    if (readFile.open(QIODevice::ReadOnly))
    {
    QByteArray saveData = readFile.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
    m_currentJsonObject = jsonDocument.object();
}
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
    QString fileData = QDir::homePath().append("/.config/todo.json");
    QFileInfo fileInfo(fileData);
    QDir::setCurrent(fileInfo.path());
     QFile file(fileData);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    QJsonObject textObject;
    textObject.insert("completed",false);
    textObject["deadline"] = ui->lineEdit->text();
    textObject["task"] = ui->plainTextEdit->toPlainText();

    QJsonArray textsArray = m_currentJsonObject["todo"].toArray();
    textsArray.append(textObject);
    m_currentJsonObject["todo"] = textsArray;
    file.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    //file.close();
   emit on_dialogTextAdded(ui->plainTextEdit->toPlainText());
   QDialog::close();
    ui->plainTextEdit->clear();
}
