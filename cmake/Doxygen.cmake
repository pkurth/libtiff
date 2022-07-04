# Doxygen documentation
find_package(Doxygen)
set(DOXYGEN_DEFAULT OFF)
if(DOXYGEN_FOUND)
    set (DOXYGEN_DEFAULT ON)
endif()
option(doxygen "Enable doxygen documentation" ${DOXYGEN_DEFAULT})
set(BUILD_DOXYGEN ${doxygen})
