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
#include <QDebug>
secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
     // setCentralWidget(ui->plainTextEdit);
    ui->pushButton->setEnabled(false);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, [&](){
       if(ui->plainTextEdit->toPlainText().isEmpty()){
           ui->pushButton->setEnabled(false);
       }else{
           ui->pushButton->setEnabled(true);
       }
    });
    //qDebug()<<itemrow;
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
    if(ui->plainTextEdit->toPlainText().isEmpty()){
        ui->pushButton->setDisabled(true);

    }else{
        ui->pushButton->setDisabled(false);
    }
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
    textObject["deadline"] = ui->dateEdit->text();
    textObject["task"] = ui->plainTextEdit->toPlainText();

    QJsonArray textsArray = m_currentJsonObject["todo"].toArray();
    textsArray.append(textObject);
    m_currentJsonObject["todo"] = textsArray;
    file.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    //file.close();
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(ui->plainTextEdit->toPlainText());
    item->setCheckState(Qt::Unchecked);
    emit on_dialogTextAdded(item);
    QDialog::close();
    ui->plainTextEdit->clear();
}
