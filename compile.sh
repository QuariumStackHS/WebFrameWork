

g++ framework/framework.cpp -std=c++17 -Iinclude -c -o temp/framework.o

g++ temp/*.o -shared -o Lib/FW