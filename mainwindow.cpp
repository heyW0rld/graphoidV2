#include "mainwindow.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    Создание виджетов
    ui->setupUi(this);
    this->setWindowTitle("Графан");
//    this->setStyleSheet("background-color: #E8EBED");

    QHBoxLayout *mainlay = new QHBoxLayout;
    QHBoxLayout *hlay = new QHBoxLayout;
    QVBoxLayout *vlay = new QVBoxLayout;
    Delegate *dlg = new Delegate;

//    Выпадающий список
    cmbx = new QComboBox(this);
    view = new QListView();
    view->setStyleSheet("QListView{"
                        "   color: #696969;"
                        "   background-color: white;"
                        "   border: 1px solid #828282;"
                        "   border-radius: 4px;"
                        "   font-size: 20px;"
                        "}");
    cmbx->setView(view);
    cmbx->setStyleSheet("QComboBox{"
                        "   color: #696969;"
                        "   background-color: white;"
                        "   border: 1px solid #828282;"
                        "   border-radius: 4px;"
                        "   font-size: 20px;"
                        "}"
                        ""
                        "QComboBox:hover{"
                        "   border: 1px solid #828282;"
                        "   background-color: #E8EBED;"
                        "}"
                        "QComboBox:hover:pressed{"
                        "   border: 1px solid #828282;"
                        "   background-color: #E8EBED;"
                        "}");
    cmbx->addItem("Неориентированный граф");
    cmbx->addItem("Ориентированный граф");


//    Кнопки
    undo = new QPushButton("Отмена", this);
    undo->setShortcut(tr("Ctrl+Z"));
    undo->setStyleSheet("QPushButton{"
                        "   color: #696969;"
                        "   background-color: white;"
                        "   border: 1px solid #828282;"
                        "   border-radius: 4px;"
                        "   font-size: 20px;"
                        "}"
                        ""
                        "QPushButton:hover{"
                        "   border: 1px solid #828282;"
                        "   background-color: #E8EBED;"
                        "}"
                        "QPushButton:hover:pressed{"
                        "   background-color: gray;"
                        "   color: white;"
                        "}");

    redo = new QPushButton("Повторить", this);
    redo->setShortcut(tr("Ctrl+Shift+Z"));
    redo->setStyleSheet("QPushButton{"
                        "   color: #696969;"
                        "   background-color: white;"
                        "   border: 1px solid #828282;"
                        "   border-radius: 4px;"
                        "   font-size: 20px;"
                        "}"
                        ""
                        "QPushButton:hover{"
                        "   border: 1px solid #828282;"
                        "   background-color: #E8EBED;"
                        "}"
                        "QPushButton:hover:pressed{"
                        "   background-color: gray;"
                        "   color: white;"
                        "}");
    clean = new QPushButton("Очистить холст", this);
    clean->setShortcut(tr("Ctrl+R"));
    clean->setStyleSheet("QPushButton{"
                        "   color: #696969;"
                        "   background-color: white;"
                        "   border: 1px solid #828282;"
                        "   border-radius: 4px;"
                        "   font-size: 20px;"
                        "}"
                        ""
                        "QPushButton:hover{"
                        "   border: 1px solid #828282;"
                        "   background-color: #E8EBED;"
                        "}"
                        "QPushButton:hover:pressed{"
                        "   background-color: gray;"
                        "   color: white;"
                        "}");

//    Матрица
    table = new QTableWidget;
    table->setMinimumSize(300, 400);
    table->setMaximumSize(400, 20000);
    table->setRowCount(0);
    table->setColumnCount(0);
    table->horizontalHeader()->setDefaultSectionSize(40);
    table->verticalHeader()->setDefaultSectionSize(40);
    table->horizontalHeader()->setMaximumSectionSize(40);
    table->horizontalHeader()->setMinimumSectionSize(40);
    table->verticalHeader()->setMaximumSectionSize(40);
    table->verticalHeader()->setMinimumSectionSize(40);
    table->setItemDelegate(dlg);

    QTableWidgetItem *item = new QTableWidgetItem(tr("1"));
    table->setItem(0, 0, item);

//    Вкладки
    tab = new QTabWidget;
    tab->setTabsClosable(true);
    newG();

//    Компановка виджетов
    mainlay->addWidget(tab);
    hlay->addWidget(undo);
    hlay->addSpacing(8);
    hlay->addWidget(redo);
    vlay->addSpacing(22);
    vlay->addWidget(cmbx);
    vlay->addSpacing(8);
    vlay->addItem(hlay);
    vlay->addSpacing(8);
    vlay->addWidget(clean);
    vlay->addSpacing(8);
    vlay->addWidget(table);
    vlay->addSpacing(4);
    mainlay->addItem(vlay);

    ui->centralwidget->setLayout(mainlay);

//    Меню:
    menuBar()->setStyleSheet("QMenu{"
                        "   color: black;"
                        "   background-color: white;"
                        "   border: 1px solid #828282;"
                        "}"
                        ""
                        "QMenu:selected{"
                        "   border: 1px solid #828282;"
                        "   background-color: #E8EBED;"
                        "}"
                        "QMenu:selected:pressed{"
                        "   background-color: #828282;"
                        "   color: white;"
                        "}");

//    Открытие, закрытие, сохранение файла, выход из программы
    QMenu *file = menuBar()->addMenu("&Файл");
    QAction *newGraph = new QAction(tr("&Создать"), this);
    newGraph->setShortcut(tr("Ctrl+N"));
    QAction *openGraph = new QAction(tr("&Открыть"), this);
    openGraph->setShortcut(tr("Ctrl+O"));
    QMenu *saveAs = new QMenu(tr("&Сохранить как"), this);
    QAction *savePicture = new QAction(tr("&Изображение"), this);
    savePicture->setShortcut(tr("Alt+I"));
    QAction *saveIncident = new QAction(tr("&Матрицу инцидентности"), this);
    saveIncident->setShortcut(tr("Alt+D"));
    QAction *saveSmejn = new QAction(tr("&Матрицу смежности"), this);
    saveSmejn->setShortcut(tr("Alt+M"));
    QAction *saveV = new QAction(tr("&Сохранение вершин"), this);
    saveV->setShortcut(tr("Alt+V"));
    QAction *saveR = new QAction(tr("&Сохранение ребер"), this);
    saveR->setShortcut(tr("Alt+R"));

    QAction *exit = new QAction(tr("&Выход"), this);
    exit->setShortcut(tr("Ctrl+E"));
    file->addAction(newGraph);
    file->addAction(openGraph);
    file->addMenu(saveAs);
    saveAs->addAction(savePicture);
    saveAs->addAction(saveSmejn);
    saveAs->addAction(saveIncident);
    saveAs->addAction(saveV);
    saveAs->addAction(saveR);
    file->addAction(exit);

    /*
    //Изменение
    QMenu *changeGraph = menuBar()->addMenu("&Изменить");
    QAction *un = new QAction(tr("&Отмена"), this);
    un->setShortcut(tr("Ctrl+Z"));
    QAction *re = new QAction(tr("&Повторить"), this);
    re->setShortcut(tr("Ctrl+Shift+Z"));
    changeGraph->addAction(un);
    changeGraph->addAction(re);
    */

//    Функционал
    QMenu *functions = menuBar()->addMenu("&Задачи теории графов");

//          ===== <ЗАДАНИЯ> =====
//    2 лаба
    QMenu *f1 = new QMenu(tr("&Поиск пути"), this);
    QAction *f1_1 = new QAction(tr("&Breagth-First Search"), this);
    QAction *f1_2 = new QAction(tr("&A*"), this);
    QAction *f1_3 = new QAction(tr("&Iterative deepening A*"), this);
    functions->addMenu(f1);
    f1->addAction(f1_1);
    f1->addAction(f1_2);
    f1->addAction(f1_3);

//    3 лаба
    QMenu *f2 = new QMenu(tr("&Алгоритм Дейкстры и близкие к нему"), this);
    QAction *f2_1 = new QAction(tr("&Флойд-Уоршелл"), this);
    QAction *f2_2 = new QAction(tr("&Дейкстра"), this);
    QAction *f2_3 = new QAction(tr("&Беллман-Форд"), this);
    QAction *f2_4 = new QAction(tr("&Джонсон"), this);
    functions->addMenu(f2);
    f2->addAction(f2_1);
    f2->addAction(f2_2);
    f2->addAction(f2_3);
    f2->addAction(f2_4);

//    4 лаба
    QAction *f3 = new QAction(tr("&Эксцентриситет, радиус, диаметр и степени"), this);
    functions->addAction(f3);

//    5 лаба
    QAction *f4 = new QAction(tr("&Изоморфизм графов"), this);
    functions->addAction(f4);

//    6 лаба
    QAction *f5 = new QAction(tr("&Связность графа"), this);
    functions->addAction(f5);

//    7 лаба
    QAction *f6 = new QAction(tr("&Дополнение для графа"), this);
    functions->addAction(f6);

    QAction *f7 = new QAction(tr("&Бинарные операции над графами"), this);
    functions->addAction(f7);

//  9 лаба
        QAction *f9 = new QAction(tr("&Планарность"), this);
        functions->addAction(f9);

//    10 лаба
    QAction *f10 = new QAction(tr("&Восстановление графа из вектора"), this);
    functions->addAction(f10);

//    11 лаба
    QAction *f11 = new QAction(tr("&Экстремальные графы"), this);
    functions->addAction(f11);

//    12 лаба
    QMenu *f12 = new QMenu(tr("&Каркас графа"), this);
    QAction *f121 = new QAction(tr("&Алгоритм Краскала"), this);
    QAction *f122 = new QAction(tr("&Алгоритм Прима"), this);
    QAction *f123 = new QAction(tr("&Алгоритм Борувки"), this);
    functions->addMenu(f12);
    f12->addAction(f121);
    f12->addAction(f122);
    f12->addAction(f123);

//    13 лаба
    QAction *f13 = new QAction(tr("&Задача о цикле"), this);
    functions->addAction(f13);

//    15 лаба
    QAction *f15 = new QAction(tr("&Задача о свадьбах"), this);
    functions->addAction(f15);

//          ===== </ЗАДАНИЯ> =====


//    Информация
    QMenu *about = menuBar()->addMenu("?");
    QAction *creators = new QAction("О&б авторах");
    creators->setShortcut(tr("Ctrl+I"));
    QAction *tutorial = new QAction("&О программе");
    tutorial->setShortcut(tr("Ctrl+T"));
    about->addAction(creators);
    about->addAction(tutorial);

//    Слоты и сигналы
    connect(cmbx, SIGNAL(currentIndexChanged(int)),this, SLOT(changeModeOrient(int)));
    connect(tab,SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
    connect(newGraph, SIGNAL(triggered()), this, SLOT(newG()));
    connect(openGraph, SIGNAL(triggered()), this, SLOT(openG()));
    connect(savePicture, SIGNAL(triggered()), this, SLOT(savePic()));
    connect(saveSmejn, SIGNAL(triggered()), this, SLOT(saveAdj()));
    connect(saveIncident, SIGNAL(triggered()), this, SLOT(saveInc()));
    connect(saveV, SIGNAL(triggered()), this, SLOT(saveVer()));
    connect(saveR, SIGNAL(triggered()), this, SLOT(saveReb()));
    connect(exit, SIGNAL(triggered()), this, SLOT(closeG()));
    connect(undo, SIGNAL(clicked()), this, SLOT(undoG()));
    connect(redo, SIGNAL(clicked()), this, SLOT(redoG()));
    connect(clean, SIGNAL(clicked()), this, SLOT(cleanG()));
    connect(creators, SIGNAL(triggered()), this, SLOT(aboutC()));
    connect(tutorial, SIGNAL(triggered()), this, SLOT(aboutP()));
    connect(table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(synchronizeMatrix(QTableWidgetItem*)));

//    Задачи теории графов
    connect(f1_1, SIGNAL(triggered()), this, SLOT(func1_1()));
    connect(f1_2, SIGNAL(triggered()), this, SLOT(func1_2()));
    connect(f1_3, SIGNAL(triggered()), this, SLOT(func1_3()));

    connect(f2_1, SIGNAL(triggered()), this, SLOT(func2_1()));
    connect(f2_2, SIGNAL(triggered()), this, SLOT(func2_2()));
    connect(f2_3, SIGNAL(triggered()), this, SLOT(func2_3()));
    connect(f2_4, SIGNAL(triggered()), this, SLOT(func2_4()));

    connect(f3, SIGNAL(triggered()), this, SLOT(func3()));

    connect(f4, SIGNAL(triggered()), this, SLOT(func4()));

    connect(f5, SIGNAL(triggered()), this, SLOT(func5()));

    connect(f6, SIGNAL(triggered()), this, SLOT(func6()));

    connect(f7, SIGNAL(triggered()), this, SLOT(func7()));

    connect(f9, SIGNAL(triggered()), this, SLOT(func9()));

    connect(f10, SIGNAL(triggered()), this, SLOT(func10()));

    connect(f11, SIGNAL(triggered()), this, SLOT(func11()));

    connect(f121, SIGNAL(triggered()), this, SLOT(func121()));

    connect(f122, SIGNAL(triggered()), this, SLOT(func122()));

    connect(f123, SIGNAL(triggered()), this, SLOT(func123()));

    connect(f13, SIGNAL(triggered()), this, SLOT(func13()));

    connect(f15, SIGNAL(triggered()), this, SLOT(func15()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


//Слоты
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Выход");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Все несохраненные данные будут утеряны!");
    msgBox.setInformativeText("Выйти из программы?");
    QPushButton *yesButton = msgBox.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *noButton = msgBox.addButton(tr("Нет"), QMessageBox::ActionRole);
    msgBox.setDefaultButton(yesButton);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton)
    {
        event->accept();
    }
    else if (msgBox.clickedButton() == noButton)
    {
        event->ignore();
    }
}

void MainWindow::closeTab(int index)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Закрытие вкладки");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Все несохраненные данные будут утеряны!");
    msgBox.setInformativeText("Закрыть вкладку?");
    QPushButton *yesButton = msgBox.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *noButton = msgBox.addButton(tr("Нет"), QMessageBox::ActionRole);
    msgBox.setDefaultButton(yesButton);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton)
    {
        tab ->removeTab(index);
//        qDebug()<<index;
    }
    else if (msgBox.clickedButton() == noButton)
    {
        return;
    }
}

void MainWindow::changeTab(int index)
{
    Q_UNUSED(index)
    if (tab->count() == 0)
        newG();
    changeModeOrient(cmbx->currentIndex());
    changeMatrix();
}

void MainWindow::newG()
{
    k = num;
    for (int i = 0; i < num; i++)
    {
        if (tab->tabText(i) != "Граф " + QString::number(i + 1))
        {
            k = i + 1;
            break;
        }
    }
    QString s = "Граф " + QString::number(k);
    Canvas *cnv = new Canvas;
    cnv->setModeOrient(cmbx->currentIndex());

//    Обработка матрицы
    connect(cnv, SIGNAL(changeGraph()), this, SLOT(changeMatrix()));

    cnv->setMinimumSize(700, 400);
    cnv->setMaximumSize(20000, 20000);
    tab->insertTab(k - 1, cnv, s);
    tab->setCurrentIndex(k-1);
    num++;
}

void MainWindow::openG()
{
    QString openfile = QFileDialog::getOpenFileName(this, tr("Открыть"), "",
            tr("*.adj *.inc *.edjes *.ver"));
//    qDebug()<<openfile;
    QVector<QVector<QString>> vec;
    Graph graph;

    if(openfile.contains(".adj")){
        graph = parseAdjFile(openfile);
        qDebug()<<"gea";
        newG();
        qDebug()<<"gea";
        dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
        qDebug()<<"gea";
        changeMatrix();
        qDebug()<<"gea";
    }
    if(openfile.contains(".inc")){
        graph = parseIncFile(openfile);
        newG();
        dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
        changeMatrix();
    }
    if(openfile.contains(".edjes")){
        graph = parseEdgesFile(openfile, dynamic_cast<Canvas*>(tab->currentWidget())->getGraph());
        newG();
        dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
        changeMatrix();
    }
    if(openfile.contains(".ver")){
        graph = parseVertexFile(openfile);
        newG();
        dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
        changeMatrix();
    }
    qDebug()<<"gea";
}

void MainWindow::savePic()
{
    QString filename =  QFileDialog::getSaveFileName(this, "Save as", "filename", "PNG(*.png);; JPEG(*.jpg *.jpeg)");
    tab->currentWidget()->grab().save(filename);
}
//сохранение матрицы смежности
void MainWindow::saveAdj()
{
//    в этом будет хранится матрица
    QVector<QVector<QString>> vec;
    QString savefile = QFileDialog::getSaveFileName(this, "Save as", "filename", "*.adj");
    QVector<QString> InVec;
//    парсинг матрицы смежности, которая на экране
    for(int i = 0; i < table->rowCount(); ++i){
        for(int j = 0; j < table->columnCount(); ++j)
              InVec.append(table->item(i,j)->text());
        vec.append(InVec);
        InVec.clear();
    }
    SaveAdjmatrix(savefile, vec);
}


void MainWindow::saveInc()
{
    QString savefile = QFileDialog::getSaveFileName(this, "Save as", "filename", "*.inc");
    SaveIncmatrix(savefile,dynamic_cast<Canvas*>(tab->currentWidget())->getGraph());

    getIncMatrix( dynamic_cast<Canvas*>(tab->currentWidget())->getGraph());
}


void MainWindow::saveVer()
{
    QString savefile = QFileDialog::getSaveFileName(this, "Save as", "filename", "*.ver");
        SaveVertexGraph(savefile, dynamic_cast<Canvas*>(tab->currentWidget())->getGraph());
}

void MainWindow::saveReb()
{
    QString savefile = QFileDialog::getSaveFileName(this, "Save as", "filename", "*.edjes");
    SaveEdges(savefile,  dynamic_cast<Canvas*>(tab->currentWidget())->getGraph());
}

void MainWindow::closeG()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Выход");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Все несохраненные данные будут утеряны!");
    msgBox.setInformativeText("Выйти из программы?");
    QPushButton *yesButton = msgBox.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *noButton = msgBox.addButton(tr("Нет"), QMessageBox::ActionRole);
    msgBox.setDefaultButton(yesButton);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton)
    {
        QApplication::quit();
    }
    else if (msgBox.clickedButton() == noButton)
    {
        return;
    }

}
void MainWindow::undoG()
{
//    Отмена
    if(tab->count()){
        dynamic_cast<Canvas*>(tab->currentWidget())->undo();
        changeMatrix();
    }
}

void MainWindow::redoG()
{
//    Повторить
    if(tab->count()){
        dynamic_cast<Canvas*>(tab->currentWidget())->redo();
        changeMatrix();
    }
}

void MainWindow::cleanG()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Очистить");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Все несохраненные данные будут утеряны!");
    msgBox.setInformativeText("Очистить холст?");
    QPushButton *yesButton = msgBox.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *noButton = msgBox.addButton(tr("Нет"), QMessageBox::ActionRole);
    msgBox.setDefaultButton(yesButton);
    msgBox.exec();

    if (msgBox.clickedButton() == yesButton)
    {
        dynamic_cast<Canvas*>(tab->currentWidget())->clear();
        changeMatrix();
    }
    else if (msgBox.clickedButton() == noButton)
        return;

}

void MainWindow::aboutC()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о создателях проекта");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("ВУЗ: МАИ\nФакультет: 8\n"
                   "Группа: М8О-31_Б-17\nФИ: Муравьев Антон, Павлов Дмитрий, "
                   "Андреев Даниил, Холуев Владислав, Олег Лазаревич, "
                   "Александр Водяков, Сергей Сергеев, Александр Нехаев.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::aboutP()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Информация о программе");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Впадлу писать, но ТЗ по идее выполнено");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

//Обработка матрицы
void MainWindow::changeModeOrient(int index)
{
    dynamic_cast<Canvas*>(tab->currentWidget())->setModeOrient(index);
}

void MainWindow::changeMatrix()
{

//    Получаю граф
        Graph graph = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();

        auto all_vertex = graph.getVertexAsKeys().toList();

        check = true;

//        Сортирую по строкам
        std::sort(all_vertex.begin(), all_vertex.end(), compare);

        table->clear();
        table->setRowCount(all_vertex.size());
        table->setColumnCount(all_vertex.size());

        for(int i = 0; i<table->rowCount();i++){
            for(int j = 0; j<table->rowCount();j++){
                QTableWidgetItem *item = new QTableWidgetItem("0");
                table->setItem(i,j, item);
            }
        }

//        Вывод весов ребер и формирование заголовков
        QStringList name_list;
        int index = 0;//Это индекс вершины в матрице
        for(auto ver : all_vertex){
//            добавляю строку для заголовка
            name_list.append(ver->getName());
//            вывожу ребра
            for(auto edge : graph.vertexAt(ver)){

                int ver_index = all_vertex.indexOf(edge->getVertex());

                int weight = table->item(index, ver_index)->text().toInt();
                table->setItem(index, ver_index, new QTableWidgetItem(QString::number(edge->getWeight() + weight)));

                if(edge->getVecSrc() && ver_index!=index){
                    int synchron_weight = table->item(ver_index, index)->text().toInt();
                    table->setItem(ver_index, index, new QTableWidgetItem(QString::number(edge->getWeight() + synchron_weight)));
                }
            }
            index++;
        }
        table->setHorizontalHeaderLabels(name_list);
        table->setVerticalHeaderLabels(name_list);

        check = false;

}

void MainWindow::synchronizeMatrix(QTableWidgetItem *item)
{
//    Почему при двойном нажатии на вершину происходит перерисовка матрицы???
//    Скорее всего из-за начала отрисовки ребра

//    здесь стоит условие, потому что сигнал приходит
//    тогда когда пользователем создается новая вершина или ребро
//    а этот сигнал обрабатывать не надо
    if(!check){
//        qDebug() << item->row() << item->column();

        Graph graph = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
        auto all_vertex = graph.getVertexAsKeys().toList();
        std::sort(all_vertex.begin(), all_vertex.end(), compare);

//        вершина откуда
        auto ver1 = all_vertex[item->row()];
//        вершина куда
        auto ver2 = all_vertex[item->column()];

//        список всех ребер между двумя этими вершинами
        auto ver_data = graph[ver2];

        QMutableListIterator<edge_smpt> j(ver_data);
        while(j.hasNext()){
            auto &ed = j.next();
            if(ed->getVertex() == ver1 && ed->getVecSrc())
                j.remove();
        }

        graph[ver2] = ver_data;
        ver_data = graph[ver1];

//        удаляю все ребра между двумя вершинами от ver1 к ver2
        QMutableListIterator<edge_smpt> i(ver_data);
        while(i.hasNext()){
            if(i.next()->getVertex() == ver2)
                i.remove();
        }

//        добавляю одно ребро с введенным весом
        if(item->text().toInt() != 0){
            if(item->row() != item->column()){
                ver_data.append(edge_smpt(new Edge(ver1, ver2, item->text().toInt())));
                ver_data.last()->setVecEnd(true);
            }
            else{
                edge_smpt edge = edge_smpt(new Edge(ver1, ver1, item->text().toInt()));
                edge->setPoint(ver1->getPoint().x(), ver1->getPoint().y() - VER_RADIUS > 0
                                ? ver1->getPoint().y() - VER_RADIUS : ver1->getPoint().y() + VER_RADIUS);
                ver_data.append(edge);
                ver_data.last()->setVecEnd(true);
            }

            if(this->cmbx->currentText() == "Неориентированный граф")
                ver_data.last()->setVecSrc(true);
        }
//        помещаю измененный список обратно
        graph[ver1] = ver_data;
//        помещаю новый graph в Canvas
        dynamic_cast<Canvas*>(tab->currentWidget())->undoPush();
        dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
        dynamic_cast<Canvas*>(tab->currentWidget())->repaint();
        changeMatrix();
    }
}


//ЛР 2-21

#include "lab2.h"
//Поиск пути
void MainWindow::func1_1()
{
    //BSF - поиск в ширину(Breadth-First-Search)
    Graph g = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().copy();
            try
            {
                int amount = 0;
                QList <vertex_smpt> vertices = g.getVertexAsKeys().toList();
                qSort(vertices.begin(), vertices.end(), compare);
                QList<QString> verticesNamesL;
                for (auto it = vertices.begin(); it != vertices.end(); it++)
                {
                    verticesNamesL.append((*it)->getName());
                }
                QVector<QString> verticesNames = verticesNamesL.toVector();

                QString startName = QInputDialog::getText(this, "BFS*", "Введите имя начальной вершины:");
                if (!verticesNames.contains(startName))
                {
                    QMessageBox::warning(this, "BFS", "Нет вершины с именем " + startName + "!");
                    return;
                }

                int startIndex = verticesNames.indexOf(startName);
                qDebug() << "someth1";

                QString endName = QInputDialog::getText(this, "BFS", "Введите имя конечной вершины:");
                if (!verticesNames.contains(endName))
                {
                    QMessageBox::warning(this, "BFS", "Нет вершины с именем " + endName + "!");
                    return;
                }
                qDebug() << "someth2";
                int endIndex = verticesNames.indexOf(endName);

                if (startIndex == endIndex)
                {
                    QMessageBox::warning(this, "BFS", "Укажите разные вершины!");
                    return;
                }
                qDebug() << "someth3";
                QVector<vertex_smpt> way = lab2::BFS(g, startIndex, endIndex);
                qSort(way.begin(), way.end(), compare);

                way[0]->setColor(QColor(255, 0, 0, 255));
                 qDebug() << "smt" <<endl;
                for (int i = 1; i < way.count(); i++)
                {
                    way[i]->setColor(QColor(255, 0, 0, 255));
                    edge_smpt min_ed = nullptr;
                    for(auto &edge : g[way[i-1]]){
                        if(edge->getVertex()->getName() == way[i]->getName()){
                            if(min_ed.get() == nullptr){
                                min_ed = edge;
                            }
                            else{
                                if(edge->getWeight() < min_ed->getWeight())
                                    min_ed = edge;
                            }
                        }
                    }

                    for(auto &edge : g[way[i]])
                        {
                            if(edge->getVertex()->getName() == way[i-1]->getName() && edge->getVecSrc())
                            {
                                if(min_ed.get() == nullptr)
                                {
                                        min_ed = edge;
                                }
                                    else{
                            if(edge->getWeight() < min_ed->getWeight())
                                    min_ed = edge;
                                }
                        }
                  }


                    if(min_ed.get() != nullptr)
                    {
                        min_ed->setColor(QColor(255, 0, 0, 255));
                        amount+= min_ed->getWeight();
                    }
                }
                newG();
                dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(g);
                QString additionStr = "";



                    additionStr.append(QString::number(amount));
                    additionStr.append(" ");


                QMessageBox::about(nullptr, "Результат:", "Расстояние между вершинами: " + additionStr);




                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setTextFormat(Qt::RichText);
                //msgBox.setText("Все несохраненные данные будут утеряны!");
                msgBox.setInformativeText("Желаете сохранить результат?");
                QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
                QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
                msgBox.setDefaultButton(yesButton);
                msgBox.exec();

                if (msgBox.clickedButton() == yesButton)
                {
                    //QVector<QVector<QString>> vec;
                    QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
                    Save_Result_Path_amount(savefile, amount);
                }
                else if (msgBox.clickedButton() == noButton)
                {

                }
                changeMatrix();
            }
            catch (int smth)
            {
                QMessageBox::about(this, "Ошибка", "Такого пути нет!");
            }
            catch (...)
            {
                QMessageBox::about(this, "Ошибка", "Тотальная ошибка данных!");
            }
}

void MainWindow::func1_2()
{
//    qDebug()<<"func12";
//   A*
    Graph g = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().copy();
            try
            {
                QList <vertex_smpt> vertices = g.getVertexAsKeys().toList();
                qSort(vertices.begin(), vertices.end(), compare);
                QList<QString> verticesNamesL;
                int amount = 0;
                for (auto it = vertices.begin(); it != vertices.end(); it++)
                {
                    verticesNamesL.append((*it)->getName());
                }
                QVector<QString> verticesNames = verticesNamesL.toVector();

                QString startName = QInputDialog::getText(this, "A*", "Введите имя начальной вершины:");
                if (!verticesNames.contains(startName))
                {
                    QMessageBox::warning(this, "A*", "Нет вершины с именем " + startName + "!");
                    return;
                }

                int startIndex = verticesNames.indexOf(startName);
                qDebug() << "someth1";

                QString endName = QInputDialog::getText(this, "A*", "Введите имя конечной вершины:");
                if (!verticesNames.contains(endName))
                {
                    QMessageBox::warning(this, "A*", "Нет вершины с именем " + endName + "!");
                    return;
                }
                qDebug() << "someth2";
                int endIndex = verticesNames.indexOf(endName);

                if (startIndex == endIndex)
                {
                    QMessageBox::warning(this, "A*", "Укажите разные вершины!");
                    return;
                }
                qDebug() << "someth3";
                QVector<vertex_smpt> way = lab2::A_Star(g, startIndex, endIndex);



                qSort(way.begin(), way.end(), compare);
                way[0]->setColor(QColor(255, 0, 0, 255));
                 qDebug() << "smt" <<endl;
                for (int i = 1; i < way.count(); i++)
                {
                    way[i]->setColor(QColor(255, 0, 0, 255));
                    edge_smpt min_ed = nullptr;
                    for(auto &edge : g[way[i-1]]){
                        if(edge->getVertex()->getName() == way[i]->getName()){
                            if(min_ed.get() == nullptr){
                                min_ed = edge;
                            }
                            else{
                                if(edge->getWeight() < min_ed->getWeight())
                                    min_ed = edge;
                            }
                        }
                    }

                    for(auto &edge : g[way[i]])
                        {
                            if(edge->getVertex()->getName() == way[i-1]->getName() && edge->getVecSrc())
                            {
                                if(min_ed.get() == nullptr)
                                {
                                        min_ed = edge;
                                }
                                    else{
                            if(edge->getWeight() < min_ed->getWeight())
                                    min_ed = edge;
                                }
                        }
                  }


                    if(min_ed.get() != nullptr)
                    {
                        min_ed->setColor(QColor(255, 0, 0, 255));
                        amount+= min_ed->getWeight();
                    }
                }

                newG();
                dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(g);
                QString additionStr = "";



                    additionStr.append(QString::number(amount));
                    additionStr.append(" ");


                QMessageBox::about(nullptr, "Результат:", "Расстояние между вершинами: " + additionStr);




                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setTextFormat(Qt::RichText);
                //msgBox.setText("Все несохраненные данные будут утеряны!");
                msgBox.setInformativeText("Желаете сохранить результат?");
                QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
                QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
                msgBox.setDefaultButton(yesButton);
                msgBox.exec();

                if (msgBox.clickedButton() == yesButton)
                {
                    //QVector<QVector<QString>> vec;
                    QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
                    Save_Result_Path_amount(savefile, amount);
                }
                else if (msgBox.clickedButton() == noButton)
                {

                }
                changeMatrix();
            }
            catch (int smth)
            {
                QMessageBox::about(this, "Ошибка", "Такого пути нет!");
            }
            catch (...)
            {
                QMessageBox::about(this, "Ошибка", "Тотальная ошибка данных!");
            }
}

void MainWindow::func1_3()
{
//    qDebug()<<"func13";
//   Iterative deepening A*
    Graph g = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().copy();
            try
            {
                int amount = 0;
                QList <vertex_smpt> vertices = g.getVertexAsKeys().toList();
                qSort(vertices.begin(), vertices.end(), compare);
                QList<QString> verticesNamesL;
                for (auto it = vertices.begin(); it != vertices.end(); it++)
                {
                    verticesNamesL.append((*it)->getName());
                }
                QVector<QString> verticesNames = verticesNamesL.toVector();

                QString startName = QInputDialog::getText(this, "A*", "Введите имя начальной вершины:");
                if (!verticesNames.contains(startName))
                {
                    QMessageBox::warning(this, "A*", "Нет вершины с именем " + startName + "!");
                    return;
                }

                int startIndex = verticesNames.indexOf(startName);
                qDebug() << "someth1";

                QString endName = QInputDialog::getText(this, "A*", "Введите имя конечной вершины:");
                if (!verticesNames.contains(endName))
                {
                    QMessageBox::warning(this, "A*", "Нет вершины с именем " + endName + "!");
                    return;
                }
                qDebug() << "someth2";
                int endIndex = verticesNames.indexOf(endName);

                if (startIndex == endIndex)
                {
                    QMessageBox::warning(this, "A*", "Укажите разные вершины!");
                    return;
                }
                qDebug() << "someth3";
                QVector<vertex_smpt> way = lab2::A_Star_IrerativeDeepening(g, startIndex, endIndex);
                QVector<int> path(way.count());

                qSort(way.begin(), way.end(), compare);
                way[0]->setColor(QColor(255, 0, 0, 255));
                 qDebug() << "smt" <<endl;
                for (int i = 1; i < way.count(); i++)
                {
                    way[i]->setColor(QColor(255, 0, 0, 255));
                    edge_smpt min_ed = nullptr;
                    for(auto &edge : g[way[i-1]]){
                        if(edge->getVertex()->getName() == way[i]->getName()){
                            if(min_ed.get() == nullptr){
                                min_ed = edge;
                            }
                            else{
                                if(edge->getWeight() < min_ed->getWeight())
                                    min_ed = edge;
                            }
                        }
                    }

                    for(auto &edge : g[way[i]])
                        {
                            if(edge->getVertex()->getName() == way[i-1]->getName() && edge->getVecSrc())
                            {
                                if(min_ed.get() == nullptr)
                                {
                                        min_ed = edge;
                                }
                                    else{
                            if(edge->getWeight() < min_ed->getWeight())
                                    min_ed = edge;
                                }
                        }
                  }


                    if(min_ed.get() != nullptr)
                    {
                        min_ed->setColor(QColor(255, 0, 0, 255));
                        amount+= min_ed->getWeight();
                    }
                }
                newG();
                dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(g);
                QString additionStr = "";



                    additionStr.append(QString::number(amount));
                    additionStr.append(" ");


                QMessageBox::about(nullptr, "Результат:", "Расстояние между вершинами: " + additionStr);




                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setTextFormat(Qt::RichText);
                //msgBox.setText("Все несохраненные данные будут утеряны!");
                msgBox.setInformativeText("Желаете сохранить результат?");
                QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
                QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
                msgBox.setDefaultButton(yesButton);
                msgBox.exec();

                if (msgBox.clickedButton() == yesButton)
                {
                    //QVector<QVector<QString>> vec;
                    QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
                    Save_Result_Path_amount(savefile, amount);
                }
                else if (msgBox.clickedButton() == noButton)
                {

                }
                changeMatrix();
            }
            catch (int smth)
            {
                QMessageBox::about(this, "Ошибка", "Такого пути нет!");
            }
            catch (...)
            {
                QMessageBox::about(this, "Ошибка", "Тотальная ошибка данных!");
            }

}

#include "lab3.h"
//Алгоритм Дейкстры и близкие к нему
void MainWindow::func2_1()
{
    //    qDebug()<<"func21";
    //   Флойд-Уоршелл
    Graph g  = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
    try{
          QList<vertex_smpt> vertices = g.getVertexAsKeys().toList();
          QList<QString> verticesNamesL;
          for (auto it = vertices.begin(); it != vertices.end(); it++)
          {
              verticesNamesL.append((*it)->getName());
          }
          QVector<QString> verticesNames = verticesNamesL.toVector();

          QString startName = QInputDialog::getText(this, "FloydWarshall", "Введите имя начальной вершины:");
          if (!verticesNames.contains(startName))
          {
              QMessageBox::warning(this, "FoydWarshalll", "Нет вершины с именем " + startName + "!");
              return;
          }
          int startIndex = verticesNames.indexOf(startName);
          QVector<int> allPath = lab3::Dijkstra(g, startIndex);
          lab3::FloydWarshall(g, startIndex );
          QString additionStr = "";
          for(int i = 0; i < allPath.count(); i++)
          {

              additionStr.append(QString::number(allPath[i]));
              additionStr.append(" ");
          }

          QMessageBox::about(nullptr, "Результат:", "Вектор расстояния: " + additionStr);
          QMessageBox msgBox;
          msgBox.setIcon(QMessageBox::Question);
          msgBox.setTextFormat(Qt::RichText);
          //msgBox.setText("Все несохраненные данные будут утеряны!");
          msgBox.setInformativeText("Желаете сохранить результат?");
          QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
          QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
          msgBox.setDefaultButton(yesButton);
          msgBox.exec();

          if (msgBox.clickedButton() == yesButton)
          {
              //QVector<QVector<QString>> vec;
              QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
              Save_Result_Path(savefile, allPath);
          }
          else if (msgBox.clickedButton() == noButton)
          {

          }
    }catch (int smth)
    {
        QMessageBox::about(this, "Ошибка", "Не корректные данные!");
    }
    catch (...)
    {
        QMessageBox::about(this, "Ошибка", "Тотальная ошибка данных!");
    }
}

void MainWindow::func2_2()
{
//    qDebug()<<"func22";
//   Дейкстра
    Graph g = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
       try
       {
           QList<vertex_smpt> vertices = g.getVertexAsKeys().toList();
           QList<QString> verticesNamesL;
           for (auto it = vertices.begin(); it != vertices.end(); it++)
           {
               verticesNamesL.append((*it)->getName());
           }
           QVector<QString> verticesNames = verticesNamesL.toVector();

           QString startName = QInputDialog::getText(this, "Dijkstra", "Введите имя начальной вершины:");
           if (!verticesNames.contains(startName))
           {
               QMessageBox::warning(this, "Dijkstra", "Нет вершины с именем " + startName + "!");
               return;
           }
           int startIndex = verticesNames.indexOf(startName);

           QVector<int> way = lab3::Dijkstra(g, startIndex);
           //lab3::Dijkstra(g, startIndex);
           QString additionStr = "";
           for(int i = 0; i < way.count(); i++)
           {

               additionStr.append(QString::number(way[i]));
               additionStr.append(" ");
           }

           QMessageBox::about(nullptr, "Результат:", "Вектор расстояния: " + additionStr);




           QMessageBox msgBox;
           msgBox.setIcon(QMessageBox::Question);
           msgBox.setTextFormat(Qt::RichText);
           //msgBox.setText("Все несохраненные данные будут утеряны!");
           msgBox.setInformativeText("Желаете сохранить результат?");
           QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
           QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
           msgBox.setDefaultButton(yesButton);
           msgBox.exec();

           if (msgBox.clickedButton() == yesButton)
           {
               //QVector<QVector<QString>> vec;
               QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
               Save_Result_Path(savefile, way);
           }
           else if (msgBox.clickedButton() == noButton)
           {

           }

       }
       catch (int smth)
       {
           QMessageBox::about(this, "Ошибка", "Не корректные данные!");
       }
       catch (...)
       {
       }
}

void MainWindow::func2_3()
{
//    qDebug()<<"func23";
//   Беллман-Форд
    Graph g  = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
    try{
          QList<vertex_smpt> vertices = g.getVertexAsKeys().toList();
          QList<QString> verticesNamesL;
          for (auto it = vertices.begin(); it != vertices.end(); it++)
          {
              verticesNamesL.append((*it)->getName());
          }
          QVector<QString> verticesNames = verticesNamesL.toVector();

          QString startName = QInputDialog::getText(this, "BellmanFord", "Введите имя начальной вершины:");
          if (!verticesNames.contains(startName))
          {
              QMessageBox::warning(this, "BellmanFord", "Нет вершины с именем " + startName + "!");
              return;
          }
          int startIndex = verticesNames.indexOf(startName);
          lab3::BellmanFord(g, startIndex);
    } catch (int smth)
    {
        QMessageBox::about(this, "Ошибка", "Не корректные данные!");
    }
    catch (...)
    {
        QMessageBox::about(this, "Ошибка", "Тотальная ошибка данных!");
    }
}

void MainWindow::func2_4()
{
//    qDebug()<<"func24";
//   Джонсон
    Graph g  = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
    try{
          QList<vertex_smpt> vertices = g.getVertexAsKeys().toList();
          QList<QString> verticesNamesL;
          for (auto it = vertices.begin(); it != vertices.end(); it++)
          {
              verticesNamesL.append((*it)->getName());
          }
          QVector<QString> verticesNames = verticesNamesL.toVector();

          QString startName = QInputDialog::getText(this, "Jonson", "Введите имя начальной вершины:");
          if (!verticesNames.contains(startName))
          {
              QMessageBox::warning(this, "Jonson", "Нет вершины с именем " + startName + "!");
              return;
          }
          int startIndex = verticesNames.indexOf(startName);
          lab3::Jonson(g, startIndex);
    } catch (int smth)
    {
        QMessageBox::about(this, "Ошибка", "Не корректные данные!");
    }
    catch (...)
    {
        QMessageBox::about(this, "Ошибка", "Тотальная ошибка данных!");
    }
}

#include "lab4.h"
//Эксцентриситет, радиус, диаметр и степени
void MainWindow::func3()
{
//    qDebug()<<"func3";
    Graph g = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
    lab4::Eccentricity(g);
}

#include "task5.h"
//Изоморфизм графов
void MainWindow::func4()
{
//    qDebug()<<"isomorphism";

    try{
    if (tab->count() != 2)
           {
               QMessageBox::warning(this, "Ошибка!", "2 вкладки!");
               return;
           }
           bool isIsomorphic = lab5::Isomorphism(dynamic_cast<Canvas*>(tab->widget(0))->getGraph(), dynamic_cast<Canvas*>(tab->widget(1))->getGraph());

    } catch (int smth)
    {
        QMessageBox::about(this, "Ошибка", "Не корректные данные!");
    }
    catch (...)
    {
        QMessageBox::about(this, "Ошибка", "Тотальная ошибка!");
    }
}

#include "task6.h"
//Связность графа
void MainWindow::func5()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Связность графа");
    msgBox.setIcon(QMessageBox::Information);

    if(!task6::isGraphOrient(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare)))
    {
    //строка с компонентами связности
    QString str_comps = "", str_ver;
    for(auto it : task6::find_comps(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare)))
    {
        str_ver = "\t";
        for(auto jt : it)
            str_ver += (table->horizontalHeaderItem(jt)->text() + " ");
        str_comps += ("{" + str_ver + "}<br>");
    }
    int count_comps = task6::find_comps(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare)).size();

    msgBox.setText("Граф " +
                   (count_comps == 1 ? QString("связный") : QString("несвязный")) +
                   "<br>Компоненты связности(" + QString::number(count_comps) + "):<br>" + str_comps +
                   "Количество мостов: " +
                   QString::number(task6::find_bridges(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare))) +
                   "<br>Количество шарниров: " +
                   QString::number(task6::find_cutpoint(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare))));
    }
    else
    {
        QString type;
        QVector<QVector<int>> tmp = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare);

        for(int i = 0; i < tmp.size(); ++i)
            for(int j = 0; j < tmp.size(); ++j)
                if(tmp[i][j] != tmp[j][i])
                {
                    tmp[i][j] = 1;
                    tmp[j][i] = 1;
                }
        if(task6::strongComp(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare)) == 1)
            type = QString("сильно-связный");
        else if(task6::find_comps(tmp).size() == 1)
            type = QString("слабо-связный");
        else
            type = QString("несвязный");
        msgBox.setText("Граф ориентированный, " + type);

    }

    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}


//Дополнение для графа
void MainWindow::func6()
{
    bool isOrient = false;
    if (table->rowCount() > 1){
        int isFullGraph = 0;
        QVector<QVector<int>> matrix;
        for (int i = 0; i < table->rowCount(); i++) {
            QVector<int> vector;
            for (int j = 0; j < table->rowCount(); j++) {
                QTableWidgetItem *x = table->item(i, j);
                if (x->text().toInt() != 0 && i != j) {
                    isFullGraph++;
                }
                vector.push_back(x->text().toInt());
            }
            matrix.push_back(vector);
        }
        for (int i = 0; i < table->rowCount(); i++) {
            for (int j = 0; j < table->rowCount(); j++)
                if (matrix[i][j] != matrix[j][i]) {
                    isOrient = true;
                    break;
                }
            if (isOrient == true) {
                break;
            }
        }
        if (isFullGraph == table->rowCount() * (table->rowCount() - 1)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Графан");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Граф полный!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        else {
            if (isOrient == false && cmbx->currentText() == "Ориентированный граф") {
                cmbx->setCurrentIndex(0);
            } else if (isOrient == true && cmbx->currentText() == "Неориентированный граф") {
                cmbx->setCurrentIndex(1);
            }
            Graph graph = (dynamic_cast<Canvas*>(tab->currentWidget())->getGraph()).copy();
            newG();
            dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
            changeMatrix();
            for (int i = 0; i < table->rowCount(); i++)
                for (int j = 0; j < table->rowCount(); j++) {
                    if (isOrient == false) {
                        if (matrix[i][j] > 0 && j > i) {
                            QTableWidgetItem *item = new QTableWidgetItem(tr("0"));
                            table->setItem(i, j, item);
                        }
                        else if (j > i) {
                            QTableWidgetItem *item = new QTableWidgetItem(tr("1"));
                            table->setItem(i, j, item);
                        }
                    }
                    else {
                        if (matrix[i][j] > 0 && j != i) {
                            QTableWidgetItem *item = new QTableWidgetItem(tr("0"));
                            table->setItem(i, j, item);
                        }
                        else if (j != i) {
                            QTableWidgetItem *item = new QTableWidgetItem(tr("1"));
                            table->setItem(i, j, item);
                        }
                    }
                }
            changeMatrix();
        }
    }
}

void MainWindow::func7()
{
    QStringList items;
    bool ok;

    items << tr("объединение A и B") << tr("пересечение A и B") << tr("вычитание B из A") << tr("вычитание A из B")
          << tr("импликация из A в B") << tr("импликация из B в A") << tr("коимпликация из A в B") << tr("коимпликация из B в A")
          << tr("исключающее или A и B") << tr("эквивалентность A и B") << tr("штрих Шефера A и B") << tr("стрелка Пирса A и B");

    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                        tr("Выберите нужную операцию:"), items, 0, false, &ok);

    if (!ok || item.isEmpty()) return;

    int inameA = QInputDialog::getInt(this, tr(""),
                                    tr("Введите номер вкладки графа A:"), tab->tabText(tab->currentIndex()).mid(5).toInt(), 0, 100, 1, &ok);
    if (!ok) return;

    int inameB = QInputDialog::getInt(this, tr(""),
                                    tr("Введите номер вкладки графа B:"), tab->tabText(tab->currentIndex()).mid(5).toInt(), 0, 100, 1, &ok);
    if (!ok) return;

    QString nameA = "Граф " + QString::number(inameA);
    QString nameB = "Граф " + QString::number(inameB);

    int indexA = -1, indexB = -1;

    for(int i = 0; i < tab->count(); i++){
        if(tab->tabText(i) == nameA)
            indexA = i;
        if(tab->tabText(i) == nameB)
            indexB = i;
    }

    if(indexA == -1 || indexB == -1){
        QMessageBox::about(this, "Некорректный ввод", "Вы ввели номер не существующего графа");
        return;
    }
    //по ТЗ у графов должно соответствовать множество вершин. Я беру как соответствие равенство числа вершин.
    if(dynamic_cast<Canvas*>(tab->widget(indexA))->getGraph().getVertexAsKeys().size() !=
            dynamic_cast<Canvas*>(tab->widget(indexB))->getGraph().getVertexAsKeys().size()){
        QMessageBox::about(this, "Нельзя применить операцию", "У графов не соответсвуют множества вершин. Добейтесь равенства количества вершин.");
        return;
    }

    QVector<QVector<int>> adjC;
    Graph g = binaryOperationsOnGraphs(items.indexOf(item),
            dynamic_cast<Canvas*>(tab->widget(indexA))->getGraph(),
            dynamic_cast<Canvas*>(tab->widget(indexB))->getGraph(), adjC);
    newG();
    dynamic_cast<Canvas*>(tab->widget(tab->currentIndex()))->setGraph(g);
    changeMatrix();
    for(int i = 0; i < adjC.size(); ++i){
        for(int j = 0; j < adjC.size(); ++j){
            if(adjC[i][j] != 0)
                table->setItem(i, j, new QTableWidgetItem(QString::number(adjC[i][j])));
        }
    }
    changeMatrix();
}

#include "task9.h"
//планарность графа
void MainWindow::func9(){
    if (table->rowCount() > 1){
        QVector<QVector<int>> matrix;
        for (int i = 0; i < table->rowCount(); i++) {
            QVector<int> vector;
            for (int j = 0; j < table->rowCount(); j++) {
                QTableWidgetItem *x = table->item(i, j);
                vector.push_back(x->text().toInt());
            }
            matrix.push_back(vector);
        }
        Graph gr = lab9(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph(),matrix);
        newG();
        dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(gr);
        changeMatrix();
    }
}

// Восстановление графа из вектора
void MainWindow::func10()
{
  QString taskName = "Восстановление графа из вектора степеней вершин";

  bool ok;
  QString text = QInputDialog::getText(
        this, taskName, tr("Введите набор степеней вершин (целых "
                           "неотрицательных чисел) через пробел:"),
        QLineEdit::Normal, "", &ok, Qt::MSWindowsFixedSizeDialogHint).trimmed();

  if (!ok)
    return;
  if (text.isEmpty()) {
    QMessageBox::information(this, taskName, "Пустой ввод", QMessageBox::Ok);
    return;
  }

  QList<int> powerList;
  int vertexPower = 0;
  int sum = 0;
  QStringList stringList = text.split(" ", QString::SkipEmptyParts);
  foreach (QString string, stringList) {
      vertexPower = string.toUInt(&ok);
      if (!ok) {
          QMessageBox::critical(this, taskName,
                                tr("Некорректный ввод"), QMessageBox::Ok);
          return;
      }
      powerList.append(vertexPower);
      sum += vertexPower;
  }
  if (0 != sum % 2) {
      QMessageBox::critical(this, taskName,
                            tr("Нечётная сумма степеней"), QMessageBox::Ok);
      return;
  }

}


// Экстремальные графы
void MainWindow::func11()
{

}

void MainWindow::func121()
{
    QVector < pair < int, pair<int,int> > > g;
    QVector<QVector<int>> newmatrix;
    int n = table->rowCount();
    for (int i = 0; i < table->rowCount(); i++) {
        QVector<int> newvector;
        for (int j = 0; j < table->rowCount(); j++) {
            newvector.push_back(0);
            QTableWidgetItem *x = table->item(i, j);
            if (x->text().toInt() > 0) {
                g.push_back(make_pair(x->text().toInt(), make_pair(i, j)));
            }
        }
        newmatrix.push_back(newvector);
    }

    QVector < pair < int, pair<int,int> > > res;

    sort (g.begin(), g.end());

    QVector<int> tree_id;

    for (int i = 0; i < n; i++)
        tree_id.push_back(i);

    for (int i=0; i<n; ++i)
        tree_id[i] = i;
    for (int i=0; i<g.size(); ++i)
    {
        int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
        if (tree_id[a] != tree_id[b])
        {
            res.push_back (make_pair(l, make_pair(a, b)));
            int old_id = tree_id[b],  new_id = tree_id[a];
            for (int j=0; j<n; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }

    for (int i = 0; i < res.size(); i++) {
        newmatrix[res.at(i).second.first][res.at(i).second.second] = res.at(i).first;
    }
    if (cmbx->currentText() == "Ориентированный граф") {
        cmbx->setCurrentIndex(0);
    }
    Graph graph = (dynamic_cast<Canvas*>(tab->currentWidget())->getGraph()).copy();
    newG();
    dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
    changeMatrix();
    for (int i = 0; i < table->rowCount(); i++)
        for (int j = 0; j < table->rowCount(); j++) {
                if (newmatrix[i][j] > 0 && j > i) {
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(newmatrix[i][j]));
                    table->setItem(i, j, item);
                }
                else if (j > i) {
                    QTableWidgetItem *item = new QTableWidgetItem(tr("0"));
                    table->setItem(i, j, item);
                }
            }
    changeMatrix();
}


void prim(QVector<QVector<int>> &g, QVector<int> &v, QVector<QVector<int>> &newg) {
    int min = 10000000;
    int x = 0;
    int y = 0;
    for (int i = 0; i < g[0].size(); i++) {
        for (int j = 0; j < g[0].size(); j++) {
            if (v[i] == 1 && v[j] == 0 && g[i][j] > 0 && g[i][j] < min) {
                min = g[i][j];
                x = i;
                y = j;
            }
        }
    }
    if (x == 0 && y == 0 && min == 10000000){
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 0) {
                v[i] = 1;
                prim(g, v, newg);
            }
        }
    }
    newg[x][y] = min;
    newg[y][x] = min;
    v[y] = 1;
    int z = 0;
    for (int k = 0; k < g[0].size(); k++) {
        if (v[k] == 1) {
            z++;
        }
    }
    if (z < v.size())
        prim(g, v, newg);
}

void MainWindow::func122()
{
    QVector<QVector<int>> matrix;
    QVector<QVector<int>> newmatrix;
    for (int i = 0; i < table->rowCount(); i++) {
        QVector<int> vector;
        QVector<int> newvector;
        for (int j = 0; j < table->rowCount(); j++) {
            QTableWidgetItem *x = table->item(i, j);
            vector.push_back(x->text().toInt());
            newvector.push_back(0);
        }
        matrix.push_back(vector);
        newmatrix.push_back(newvector);
    }
    QVector<int> v;
    for (int i = 0; i < matrix[0].size(); i++) {
        if (i == 0) {
            v.push_back(1);
        }
        else {
            v.push_back(0);
        }
    }
    prim(matrix, v, newmatrix);
    if (cmbx->currentText() == "Ориентированный граф") {
        cmbx->setCurrentIndex(0);
    }
    Graph graph = (dynamic_cast<Canvas*>(tab->currentWidget())->getGraph()).copy();
    newG();
    dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
    changeMatrix();
    for (int i = 0; i < table->rowCount(); i++)
        for (int j = 0; j < table->rowCount(); j++) {
                if (newmatrix[i][j] > 0 && j > i) {
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(newmatrix[i][j]));
                    table->setItem(i, j, item);
                }
                else if (j > i) {
                    QTableWidgetItem *item = new QTableWidgetItem(tr("0"));
                    table->setItem(i, j, item);
                }
            }
    changeMatrix();
}

void MainWindow::func123() {
    QVector < pair < int, pair<int,int> > > g;
    QVector<QVector<int>> newmatrix;
    int n = table->rowCount();
    for (int i = 0; i < table->rowCount(); i++) {
        QVector<int> newvector;
        for (int j = 0; j < table->rowCount(); j++) {
            newvector.push_back(0);
            QTableWidgetItem *x = table->item(i, j);
            if (x->text().toInt() > 0) {
                g.push_back(make_pair(x->text().toInt(), make_pair(i, j)));
            }
        }
        newmatrix.push_back(newvector);
    }

    QVector < pair < int, pair<int,int> > > res;

    sort (g.begin(), g.end());

    QVector<int> tree_id;

    for (int i = 0; i < n; i++)
        tree_id.push_back(i);

    for (int i=0; i<n; ++i)
        tree_id[i] = i;
    for (int i=0; i<g.size(); ++i)
    {
        int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
        if (tree_id[a] != tree_id[b])
        {
            res.push_back (make_pair(l, make_pair(a, b)));
            int old_id = tree_id[b],  new_id = tree_id[a];
            for (int j=0; j<n; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }

    for (int i = 0; i < res.size(); i++) {
        newmatrix[res.at(i).second.first][res.at(i).second.second] = res.at(i).first;
    }
    if (cmbx->currentText() == "Ориентированный граф") {
        cmbx->setCurrentIndex(0);
    }
    Graph graph = (dynamic_cast<Canvas*>(tab->currentWidget())->getGraph()).copy();
    newG();
    dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(graph);
    changeMatrix();
    for (int i = 0; i < table->rowCount(); i++)
        for (int j = 0; j < table->rowCount(); j++) {
                if (newmatrix[i][j] > 0 && j > i) {
                    QTableWidgetItem *item = new QTableWidgetItem(QString::number(newmatrix[i][j]));
                    table->setItem(i, j, item);
                }
                else if (j > i) {
                    QTableWidgetItem *item = new QTableWidgetItem(tr("0"));
                    table->setItem(i, j, item);
                }
            }
    changeMatrix();
}

#include "task13.h"
void MainWindow::func13()
{
    QVector<int>cycle = task13::minCycle(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare));
    if(cycle.size())
    {
    for(auto verInCyc : cycle) //todo create new graph
        for(auto ver : dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().getVertexAsKeys())
        {
            if(ver->getName() == table->horizontalHeaderItem(verInCyc)->text())
                ver->setColor(Qt::red);
        }
    }
    else
    {
        QString centerStr;
        QVector<int> center = task13::centerVer(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph());
        for(auto verCenter : center) //todo create new graph
            for(auto ver : dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().getVertexAsKeys())
            {
                if(ver->getName() == table->horizontalHeaderItem(verCenter)->text())
                    centerStr+=(ver->getName() + " ");
            }

        QString depthStr;
        for(auto it: center)
            depthStr += QString::number(task13::depth(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph(), it)) + " ";

        QString pruferStr;
        for(auto it: task13::Prufer(dynamic_cast<Canvas*>(tab->currentWidget())->getGraph().toAdjacencyMatrix(compare)))
            pruferStr += (table->horizontalHeaderItem(it)->text() + " ");

        QMessageBox::about(this, "Задача о цикле", "Циклов нет<br>Центр(ы) дерева: " + centerStr +"<br>Глубина: " + depthStr + "<br>Код Прюфера: "
                           + pruferStr);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setTextFormat(Qt::RichText);
        //msgBox.setText("Все несохраненные данные будут утеряны!");
        msgBox.setInformativeText("Желаете сохранить код Прюфера в файл?");
        QPushButton *yesButton = msgBox.addButton(QObject::tr("Да"), QMessageBox::ActionRole);
        QPushButton *noButton = msgBox.addButton(QObject::tr("Нет"), QMessageBox::ActionRole);
        msgBox.setDefaultButton(yesButton);
        msgBox.exec();

        if (msgBox.clickedButton() == yesButton)
        {
            QString savefile = QFileDialog::getSaveFileName(nullptr, "Save as", "filename", "*.txt");
            QFile file(savefile);
            if(file.exists() || file.open(QIODevice::WriteOnly ))
            {
                 file.open(QIODevice::WriteOnly);
            }

                file.write(pruferStr.toStdString().c_str());

                file.close();
        }
    }


}
// Задача о свадьбах
void MainWindow::func15()
{
    Graph g = dynamic_cast<Canvas*>(tab->currentWidget())->getGraph();
    QList<vertex_smpt> vertices = g.getVertexAsKeys().toList();
    QList<QString> verticesNamesL;
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        verticesNamesL.append((*it)->getName());
    }
    QVector<QString> verticesNames = verticesNamesL.toVector();
    QVector<QString> firstDOLA;
    QVector<QString> secondDOLA;
//    QString startName = QInputDialog::getText(this, "FloydWarshall", "Введите имя начальной вершины:");

    while(true){

        QString startName = QInputDialog::getText(this, "С хуем", "Введите имя вершины:");
        if(startName =="-")
            break;
        if (!verticesNames.contains(startName))
        {
            QMessageBox::warning(this, "ты невнимательная мразь", "Нет вершины с именем " + startName + "!");
            return;
        }

        firstDOLA.append(startName);
        }
    while(true){
        QString startName = QInputDialog::getText(this, "Без хуя", "Введите имя вершины:");
        if(startName =="-")
            break;
        if (!verticesNames.contains(startName)){
            QMessageBox::warning(this, "ты невнимательная мразь", "Нет вершины с именем " + startName + "!");
            return;
        }
        if(firstDOLA.contains(startName)){
            QMessageBox::warning(this, "ты невнимательная мразь", " ты уже писал это, слепошара!!!");
            return;
        }

        secondDOLA.append(startName);
    }
   if(firstDOLA.size() == secondDOLA.size()){
    g = lab15(g,firstDOLA,secondDOLA);
    }else{
       QMessageBox::warning(this, "ты невнимательная мразь", " количества не сопадают");
       return;
    }
   newG();
    dynamic_cast<Canvas*>(tab->currentWidget())->setGraph(g);
}
