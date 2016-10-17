cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

###############################################################################
## project definition #########################################################
###############################################################################
set(LIBRARY_OUTPUT_VERSION 1.0)
set(LIBRARY_OUTPUT_NAME MongoDao)
set(LIBRARY_OUTPUT_LANGUAGE CXX)
set(LIBRARY_OUTPUT_BUILD_TYPE DEBUG) # DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL
project(${LIBRARY_OUTPUT_NAME} VERSION ${LIBRARY_OUTPUT_VERSION} LANGUAGES ${LIBRARY_OUTPUT_LANGUAGE})

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES src/*.cpp)
include_directories(inc)  
 	
###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_library(${LIBRARY_OUTPUT_NAME} SHARED ${SOURCES})
#Set Debug or Release
set(CMAKE_BUILD_TYPE ${LIBRARY_OUTPUT_BUILD_TYPE})

###############################################################################
## compiler definitions########################################################
###############################################################################

#enable c++11 and set it required
set_property(TARGET ${LIBRARY_OUTPUT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${LIBRARY_OUTPUT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

###############################################################################
## dependencies ###############################################################
###############################################################################

# POCO
set(POCO_PREFIX "/usr/local")
set(POCO_INCLUDE_DIR"${POCO_PREFIX}/include")
set(POCO_LIB_DIR "${POCO_PREFIX}/lib")
set(POCO_LIBS
        "${POCO_LIB_DIR}/libPocoNet.so"
        "${POCO_LIB_DIR}/libPocoUtil.so"
        "${POCO_LIB_DIR}/libPocoFoundation.so"
        "${POCO_LIB_DIR}/libPocoJSON.so"
        "${POCO_LIB_DIR}/libPocoMongoDB.so")

include_directories(${POCO_INCLUDE})
link_directories(${POCO_LIB_DIR})
target_link_libraries(${LIBRARY_OUTPUT_NAME} ${POCO_LIBS})











####################
##  TBD  ##
####################

# Set installation destination folder for .so and .h files.
# Change the destination folder
###############################
set(INSTALLATION_DIR "/home/developer/workspace/SpiderBite/env/mongodao/lib")
set(HEADER_DIR "/home/developer/workspace/SpiderBite/env/mongodao/inc")

# Set header location that will be copied
file(GLOB HEADERS inc/*)


INSTALL( FILES "${CMAKE_CURRENT_SOURCE_DIR}/libMongoDao.so"
	DESTINATION ${INSTALLATION_DIR}
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ WORLD_WRITE)

# Install .h files
foreach(ITEM ${HEADERS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()

INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION ${HEADER_DIR} 
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ WORLD_WRITE)

INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION ${HEADER_DIR} )
	



