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

    // button connections
    connect(ui->findButton, &QPushButton::clicked, this, &MainWindow::find);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::load);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sort);

    // set canny toolbar hidden if detect edges unchecked
    ui->cannyOptions->setVisible(false);
    connect(ui->detectEdges, &QCheckBox::stateChanged, ui->cannyOptions, &QWidget::setVisible);

    // make edges be drawn if canny sliders being pressed
    connect(ui->cannyBlurSlider, &QSlider::sliderPressed, this, &MainWindow::drawEdges);
    connect(ui->cannyBlurSlider, &QSlider::sliderReleased, this, &MainWindow::drawBuffer);
    connect(ui->cannyBlurSlider, &QSlider::valueChanged, this, &MainWindow::detectAndDrawEdges);
    connect(ui->cannyThreshSlider, &QSlider::sliderPressed, this, &MainWindow::drawEdges);
    connect(ui->cannyThreshSlider, &QSlider::sliderReleased, this, &MainWindow::drawBuffer);
    connect(ui->cannyThreshSlider, &QSlider::valueChanged, this, &MainWindow::detectAndDrawEdges);
    connect(ui->cannyRatioSlider, &QSlider::sliderPressed, this, &MainWindow::drawEdges);
    connect(ui->cannyRatioSlider, &QSlider::sliderReleased, this, &MainWindow::drawBuffer);
    connect(ui->cannyRatioSlider, &QSlider::valueChanged, this, &MainWindow::detectAndDrawEdges);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBuffer()
{
    ui->imageView->setPixmap(QPixmap::fromImage(buffer));
}

void MainWindow::drawEdges()
{
    ui->imageView->setPixmap(QPixmap::fromImage(edges));
}

void MainWindow::loadFile(const QString &filename)
{
    buffer = QImage(filename);
    if (buffer.isNull())
    {
        // TODO: throw error
    }

    if (this->buffer.format() != QImage::Format_RGB888)
    {
        buffer = buffer.convertToFormat(QImage::Format_RGB888);
    }

    drawBuffer();
    detectEdges();
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
    QString filename = ui->filePath->text();
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
    auto compareFunction = (Pixelsort::CompareFunction)ui->compareFunctionCombo->currentIndex();
    auto direction = (Pixelsort::Direction)ui->directionCombo->currentIndex();
    Pixelsort p(direction, compareFunction, ui->detectEdges->checkState() ? &edges : NULL);
    p.run(buffer);
    drawBuffer();
}

void MainWindow::detectEdges()
{
    if (!buffer.isNull())
    {
        int blurRadius = ui->cannyBlurSlider->value();
        int lowThreshold = ui->cannyThreshSlider->value();
        int ratio = ui ->cannyRatioSlider->value();
        edges = CvUtil::findEdges(buffer, blurRadius, lowThreshold, ratio);
    }
}

void MainWindow::detectAndDrawEdges()
{
    detectEdges();
    drawEdges();
}
