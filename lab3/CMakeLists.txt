cmake_minimum_required(VERSION 3.10)

set(C_STANDARD c11)

project(LAB3_impl)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

# add_custom_command(
#     OUTPUT  javaMain.class
#     COMMAND javac javaMain.java
#     WORKING_DIRECTORY src
#     SOURCES javaMain
# )

# add_custom_command(
#     OUTPUT  src/javaMain.class include/javaMain.h
#     COMMAND javac -h ../include javaMain.java
#     WORKING_DIRECTORY src
#     SOURCES javaMain
# )

add_custom_target(
    javaMainClass
    COMMAND javac -d ${CMAKE_BINARY_DIR} -cp ${CMAKE_BINARY_DIR} javaMain.java 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
    SOURCES ${PROJECT_SOURCE_DIR}/src/javaMain.java
)

add_custom_target(
    javaMainH
    COMMAND javac -h ${PROJECT_SOURCE_DIR}/include javaMain.java
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
    SOURCES ${PROJECT_SOURCE_DIR}/src/javaMain.java
)

ADD_LIBRARY(LAB3_impl SHARED src/javaImp.c)

add_dependencies(
    LAB3_impl
    javaMainClass
    javaMainH
)

configure_file(
    src/cmake_var.h.in
    ${PROJECT_SOURCE_DIR}/include/cmake_var.h
)

target_include_directories(LAB3_impl PUBLIC ${JNI_INCLUDE_DIRS})
target_include_directories(LAB3_impl PUBLIC include)
target_link_directories(LAB3_impl PUBLIC ${JNI_LIBRARIES})



project(LAB3_runner)
ADD_executable(LAB3_runner src/runner.c)
target_include_directories(LAB3_runner PUBLIC include)