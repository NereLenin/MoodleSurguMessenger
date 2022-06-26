QT += quick


#QMAKE_LFLAGS += -static-libgcc -static-libstdc++
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#

# prebuild install openssl library for Android's complects
android: include(D:\Android\Sdk\android_openssl\openssl.pri)

SOURCES += \
        appengine.cpp \
        main.cpp \
        src/conversation/conversation.cpp \
        src/conversation/conversationmanager.cpp \
        src/conversation/message.cpp \
        src/courses/course.cpp \
        src/network/moodlenetworkmanager.cpp \
        src/profiles/account.cpp \
        src/profiles/member.cpp \
        src/profiles/profile.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    appengine.h \
    src/conversation/conversation.h \
    src/conversation/conversationmanager.h \
    src/conversation/message.h \
    src/courses/course.h \
    src/network/moodlenetworkmanager.h \
    src/profiles/account.h \
    src/profiles/member.h \
    src/profiles/profile.h

