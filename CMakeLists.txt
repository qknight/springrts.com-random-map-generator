project(qtproject) # the name of your project

cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED) # find and setup Qt3 for this project

# add_definitions(${QT_DEFINITIONS})

# tell cmake where to search for libraries:
# link_directories(${KDE3_LIB_DIR})

# tell cmake where to search for Qt/KDE headers:
# include_directories(${QT_INCLUDE_DIR})

# tell cmake to process CMakeLists.txt in that subdirectory
add_subdirectory(src)
