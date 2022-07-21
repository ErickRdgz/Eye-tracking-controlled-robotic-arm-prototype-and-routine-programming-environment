QT       += core gui serialport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    armvideo.cpp \
    eyetracking.cpp \
    lista.cpp \
    main.cpp \
    interfazocular.cpp \
    arduino.cpp \
    cinematica.cpp \
    revolutearm.cpp \
    sequencer.cpp \
    configwindow.cpp \
    findEyeCenter.cpp \
    helpers.cpp

HEADERS += \
    armvideo.h \
    eyetracking.h \
    interfazocular.h \
    lista.h \
    arduino.h \
    cinematica.h \
    revolutearm.h \
    sequencer.h \
    constants.h \
    configwindow.h \
    findEyeCenter.h \
    helpers.h

FORMS += \
    interfazocular.ui \
    configwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../OpenCV1/NBuild/install/x64/vc15/lib/ -lopencv_core410 -opencv_aruco410d.lib -lopencv_imgproc410  -lopencv_face410 -opencv_barcode410d.lib -opencv_bgsegm410d.lib -opencv_bioinspired410d.lib -opencv_calib3d410d.lib -opencv_ccalib410d.lib -opencv_core410d.lib -opencv_datasets410d.lib -opencv_dnn410d.lib -opencv_dnn_objdetect410.lib -opencv_dnn_superres410d.lib -opencv_dpm410d.lib -opencv_face410d.lib -opencv_features2d410d.lib -opencv_flann410d.lib -opencv_fuzzy410d.lib -opencv_gapi410d.lib -opencv_hfs410d.lib -opencv_highgui410d.lib -opencv_imgcodecs410d.lib -opencv_imgproc410d.lib -opencv_img_hash410d.lib -opencv_intensity_transform410d.lib -opencv_line_descriptor410d.lib -opencv_mcc410d.lib -opencv_ml410d.lib -opencv_objdetect410d.lib -opencv_optflow410d.lib -opencv_phase_unwrapping410d.lib -opencv_photo410d.lib -opencv_plot410d.lib -opencv_quality410d.lib -opencv_reg410d.lib -opencv_saliency410d.lib -opencv_shape410d.lib -opencv_structured_light410d.lib -opencv_superres410d.lib -opencv_surface_matching410d.lib -opencv_text410d.lib -opencv_video410d.lib -opencv_videoio410d.lib -opencv_videostab410d.lib -opencv_wechat_qrcode410d.lib -opencv_ximgproc410d.lib -opencv_xobjdetect410d.lib -opencv_xphoto410d.lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../OpenCV1/NBuild/install/x64/vc15/lib/ -lopencv_core410d -lopencv_videoio410d -lopencv_objdetect410d -lopencv_imgproc410d -lopencv_face410d
else:unix: LIBS += -L$$PWD/../../../../../../OpenCV1/NBuild/install/x64/vc15/lib/ -lopencv_core410 -lopencv_objdetect410 -lopencv_imgproc410 -lopencv_face410

INCLUDEPATH += $$PWD/../../../../../../OpenCV1/NBuild/install/include
DEPENDPATH += $$PWD/../../../../../../OpenCV1/NBuild/install/include
