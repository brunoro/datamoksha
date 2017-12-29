#include "cvutil.h"

QImage CvUtil::CvMatToQImage(cv::Mat const& src)
{
     cv::Mat temp;
     int code = src.channels() == 1 ? CV_GRAY2RGB : CV_BGR2RGB;
     cv::cvtColor(src, temp, code);
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat CvUtil::QImageToCvMat(QImage const& src)
{
     cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
     cv::Mat result; // deep copy just in case
     cv::cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}

QImage CvUtil::findEdges(QImage &img, int blurRadius, int lowThreshold, int ratio)
{
    cv::Mat gray, edges, blur;
    cv::cvtColor(QImageToCvMat(img), gray, CV_BGR2GRAY);
    cv::blur(gray, blur, cv::Size(blurRadius, blurRadius));
    cv::Canny(blur, edges, lowThreshold, ratio);
    return CvMatToQImage(edges);
}
