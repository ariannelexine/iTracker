project (pupiltracker)
cmake_minimum_required(VERSION 2.8)

# configure gcc compiler flags
#IF(UNIX)
#    IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
#        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
#        IF(GCC_VERSION VERSION_LESS 4.7)
#            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#        ELSE()
#            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#        ENDIF()
#    ELSE()
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#    ENDIF()
#ENDIF(UNIX)

# explicitly set c++11 
set(CMAKE_CXX_STANDARD 11)

# configure boost
#IF(WIN32)
#	set(BOOST_ROOT "C:/boost_1_60_0")
#	set(BOOST_INCLUDEDIR ${BOOST_ROOT}/boost)
#	set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib64-msvc-12.0)
#   find_package(Boost 1.55.0 COMPONENTS random) 
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#ELSE(WIN32)
#    find_package(Boost REQUIRED)
#ENDIF(WIN32)

# configure OpenCV
IF(WIN32)
    # set the opencv directories manually
    message("Windows platform detected, setting OpenCV configuration manually...")
    set(OPENCV_ROOT_DIR "C:/OpenCV")
	set(OPENCV_BUILD_DIR ${OPENCV_ROOT_DIR}/build/x64/vc12)
    set(OPENCV_INCLUDE_DIRS ${OPENCV_ROOT_DIR}/build/include; ${OPENCV_ROOT_DIR}/build/include/opencv; ${OPENCV_ROOT_DIR}/build/include/opencv2)
    set(OPENCV_LIB_DIRS ${OPENCV_BUILD_DIR}/lib)

    # set the include and link directories
    include_directories(${OPENCV_INCLUDE_DIRS})
    link_directories(${OPENCV_LIB_DIRS})
    
    # find all of the libs in OPENCV_LIB_DIRS
    file(GLOB OpenCV_LIBS RELATIVE ${OPENCV_LIB_DIRS} ${OPENCV_LIB_DIRS}/*.lib)
    message("Found OpenCV libs...")
    message(${OpenCV_LIBS})
ELSE(WIN32)
    find_package(OpenCV REQUIRED)
ENDIF(WIN32)

# configure TBB
IF(WIN32)
    # set the opencv directories manually
    message("Windows platform detected, setting OpenCV configuration manually...")
    set(TBB_ROOT_DIR "C:/tbb44_20151115oss")

    # set the include and link directories
    include_directories(${TBB_ROOT_DIR}/include)
    link_directories(${TBB_ROOT_DIR}/lib/intel64/vc12)
ELSE(WIN32)
	#find_package(TBB REQUIRED)
ENDIF(WIN32)

add_executable(swirski_tracker swirski_main.cpp)
add_library(swirski_lib swirski_pupil/PupilTracker.cpp swirski_pupil/cvx.cpp swirski_pupil/utils.cpp)
target_link_libraries(swirski_tracker swirski_lib ${OpenCV_LIBS} tbb)

add_executable(canny_tracker canny_main.cpp canny_pupil/PupilTracker.cpp)
target_link_libraries(canny_tracker ${OpenCV_LIBS})
