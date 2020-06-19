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
#include <QJsonValue>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setCentralWidget(ui->listWidget);
    //setCentralWidget(ui->listWidget2);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listwidget_clicked);
    QFile file(QDir::homePath().append("/.config/todo.json"));
    if(file.open(QIODevice::ReadOnly)){
        QByteArray rawData = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(rawData));
        QJsonObject json = doc.object();
         foreach(const QJsonValue &value ,json) {
            QJsonObject obj = value.toObject();
            // using namespace std;
            QJsonArray todo = json["todo"].toArray();
            //qDebug()<<todo;
            for(int i = 0 ; i < todo.size() ; i++){
                if (todo[i].toObject()["completed"].toBool() == false){
                    ui->listWidget->addItem(todo[i].toObject()["task"].toString());
                     //qDebug()<<todo[i].toObject()["bool"].toString();
                }
            }
        }
    }
    QFile filecp(QDir::homePath().append("/.config.todo"));
    if(filecp.open(QIODevice::ReadOnly)){
        QByteArray rawdata = filecp.readAll();
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
    }
    setWindowTitle("Koompi Todo x List");
    //setStyleSheet("background-color:#7FDBFF");
    setWindowTitle("Koompi Todo x List");
    //ui->listWidget->setStyleSheet("background-color:pink");
    //ui->listView->setStyleSheet("background-color:pink");
    //ui->pushButton->setStyleSheet("background-color:white");
    QPixmap pix(":/rec/img/icons8-todo-list-96.png");
    //QPixmap pix(":/rec/img/download.png");
    int h = ui->picLabel->height();
    int w = ui->picLabel->width();
    ui->picLabel->setPixmap(pix.scaled(w,h));
    QPixmap addpix(":/rec/img/icons8-add-new-96.png");
    //int addh = ui->addPic->height();
    //int addw = ui->addPic->width();
    //ui->addPic->setPixmap(addpix.scaled(addw,addh));
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
    QString fileDel(QDir::homePath().append("/.config/todo.json"));
    QFileInfo fileinfo(fileDel);
    QDir::setCurrent(fileinfo.path());
    QFile fileObjDel(fileDel);
    if(fileObjDel.open(QIODevice::ReadWrite)){
        QByteArray bytearray = fileObjDel.readAll();
        QFile writejsback(fileDel);
        if(writejsback.open(QIODevice::WriteOnly)){
            QJsonDocument Doc(QJsonDocument::fromJson(bytearray));
            QJsonObject obj = Doc.object();
            QJsonArray array = obj["todo"].toArray();
            //qDebug()<<array;
            array.removeAt(selectedRow);
            // array.append(obj);
            m_currentJsonObject["todo"]= array;
            //qDebug()<<QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented);
            //fileObjDel.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
            writejsback.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
        }
    }
}

void MainWindow::update(QString txt)
{
    ui->label->setText(txt);
}

void MainWindow::on_finishButton_clicked()
{   ui->listWidget->takeItem(ui->listWidget->currentRow());
    QString fileDel(QDir::homePath().append("/.config/todo.json"));
        QFileInfo fileinfo(fileDel);
        QDir::setCurrent(fileinfo.path());
        QFile fileObjDel(fileDel);
        if(fileObjDel.open(QIODevice::ReadWrite)){
            QByteArray bytearray = fileObjDel.readAll();
            QFile writejsback(fileDel);
            if(writejsback.open(QIODevice::WriteOnly)){
                QJsonDocument Doc(QJsonDocument::fromJson(bytearray));
                QJsonObject obj = Doc.object();
                QJsonArray array = obj["todo"].toArray();
                QJsonValue valuexx = obj.value(QString("todo"));
                QJsonDocument docc = QJsonDocument(array);
                QJsonObject objttrue ;
               // for(int i = 0 ; i < array.size() ; i++){
                   // if (array[i].toObject()["completed"].toBool() == false){
                        //qDebug()<<array[i].toObject()["completed"].toBool();
                        //qDebug()<<array.toObject()["completed"].toBool();

               // }
                     QJsonValue xx = array[selectedRow].toObject()["completed"].toBool();
                       qDebug()<<array[selectedRow].toObject()["completed"].toBool();
                       qDebug()<<array[selectedRow].toObject()["task"].toString();
                       qDebug()<<array[selectedRow].toObject()["deadeline"].toDouble();
                       qDebug()<<xx;
 array.removeAt(array[selectedRow].toObject()["completed"].toBool());
                qDebug()<<array;

                //obj.removeAt(1);
                /*QByteArray saveData = readFile.readAll();
                QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
                m_currentJsonObject = jsonDocument.object();
                */// qDebug()<<array;
                //qDebug()<<QJsonDocument(obj).toJson(QJsonDocument::Indented);
               //obj.remove("completed",false);
                // array.append(obj);
                m_currentJsonObject["todo"]= array;
            }
           // fileObjDel.remove(array[selectedRow].toObject()["completed"].toBool(true));
                //qDebug()<<QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented);
                //fileObjDel.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
                //writejsback.write(array[selectedRow].toObject()["completed"].toBool(true));
        }
    //move location file
    /*QString taskItem = ui->listWidget->currentItem()->text();
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
    // cp = complet*/
}
void MainWindow::on_recieveData(QString readData)
{
    QListWidgetItem *item = new QListWidgetItem(readData);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);
}

void MainWindow::on_listwidget_clicked(QListWidgetItem *getItem)
{
    qDebug() << "Item clicked"<<endl;
    selectedRow = ui->listWidget->row(getItem);
    qDebug() << selectedRow<<endl;

}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
    widget = ui->listWidget->currentItem();
    int currentRow = ui->listWidget2->currentRow();
    ui->listWidget2->addItem(widget->text());
    ui->listWidget->takeItem(ui->listWidget->currentRow());
    QFile cpFile(QDir::homePath().append("/.config/todo.json"));
   // QFile cpFile("/home/sunny/Downloads/NEW.json");
    if(cpFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        /*
        QString inputData = cpFile.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(inputData.toUtf8());  // This gets the document
        QJsonObject obj = jsonDoc.object(); // This converts the document into an object
        QJsonValue value = obj.value(QString("completed")); // Contains the value I want to update before writing

      value = true;
      qDebug()<<value;
    }
*/
    // read data
      QString ReplyText = cpFile.readAll();
      // qDebug() << ReplyText;
      // ask doc to parse it
      QJsonDocument doc = QJsonDocument::fromJson(ReplyText.toUtf8());
      // we know first element in file is object, to try to ask for such
      QJsonObject obj = doc.object();
      // ask object for value
      QJsonValue value = obj.value(QString("task"));
      QJsonArray array = obj["todo"].toArray();
      QJsonValue valuexx = obj.value(QString("todo"));
      QJsonDocument docc = QJsonDocument(array);
      QJsonObject objttrue ;
      qDebug()<< obj;
      qDebug() << "Bid value is" << value.toString();;
}
}
