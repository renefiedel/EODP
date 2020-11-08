set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(TESTNAME EODP-GM_UT02)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/../../src/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../../common/src/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../../common/catch/src/"
)

add_executable(${TESTNAME} 
  testRealOrbitPropagation.cpp
)

set_target_properties(${TESTNAME} PROPERTIES OUTPUT_NAME "EODP-GM_UT02")
target_link_libraries(${TESTNAME} 
  gm
  common
  configuration
  ncmap
  stdc++fs)

add_test(NAME ${TESTNAME}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ./EODP-GM_UT02)
