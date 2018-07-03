#
# Developed by:  Mario Emmenlauer (mario@emmenlauer.de)
#                Balanstrasse 43, 81669 Munich
#                http://www.biodataanalysis.de/
#
# With contributions by: 
#
#
# Copyright (c) 2014-2018, BioDataAnalysis GmbH
# All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are not permitted. All information contained herein
# is, and remains the property of BioDataAnalysis GmbH.
# Dissemination of this information or reproduction of this material
# is strictly forbidden unless prior written permission is obtained
# from BioDataAnalysis GmbH.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(BDAWorkAssessmentVigra VERSION 1.0.0)
set(COMPANY "BioDataAnalysis GmbH")
set(COPYRIGHT "Copyright (c) 2017 BioDataAnalysis GmbH. All rights reserved.")
set(IDENTIFIER "de.biodataanalysis.bdaworkassessmentvigra")
set(Vigra_DIR "/home/alam/usr/vigra-/lib/vigra/")

find_package(Vigra REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Vigra_INCLUDE_DIRS})
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    add_definitions(-DDEBUG -D_DEBUG -D_DEBUG_)
endif()
if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-deprecated-declarations")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS NO)


set(TARGETS ${TARGETS}
    task01
    task02
    task03)

foreach(TARGET ${TARGETS})
    add_executable(${TARGET} src/${TARGET}.cc)

    set_target_properties(${TARGET} PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS NO)

    target_link_libraries(${TARGET}
        PRIVATE vigraimpex)
endforeach()

