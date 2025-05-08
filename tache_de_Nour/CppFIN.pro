QT       += core gui sql
QT += core gui printsupport widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += widgets sql charts
QT += serialport



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    nour.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    mainwindow.h \
    nour.h

FORMS += \
    mainwindow.ui \
    nour.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    extract_logic.py \
    extract_skills.py \
    generate_logo.py \
    skills_cache.py
