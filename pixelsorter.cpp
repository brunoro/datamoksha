#include "pixelsorter.h"

Pixelsorter::Pixelsorter()
{

}

int compare_pixel(const void *a, const void *b)
{
    QRgb pa = *(QRgb*)a;
    QRgb pb = *(QRgb*)b;
    return QColor::fromRgb(pb).hue() - QColor::fromRgb(pa).hue();
}

void Pixelsorter::run(QImage &img)
{
    for (int i = 0; i < img.height(); i++)
    {
        qsort(img.scanLine(i), img.width(), img.depth() / 8, &compare_pixel);
    }
}
