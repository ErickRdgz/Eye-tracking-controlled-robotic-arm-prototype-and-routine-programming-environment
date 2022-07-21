#include "eyetracking.h"

#include <QDebug>


#include <queue>
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "findEyeCenter.h"
//#include "findEyeCorner.h"

using namespace cv;
using namespace cv::face;

EyeTracking::EyeTracking(QObject *parent, QString CAM_ID)
    :QThread{parent}
{
    if(CAM_ID=="0"){
         videoCapture.open(0);
    }else{
    videoCapture.open(CAM_ID.toStdString());
    }
}

bool EyeTracking::LoadCascadeClassifiers()
{
    if (!faceCascade.load("C:/OpenCV1/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"))
    {
        qDebug()<<"no se pudo cargar face";
        return false;
    }
    return true;
}


void EyeTracking::run()
{
    if (!LoadCascadeClassifiers()){
         return;
    }

    facemark = FacemarkLBF::create();
    facemark->loadModel("C:/OpenCV1/opencv/sources/data/haarcascades/lbfmodel.yaml");

    if(!videoCapture.isOpened()){
        qDebug()<<"no abrio la camara ";
         return;
    }

    while (true) {
        videoCapture>>this->videoFrame;
        if(this->videoFrame.empty())
            continue;

         if (!detectEyes())cv::flip(this->videoFrame,this->videoFrame,1);

        videoPixMap=cvMatToQPixmap(this->videoFrame);
        emit newVideoFrame();
    }
}

bool EyeTracking::detectEyes()
{
    //-----------------------------------------------------------
    // ############## pretratamiento de imagen ##################
    std::vector<cv::Rect> faces;
    std::vector<cv::Mat> rgbChannels(3);
    cv::Mat  FullVideo;
    videoFrame.copyTo(FullVideo);         //------------------
    cv::split(this->videoFrame, rgbChannels);
    cv::Mat frame_gray = rgbChannels[2];


    //-----------------------------------------------------------
    //################    Face detection    #####################
    this->faceCascade.detectMultiScale( frame_gray, faces,
                                        1.1,
                                        2,
                                        0|cv::CASCADE_SCALE_IMAGE|cv::CASCADE_FIND_BIGGEST_OBJECT,
                                        cv::Size(150, 150) );
    if (faces.size() == 0) return false;
    cv::Rect face=faces[0];



    //-----------------------------------------------------------
    //################    Eye detection    #####################
    cv::Mat faceROI = frame_gray(face);
    cv::Mat debugFace = faceROI;
    if (kSmoothFaceImage) {
        double sigma = kSmoothFaceFactor * face.width;
        GaussianBlur( faceROI, faceROI, cv::Size( 0, 0 ), sigma);
    }

    //-- Find eye regions
    int eye_region_width = face.width * (kEyePercentWidth/100.0);
    int eye_region_height = face.width * (kEyePercentHeight/100.0);
    int eye_region_top = face.height * (kEyePercentTop/100.0);
    cv::Rect EyeRegion(face.width - eye_region_width - face.width*(kEyePercentSide/100.0),
                           eye_region_top,
                           eye_region_width,
                           eye_region_height);

    //-- Find eye Center
    static std::vector<cv::Point> leftPupilPoints;
    cv::Point leftPupil;
    leftPupil = findEyeCenter(faceROI,EyeRegion,"Right Eye");
    leftPupil= stabilize(leftPupilPoints, leftPupil,STABILIZE_WINDOW);
    cv::Point faceReferencedPupil(leftPupil.x + EyeRegion.x,
                                  leftPupil.y + EyeRegion.y);

    //-----------------------------------------------------------
    //################    Facemark    #####################

    std::vector< std::vector<Point2f> > landmarks;
    bool success = facemark->fit(frame_gray,faces,landmarks);      // Run landmark detector
    if(! success) return false;

    //-----------------------------------------------------------
    //################    Eye LandMark    #####################


    Point2f LeftEdge=landmarks[0].at(45);
    LeftEdge.x=LeftEdge.x-face.x;
    LeftEdge.y=LeftEdge.y-face.y;
    Point2f RightEdge=landmarks[0].at(42);
    RightEdge.x=RightEdge.x-face.x;
    RightEdge.y=RightEdge.y-face.y;
     if ((EyeRegion.y*1.26)>faceReferencedPupil.y) return false; // if eye center is out of valid range, return
     if (faceReferencedPupil.x>LeftEdge.x) return false;

     static std::vector<cv::Point> RightEdgePoints;
     static std::vector<cv::Point> LeftEdgePoints;
     RightEdge.x=RightEdge.x-3;
     LeftEdge.x=LeftEdge.x+4;
     RightEdge=stabilize(RightEdgePoints,RightEdge,STABILIZE_WINDOW);
     LeftEdge =stabilize(LeftEdgePoints ,LeftEdge ,STABILIZE_WINDOW);

     float  XRatio=((faceReferencedPupil.x-LeftEdge.x)/(RightEdge.x-faceReferencedPupil.x));
     if (XRatio>6) return false;

     float Y_edgesCenter= (LeftEdge.y+RightEdge.y)/2;
     float Y_segment= sqrt((Y_edgesCenter-faceReferencedPupil.y)*(Y_edgesCenter-faceReferencedPupil.y));
     float YRatio=(LeftEdge.x-RightEdge.x)/Y_segment;

    Position_t position= getOcularCommand(XRatio,YRatio);


    //-----------------------------------------------------------
    //################    Draw Results    #####################


    //-- cut and  draw over comptured video frame to focus  on the face and results
    this->videoFrame=this->videoFrame(face);

     circle(this->videoFrame,
            faceReferencedPupil,
            3,
            cv::Scalar( 0,255, 255),
            1);
     circle(this->videoFrame,
            LeftEdge,
            2,
            cv::Scalar( 255,255,0),
            -1);
     circle(this->videoFrame,
            RightEdge,
            2,
            cv::Scalar( 255,255,0),
            -1);
    if(position==EYE_UP)circle(this->videoFrame,
                        cv::Point(faceReferencedPupil.x         ,faceReferencedPupil.y-10),
                        2,
                        cv::Scalar( 0,0, 255),
                        -1);
    if(position==EYE_RIGHT) circle(this->videoFrame,
                            cv::Point(faceReferencedPupil.x-10  ,faceReferencedPupil.y),
                            2,
                            cv::Scalar( 0,0, 255),
                            -1);
    if(position==EYE_LEFT)circle(this->videoFrame,
                          cv::Point(faceReferencedPupil.x+10    ,faceReferencedPupil.y),
                          2,
                          cv::Scalar( 0,0, 255),
                          -1);


    cv::flip(this->videoFrame,this->videoFrame,1);

    return  true;
}

Position_t EyeTracking::getOcularCommand(float XRatio, float YRario)
{
    static Position_t Pos=EYE_NEUTRAL;
    if(XRatio> this->rightLimit){
        qDebug()<<"Right";
        if(Pos==EYE_RIGHT){
            if (timer.hasExpired(this->commandTime *1000)){
                emit moveRight();
                timer.start();
            }
        }else{
             timer.start();
        }
        Pos=EYE_RIGHT;
        return Pos;

    }
    if(XRatio< this->leftLimit){
        qDebug()<<"Left";
        if(Pos==EYE_LEFT){
            if (timer.hasExpired(this->commandTime*1000)){
                emit moveLeft();
                timer.start();
            }
        }else{
            timer.start();
        }
        Pos=EYE_LEFT;
        return Pos;

    }
    if(YRario< this->upperLimit){
        qDebug()<<"Up";
        if(Pos==EYE_UP){
            if (timer.hasExpired(this->commandTime*1000)){
                emit moveUp();
                timer.start();
            }
        }else{
            timer.start();
        }
        Pos=EYE_UP;
        return Pos;
    }
    Pos=EYE_NEUTRAL;
    return Pos;
}


Point EyeTracking::stabilize(std::vector<Point> points, Point newPoint, int windowSize)
{
    //    static std::vector<cv::Point> points;

          float sumX = 0;
          float sumY = 0;
          int count = 0;
        if ((int)points.size()<windowSize){
            points.push_back(newPoint);
        }else{
            for(size_t i=1; (int)i<windowSize-1;i++){
                points.at(i)=points.at(i+1);
            }
            points.at(windowSize-1)=newPoint;
        }
        for (size_t i = std::max(0, (int)(points.size() - windowSize)); i < points.size(); i++)
          {
              sumX += points[i].x;
              sumY += points[i].y;
              ++count;
          }
          if (count > 0)
          {
              sumX /= count;
              sumY /= count;
          }
          return cv::Point(sumX, sumY);
}

QImage EyeTracking::cvMatToQImage(const Mat &inMat)
{
    switch ( inMat.type() )
    {
       // 8-bit, 4 channel
       case CV_8UC4:
       {
          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_ARGB32 );

          return image;
       }

       // 8-bit, 3 channel
       case CV_8UC3:
       {
          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_RGB888 );

          return image.rgbSwapped();
       }

       // 8-bit, 1 channel
       case CV_8UC1:
       {
  #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_Grayscale8 );
  #else
          static QVector<QRgb>  sColorTable;

          // only create our color table the first time
          if ( sColorTable.isEmpty() )
          {
             sColorTable.resize( 256 );

             for ( int i = 0; i < 256; ++i )
             {
                sColorTable[i] = qRgb( i, i, i );
             }
          }

          QImage image( inMat.data,
                        inMat.cols, inMat.rows,
                        static_cast<int>(inMat.step),
                        QImage::Format_Indexed8 );

          image.setColorTable( sColorTable );
  #endif

          return image;
       }

       default:
  //        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
          break;
    }

    return QImage();
}

QPixmap EyeTracking::cvMatToQPixmap(const Mat &inMat)
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}
