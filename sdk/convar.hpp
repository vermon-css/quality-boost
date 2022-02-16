#pragma once

#include "color.hpp"

class IConVar;
class UtlVector;
class Command;

using ChangeCallbackFn = void (*)(IConVar*, const char*, float);
using CommandCallbackFn = void (*)(const Command&);
using CommandCompletionCallback = void (*)(const char*, char*[64]);

class IConVar {
public:
    virtual void set_value(const char* value) = 0;
    virtual void set_value(float value) = 0;
    virtual void set_value(int value) = 0;
    virtual void set_value(Color value) = 0;
    virtual const char* get_name() const = 0;
    virtual const char* get_base_name() const = 0;
    virtual bool is_flag_set(int flag) const = 0;
    virtual int get_split_screen_player_slot() const = 0;
};

class ConCommandBase {
public:
    virtual ~ConCommandBase();
    virtual bool is_command() const;
    virtual bool is_flag_set(int flag) const;
    virtual void add_flags(int flags);
    virtual const char* get_name() const;
    virtual const char* get_help_text() const;
    virtual bool is_registered() const;
    virtual int get_dll_identifier() const;

protected:
    virtual void create_base(const char* name, const char* help_string="", int flags=0);
    virtual void init();

public:
    ConCommandBase* next;
    bool registered;
    const char* name;
    const char* help_string;
    int flags;
};

class ConCommand : public ConCommandBase {
public:
    virtual int auto_complete_suggest(const char* partial, UtlVector& commands);
    virtual bool can_auto_complete();
    virtual void dispatch(const Command& c);

private:
    CommandCallbackFn command_callback;
    CommandCompletionCallback command_completion_callback;

    bool has_completion_callback : 1;
    bool using_new_command_callback : 1;
    bool using_command_callback_interface : 1;
};

class ConVar : public ConCommandBase, public IConVar {
public:
    virtual ~ConVar();
    virtual bool is_flag_set(int flag) const;
    virtual const char* get_help_text() const;
    virtual bool is_registered() const;
    virtual const char* get_name() const;
    virtual void add_flags(int flags);
    virtual bool is_command() const;
    virtual void set_value(const char* value);
    virtual void set_value(float value);
    virtual void set_value(int value);

private:
    virtual void internal_set_value(const char* value);
    virtual void internal_set_float_value(float new_value, bool force=false);
    virtual void internal_set_int_value(int value);
    virtual void clamp_value(float& value);
    virtual void change_string_value(const char* temp_val, float old_value);
    virtual void init();

public:
    ConVar* parent;
    const char* default_value;
    char* string;
    int string_length;
    float float_value;
    int int_value;
    bool has_min;
    float min_val;
    bool has_max;
    float max_val;
    bool has_comp_min;
    float comp_min_val;
    bool has_comp_max;
    float comp_max_val;
    bool competitive_restrictions;
    ChangeCallbackFn change_callback;
};

inline
ConCommandBase::~ConCommandBase() {

}

inline
bool ConCommandBase::is_command() const {
    return true;
}

inline
bool ConCommandBase::is_flag_set(int flag) const {
    return this->flags & flag;
}

inline
void ConCommandBase::add_flags(int flags) {
    this->flags |= flags;
}

inline
const char* ConCommandBase::get_name() const {
    return this->name;
}

inline
const char* ConCommandBase::get_help_text() const {
    return this->help_string;
}

inline
bool ConCommandBase::is_registered() const {
    return this->registered;
}

inline
int ConCommandBase::get_dll_identifier() const {
    return -1;
}

inline
void ConCommand::dispatch(const Command& c) {
    this->command_callback(c);
}

inline
int ConCommand::auto_complete_suggest(const char* partial, UtlVector& commands) {
    return 0;
}

inline
bool ConCommand::can_auto_complete() {
    return this->has_completion_callback;
}

inline
void ConCommandBase::create_base(const char* name, const char* help_string, int flags) {
	
}

inline
void ConCommandBase::init() {

}
