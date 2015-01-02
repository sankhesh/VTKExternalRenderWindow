cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

include_directories(
  ${OPENGL_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  )

add_executable(glutWindow main.cpp)
target_link_libraries(glutWindow
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
  ${VTK_LIBRARIES}
  )
