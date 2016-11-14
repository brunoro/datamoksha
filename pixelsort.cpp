#include "pixelsort.h"

Pixelsort::Pixelsort(Pixelsort::Direction direction, Pixelsort::CompareFunction compareFunction)
{
    this->direction = direction;
    this->compareFunction = compareFunction;
}

int compare_red(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).red() - QColor::fromRgb(*(QRgb*)b).red(); }
int compare_green(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).green() - QColor::fromRgb(*(QRgb*)b).green(); }
int compare_blue(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).blue() - QColor::fromRgb(*(QRgb*)b).blue(); }
int compare_hue(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).hue() - QColor::fromRgb(*(QRgb*)b).hue(); }
int compare_saturation(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).saturation() - QColor::fromRgb(*(QRgb*)b).saturation(); }
int compare_value(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).value() - QColor::fromRgb(*(QRgb*)b).value(); }
int compare_cyan(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).cyan() - QColor::fromRgb(*(QRgb*)b).cyan(); }
int compare_magenta(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).magenta() - QColor::fromRgb(*(QRgb*)b).magenta(); }
int compare_yellow(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).yellow() - QColor::fromRgb(*(QRgb*)b).yellow(); }
int compare_black(const void *a, const void *b) { return QColor::fromRgb(*(QRgb*)a).black() - QColor::fromRgb(*(QRgb*)b).black(); }

int (*Pixelsort::getCompareFunctionPointer())(const void *a, const void *b)
{
    switch (this->compareFunction)
    {
    case CompareHue: return &compare_hue;
    case CompareSaturation: return &compare_saturation;
    case CompareValue: return &compare_value;
    case CompareRed: return &compare_red;
    case CompareGreen: return &compare_green;
    case CompareBlue: return &compare_blue;
    case CompareCyan: return &compare_cyan;
    case CompareMagenta: return &compare_magenta;
    case CompareYellow: return &compare_yellow;
    case CompareBlack: return &compare_black;
    }
}

QString Pixelsort::compareFunctionLabel(Pixelsort::CompareFunction compareFunction)
{
    switch (compareFunction)
    {
    case CompareHue: return "HSV Hue";
    case CompareSaturation: return "HSV Saturation";
    case CompareValue: return "HSV Value";
    case CompareRed: return "RGB Red";
    case CompareGreen: return "RGB Green";
    case CompareBlue: return "RGB Blue";
    case CompareCyan: return "CYMK Cyan";
    case CompareMagenta: return "CMYK Magenta";
    case CompareYellow: return "CMYK Yellow";
    case CompareBlack: return "CMYK Black";
    }
}

QStringList Pixelsort::compareFunctionLabels()
{
    QStringList list;
    for (int i = Pixelsort::CompareFirst; i <= Pixelsort::CompareLast; i++)
    {
        list << Pixelsort::compareFunctionLabel((Pixelsort::CompareFunction)i);
    }
    return list;
}

void Pixelsort::sortHorizontal(QImage &img)
{
    for (int i = 0; i < img.height(); i++)
    {
        qsort(img.scanLine(i), img.width(), img.depth() / 8, this->getCompareFunctionPointer());
    }
}

void Pixelsort::sortVertical(QImage &img)
{
    for (int i = 0; i < img.width(); i++)
    {
        QRgb *column = (QRgb *)malloc(sizeof(QRgb) * img.height());
        for (int j = 0; j < img.height(); j++)
        {
            column[j] = img.pixel(i, j);
        }

        qsort(column, img.height(), img.depth() / 8, this->getCompareFunctionPointer());

        for (int j = 0; j < img.height(); j++)
        {
            img.setPixel(i, j, column[j]);
        }

        free(column);
    }
}

void Pixelsort::run(QImage &img)
{
    switch (this->direction)
    {
    case DirectionHorizontal:
        this->sortHorizontal(img);
    case DirectionVertical:
        this->sortVertical(img);
    }
}
