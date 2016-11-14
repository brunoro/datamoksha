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

    Pixelsort(Direction direction, CompareFunction compareFunction);
    void run(QImage &img);

    static QString compareFunctionLabel(CompareFunction compareFunction);
    static QStringList compareFunctionLabels();

private:
    Direction direction;
    CompareFunction compareFunction;

    int (*getCompareFunctionPointer())(const void *a, const void *b);
    void sortHorizontal(QImage &img);
    void sortVertical(QImage &img);

};

#endif // PIXELSORT_H
