# 设置CMake最低版本要求
cmake_minimum_required(VERSION 3.16)

# 项目名称和版本
project(promelo VERSION 0.1 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用Qt的自动MOC、UIC和RCC处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)



# 查找Qt5组件
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Core)

# 定义scintilla源文件
file(GLOB SCINTILLA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/src/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/qt/ScintillaEditBase/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/qt/ScintillaEdit/*.cpp"
)

# 定义lexilla源文件
file(GLOB LEXILLA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/lexilla/lexlib/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/lexilla/lexers/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/lexilla/src/*.cxx"
)

# 添加包含目录
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/include"  # 修复了拼写错误 inlcude -> include
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/qt/ScintillaEditBase"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/qt/ScintillaEdit"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/scintilla/win32"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/lexilla/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/3dPart/lexilla/lexlib"
)

# Add definitions for Scintilla
add_definitions(-DSCINTILLA_QT)
add_definitions(-DSCI_LEXER)
add_definitions(-DSCI_USE_QT_EVENTS)
# 添加静态库编译选项（如果Scintilla是静态链接）
# 在CMake中定义动态库导出宏
add_definitions(-DSCI_QT_DLL)
add_definitions(-DSCI_QT)


add_definitions(-DMAKING_LIBRARY)

include_directories(promelo
    ${PROJECT_SOURCE_DIR}
)


# 创建可执行文件
add_executable(promelo
    main.cpp
    promelowindow.h
    promelowindow.cpp
    promeloeditor.h
    promeloeditor.cpp
    promelowindow.ui
    promeloeditorpanel.cpp
    promeloeditorpanel.h
    res.qrc
    ${SCINTILLA_SOURCES}
    ${LEXILLA_SOURCES}
)

# 链接Qt库
target_link_libraries(promelo PRIVATE Qt5::Widgets)

# 链接Windows输入法库
if(WIN32)
    target_link_libraries(promelo PRIVATE Imm32)
target_link_libraries(promelo PRIVATE Qt5::Core)
target_link_libraries(promelo PRIVATE Qt5::Core)
endif()

# 设置目标属性
set_target_properties(promelo PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 安装规则
include(GNUInstallDirs)
install(TARGETS promelo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
