#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pcb.h"
#include "vector"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static bool compare(PCB* a,PCB* b);
    static const int maxPrio=50;
    void Random_Create_PCB();
    void insertReadyQueue(PCB* process,int name);
    void showProcess();



    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_createprocess_clicked();
    void on_deleteprocess_clicked();

    void on_start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
