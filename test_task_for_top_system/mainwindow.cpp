#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , thread (nullptr)
    , engine (nullptr)
    , numClick (0)
    , randNumber (0)
    , colors ({Qt::yellow, Qt::green, Qt::magenta, Qt:: blue})
    , idColor (0)
{
    ui->setupUi(this);

    initUi();
    startGame();
}

MainWindow::~MainWindow()
{
    engine->quit = true;
    QMessageBox::information(this, "Внимание", "Приходите еще.", "Обязательно приду.");
    delete ui;
}

void MainWindow::initUi()
{
    ui->lcdTrueAns->setPalette(QPalette(Qt::green));
    ui->lcdFalseAns->setPalette(QPalette(Qt::red));

    ui->pbStart->setEnabled(false);
    ui->pbStop->setEnabled(true);

    ui->lcdFalseAns->display(0);
    ui->lcdNumClick->display(0);
    ui->lcdTrueAns->display(0);
}

void MainWindow::startGame()
{
    thread = new QThread();
    engine = new Engine();

    engine->moveToThread(thread);

    connect(thread, &QThread::started, engine, &Engine::doWork);
    connect(engine, &Engine::workFinished, thread, &QThread::quit);

    // automatically delete thread and engine object when work is done
    connect(engine, &Engine::workFinished, engine, &Engine::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    connect(engine, &Engine::update, this, &MainWindow::repaint);

    thread->start();

    genRandNum();

    numClick = 0;
}

void MainWindow::genRandNum()
{
    randNumber = QRandomGenerator::global()->generate() % 5;

    idColor >= colors.size() ? idColor = 0 : ++idColor;
    ui->lcdNumClick->setPalette(colors.at(idColor));
    ui->lcdNumClick->display(static_cast<int>(randNumber));
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    ++numClick;
}

void MainWindow::repaint()
{
    if (numClick == randNumber)
        ui->lcdTrueAns->display(ui->lcdTrueAns->value()+1);
    else
        ui->lcdFalseAns->display(ui->lcdFalseAns->value()-1);

    numClick = 0;
    genRandNum();
}

void MainWindow::on_pbStart_clicked()
{
    initUi();
    startGame();
}


void MainWindow::on_pbStop_clicked()
{
    engine->quit = true;

    ui->pbStart->setEnabled(true);
    ui->pbStop->setEnabled(false);
}

