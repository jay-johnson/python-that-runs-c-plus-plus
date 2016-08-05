cmake_minimum_required(VERSION 2.8)

# Turn this to on for logging
set(CMAKE_VERBOSE_MAKEFILE off)

project(pythonwrapper)

# Find Boost
find_package(Boost COMPONENTS filesystem system date_time python REQUIRED)
message("---- Boost Include:  " ${Boost_INCLUDE_DIRS} )
message("---- Boost Libs:     " ${Boost_LIBRARIES} )

# Find Python
find_package(PythonLibs REQUIRED)
message("---- Python Include: " ${PYTHON_INCLUDE_DIRS} )
message("---- Python Libs:    " ${PYTHON_LIBRARIES} )

# Target the 2.7 and includes for 2.7
set(PYTHON_VERSION 2.7)
set(PYTHON_INCLUDE /usr/include/python${PYTHON_VERSION})

SET(MODULE_NAME    pyapi_wrapper_ext)
PROJECT(${MODULE_NAME}_py)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(PTYHON_VERSION      "2.7")
set(PYTHON_LIBRARY      "python${PTYHON_VERSION}")
set(PYTHON_INCLUDE_DIR  "/usr/include/python${PYTHON_VERSION}")
set(CMAKE_C_FLAGS       "-j4")
set(CMAKE_CXX_FLAGS     "-Wall -std=c++0x")


FIND_PACKAGE(PythonLibs)
IF(PYTHONLIBS_FOUND)
  INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_DIRS}")
ELSE()
  MESSAGE(FATAL_ERROR "Unable to find PythonLibs.")
ENDIF()

FIND_PACKAGE(Boost)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES("${Boost_INCLUDE_DIRS}" "./headers")
  SET(Boost_USE_STATIC_LIBS     OFF)
  SET(Boost_USE_MULTITHREADED    ON)
  SET(Boost_USE_STATIC_RUNTIME     OFF)
  FIND_PACKAGE(Boost  ${BOOST_VERSION}    COMPONENTS python)  
ELSEIF(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Unable to find Boost.")
ENDIF()

# include other source codes.
ADD_LIBRARY(${MODULE_NAME} MODULE  
    src/lib_pyapi_wrapper_ext.cpp
    src/pyapi_wrapper.cpp
    )

set_target_properties(${MODULE_NAME}
    PROPERTIES 
    SUFFIX ".so")
    
TARGET_LINK_LIBRARIES(${MODULE_NAME} 
    ${Boost_LIBRARIES} 
    ${PYTHON_LIBRARIES} 
    )

