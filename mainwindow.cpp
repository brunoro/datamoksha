#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findButton, &QPushButton::clicked, this, &MainWindow::find);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::load);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sort);
}

void MainWindow::drawBuffer()
{
    this->ui->imageView->setPixmap(QPixmap::fromImage(this->buffer));
}

void MainWindow::loadFile(const QString &fileName)
{
    this->buffer = QImage(fileName);
    this->drawBuffer();
}

void MainWindow::find()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::load()
{
    QString fileName = this->ui->filePath->text();
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::sort()
{
    Pixelsorter p;
    p.run(this->buffer);
    this->drawBuffer();
}

MainWindow::~MainWindow()
{
    delete ui;
}
