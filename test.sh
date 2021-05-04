sh compile.sh

g++ test/test.cpp -std=c++17 -Iinclude -c -o temp/test/test.o

g++ temp/test/test.o Lib/FW -o WebServer