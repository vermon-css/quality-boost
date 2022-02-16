if not exist ".\target" mkdir target
clang++ -shared -m32 -std=c++2a -I . -o target/macro.dll src/*.cpp
