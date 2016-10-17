cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(DAO_Test VERSION 0.1 LANGUAGES CXX)

set(_ECLIPSE_VERSION "4.5")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES
 *.h
 *.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_executable(DAO_Test ${SOURCES})

#Set Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# just for example add some compiler flags
#target_compile_options(DAO_Test PUBLIC -Wextra)

###############################################################################
## compiler definitions########################################################
###############################################################################

#enable c++11 and set it required
set_property(TARGET DAO_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET DAO_Test PROPERTY CXX_STANDARD_REQUIRED ON)

###############################################################################
## dependencies ###############################################################
###############################################################################

# MongoDao
#set(DAO_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}../build") # the directory containing "include" and "lib"
#set(DAO_INCLUDE_DIR"${CMAKE_CURRENT_SOURCE_DIR}../inc")
#set(DAO_LIB_DIR "${DAO_PREFIX}")
#set(DAO_LIBS
#        "${DAO_LIB_DIR}/libMongoDao.a")
        
set(DAO_LIBRARY_DIRS ${CMAKE_CURRENT_LIST_DIR}/../build)  
set(DAO_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/../inc)  
find_library(  
	DAO_LIBRARIES  
	NAMES MongoDao  
	PATHS ${CMAKE_CURRENT_LIST_DIR}/../build  
	PATH_SUFFIXES "lib"  
	NO_DEFAULT_PATH  
)  

# CPPUNIT
find_library(CPPUNIT_LIBRARY_DEBUG NAMES cppunit cppunit_dll cppunitd cppunitd_dll
            	PATHS  
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            PATH_SUFFIXES debug )

find_library(CPPUNIT_LIBRARY_RELEASE NAMES cppunit cppunit_dll
            PATHS   ${PATH}/lib
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            PATH_SUFFIXES release )

if(CPPUNIT_LIBRARY_DEBUG AND NOT CPPUNIT_LIBRARY_RELEASE)
    set(CPPUNIT_LIBRARY_RELEASE ${CPPUNIT_LIBRARY_DEBUG})
endif(CPPUNIT_LIBRARY_DEBUG AND NOT CPPUNIT_LIBRARY_RELEASE)

set( CPPUNIT_LIBRARY debug ${CPPUNIT_LIBRARY_DEBUG} optimized ${CPPUNIT_LIBRARY_RELEASE} )

        
# POCO
# set the POCO paths and libs
set(POCO_PREFIX "/usr/local") # the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR"${POCO_PREFIX}/include")
set(POCO_LIB_DIR "${POCO_PREFIX}/lib")
set(POCO_LIBS
        "${POCO_LIB_DIR}/libPocoNet.so"
        "${POCO_LIB_DIR}/libPocoUtil.so"
        "${POCO_LIB_DIR}/libPocoFoundation.so"
        "${POCO_LIB_DIR}/libPocoJSON.so"
        "${POCO_LIB_DIR}/libPocoMongoDB.so")

#set(Poco_USE_STATIC_LIBS OFF) 
#set(Poco_USE_MULTITHREADED ON)  
#set(Poco_USE_STATIC_RUNTIME OFF) 
#find_package(Poco 1.7.3 EXACT COMPONENTS PocoNet PocoUtil PocoFoundation PocoJSON PocoMongoDB regex date_time log log_setup REQUIRED)        

include_directories(${DAO_INCLUDE} ${POCO_INCLUDE})
link_directories(${DAO_LIBRARY_DIRS} ${POCO_LIB_DIR} ${CPPUNIT_LIBRARY})
target_link_libraries(DAO_Test ${DAO_LIBRARIES} ${POCO_LIBS} ${CPPUNIT_LIBRARY})