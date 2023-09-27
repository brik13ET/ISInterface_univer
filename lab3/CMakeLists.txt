cmake_minimum_required(VERSION 3.10)

set(C_STANDARD c11)

project(LAB3_impl)

find_package(JNI)
message(STATUS "JNI_FOUND=${JNI_FOUND}")
if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
    list (GET JNI_INCLUDE_DIRS 0 JNI_INCLUDE_DIRS_HEAD)
endif()

add_custom_target(
    javaMainClass 
    COMMAND javac -d ${CMAKE_BINARY_DIR} -cp ${CMAKE_BINARY_DIR} javaMain.java
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
    SOURCES ${PROJECT_SOURCE_DIR}/src/javaMain.java
)
add_custom_target(
    javaClassCopy
    SOURCES ${PROJECT_SOURCE_DIR}/src/javaMain.java
)
add_custom_command(
    TARGET javaClassCopy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t
            "${CMAKE_CURRENT_BINARY_DIR}/"
            "${PROJECT_SOURCE_DIR}/src/javaMain.class"
)

add_custom_target(
    javaMainH
    COMMAND javac -h ${PROJECT_SOURCE_DIR}/include javaMain.java
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src
    SOURCES ${PROJECT_SOURCE_DIR}/src/javaMain.java
)

ADD_LIBRARY(LAB3_impl SHARED src/javaImp.c)

add_dependencies(
    javaClassCopy
    javaMainClass
)

add_dependencies(
    LAB3_impl
    javaMainH
    javaClassCopy
)


target_compile_options(LAB3_impl PUBLIC -fPIC)
target_include_directories(LAB3_impl PUBLIC ${JNI_INCLUDE_DIRS})
target_include_directories(LAB3_impl PUBLIC ${JAVA_INCLUDE_PATH})
target_include_directories(LAB3_impl PUBLIC include)
target_link_directories(LAB3_impl PUBLIC ${JNI_LIBRARIES})



project(LAB3_runner)
ADD_executable(LAB3_runner src/runner.c)
configure_file(
    src/cmake_var.h.in
    ${PROJECT_SOURCE_DIR}/include/cmake_var.h
)
target_include_directories(LAB3_runner PUBLIC include)

add_dependencies(
    LAB3_runner
    LAB3_impl
)