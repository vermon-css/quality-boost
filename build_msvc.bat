if not exist ".\target" mkdir target
if not exist ".\build" mkdir build
cl /Fo:build/ /I . /std:c++20 /LD /Fe:target/macro.dll main.cpp
