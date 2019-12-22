#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QMessageBox>
#include "canvas.h"
#include <QTableWidget>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTabWidget>
#include <QApplication>
#include <QPushButton>
#include <QCloseEvent>
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QPushButton>
#include <QTableWidget>
#include <QSpacerItem>
#include <QHeaderView>
#include "delegate.h"
#include "file.h"
#include "saving.h"
#include <QComboBox>
#include <QListView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int num = 1, k = 1;
    QComboBox *cmbx;
    QListView *view;
    QTableWidget *table;
    QTabWidget *tab;
    QPushButton *undo, *redo, *clean;

private:
    Ui::MainWindow *ui;
    bool check;

private slots:
    void changeModeOrient(int index);
    void closeEvent (QCloseEvent *event);
    void closeTab(int index);
    void changeTab(int index);
    void newG();
    void openG();
    void savePic();
    void saveAdj();
    void saveInc();
    void saveVer();
    void saveReb();
    void closeG();
    void undoG();
    void redoG();
    void aboutC();
    void aboutP();
    void cleanG();

//    Обработка матрицы
    void changeMatrix();
    void synchronizeMatrix(QTableWidgetItem*);

//    Алгоритмы
    void func1_1();
    void func1_2();
    void func1_3();

    void func2_1();
    void func2_2();
    void func2_3();
    void func2_4();

    void func3();

    void func4();

    void func5();

    void func6();

    void func7();

    void func9();

    void func10();

    void func11();

    void func15();
};

#endif // MAINWINDOW_H
