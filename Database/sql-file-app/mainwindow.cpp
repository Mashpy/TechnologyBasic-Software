#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Read from my PC server
    readServerDb();
    // Write into db file
    exportDb();

    //Text.clear();
   // CatVar.clear();
  //  CatVar.clear();
    // Read from db file
    readDb();

    for(int i=0;i<CatIdVar2.size();i++)
        ui->comboBox->addItem(CatIdVar2.at(i));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("technologybasic.db");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query1("SELECT * from jos_content order by title;");
    QSqlRecord record = query1.record();
    while (query1.next())
    {
        TitleVar << query1.value(record.indexOf("title")).toString();
        TextVar << query1.value(record.indexOf("introtext")).toString();
        CatIdVar1 << query1.value(record.indexOf("catid")).toString();
    }
    QSqlQuery query2("SELECT * from jos_categories");
    QSqlRecord record1 = query2.record();
    while (query2.next())
    {
       CatVar << query2.value(record1.indexOf("catalias")).toString();
       CatIdVar2 << query2.value(record1.indexOf("catid")).toString();
    }

}

void MainWindow::readServerDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("technolo");
    db.setUserName("root");
    db.setPassword("");
    db.open();

    QSqlQuery query1("SELECT * from jos_content order by title;");
    QSqlRecord record = query1.record();
    while (query1.next())
    {
        TitleVar << query1.value(record.indexOf("title")).toString();
        TextVar << query1.value(record.indexOf("introtext")).toString();
        CatIdVar1 << query1.value(record.indexOf("catid")).toString();
    }
    QSqlQuery query2("SELECT * from jos_categories");
    QSqlRecord record1 = query2.record();
    while (query2.next())
    {
       CatVar << query2.value(record1.indexOf("catalias")).toString();
       CatIdVar2 << query2.value(record1.indexOf("catid")).toString();
    }
}

void MainWindow::exportDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("technologybasic.db");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query1;
    query1.exec("CREATE TABLE `jos_content` (`title` varchar(255),`introtext` text,`catid` int(10))");
    for(int i=0;i<TitleVar.size();i++){
        query1.exec(QString("INSERT INTO `jos_content` VALUES ('%1','%2','%3')").arg(TitleVar.at(i)).arg(TextVar.at(i)).arg(CatIdVar1.at(i)));}

    QSqlQuery query2;
    query1.exec("CREATE TABLE `jos_categories` (`catalias` varchar(255),`catid` int(11))");
    for(int i=0;i<CatVar.size();i++){
        query1.exec(QString("INSERT INTO `jos_categories` VALUES ('%1','%2')").arg(CatVar.at(i)).arg(CatIdVar2.at(i)));}

}

void MainWindow::on_comboBox_activated(int index)
{
    ui->webView->setHtml(TextVar.at(index));
}
