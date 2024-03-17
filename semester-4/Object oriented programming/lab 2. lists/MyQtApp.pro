TEMPLATE = app
TARGET = MyQtApp
INCLUDEPATH += .

# Указываем исходные файлы
SOURCES += \
    main.cpp \
    ui_designer.h

# Указываем заголовочные файлы
HEADERS += \
    ui_designer.h

# Указываем файлы форм
FORMS += \
    designer.ui

# Добавляем необходимые модули Qt
QT += widgets
