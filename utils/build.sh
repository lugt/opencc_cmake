#!/bin/bash
echo "starting to make a building dir : cmake-build-dir"
SCRIPT_DIR=$(dirname $0)/../
CMAKE_BUILD_DIR=${SCRIPT_DIR}/../cmake-build-debug
if [ "$1" = "rebuild" ]
then
	echo "########### rebuild"
	if [ -e ${CMAKE_BUILD_DIR} ]
	then
		rm -rf ${CMAKE_BUILD_DIR}
	fi
fi
if [ ! -e ${CMAKE_BUILD_DIR} ]
then
	mkdir ${CMAKE_BUILD_DIR}
fi
cd ${CMAKE_BUILD_DIR}
cmake ..
# cmake twice, second make will be ok, so strange
cmake ..
echo " -------- OPENCC CMAKE FINISHED --------------"
echo " -------- OPENCC MAKE STARTING ---------------"
make b2w -j 2
echo " -------- OPENCC CMAKE Making Starting -------"
echo " ----   Ready To Use : ./cmake-build-debug/wgen/wgen         ----"
echo " ----   Ready To Use : ./cmake-build-debug/irtools/ir_b2a    ----"
echo " ----   Ready To Use : ./cmake-build-debug/irtools/ir_size   ----"
echo " ----   More coming .......                                  ----"
