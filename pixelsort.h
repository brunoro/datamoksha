#ifndef PIXELSORT_H
#define PIXELSORT_H

#include <QImage>
#include <QString>
#include <cstdlib>
#include "operation.h"

class Pixelsort : public Operation
{
public:
    typedef enum
    {
        DirectionHorizontal,
        DirectionVertical
    } Direction;

    static QString directionLabel(Direction direction);
    static QStringList directionLabels();

    typedef enum
    {
        CompareHue,
        CompareSaturation,
        CompareValue,
        CompareRed,
        CompareGreen,
        CompareBlue,
        CompareCyan,
        CompareMagenta,
        CompareYellow,
        CompareBlack,
        CompareFirst = CompareHue,
        CompareLast = CompareBlack
    } CompareFunction;

    static QString compareFunctionLabel(CompareFunction compareFunction);
    static QStringList compareFunctionLabels();

    Pixelsort(Direction direction, CompareFunction compareFunction, QImage *edges);
    void run(QImage &img);

private:
    Direction direction;
    CompareFunction compareFunction;
    QImage *edges;

    int (*getCompareFunctionPointer())(const void *a, const void *b);

    void sortColumn(QImage &img, int x, int start, int length);
    void sortRow(QImage &img, int y, int start, int length);

    void sortHorizontal(QImage &img);
    void sortVertical(QImage &img);
};

#endif // PIXELSORT_H
