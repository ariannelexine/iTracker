project (pupiltracker)
cmake_minimum_required(VERSION 2.8)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_LESS 4.7)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else ()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
else ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()



# configure OpenCV
IF(WIN32)
    message("Windows platform detected, generating OpenCV configuration...")
    
    set(OPENCV_BUILD_DIR "C:/OpenCV/build/x64/vc10")
    set(OPENCV_INCLUDE_DIRS "C:/OpenCV/build/include;C:/OpenCV/build/include/opencv;C:/OpenCV/build/include/opencv2")
    set(OPENCV_LIB_DIRS "C:/OpenCV/build/x64/vc10/lib")

    # find all of the subdirectories in OPENCV_LIB_DIRS to include
    include_directories(${OPENCV_BUILD_DIR})
    include_directories(${OPENCV_INCLUDE_DIRS})
    link_directories(${OPENCV_LIB_DIRS})
    
    # find all of the libs in OPENCV_LIB_DIRS
    file(GLOB OpenCV_LIBS RELATIVE ${OPENCV_LIB_DIRS} ${OPENCV_LIB_DIRS}/*247.lib)
    message("Found OpenCV libs...")
    message(${OpenCV_LIBS})
ELSE(WIN32)
    find_package (OpenCV REQUIRED)
ENDIF(WIN32)


find_package (OpenCV REQUIRED)

add_executable (pupil_tracker main.cpp)
add_library (pupil_lib lib/PupilTracker.cpp lib/cvx.cpp lib/utils.cpp)
target_link_libraries(pupil_tracker pupil_lib ${OpenCV_LIBS} tbb)
