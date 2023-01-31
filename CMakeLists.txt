cmake_minimum_required(VERSION 3.5)

project(Floorplan_Optimizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(PROJECT_SOURCES
        main.cpp
	UI/Windows/mainwindow.cpp
	UI/Windows/mainwindow.h
	UI/Windows/mainwindow.ui
	UI/Windows/resultDialog.h
	UI/Windows/resultDialog.cpp
	UI/Windows/resultDialog.ui
	UI/Windows/optOptionsDialog.h
	UI/Windows/optOptionsDialog.cpp
	UI/Windows/optOptionsDialog.ui
	UI/RenderArea/renderarea.h
	UI/RenderArea/renderarea.cpp
	UI/RenderArea/ralineedit.h
	UI/RenderArea/ralineedit.cpp
	UI/TypesTree/typetreewidget.h
	UI/TypesTree/typetreewidget.cpp
	UI/TypesTree/typeTreeItem.h
	UI/TypesTree/typeTreeItem.cpp
	UI/TypesTree/variantTreeItem.h
	UI/TypesTree/variantTreeItem.cpp
	UI/requirementsTree.h
	UI/requirementsTree.cpp
	UI/Visualizer/configurationPlane.h
	UI/Visualizer/configurationPlane.cpp
	XML_Management/XMLFileManager.h
	XML_Management/XMLFileManager.cpp
	Algorithm/AlgorithmManager.h
	Algorithm/AlgorithmManager.cpp
	Algorithm/GraphNode.h
	Algorithm/GraphNode.cpp
	Algorithm/PlacementGraph.cpp
	Algorithm/PlacementGraph.h
	Algorithm/Point.h
	Algorithm/RectanglePlacer.cpp
	Algorithm/RectanglePlacer.h
	Algorithm/resultStruct.h
	Algorithm/SideEnum.h
	Algorithm/Type.h
	Algorithm/Type.cpp
	Algorithm/Variant.h
	Algorithm/Variant.cpp
	Algorithm/VariantRectangle.cpp
	Algorithm/VariantRectangle.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Floorplan_Optimizer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Floorplan_Optimizer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Floorplan_Optimizer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Floorplan_Optimizer
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Floorplan_Optimizer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Floorplan_Optimizer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Floorplan_Optimizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Floorplan_Optimizer)
endif()
