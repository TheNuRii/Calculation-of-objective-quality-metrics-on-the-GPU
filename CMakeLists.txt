cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "GPULQ")
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_MINSIZEREL)
    if("${${flag_var}}" MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif()
  endforeach()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64-v2")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=nehalem")
  endif()
endif()

find_package(OpenMP QUIET)
find_package(OpenCL REQUIRED)
find_package(Threads REQUIRED)

set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/apps")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

set(PROJECT_SOURCES
  "${APP_DIR}/main.cpp"
  "${APP_DIR}/xApp.cpp"
  "${APP_DIR}/xPrintStats.cpp"

  "${LIBS_DIR}/lib_base/xPic.cpp"
  "${LIBS_DIR}/lib_base/xSeq.cpp"
  "${LIBS_DIR}/lib_base/xPixelOpsSTD.cpp"
  "${LIBS_DIR}/lib_thread/xThreadPool.cpp"
  "${LIBS_DIR}/lib_OpelCL/xOpenCL_Enumerator.cpp"
  "${LIBS_DIR}/Metrics/IVPreProcessing/xIVPreProcessing.cpp"
  "${LIBS_DIR}/Metrics/PSNR/xPSNR.cpp"
  "${LIBS_DIR}/Metrics/PSNR/xPSNR_OpenCL.cpp"
  "${LIBS_DIR}/Metrics/SSIM/xSSIM.cpp"
  "${LIBS_DIR}/Metrics/SSIM/xSSIM_OpenCL.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${APP_DIR}
    ${LIBS_DIR}
    ${LIBS_DIR}/lib_base
    ${LIBS_DIR}/lib_OpelCL
    ${LIBS_DIR}/lib_thread
    ${LIBS_DIR}/Metrics
    ${LIBS_DIR}/Metrics/IVPreProcessing
    ${LIBS_DIR}/Metrics/PSNR
    ${LIBS_DIR}/Metrics/SSIM
    ${OpenCL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Threads::Threads
    OpenCL::OpenCL
)

if(OpenMP_CXX_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

source_group("Source Files" FILES ${PROJECT_SOURCES})


