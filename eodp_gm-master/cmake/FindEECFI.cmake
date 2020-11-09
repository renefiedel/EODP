#
# Find EECFI include directories and libraries
#
# EECFI_INCLUDE_DIR
# EECFI_LIBRARY_DIR
# EECFI_LIBRARY
# EECFI_FOUND

FOREACH(ROOT ${COTS_PATHS} ${CFIS_ROOT})

  FIND_PATH(EECFI_INCLUDE_DIR explorer_lib.h
    /opt/EECFI/include
    /opt/EOCFI/include
    ${ROOT}/EECFI/current/include
    ${ROOT}/EECFI/include
    ${ROOT}/EOCFI/current/include
    ${ROOT}/EOCFI/include
    ${ROOT}/include
    )
  
  FIND_LIBRARY(EECFI_LIBRARY explorer_lib
    ${EECFI_INCLUDE_DIR}/../lib
    ${EECFI_INCLUDE_DIR}/../lib/LINUX64
    ${EECFI_INCLUDE_DIR}/../lib/LINUX64_LEGACY
    )
  
  IF(EECFI_INCLUDE_DIR)
    IF(EECFI_LIBRARY)
	  SET(EECFI_FOUND "YES")
	  GET_FILENAME_COMPONENT(EECFI_LIBRARY_DIR ${EECFI_LIBRARY} PATH)
      SET(EECFI_LIBRARIES
        explorer_orbit
        explorer_pointing
        explorer_lib
        explorer_data_handling
        explorer_file_handling
        m)
    ENDIF(EECFI_LIBRARY)
  ENDIF(EECFI_INCLUDE_DIR)
  
ENDFOREACH(ROOT)
