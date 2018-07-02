echo "starting to make a building dir : cmake-build-dir"
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
echo " -------- OPENCC CMAKE FINISHED --------------"
echo " -------- OPENCC MAKE STARTING ---------------"
make -j 2
echo " -------- OPENCC CMAKE Making Starting -------"
echo " ----   Ready To Use : ./cmake-build-debug/wgen/wgen         ----"
echo " ----   Ready To Use : ./cmake-build-debug/irtools/ir_b2a    ----"
echo " ----   Ready To Use : ./cmake-build-debug/irtools/ir_size   ----"
echo " ----   More coming .......                                  ----"
