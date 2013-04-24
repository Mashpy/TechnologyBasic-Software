/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readDb();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    QStringList TitleVar, TextVar, CatVar,CatFilVar;
};

#endif // MAINWINDOW_H
