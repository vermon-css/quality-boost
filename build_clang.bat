if not exist ".\target" mkdir target
clang++ -shared -std=c++2a -I . -o target/macro.dll main.cpp
