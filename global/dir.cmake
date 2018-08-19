set(DEBUG ON)
if(IS_DIRECTORY)
set(OSPREY_SRC_DIR ${CMAKE_SOURCE_DIR}/../../../osprey)
endif()


######### ###############################################
#### If you want to choose a different path of osprey,###
#### uncomment the following line and change it  ########
#########################################################

# set(OSPREY_SRC_DIR <path_to_another_osprey>)

if(IS_DIRECTORY ${OSPREY_SRC_DIR})
    if(IS_FILE ${OSPREY_SRC_DIR}/../defs.mk)
        message(STATUS " [Using OSPREY] : [" ${OSPREY_SRC_DIR} "]")
    else()
        message(FATAL_ERROR "[ERR_2] : Please double check that the path to the osprey dir is properly set in global/dir.cmake")
    endif()
else()
    message(FATAL_ERROR "[ERR_1] Please double check that the path to the osprey dir is properly set in global/dir.cmake")
endif()