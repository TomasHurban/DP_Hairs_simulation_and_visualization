################################################################################
#                                                                              #
#  Bc. Tomas Hurban                                                            #
#  Diploma project                                                             #
#                                                                              #
#  Hair simulation and visualization using GPU                                 #
#  2012, May                                                                   #
#                                                                              #
#  Slovak University of Technology Bratislava                                  #
#  FACULTY OF INFORMATICS AND INFORMATION TECHNOLOGIES                         #
#                                                                              #
################################################################################

project(Hairs)

################################################################################
# Main project build
################################################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Common libraries
set(VL_LIBS_EXAMPLE VLGraphics VLCore)
set(VL_LIBS_TESTS VLMolecule VLVG VLVolume VLGraphics VLCore)

include(${QT_USE_FILE})

# all header files
SET(SOURCES_H_FILES
./CoreFunctions.hpp
./Hair.hpp
./HairEffect.hpp
./MainWindow.hpp
./Physics.hpp
./Settings.hpp
./SettingsWindow.hpp
)

# .hpp header files which contains Q_OBJECT
SET(SOURCES_H_QOBJECT
./SettingsWindow.hpp
)

# all source files
SET(SOURCES_C_FILES
./CoreFunctions.cpp
./Hair.cpp
./HairEffect.cpp
./Main.cpp
./MainWindow.cpp
./Physics.cpp
./Settings.cpp
./SettingsWindow.cpp
)

# macro to work with Q_OBJECT 
QT4_WRAP_CPP( SOURCES_H_MOC ${SOURCES_H_QOBJECT} )

SOURCE_GROUP(\\MOC "^.*moc_.*$")

# Main project
add_executable(Hairs ${SOURCES_C_FILES} ${SOURCES_H_MOC} ${SOURCES_H_FILES})
target_link_libraries(Hairs VLQt4 ${VL_LIBS_EXAMPLE} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
VL_INSTALL_TARGET(Hairs)
