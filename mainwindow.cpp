#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QColor coloritem( 213, 216, 220 );
    QBrush brushitem(coloritem);
    ui->listWidget->setSpacing(1);
    ui->listWidget2->setSpacing(1);
    ui->tabWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->listWidget2->setFocusPolicy(Qt::NoFocus);
    setCentralWidget(ui->tabWidget);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_listwidget_clicked);
    connect(ui->listWidget2, &QListWidget::itemClicked,this,&MainWindow::on_listWidget2_itemClicked);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::on_checkboxpush_clicked);
    connect(ui->listWidget2, &QListWidget::itemClicked, this, &MainWindow::on_checkboxback_clicked);
    QFile file(QDir::homePath().append("/.config/todo.json"));
    if(file.open(QIODevice::ReadOnly)){
        QByteArray rawData = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(rawData));
        QJsonObject json = doc.object();
        QJsonArray todo = json["todo"].toArray();
        qDebug()<<"Size Todo Array"<<todo.size();
        for(int i = 0 ; i < todo.size() ; i++){
            if (todo[i].toObject()["completed"].toBool() == false && todo[i].toObject()["task"].toString().isEmpty() == false){
                item = new QListWidgetItem;
                item->setText("\n " + todo[i].toObject()["task"].toString() + "\n\t\t\t\t\t\t\t\t" + todo[i].toObject()["deadline"].toString());
                item->setCheckState(Qt::Unchecked);
                item->setBackground(brushitem);
                //ui->listWidget->setFocusPolicy(Qt::NoFocus);
                item->setFlags(item->flags() &~Qt::ItemIsSelectable);
                ui->listWidget->addItem(item);
                //qDebug()<<todo[i].toObject()["task"].toString();
            }
            if (todo[i].toObject()["completed"].toBool() == true){
                itemcp = new QListWidgetItem();
                itemcp->setText("\n " + todo[i].toObject()["task"].toString() + "\n\t\t\t\t\t\t\t\t" + todo[i].toObject()["deadline"].toString());
                itemcp->setCheckState(Qt::Checked);
                itemcp->setBackground(brushitem);
                itemcp->setFlags(itemcp->flags());
                ui->listWidget2->addItem(itemcp);
            }
        }
    }
    //   QPixmap addpix(":/rec/img/icons8-add-new-96.png");
    addTextDialog = new secDialog(this);
    connect(addTextDialog, &secDialog::on_dialogTextAdded, this,
            &MainWindow::on_recieveData);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAdd_triggered()
{
    addTextDialog->show();
    //dlg->show();
}

void MainWindow::on_actionRemove_triggered()
{
    QString fileData = QDir::homePath().append("/.config/todo.json");
    QFileInfo fileInfo(fileData);
    QDir::setCurrent(fileInfo.path());
    QFile filesize(fileData);
    if(filesize.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QByteArray array = filesize.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(array));
        QJsonObject obj = doc.object();
        QJsonArray arraysize = obj["todo"].toArray();
        // + Remove Task
        //New Object
        QJsonObject newobj;
        /*
        newobj.insert("id",arraysize[id].toObject()["id"].toInt());
        newobj.insert("completed","delected");
        newobj.insert("deadline",arraysize[id].toObject()["deadline"].toString());
        newobj.insert("Deltask",arraysize[id].toObject()["task"].toString());
        //Remove And Replace
        arraysize.removeAt(id);
        arraysize.insert(id,newobj);
*/
        // + Remove CP

        newobj.insert("id",arraysize[idcpdel].toObject()["id"].toInt());
        newobj.insert("completed","delected");
        newobj.insert("deadline",arraysize[idcpdel].toObject()["deadline"].toString());
        newobj.insert("Deltask",arraysize[idcpdel].toObject()["task"].toString());
        //Remove And Replace
        arraysize.removeAt(idcpdel);
        arraysize.insert(idcpdel,newobj);

        //Rewrite All Data
        doc.setObject(newobj);
        QJsonDocument Doc(newobj);
        QJsonDocument docsize(arraysize);
        m_delecttask["todo"] = arraysize;
        //Write New Array To Replace File
        QFile newfilesize(fileData);
        if(newfilesize.open(QIODevice::WriteOnly))
        {
            newfilesize.write(QJsonDocument(m_delecttask).toJson(QJsonDocument::Indented));
            newfilesize.close();
        }
        ui->listWidget2->takeItem(ui->listWidget2->currentRow());
        // ui->listWidget->takeItem(ui->listWidget->currentRow());
    }
}

void MainWindow::on_recieveData(QListWidgetItem * item)
{
    //item->setFlags(item->flags() | Qt::ItemIsEditable);
    item->setFlags(item->flags());
    ui->listWidget->addItem(item);
}

void MainWindow::on_checkboxpush_clicked(QListWidgetItem *itemcb)
{
    QColor coloritem( 213, 216, 220 );
    QBrush brushitem(coloritem);
    if(itemcb->checkState() == Qt::Checked){
        // ui->listWidget->takeItem(selectedRow);
        qDebug() << "Item checked";

        QString fileDatanew = QDir::homePath().append("/.config/todo.json");
        QFileInfo fileInfonew(fileDatanew);
        QDir::setCurrent(fileInfonew.path());
        QFile filesizenew(fileDatanew);
        if(filesizenew.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QByteArray arraynew = filesizenew.readAll();
            QJsonDocument docnew(QJsonDocument::fromJson(arraynew));
            QJsonObject objnew = docnew.object();
            QJsonArray arraysizenew = objnew["todo"].toArray();
            //New Object
            QJsonObject newobjnew;
            newobjnew.insert("id",arraysizenew[id].toObject()["id"].toInt());
            newobjnew.insert("completed",true);
            newobjnew.insert("deadline",arraysizenew[id].toObject()["deadline"].toString());
            newobjnew.insert("task",arraysizenew[id].toObject()["task"].toString());
            //Remove And Replace
            arraysizenew.removeAt(id);
            arraysizenew.insert(id,newobjnew);

            docnew.setObject(newobjnew);
            QJsonDocument Doc(newobjnew);;
            QJsonDocument docsize(arraysizenew);
            m_objtodonew["todo"] = arraysizenew;
            //Write New Array To Replace File
            QFile newfilesize(fileDatanew);
            if(newfilesize.open(QIODevice::WriteOnly))
            {
                newfilesize.write(QJsonDocument(m_objtodonew).toJson(QJsonDocument::Indented));
                newfilesize.close();
            }

            ui->listWidget->takeItem(selectedRow);
            // ui->listWidget->takeItem(ui->listWidget->currentRow());
            //ui->listWidget->takeItem(check)

            QListWidgetItem *itemCP = new QListWidgetItem();
            itemCP->setText("\n " + arraysizenew[id].toObject()["task"].toString() + "\n\t\t\t\t\t\t\t\t" + arraysizenew[id].toObject()["deadline"].toString());
            itemCP->setCheckState(Qt::Checked);
            itemCP->setFlags(itemCP->flags());
            itemCP->setBackground(brushitem);
            //emit on_dialogTextAdded(item);
            ui->listWidget2->addItem(itemCP);
        }
    }
    /*
if (itemcb->checkState() == Qt::Checked){
    qDebug()<<"Row";
    qDebug()<<"Item Click";
    QString fileDatanew = QDir::homePath().append("/.config/todo.json");
    QFileInfo fileInfonew(fileDatanew);
    QDir::setCurrent(fileInfonew.path());
    QFile filesizenew(fileDatanew);
    if(filesizenew.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QByteArray arraynew = filesizenew.readAll();
        QJsonDocument docnew(QJsonDocument::fromJson(arraynew));
        QJsonObject objnew = docnew.object();
        QJsonArray arraysizenew = objnew["todo"].toArray();
        //New Object
        QJsonObject newobjnew;
        newobjnew.insert("id",arraysizenew[id].toObject()["id"].toInt());
        newobjnew.insert("completed",true);
        newobjnew.insert("deadline",arraysizenew[id].toObject()["deadline"].toString());
        newobjnew.insert("task",arraysizenew[id].toObject()["task"].toString());
        //Remove And Replace
        arraysizenew.removeAt(id);
        arraysizenew.insert(id,newobjnew);

        docnew.setObject(newobjnew);
        QJsonDocument Doc(newobjnew);;
        QJsonDocument docsize(arraysizenew);
        m_objtodonew["todo"] = arraysizenew;
        //Write New Array To Replace File
        QFile newfilesize(fileDatanew);
        if(newfilesize.open(QIODevice::WriteOnly))
        {
            newfilesize.write(QJsonDocument(m_objtodonew).toJson(QJsonDocument::Indented));
            newfilesize.close();
        }
        ui->listWidget->takeItem(ui->listWidget->currentRow());
        //ui->listWidget->takeItem(ui->listWidget->currentRow());
        //ui->listWidget->takeItem(check)

        QListWidgetItem *itemCP = new QListWidgetItem();
        itemCP->setText(arraysizenew[id].toObject()["task"].toString());
        itemCP->setCheckState(Qt::Checked);
        //emit on_dialogTextAdded(item);
        ui->listWidget2->addItem(itemCP);
    }
}*/
}

void MainWindow::on_checkboxback_clicked(QListWidgetItem *itemcbback)
{
    QColor coloritem( 213, 216, 220 );
    QBrush brushitem(coloritem);
    if(itemcbback->checkState() == Qt::Unchecked){
        // ui->listWidget->takeItem(selectedRow);
        qDebug() << "Item checked";

        QString fileDatanew = QDir::homePath().append("/.config/todo.json");
        QFileInfo fileInfonew(fileDatanew);
        QDir::setCurrent(fileInfonew.path());
        QFile filesizenew(fileDatanew);
        if(filesizenew.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QByteArray arraynew = filesizenew.readAll();
            QJsonDocument docnew(QJsonDocument::fromJson(arraynew));
            QJsonObject objnew = docnew.object();
            QJsonArray arraysizenew = objnew["todo"].toArray();
            //New Object
            QJsonObject newobjnew;
            newobjnew.insert("id",arraysizenew[idcpdel].toObject()["id"].toInt());
            newobjnew.insert("completed",false);
            newobjnew.insert("deadline",arraysizenew[idcpdel].toObject()["deadline"].toString());
            newobjnew.insert("task",arraysizenew[idcpdel].toObject()["task"].toString());
            //Remove And Replace
            arraysizenew.removeAt(idcpdel);
            arraysizenew.insert(idcpdel,newobjnew);

            docnew.setObject(newobjnew);
            QJsonDocument Doc(newobjnew);;
            QJsonDocument docsize(arraysizenew);
            m_objtodonew["todo"] = arraysizenew;
            //Write New Array To Replace File
            QFile newfilesize(fileDatanew);
            if(newfilesize.open(QIODevice::WriteOnly))
            {
                newfilesize.write(QJsonDocument(m_objtodonew).toJson(QJsonDocument::Indented));
                newfilesize.close();
            }

            ui->listWidget2->takeItem(selectedRowCPDel);
            // ui->listWidget->takeItem(ui->listWidget->currentRow());
            //ui->listWidget->takeItem(check)

            QListWidgetItem *itemcpcbback = new QListWidgetItem();
            itemcpcbback->setText("\n " + arraysizenew[idcpdel].toObject()["task"].toString() + "\n\t\t\t\t\t\t\t\t" + arraysizenew[idcpdel].toObject()["deadline"].toString());
            itemcpcbback->setCheckState(Qt::Unchecked);
            itemcpcbback->setFlags(itemcpcbback->flags());
            itemcpcbback->setBackground(brushitem);
            //emit on_dialogTextAdded(item);
            ui->listWidget->addItem(itemcpcbback);
        }
    }
}

void MainWindow::on_listwidget_clicked(QListWidgetItem *getItem)
{

    QString fileData = QDir::homePath().append("/.config/todo.json");
    QFile filesize(fileData);
    if(!filesize.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray array = filesize.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(array));
    QJsonObject obj = doc.object();
    QJsonArray arraysize = obj["todo"].toArray();
    for(int i =0;i<arraysize.count();i++){
        //        array[selectedRow].toObject()["task"].toString()
        if ("\n " + arraysize[i].toObject()["task"].toString() + "\n\t\t\t\t\t\t\t\t" + arraysize[i].toObject()["deadline"].toString() == getItem->text()){
            id = arraysize[i].toObject()["id"].toInt();
            qDebug() <<"ID IN JSON FILE"<< arraysize[i].toObject()["id"].toInt();
        }
    }
    selectedRow = ui->listWidget->row(getItem);
    qDebug()<<"Select Row"<<selectedRow;
    emit emitItemToList(getItem);

}
/*void MainWindow::on_pushButton_clicked()
{
    //if (item->checkState() == Qt::Checked){
        qDebug()<<"Row " << selectedRow;
       // ui->listWidget->takeItem(ui->listWidget->currentRow());
        //ui->listWidget->addItem(item);
        QString fileDel(QDir::homePath().append("/.config/todo.json"));
        QFileInfo fileinfo(fileDel);
        QDir::setCurrent(fileinfo.path());
        QFile fileObjDel(fileDel);
        if(fileObjDel.open(QIODevice::ReadWrite | QIODevice::Text)){
            QByteArray bytearray = fileObjDel.readAll();
            QJsonDocument Doc(QJsonDocument::fromJson(bytearray));
            QJsonObject obj = Doc.object();
            QJsonArray array = obj["todo"].toArray();
            QJsonValue valuexx = obj.value(QString("todo"));
            QJsonDocument docc = QJsonDocument(array);
            QJsonObject objttrue ;
            QStringList propertyNames;

            foreach (const QJsonValue & valuexx, array) {
                QJsonObject objtrue = valuexx.toObject();
                propertyNames.append(objtrue["todo"].toString());
             qDebug()<<"1111111"<<propertyNames;
            }
            qDebug()<<propertyNames;
            // for(int i = 0 ; i < array.size() ; i++){
            // if (array[i].toObject()["completed"].toBool() == false){
            //qDebug()<<array[i].toObject()["completed"].toBool();
            //qDebug()<<array.toObject()["completed"].toBool();

            // }
            QJsonValue xx = array[selectedRow].toObject()["completed"].toBool();
            QJsonObject objx = xx.toObject();
            QJsonDocument docx;
            QJsonDocument(objx).toJson(QJsonDocument::Indented);
            qDebug()<< QJsonDocument(objx).toJson();
            qDebug()<<array[selectedRow].toObject()["completed"].toBool();
            qDebug()<<"task"<<array[selectedRow].toObject()["task"].toString();
            qDebug()<<"deadline"<<array[selectedRow].toObject()["deadline"].toString();
            qDebug()<<array[selectedRow].toObject()["deadeline"].toDouble();
            qDebug()<<xx;
            qDebug()<<"array"<<array;
            for ( int i = 0 ; i< obj["todo"].toArray().size() ; i++){
            qDebug()<<"Show"<<array[i].toObject();
            }
            qDebug()<<propertyNames;


            //array.removeAt(array[selectedRow].toObject()["completed"].toBool());
            qDebug()<<array;
            qDebug()<<objx;

            fileDel.remove(array[selectedRow].toObject()["completed"].toBool());

            m_currentJsonObject["todo"]= array;

            QJsonObject newwobj;
            newwobj.insert("task",array[selectedRow].toObject()["task"].toString());
            newwobj.insert("completed",true);
            newwobj.insert("deadline",array[selectedRow].toObject()["deadline"].toString());
            QJsonArray newarray = m_objtodonew["todo"].toArray();
            newarray.append(newwobj);
            m_objtodonew["todo"] = newarray;
            QJsonDocument newdoc(m_objtodonew);
            qDebug()<<"Newww"<<newdoc.toJson(QJsonDocument::Indented);
            //ui->listWidget2->addItem(newdoc.toJson(QJsonDocument::Indented));
            //
            // Delect Old Array
            QString newfileDel(QDir::homePath().append("/.config/todo.json"));
            QFileInfo newfileinfo(newfileDel);
            QDir::setCurrent(newfileinfo.path());
            QFile newfileObjDel(newfileDel);
            if(newfileObjDel.open(QIODevice::ReadWrite)){
                QByteArray bytearray = newfileObjDel.readAll();
                QFile newwritejsback(newfileDel);
                if(newwritejsback.open(QIODevice::WriteOnly)){
                    QJsonDocument Doc(QJsonDocument::fromJson(bytearray));
                    QJsonObject obj = Doc.object();
                    QJsonArray array = obj["todo"].toArray();
                   // qDebug()<<"array"<<;
                    array.removeAt(selectedRow);
                    // array.append(obj);
                    m_currentJsonObject["todo"]= array;
                    qDebug()<<"Remove Back"<<QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented);
                    //fileObjDel.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
                    newwritejsback.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
                    newwritejsback.close();
                }
            }
            //ReadData Back

          /*

            QString openData = QDir::homePath().append("/.config/todo.json");
            QFileInfo fileInfo(openData);
            QDir::setCurrent(fileInfo.path());
            QFile readFile(openData);
            if (readFile.open(QIODevice::ReadOnly))
            {
                QByteArray saveData = readFile.readAll();
                QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));
                m_objtodonew = jsonDocument.object();
     qDebug()<<"readd"<<m_objtodonew;
    // Write Data Back
                QString fileData = QDir::homePath().append("/.config/todo.json");
                QFileInfo fileInfo(fileData);
                QDir::setCurrent(fileInfo.path());
                QFile file(fileData);
                if (file.open(QIODevice::WriteOnly) | QIODevice::Text)
                {

     \
                QJsonArray textsArray = m_objtodonew["todo"].toArray();
                textsArray.append(newwobj);
                m_objtodonew["todo"] = textsArray;
                qDebug()<<"JJ"<<QJsonDocument(m_objtodonew).toJson(QJsonDocument::Indented);
                }
                file.write(QJsonDocument(m_objtodonew).toJson(QJsonDocument::Indented));
                file.flush();
                file.close();
            }

        QListWidgetItem *itemCP = new QListWidgetItem();
            itemCP->setText(array[selectedRow].toObject()["task"].toString());
            itemCP->setCheckState(Qt::Checked);
            //emit on_dialogTextAdded(item);
  //UI       ui->listWidget2->addItem(itemCP);
    }
        ui->listWidget->takeItem(ui->listWidget->currentRow());
        }
  }
*/


void MainWindow::on_listWidget2_itemClicked(QListWidgetItem *itemCPDel)
{
    QString fileData = QDir::homePath().append("/.config/todo.json");
    QFile filesize(fileData);
    if(!filesize.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray array = filesize.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(array));
    QJsonObject obj = doc.object();
    QJsonArray arraysize = obj["todo"].toArray();

    for(int i =0;i<arraysize.count();i++){
        //        array[selectedRow].toObject()["task"].toString()
       // if (arraysize[i].toObject()["task"].toString() == itemCPDel->text()){
        if("\n " + arraysize[i].toObject()["task"].toString() + "\n\t\t\t\t\t\t\t\t" + arraysize[i].toObject()["deadline"].toString() == itemCPDel->text()){
            idcpdel = arraysize[i].toObject()["id"].toInt();
            qDebug() <<"IDCPDEL IN JSON FILE"<< arraysize[i].toObject()["id"].toInt();
        }
    }
    selectedRowCPDel = ui->listWidget2->row(itemCPDel);
    qDebug()<<"selectedCPDel"<<selectedRowCPDel;
    emit emitcpItemDel(itemCPDel);
}



