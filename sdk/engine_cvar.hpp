#pragma once

#include "app_system.hpp"
#include "convar.hpp"

class ConVar;
class ConCommand;
class IConsoleDisplayFunc;
class ICvarQuery;
class ICvarIteratorInternal;
struct Color;

class ICvar : public IAppSystem {
public:
	virtual int allocate_dll_identifier() = 0;
	virtual void register_con_command(ConCommandBase* command_base) = 0;
	virtual void unregister_con_command(ConCommandBase* command_base) = 0;
	virtual void unregister_con_commands(int id) = 0;
	virtual const char* get_command_line_value(const char* variable_name) = 0;
	virtual ConCommandBase* find_command_base(const char* name) = 0;
	virtual const ConCommandBase* find_command_base(const char* name) const = 0;
	virtual ConVar* find_var(const char* name) = 0;
	virtual const ConVar* find_var(const char* name) const = 0;
	virtual ConCommand* find_command(const char* name) = 0;
	virtual const ConCommand* find_command(const char* name) const = 0;
	virtual ConCommandBase* get_commands() = 0;
	virtual const ConCommandBase* get_commands() const = 0;
	virtual void install_global_change_callback(ChangeCallbackFn callback) = 0;
	virtual void remove_global_change_callback(ChangeCallbackFn callback) = 0;
	virtual void call_global_change_callbacks(ConVar* var, const char* old_string, float old_value) = 0;
	virtual void install_console_display_func(IConsoleDisplayFunc* func) = 0;
	virtual void remove_console_display_func(IConsoleDisplayFunc* func) = 0;
	virtual void console_color_printf(const Color& clr, const char* format, ...) const = 0;
	virtual void console_printf(const char* format, ...) const = 0;
	virtual void console_d_printf(const char* format, ...) const = 0;
	virtual void revert_flagged_convars(int flag) = 0;
	virtual void install_cvar_query(ICvarQuery* query) = 0;
	virtual bool is_material_thread_set_allowed() const = 0;
	virtual void queue_material_thread_set_value(ConVar* convar, const char* value) = 0;
	virtual void queue_material_thread_set_value(ConVar* convar, int value) = 0;
	virtual void queue_material_thread_set_value(ConVar* convar, float value) = 0;
	virtual bool has_queue_material_thread_convar_sets() const = 0;
	virtual int process_queued_material_thread_convar_sets() = 0;

protected:
	virtual ICvarIteratorInternal* factory_internal_iterator() = 0;
};
