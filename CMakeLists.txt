project(OBDepict) 
cmake_minimum_required(VERSION 2.6.0)

message(STATUS "OBDepict 0.1.0")
message(STATUS "source: ${OBDepict_SOURCE_DIR}")

set(CMAKE_MODULE_PATH ${OBDepict_SOURCE_DIR}/cmake/modules)
find_package(OpenBabel2 REQUIRED) # find and setup OpenBabel

find_package(Qt4) # find and setup Qt4 for this project
include(${QT_USE_FILE})

include_directories(
    ${OBDepict_SOURCE_DIR}/src
    ${QT_INCLUDES}
    ${OPENBABEL2_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CAIRO_INCLUDE}
)

set(depict_srcs
    src/depict.cpp    # OBDepict class
)

########################################
#  Magick++
########################################
find_file(MAGICK_CONFIG_EXE "Magick++-config" PATHS
    "/usr/bin"
    "/usr/local/bin"
)
if (MAGICK_CONFIG_EXE)
  message(STATUS "Found Image Magick++ libaries -- Enabling MagickPainter.")
  execute_process(COMMAND Magick++-config --cppflags OUTPUT_VARIABLE Magick_CPP_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND Magick++-config --cxxflags OUTPUT_VARIABLE Magick_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND Magick++-config --ldflags  OUTPUT_VARIABLE Magick_LD_FLAGS  OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND Magick++-config --libs     OUTPUT_VARIABLE Magick_LIBS      OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Magick_CPP_FLAGS} ${Magick_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Magick_LIBS} ${Magick_LD_FLAGS}")
  
  add_definitions(-DUSE_MAGICK_PAINTER)
  set(obdepict_srcs ${depict_srcs} src/magickpainter.cpp tools/magickdepict.cpp)

  add_executable(magickdepict ${obdepict_srcs})
  target_link_libraries(magickdepict ${OPENBABEL2_LIBRARIES})
  install(TARGETS magickdepict DESTINATION bin)
  
# remove_definitions(-DUSE_MAGICK_PAINTER)
endif (MAGICK_CONFIG_EXE)

########################################
#  Cairo
########################################
find_path(CAIRO_INCLUDE "cairo.h"
    "/usr/include/cairo"
    "C:/src/cairo/include"
)
find_library(CAIRO_LIBRARIES cairo)
if (CAIRO_INCLUDE AND CAIRO_LIBRARIES)
  message(STATUS "Found Cairo libaries -- Enabling CairoPainter.")
  
  add_definitions(-DUSE_CAIRO_PAINTER)
  set(obdepict_srcs ${depict_srcs} src/cairopainter.cpp tools/cairodepict.cpp)

  add_executable(cairodepict ${obdepict_srcs})
  target_link_libraries(cairodepict ${OPENBABEL2_LIBRARIES} ${CAIRO_LIBRARIES})
  install(TARGETS cairodepict DESTINATION bin)
  
endif (CAIRO_INCLUDE AND CAIRO_LIBRARIES)
  
#remove_definitions(-DUSE_CAIRO_PAINTER)

########################################
#  Qt4
########################################
if (QT_FOUND)
  message(STATUS "Found Qt4 libaries -- Enabling QtPainter.")
  set(qtdepict_srcs ${depict_srcs} src/qtpainter.cpp 
      src/qtdepict/qtdepict.cpp src/qtdepict/mainwindow.cpp)

  qt4_wrap_ui(mainwindow_UIS src/qtdepict/mainwindow.ui)
  qt4_wrap_cpp(mainwindow_MOC src/qtdepict/mainwindow.h)

  add_executable(qtdepict ${mainwindow_UIS} ${qtdepict_srcs} ${mainwindow_MOC})
  target_link_libraries(qtdepict ${OPENBABEL2_LIBRARIES} ${QT_LIBRARIES})
  install(TARGETS qtdepict DESTINATION bin)
endif (QT_FOUND)


