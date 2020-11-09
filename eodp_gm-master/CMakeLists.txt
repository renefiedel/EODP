cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
if(POLICY_CMP0012)
  cmake_policy(SET CMP0012 NEW)
endif()

# Show traces during compilation
set(CMAKE_VERBOSE_MAKEFILE ON)

# *****************************************
# Compilation target directories and flags
# *****************************************
set(WFLAGS "-Wall -Wextra -Wno-sign-compare -lstdc++ -m64")

# C++ compiler optimization level configuration
# set(CMAKE_OPTIMIZE_EXEC "-O3")
# if(DEFINED ENV{OPTIMIZE_EXEC})
#   set(CMAKE_OPTIMIZE_EXEC "-$ENV{OPTIMIZE_EXEC}")
# endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_OPTIMIZE_EXEC} -g3")
set(CMAKE_C_FLAGS "-std=gnu99")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -std=c++14 --coverage -DDEBUG_SRC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_OPTIMIZE_EXEC} -g3 -std=c++14")
set(CMAKE_CXX_FLAGS "-fopenmp ${WFLAGS}")

# ****************************************
# Build type and tests
# ****************************************
set(CMAKE_BUILD_TYPE "release")
if(DEFINED ENV{BUILD_TYPE})
  set(CMAKE_BUILD_TYPE $ENV{BUILD_TYPE})
endif()

set(BUILD_TESTS TRUE)
if(DEFINED ENV{BUILD_TESTS})
  set(BUILD_TESTS $ENV{BUILD_TESTS})
endif()

if(BUILD_TESTS)
  set(BUILD_TESTS TRUE)
endif()

message(STATUS "BUILD_TYPE is '${CMAKE_BUILD_TYPE}' (options: debug release)")
message(STATUS "BUILD_TESTS is '${BUILD_TESTS}' (options: TRUE FALSE)")

# ********************************
# Look for required COTS and CFIs
# ********************************
file(GLOB COTS_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/cots/*")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Loop on dependencies
FOREACH(LIB_IO NCMAP)
  find_package(${LIB_IO} REQUIRED)
  string(TOUPPER ${LIB_IO} LIB_IO)
  if (${LIB_IO}_FOUND)
    include_directories( ${${LIB_IO}_INCLUDE_DIR} )
    link_directories( ${${LIB_IO}_LIBRARY_DIR} )
    set(ALL_LIBRARIES ${${LIB_IO}_LIBRARY_DIR} ${ALL_LIBRARIES})
    message(STATUS "Found ${LIB_IO} includes: ${${LIB_IO}_INCLUDE_DIR}")
  else()
    message(STATUS "Error: ${LIB_IO} not found")
  endif()
ENDFOREACH(LIB_IO)

FOREACH(COTS XML2 CONFIG NETCDF BOOST)
  find_package(${COTS} REQUIRED)
  string(TOUPPER ${COTS} COTS)
  if(${COTS}_FOUND)
    include_directories( ${${COTS}_INCLUDE_DIR} )
    link_directories( ${${COTS}_LIBRARY_DIR} )
    set(ALL_LIBRARIES ${${COTS}_LIBRARY_DIR} ${ALL_LIBRARIES})
    message(STATUS "Found ${COTS} includes: ${${COTS}_INCLUDE_DIR}")
    message(STATUS "Found ${COTS} library:  ${${COTS}_LIBRARY_DIR}")
  else()
    message(STATUS "Error: ${COTS} not found")
  endif()
ENDFOREACH(COTS)

FOREACH(CFI EECFI)
  find_package(${CFI} REQUIRED)
  string(TOUPPER ${CFI} COTS)
  if(${CFI}_FOUND)
    include_directories( ${${CFI}_INCLUDE_DIR} )
    link_directories( ${${CFI}_LIBRARY_DIR} )
    set(ALL_LIBRARIES ${${CFI}_LIBRARY_DIR} ${ALL_LIBRARIES})
    message(STATUS "Found ${CFI} includes: ${${CFI}_INCLUDE_DIR}")
    message(STATUS "Found ${CFI} library:  ${${CFI}_LIBRARY_DIR}")
  else()
    message(STATUS "Error: ${CFI} not found")
  endif()
ENDFOREACH(CFI)

# ****************************************
# Configuration files
# ****************************************
INSTALL(DIRECTORY auxiliary DESTINATION ".")

# ****************************************
# Auxiliary files
# ****************************************
INSTALL(DIRECTORY conf DESTINATION ".")

# ****************************************
# README file
# ****************************************
INSTALL(FILES README.md DESTINATION ".")

# ****************************************
# Recurse subdirectories
# ****************************************
add_subdirectory(common/src)
add_subdirectory(common/catch/src)
add_subdirectory(gm/src)

if(BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(common/test)
  add_subdirectory(gm/test)
endif()
