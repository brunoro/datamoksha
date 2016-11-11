#ifndef PIXELSORTER_H
#define PIXELSORTER_H

#include <QImage>
#include <cstdlib>

class Pixelsorter
{
public:
    Pixelsorter();

    void run(QImage &img);
};

#endif // PIXELSORTER_H
