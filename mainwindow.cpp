#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // compare function combo
    ui->compareFunctionCombo->addItems(Pixelsort::compareFunctionLabels());
    ui->compareFunctionCombo->setCurrentIndex(Pixelsort::CompareFirst);

    // direction combo
    ui->directionCombo->addItems(Pixelsort::directionLabels());
    ui->directionCombo->setCurrentIndex(Pixelsort::DirectionHorizontal);

    // connections
    connect(ui->findButton, &QPushButton::clicked, this, &MainWindow::find);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::load);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sort);
}

void MainWindow::drawBuffer()
{
    this->ui->imageView->setPixmap(QPixmap::fromImage(this->buffer));
}

void MainWindow::loadFile(const QString &filename)
{
    this->buffer = QImage(filename);
    if (this->buffer.isNull())
    {
        // TODO: throw error
    }

    if (this->buffer.format() != QImage::Format_RGB888)
    {
        this->buffer = this->buffer.convertToFormat(QImage::Format_RGB32);
    }

    this->drawBuffer();
}

void MainWindow::saveFile(const QString &filename)
{
    if (!this->buffer.save(filename))
    {
        // TODO: throw error
    }
}

void MainWindow::find()
{
    QString filename = QFileDialog::getOpenFileName(this);
    this->ui->filePath->setText(filename);
    if (!filename.isEmpty())
    {
        loadFile(filename);
    }
}

void MainWindow::load()
{
    QString filename = this->ui->filePath->text();
    if (!filename.isEmpty())
    {
        loadFile(filename);
    }
}

void MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if (!filename.isEmpty())
    {
        saveFile(filename);
    }
}

void MainWindow::sort()
{
    auto compareFunction = (Pixelsort::CompareFunction)this->ui->compareFunctionCombo->currentIndex();
    auto direction = (Pixelsort::Direction)this->ui->directionCombo->currentIndex();
    Pixelsort p(direction, compareFunction, false);
    p.run(this->buffer);
    this->drawBuffer();
}

MainWindow::~MainWindow()
{
    delete ui;
}
