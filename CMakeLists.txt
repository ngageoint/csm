cmake_minimum_required(VERSION 3.10)
project(csmapi VERSION 3.0.3 DESCRIPTION "Community Sensor Model API")
set(CMAKE_CXX_STANDARD 11)

add_library(csmapi SHARED
             BundleGM.cpp
             CorrelationModel.cpp
             csmPointCloud.cpp
             Ellipsoid.cpp
             FourParameterCorrelationModel.cpp
             GeometricModel.cpp
             Isd.cpp
             LinearDecayCorrelationModel.cpp
             ModelIdentifier.cpp
             Plugin.cpp
             PointCloudGM.cpp
             PointCloudIsd.cpp
             RasterGM.cpp
             SettableEllipsoid.cpp
             Version.cpp
)

file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.h)

set_target_properties(csmapi PROPERTIES
                    VERSION ${PROJECT_VERSION}
                    SOVERSION 3
                    PUBLIC_HEADER ${HEADER_FILES}
)

target_include_directories(csmapi PUBLIC ${PROJECT_SOURCE_DIR})