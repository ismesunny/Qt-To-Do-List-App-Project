#include "secdialog.h"
#include "ui_secdialog.h"
#include "mainwindow.h"

secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);

    //Set Disable Button When Text is Empty
    ui->pushButton->setEnabled(false);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, [&](){
        if(ui->plainTextEdit->toPlainText().isEmpty()){
            ui->pushButton->setEnabled(false);
        }else{
            ui->pushButton->setEnabled(true);
        }
    });
    //Read Old Task Beforce Add New Task
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
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::on_pushButton_clicked()
{
    QString fileData = QDir::homePath().append("/.config/todo.json");
    //Read Size Array
    QFile filesize(fileData);
    if(!filesize.open(QIODevice::ReadWrite))
    {
        return;
    }
    QByteArray array = filesize.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(array));
    QJsonObject obj = doc.object();
    QJsonArray arraysize = obj["todo"].toArray();
    //Write New Task
    QFileInfo fileInfo(fileData);
    QDir::setCurrent(fileInfo.path());
    QFile file(fileData);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    QJsonObject textObject;
    textObject["id"] = arraysize.size();
    textObject.insert("completed",false);
    textObject["deadline"] = ui->dateEdit->text();
    textObject["task"] = ui->plainTextEdit->toPlainText();

    QJsonArray textsArray = m_currentJsonObject["todo"].toArray();
    textsArray.append(textObject);
    m_currentJsonObject["todo"] = textsArray;
    file.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    //Commit Task As Item
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(ui->plainTextEdit->toPlainText());
    item->setCheckState(Qt::Unchecked);
    emit on_dialogTextAdded(item);
    ui->plainTextEdit->clear();
    QDialog::close();
}
