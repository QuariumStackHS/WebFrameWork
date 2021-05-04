

g++ FrameWork/FrameWork.cpp -std=c++17 -Iinclude -c -o temp/FrameWork.o

g++ temp/*.o -shared -o Lib/FW