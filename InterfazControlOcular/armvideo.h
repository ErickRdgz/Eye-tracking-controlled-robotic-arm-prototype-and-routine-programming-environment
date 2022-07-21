#ifndef ARMVIDEO_H
#define ARMVIDEO_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#define ID_ARM_CAM /*"http://192.168.111.6:8080/video" */ "http://192.168.1.70:8080/video"



class ArmVideo: public QThread
{
    Q_OBJECT

public:
    ArmVideo(QObject *parent =nullptr, QString CAM_ID="0");
    QPixmap getVideoPixMap() const{
        return armVideoPixMap;
    }
private:
    QPixmap armVideoPixMap;
    cv::Mat videoFrame;
    cv::VideoCapture videoCapture;

    QImage  cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );

protected:
    void run() override;

signals:
    void newVideoFrame();
    void cameraNotFound();

};

#endif // ARMVIDEO_H
