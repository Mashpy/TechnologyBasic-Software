#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

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
    void exportDb();
    void readServerDb();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    QStringList TitleVar,TextVar,CatVar,CatFilVar,CatIdVar1,CatIdVar2;
};

#endif // MAINWINDOW_H
