#pragma once

#include <sdk/convar.hpp>

class MacroCommand : public ConCommand {
public:
    MacroCommand();
    virtual void dispatch(const Command& c);
} inline macro_command;
