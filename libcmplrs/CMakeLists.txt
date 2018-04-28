cmake_minimum_required(VERSION 3.4)
project(osprey)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_C_STANDARD 99)

#Global DIR
include(../global/dir.cmake)

#Global VAR
include(../global/global.cmake)

#Global SRC
include(../global/sharedsf.cmake)

#Local include(localsf.cmake)

#Making Progess
include(saveenv.cmake)
