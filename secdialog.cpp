#include "secdialog.h"
#include "ui_secdialog.h"
#include "mainwindow.h"

secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
    //ui->plainTextEdit->setFocusPolicy(Qt::NoFocus);
   //ui->dateEdit->setFocusPolicy(Qt::NoFocus);
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
    //ui->plainTextEdit->setFocusPolicy(Qt::NoFocus);
   // ui->dateEdit->setFocusPolicy(Qt::NoFocus);
    QColor coloritem( 213, 216, 220 );
        QBrush brushitem(coloritem);
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
    item->setText("\n " + ui->plainTextEdit->toPlainText() + "\n\t\t\t\t\t\t\t\t" + ui->dateEdit->text());
    item->setCheckState(Qt::Unchecked);
    item->setSelected(false);
    item->setBackground(brushitem);
    item->setFlags(item->flags() &~Qt::ItemIsSelectable);

    emit on_dialogTextAdded(item);
    ui->plainTextEdit->clear();
    QDialog::close();
}
