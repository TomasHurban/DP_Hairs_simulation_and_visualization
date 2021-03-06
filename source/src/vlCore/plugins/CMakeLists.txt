################################################################################
#                                                                              #
#  Copyright (c) 2005-2011, Michele Bosi, Thiago Bastos                        #
#  All rights reserved.                                                        #
#                                                                              #
#  This file is part of Visualization Library                                  #
#  http://www.visualizationlibrary.com                                         #
#                                                                              #
#  Released under the OSI approved Simplified BSD License                      #
#  http://www.opensource.org/licenses/bsd-license.php                          #
#                                                                              #
################################################################################

################################################################################
# Add external/3rd-party dependencies as necessary
################################################################################

if(VL_IO_2D_PNG)
	add_subdirectory("libpng")
endif()

if(VL_IO_2D_TIFF)
	add_subdirectory("libtiff")
endif()

if(VL_IO_2D_JPG OR VL_IO_2D_TIFF)
    add_subdirectory("jpeg")
endif()

if(VL_IO_2D_DICOM)
	set(VL_IO_2D_GDCM_LIB_DIR "" CACHE PATH "GDCM library directory")
	set(VL_IO_2D_GDCM_LIBRARIES "FILLME" CACHE LIST "GDCM libraries (semicolon separated)")
	set(VL_IO_2D_GDCM_INC_DIR "FILLME" CACHE PATH "GDCM include directory")

	set(_GDCM_LIBS "")
	foreach(lib ${VL_IO_2D_GDCM_LIBRARIES})
		list(APPEND _GDCM_LIBS "${VL_IO_2D_GDCM_LIB_DIR}/${lib}")
	endforeach()

	VL_PROJECT_ADD(VLCORE
		INCLUDE_DIRECTORIES "${VL_IO_2D_GDCM_INC_DIR}"
		LINK_LIBRARIES "${_GDCM_LIBS}"
	)
else()
	unset(VL_IO_2D_GDCM_LIB_DIR CACHE)
	unset(VL_IO_2D_GDCM_LIBRARIES CACHE)
	unset(VL_IO_2D_GDCM_INC_DIR CACHE)
endif()

################################################################################
# Compile-time Plugins for VLCore
################################################################################

# VLCore requires ZLib (not really a plugin, it's here for convenience)
add_subdirectory("zlib")

# List of "2D IO" plugins
set(VLCORE_PLUGINS "BMP" "DAT" "DDS" "DICOM" "JPG" "PNG" "TGA" "TIFF")

# All plugins are enabled by default, except for DICOM
set(VL_IO_2D_DICOM_OPTION "Enable DICOM support (requires GDCM)" OFF)

VL_PROCESS_PROJECT_PLUGINS(VLCORE VL_IO_2D_ ${VLCORE_PLUGINS})
