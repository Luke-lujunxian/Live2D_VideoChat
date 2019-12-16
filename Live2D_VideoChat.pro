QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network multimedia

CONFIG += c++14

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
    src/Audio.cpp \
    src/Communicator.cpp \
    src/JsonConverter.cpp \
    src/LApp/LAppAllocator.cpp \
    src/LApp/LAppDefine.cpp \
    src/LApp/LAppDelegate.cpp \
    src/LApp/LAppLive2DManager.cpp \
    src/LApp/LAppModel.cpp \
    src/LApp/LAppPal.cpp \
    src/LApp/LAppSprite.cpp \
    src/LApp/LAppTextureManager.cpp \
    src/LApp/LAppView.cpp \
    src/Model.cpp \
    src/Network_QT.cpp \
    src/Setting.cpp \
    src/UI/VideoWindow.cpp \
    src/UI/about.cpp \
    src/UI/acceptcall.cpp \
    src/UI/chat.cpp \
    src/UI/connecting.cpp \
    src/UI/errorwin.cpp \
    src/UI/mainwindow.cpp \
    src/UI/settingwin.cpp \
    src/detection.cpp \
    src/helper.cpp \
    src/main.cpp

HEADERS += \
    src/Audio.h \
    src/Communicator.hpp \
    src/JsonConverter.hpp \
    src/LApp/LAppAllocator.hpp \
    src/LApp/LAppDefine.hpp \
    src/LApp/LAppDelegate.hpp \
    src/LApp/LAppLive2DManager.hpp \
    src/LApp/LAppModel.hpp \
    src/LApp/LAppPal.hpp \
    src/LApp/LAppSprite.hpp \
    src/LApp/LAppTextureManager.hpp \
    src/LApp/LAppView.hpp \
    src/Model.hpp \
    src/Network_QT.h \
    src/Setting.h \
    src/UI/VideoWindow.h \
    src/UI/about.h \
    src/UI/acceptcall.h \
    src/UI/chat.h \
    src/UI/connecting.h \
    src/UI/errorwin.h \
    src/UI/mainwindow.h \
    src/UI/settingwin.h \
    src/detection.h \
    src/helper.hpp \
    tests/TestAnimator.hpp \
    tests/TestFacialDetection.hpp \
    tests/TestMainWindow.hpp

FORMS += \
    UI/Chat.ui \
    UI/MainWindow.ui \
    UI/SettingWin.ui \
    UI/VideoWindow.ui \
    UI/about.ui \
    UI/acceptcall.ui \
    UI/connecting.ui \
    UI/errorwin.ui

INCLUDEPATH += \
    src/ \
    src/UI/ \
    include/ \
    include/Cubism/Core \
    include/Cubism/Framework/src \
    include/Cubism/thirdparty/glew-2.1.0/include \
    include/Cubism/thirdparty/glfw-3.3.bin.WIN64/include \
    include/stb/include

debug {
LIBS += \
    $$PWD/lib/Cubism/Core/lib/windows/x86_64/141/Live2DCubismCore_MDd.lib \
    $$PWD/lib/Cubism/Framework/Release/Framework.a \
    $$PWD/lib/Cubism/thirdparty/glew-2.1.0/x64/glew32.lib \
    $$PWD/lib/Cubism/thirdparty/glew-2.1.0/x64/glew32s.lib \
    $$PWD/lib/Cubism/thirdParty/glfw-3.3.bin.WIN64/lib-mingw-w64/libglfw3.a \
    $$PWD/lib/Cubism/thirdParty/glfw-3.3.bin.WIN64/lib-mingw-w64/libglfw3dll.a \
    $$PWD/lib/opencv/x64/opencv_world412.dll.a \
    $$PWD/lib/dlib/dlib.a

DESTDIR = out/Debug/
}
release {
LIBS += \
    $$PWD/lib/Cubism/Core/lib/windows/x86_64/141/Live2DCubismCore_MD.lib \
    $$PWD/lib/Cubism/Framework/Release/Framework.a \
    $$PWD/lib/Cubism/thirdparty/glew-2.1.0/x64/glew32.lib \
    $$PWD/lib/Cubism/thirdparty/glew-2.1.0/x64/glew32s.lib \
    $$PWD/lib/Cubism/thirdParty/glfw-3.3.bin.WIN64/lib-mingw-w64/libglfw3.a \
    $$PWD/lib/Cubism/thirdParty/glfw-3.3.bin.WIN64/lib-mingw-w64/libglfw3dll.a \
    $$PWD/lib/opencv/x64/opencv_world412.dll.a \
    $$PWD/lib/dlib/dlib.a

DESTDIR = out/Release/
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
