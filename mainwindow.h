#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "pixelsorter.h"

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
    QImage buffer;

    void loadFile(const QString &fileName);
    void drawBuffer();

private slots:
    void find();
    void load();
    void sort();
};

#endif // MAINWINDOW_H
