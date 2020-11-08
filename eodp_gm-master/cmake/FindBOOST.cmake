#
# Find BOOST include directories and libraries
#
# BOOST_INCLUDE_DIR
# BOOST_LIBRARY_DIR
# BOOST_LIBRARY
# BOOST_FOUND

FOREACH(ROOT ${COTS_PATHS})

  FIND_PATH(BOOST_INCLUDE_DIR boost/multi_array.hpp
    ${ROOT}/include
    NO_DEFAULT_PATH
    )
  
  FIND_LIBRARY(BOOST_LIBRARY boost_atomic boost_chrono boost_container boost_mpi boost_system boost_thread
    ${BOOST_INCLUDE_DIR}/../lib
    NO_DEFAULT_PATH
    )
    
  IF(BOOST_INCLUDE_DIR)
    IF(BOOST_LIBRARY)
	  SET(BOOST_FOUND "YES")
	  GET_FILENAME_COMPONENT(BOOST_LIBRARY_DIR ${BOOST_LIBRARY} PATH)
    ENDIF(BOOST_LIBRARY)
  ENDIF(BOOST_INCLUDE_DIR)
  
ENDFOREACH(ROOT)
