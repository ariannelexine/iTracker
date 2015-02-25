project (pupiltracker)
cmake_minimum_required(VERSION 2.8)

# configure gcc compiler flags
IF(UNIX)
    IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
        IF(GCC_VERSION VERSION_LESS 4.7)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        ELSE()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        ENDIF()
    ELSE()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ENDIF()
ENDIF(UNIX)

# configure boost
IF(WIN32)
    find_package(Boost 1.50.0 COMPONENTS random) 
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ELSE(WIN32)
    find_package(Boost REQUIRED)
ENDIF(WIN32)

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
    file(GLOB OpenCV_LIBS RELATIVE ${OPENCV_LIB_DIRS} ${OPENCV_LIB_DIRS}/*2410.lib)
    message("Found OpenCV libs...")
    message(${OpenCV_LIBS})
ELSE(WIN32)
    find_package(OpenCV REQUIRED)
ENDIF(WIN32)

# configure tbb
IF(WIN32)
    set(TBB_BUILD_DIR "C:/tbb43_20140724oss/bin;C:/tbb43_20140724oss/bin/intel64;C:/tbb43_20140724oss/bin/intel64/vc10")
    set(TBB_INCLUDE_DIRS "C:/tbb43_20140724oss/include;C:/tbb43_20140724oss/include/tbb;C:/tbb43_20140724oss/include/serial")
    set(TBB_LIBRARY_DIRS "C:/tbb43_20140724oss/lib/intel64/vc10")
    include_directories(${TBB_BUILD_DIR})
    include_directories(${TBB_INCLUDE_DIRS})
    link_directories(${TBB_LIBRARY_DIRS})
    file(GLOB tbb RELATIVE ${TBB_LIBRARY_DIRS} ${TBB_LIBRARY_DIRS}/*.lib)
ELSE(WIN32)
    set(TBB_BUILD_DIR "~/opencv-2.4.10/build/3rdparty/tbb/tbb41_20130116oss")
    set(TBB_INCLUDE_DIRS "~/opencv-2.4.10/build/3rdparty/tbb/tbb41_20130116oss/include")
    set(TBB_LIBRARY_DIRS "~/opencv-2.4.10/build/lib")
    include_directories(${TBB_BUILD_DIR})
    include_directories(${TBB_INCLUDE_DIRS})
    link_directories(${TBB_LIBRARY_DIRS})
    file(GLOB tbb RELATIVE ${TBB_LIBRARY_DIRS} ${TBB_LIBRARY_DIRS}/*.lib)
ENDIF(WIN32)

#set(FIND_TBB true)
#IF(FIND_TBB)
#    message("FIND_TBB true, generating TBB configuration with FindTBB...")
#
#    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/")
#    find_package(TBB REQUIRED)

    # find the appropriate subdirectories
#    message("TBB_INCLUDE_DIRS: " ${TBB_INCLUDE_DIRS})
#    message("TBB_LIBRARY_DIRS: " ${TBB_LIBRARY_DIRS})
#    include_directories(${TBB_INCLUDE_DIRS})
#    link_directories(${TBB_LIBRARY_DIRS})
    
    # find the TBB libs
#    file(GLOB TBB_LBRARIES RELATIVE ${TBB_LIBRARY_DIRS} ${TBB_LIBRARY_DIRS}/libtbb*)
#    message("TBB_LIBRARIES: " ${TBB_LBRARIES})
#    set(tbb ${TBB_LIBRARIES})
#ENDIF(FIND_TBB)

add_executable (pupil_tracker main.cpp)
add_library (pupil_lib lib/PupilTracker.cpp lib/cvx.cpp lib/utils.cpp)
target_link_libraries(pupil_tracker pupil_lib ${OpenCV_LIBS} tbb)
