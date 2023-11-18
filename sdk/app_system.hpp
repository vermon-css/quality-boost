#pragma once

#include "interfaces.hpp"

enum class InitReturnVal;

class IAppSystem {
public:
    virtual bool connect(create_interface_fn factory) = 0;
    virtual void disconnect() = 0;
    virtual void* query_interface(const char* s) = 0;
    virtual InitReturnVal init() = 0;
    virtual void shutdown() = 0;
};
