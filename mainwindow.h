#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "pixelsort.h"

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

    void loadFile(const QString &filename);
    void saveFile(const QString &filename);
    void drawBuffer();

private slots:
    void find();
    void load();
    void save();
    void sortH();
    void sortV();
};

#endif // MAINWINDOW_H
