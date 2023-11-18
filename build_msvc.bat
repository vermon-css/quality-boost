if not exist ".\target" mkdir target

cl /I . /std:c++20 /LD /Fe:target/macro.dll main.cpp
