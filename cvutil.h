#ifndef CVUTIL_H
#define CVUTIL_H

#include <QImage>
#include <cv.hpp>

namespace CvUtil {
    QImage CvMatToQImage(cv::Mat const& src);
    cv::Mat QImageToCvMat(QImage const& src);

    QImage findEdges(QImage &img, int blurRadius, int lowThreshold, int ratio);
}

#endif // CVUTIL_H
