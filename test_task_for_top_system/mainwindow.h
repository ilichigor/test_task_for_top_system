#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "engine.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
    void repaint();

private slots:
    void on_pbStart_clicked();

    void on_pbStop_clicked();

private:
    Ui::MainWindow *ui;

    QThread* thread;
    Engine* engine;

    quint32 numClick;
    quint32 randNumber;

    QVector<QColor> colors;
    quint32 idColor; //! to change color lcdNumClick when generating a new randNumber

    void initUi();
    void startGame();
    void genRandNum();
};
#endif // MAINWINDOW_H
