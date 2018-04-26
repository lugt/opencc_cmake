cmake_minimum_required(VERSION 3.4)
project(osprey)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_C_STANDARD 99)

#Global DIR
include(varib/dir.cmake)

#Global VAR
include(varib/global.cmake)

#Global SRC
include(varib/sharedsf.cmake)

#Local VAR
include(varib/ela.cmake)

#Local DIR
include(varib/local.cmake)

#Local Source
include(varib/localsf.cmake)

#Making Progess
include(varib/saveenv.cmake)
