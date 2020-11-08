add_library(common
  STATIC
  StringManager.cpp
  FIPSModule.cpp
  FIPSException.cpp
)

target_link_libraries(common 
  configuration
  xml2
  netcdf
  netcdf_c++4
  ncmap
  boost_filesystem
  boost_system
)

install(TARGETS common
  ARCHIVE
  DESTINATION lib
)

install(FILES
  Common.hpp
  StringManager.hpp
  FIPSModule.hpp
  FIPSException.hpp
  DESTINATION include
)

