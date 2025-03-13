QT += core gui sql

# If the Qt major version is greater than 4, add the widgets module
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Enable C++17 features
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# Uncomment the following line to disable deprecated APIs before Qt 6.0.0
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Add source files for the project
SOURCES += \
    chartwidget.cpp \
    connection.cpp \
    dashbored.cpp \
    employee.cpp \
    main.cpp \
    mainwindow.cpp \
    sign_up.cpp

# Add header files for the project
HEADERS += \
    chartwidget.h \
    connection.h \
    dashbored.h \
    employee.h \
    mainwindow.h \
    sign_up.h

# Add UI form files for the project
FORMS += \
    dashbored.ui \
    mainwindow.ui \
    sign_up.ui

# Deployment settings (for different platforms)
# For QNX platform
qnx: target.path = /tmp/$${TARGET}/bin
# For Unix (non-Android)
else: unix:!android: target.path = /opt/$${TARGET}/bin

# If the target path is not empty, add the target to the installation list
!isEmpty(target.path): INSTALLS += target
