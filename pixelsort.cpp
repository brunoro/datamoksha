#include "pixelsort.h"

Pixelsort::Pixelsort(Pixelsort::Direction direction, Pixelsort::CompareFunction compareFunction, bool useEdges)
{
    this->direction = direction;
    this->compareFunction = compareFunction;
    this->useEdges = useEdges;
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
    for (int i = CompareFirst; i <= CompareLast; i++)
    {
        list << Pixelsort::compareFunctionLabel((CompareFunction)i);
    }
    return list;
}

QString Pixelsort::directionLabel(Pixelsort::Direction direction)
{
    switch (direction)
    {
    case DirectionHorizontal: return "Horizontal";
    case DirectionVertical: return "Vertical";
    }
}


QStringList Pixelsort::directionLabels()
{
    QStringList list;
    list << Pixelsort::directionLabel(DirectionHorizontal);
    list << Pixelsort::directionLabel(DirectionVertical);
    return list;
}

void Pixelsort::sortRow(QImage &img, int y; int start, int length)
{
    qsort(img.scanLine(y) + start * numBytes, length, numBytes, this->getCompareFunctionPointer());
}

void Pixelsort::sortColumn(QImage &img, int x; int start, int length)
{
    QRgb *column = (QRgb*)malloc(sizeof(QRgb) * length);
    for (int i = 0; i < length; i++) { column[i] = img.pixel(x, start + i); }

    qsort(column, length, numBytes, this->getCompareFunctionPointer());

    for (int i = 0; i < length; i++) { img.setPixel(x, start + i, column[i]); }

    free(column);
}


void Pixelsort::sortHorizontal(QImage &img)
{
    int numLines = img.height();
    int start = 0;
    int length = img.width();
    int numBytes = img.depth() / 8;

    for (int i = 0; i < numLines; i++)
    {
        this->sortRow(img, i, start, length);
    }
}

void Pixelsort::sortVertical(QImage &img)
{
    int numLines = img.width();
    int start = 0;
    int length = img.height();
    int numBytes = img.depth() / 8;

    for (int i = 0; i < numLines; i++)
    {
        this->sortColumn(img, i, start, length);
    }
}

void Pixelsort::run(QImage &img)
{
    switch (this->direction)
    {
    case DirectionHorizontal:
        this->sortHorizontal(img);
        break;
    case DirectionVertical:
        this->sortVertical(img);
        break;
    }
}

QImage Pixelsort::CvMatToQImage(cv::Mat const& src)
{
     cv::Mat temp;
     cvtColor(src, temp,CV_BGR2RGB);
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat Pixelsort::QImageToCvMat(QImage const& src)
{
     cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
     cv::Mat result; // deep copy just in case
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}
