#ifndef EYETRACKING_H
#define EYETRACKING_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/dnn/dnn.hpp>
#include "constants.h"
#include <QElapsedTimer>
#include <opencv2/face.hpp>

class EyeTracking: public QThread
{
    Q_OBJECT
public:
    EyeTracking(QObject *parent =nullptr, QString CAM_ID="0");
    QPixmap getVideoPixMap() const{
        return videoPixMap;
    }

    void setUpperLimit(float value){
        this->upperLimit=value;
    }

    void setRightLimit(float value){
        this->rightLimit=value;
    }

    void setLeftLimit(float value){
        this->leftLimit=value;
    }
    void setCommandTime(float value){
        this->commandTime=value;
    }

private:
    QElapsedTimer timer;
    cv::Ptr<cv::face::Facemark> facemark;

    float upperLimit=UPPER_LIMIT;
    float rightLimit=RIGHT_LIMIT;
    float leftLimit=LEFT_LIMIT;
    float commandTime=EYE_COMMAND_TIMEOUT;

    QPixmap videoPixMap;
    cv::Mat videoFrame;
//    cv::Point leftPupil;
    cv::VideoCapture videoCapture;

    cv::CascadeClassifier faceCascade;
    bool LoadCascadeClassifiers();

    bool detectEyes();
    void findEyes(cv::Mat frame_gray, cv::Rect face);

    QImage  cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );

    Position_t getOcularCommand(float XRatio,float YRario);
    cv::Point stabilize( std::vector<cv::Point> points,cv::Point newPoint, int windowSize);
protected:
    void run() override;

signals:
    void newVideoFrame();
    void moveUp();
    void moveRight();
    void moveLeft();

};

#endif // EYETRACKING_H
