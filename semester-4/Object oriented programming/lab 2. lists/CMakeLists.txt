include_directories(/usr/include/qt/QtCore)
cmake_minimum_required(VERSION 3.16) # Указываем минимальную версию CMake, необходимую для проекта

project(MyQtApp VERSION 1.0.0 LANGUAGES CXX) # Устанавливаем имя проекта и его версию

set(CMAKE_CXX_STANDARD 17) # Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Требуем поддержки C++17

find_package(Qt6 REQUIRED COMPONENTS Widgets) # Находим необходимые компоненты Qt (в данном случае Widgets)

# Добавляем исполняемый файл и указываем его исходные файлы
add_executable(MyQtApp
    main.cpp
    designer.cpp # Путь к вашему файлу с реализацией класса из designer.ui
    ui_designer.h # Файл заголовка, сгенерированный из designer.ui
)

# Связываем исполняемый файл с библиотеками Qt
target_link_libraries(MyQtApp PRIVATE Qt6::Widgets)

# Включаем автоматическое генерирование moc-файлов и uic-файлов для файлов Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
