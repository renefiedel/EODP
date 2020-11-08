include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/../../common/src/"
)

add_executable(gm_exec main.cpp)

target_link_libraries(gm_exec 
  gm 
  common
  configuration
  netcdf
  netcdf_c++4
  ncmap
  pthread
  m
  dl
  explorer_orbit
  explorer_pointing
  explorer_lib
  explorer_data_handling
  explorer_file_handling
  geotiff
  tiff
)

set_target_properties(gm_exec PROPERTIES OUTPUT_NAME "geometry_module")

install(TARGETS gm_exec
  RUNTIME
  DESTINATION bin
)

add_library(gm
  STATIC
  GeometryModule.cpp
  GMRealGridICD.cpp
  GMException.cpp
  GeometryModuleConfiguration.cpp
)

target_link_libraries(gm
  common
  configuration
  netcdf
  netcdf_c++4
  ncmap
  pthread
  m
  dl
  explorer_orbit
  explorer_pointing
  explorer_lib
  explorer_data_handling
  explorer_file_handling
  geotiff
  tiff
)

install(TARGETS gm
  ARCHIVE
  DESTINATION lib
)

install(FILES
  GeometryModule.hpp
  GMRealGridICD.hpp
  GMException.hpp
  GeometryModuleConfiguration.hpp
  DESTINATION include
)
