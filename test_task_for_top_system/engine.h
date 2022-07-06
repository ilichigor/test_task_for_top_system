#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = nullptr);
    bool quit;

public slots:
    void doWork();

signals:
    void workFinished();
    void update();
};

#endif // ENGINE_H
