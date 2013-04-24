/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fvupdater.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Connect the "check for updates manually" button with the autoupdater
	connect(ui->updateButton, SIGNAL(clicked()),
			FvUpdater::sharedUpdater(), SLOT(CheckForUpdatesNotSilent()));
}

MainWindow::~MainWindow()
{
	delete ui;
}
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QListWidget>
#include <QLabel>
#include "fvupdater.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    readDb();
    for(int i=0;i<TitleVar.size();i++)
    {

        ui->listWidget->addItem(TitleVar.at(i));
    }
    for(int i=0; i< CatVar.size();i++)
    {
        ui->comboBox->addItem(CatVar.at(i));

    }
    connect(ui->updateButton, SIGNAL(clicked()),
            FvUpdater::sharedUpdater(),SLOT(CheckForUpdatesSilent()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("technolo");
    db.setUserName("root");
    db.setPassword("");


// db.setDatabaseName(QDir::home().absoluteFilePath("technologybasic.db"));
        db.open();
        QSqlQuery query1("SELECT * from jos_content;");
        QSqlRecord record = query1.record();
        while (query1.next())
        {
            TitleVar << query1.value(record.indexOf("title")).toString();
            TextVar << query1.value(record.indexOf("introtext")).toString();
        }
        QSqlQuery query2("SELECT * from jos_categories");
        QSqlRecord record1 = query2.record();
        while (query2.next())
        {
           CatVar << query2.value(record1.indexOf("catalias")).toString();
        }

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString var = TextVar.at(TitleVar.indexOf(item->text()));
      var.replace("<img src=\"images",
                   "<img src=\"file:///"+qApp->applicationDirPath()+"/images");
      var.replace("<p><img src=",
                   "<p align=center><img src=");
        ui->textBrowser->setHtml(var);
        ui->textBrowser->setStyleSheet("font:10pt \"SolaimanLipi\";");
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1,Qt::CaseInsensitive,QRegExp::Wildcard);
    ui->listWidget->clear();
    ui->listWidget->addItems(TitleVar.filter(regExp));
}


void MainWindow::on_comboBox_activated(int index)
{
    ui->listWidget->clear();
    CatFilVar.clear();  //Just added this code.
    QString abc= ui->comboBox->currentText();
    QSqlQuery query3("select * from jos_content,jos_categories where catalias='"+abc+"' and jos_content.catid=jos_categories.catid");
            QSqlRecord record2= query3.record();
    while(query3.next())
    {
        CatFilVar<<query3.value(record2.indexOf("title")).toString();
    }

    ui->listWidget->clear();
    for(int i=0; i<CatFilVar.size();i++){
    ui->listWidget->addItem(CatFilVar.at(i));
    }
}
