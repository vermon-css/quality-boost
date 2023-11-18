#include <cstring>
#include <cstdlib>

#include <Windows.h>
#include <Psapi.h>

#include <sdk/client_entity_list.hpp>
#include <sdk/base_handle.hpp>
#include <sdk/user_cmd.hpp>
#include <sdk/player_buttons.hpp>
#include <sdk/player_info_manager.hpp>
#include <sdk/global_vars.hpp>
#include <sdk/player_flags.hpp>
#include <sdk/engine_cvar.hpp>
#include <sdk/command.hpp>

#include "plugin.hpp"
#include "offsets.hpp"
#include "command.hpp"

class BasePlayer;
class IClientMode;

constexpr int client_mode_create_move_vtable_index = 21;

Plugin pl;

MacroCommand command;

BasePlayer** local_player;

ICvar* engine_cvar;
GlobalVars* global_vars;
IClientEntityList* entity_list;
IClientMode* client_mode;

bool (__thiscall *original_create_move)(IClientMode*, float, UserCmd*);

bool pull = false;
float throw_time = 0.0f;
float delay_time = 0.1f;

extern "C" __declspec(dllexport)
void* CreateInterface(const char* name, InterfaceReturnStatus* rc) {
    void* p = (std::strcmp(name, interface_version_server_plugin_callbacks) == 0) ? &pl : nullptr;

    if (rc)
        *rc = (p ? InterfaceReturnStatus::OK : InterfaceReturnStatus::FAILED);

    return p;
}

bool __fastcall create_move(IClientMode* client_mode, void*, float input_sample_time, UserCmd* cmd) {
    if (!cmd->command_number || !*local_player)
        return original_create_move(client_mode, input_sample_time, cmd);

    auto tick_base_time = *offset<int>(*local_player, offsets::tick_base) * global_vars->interval_per_tick;

    if (throw_time) {
        if (throw_time < tick_base_time) {
            cmd->buttons |= PlayerButtons::JUMP;
            throw_time = 0.0f;
        }
    }
    else if (pull) {
        cmd->buttons &= ~PlayerButtons::ATTACK;
        throw_time = tick_base_time + delay_time;
        pull = false;
    }
    else {
        auto active_weapon = *offset<BaseHandle>(*local_player, offsets::active_weapon);
        auto weapon = entity_list->get_client_entity_from_handle(active_weapon);

        constexpr unsigned short flashbang_handle = 9728;

        if (!weapon || (*offset<unsigned short>(weapon, offsets::weapon_file_info) != flashbang_handle))
            return original_create_move(client_mode, input_sample_time, cmd);

        auto flags = *offset<int>(*local_player, offsets::flags);
        auto next_attack = *offset<float>(*local_player, offsets::next_attack);

        if ((flags & PlayerFlags::ON_GROUND) && (next_attack <= global_vars->cur_time) && (cmd->buttons & PlayerButtons::ATTACK2)) {
            cmd->buttons |= PlayerButtons::ATTACK;
            cmd->buttons &= ~PlayerButtons::ATTACK2;
            pull = true;
        }
    }

    return original_create_move(client_mode, input_sample_time, cmd);
}

MacroCommand::MacroCommand() {
    this->registered = false;
    this->name = "macro";
    this->help_string = "Quality Boost";
    this->flags = 0;
}

void MacroCommand::dispatch(const Command& c) {
    if (c.count() > 1)
        delay_time = std::atof(c[1]);
    else
        engine_cvar->console_printf("Delay is %.3f\n", delay_time);
}

bool Plugin::load(create_interface_fn ef, create_interface_fn sf) {
    engine_cvar = reinterpret_cast<ICvar*>(ef(interface_version_engine_cvar, nullptr));

    engine_cvar->register_con_command(&command);

    auto client_module = GetModuleHandleA("client.dll");
    auto cf = reinterpret_cast<create_interface_fn>(GetProcAddress(client_module, "CreateInterface"));
    
    entity_list = reinterpret_cast<IClientEntityList*>(cf(interface_version_client_entity_list, nullptr));

    MODULEINFO client_module_info;
    GetModuleInformation(GetCurrentProcess(), client_module, &client_module_info, sizeof(MODULEINFO));

    DWORD old_protection;
    VirtualProtect(client_module_info.lpBaseOfDll, client_module_info.SizeOfImage, PAGE_EXECUTE_READWRITE, &old_protection);

    local_player = offset<BasePlayer*>(client_module_info.lpBaseOfDll, offsets::local_player);
    global_vars = *offset<GlobalVars*>(client_module_info.lpBaseOfDll, offsets::global_vars);
    client_mode = *offset<IClientMode*>(client_module_info.lpBaseOfDll, offsets::client_mode);

    auto vtable = *reinterpret_cast<void***>(client_mode);

    original_create_move = reinterpret_cast<decltype(original_create_move)>(vtable[client_mode_create_move_vtable_index]);
    vtable[client_mode_create_move_vtable_index] = reinterpret_cast<void*>(create_move);

    return true;
}

void Plugin::unload() {
    auto vtable = *reinterpret_cast<void***>(client_mode);
    vtable[client_mode_create_move_vtable_index] = reinterpret_cast<void*>(original_create_move);

    engine_cvar->unregister_con_command(&command);
}

void Plugin::pause() {
    
}

void Plugin::unpause() {
    
}

const char* Plugin::get_plugin_description() {
    return "Quality Boost";
}

void Plugin::level_init(const char* map_name) {
    
}

void Plugin::server_activate(Edict* edict_list, int edict_count, int max_clients) {

}

void Plugin::game_frame(bool simulating) {

}

void Plugin::level_shutdown() {
    
}

void Plugin::client_active(Edict* ent) {
    
}

void Plugin::client_disconnect(Edict* ent) {
    
}

void Plugin::client_put_in_server(Edict* ent, const char* player_name) {
    
}

void Plugin::set_command_client(int index) {
    
}

void Plugin::client_settings_changed(Edict* edict) {
    
}

PluginResult Plugin::client_connect(bool* allow_connect, Edict* ent, const char* name, const char* address, char* reject, int max_reject_len) {
    return PluginResult::CONTINUE;
}

PluginResult Plugin::client_command(Edict* ent, const Command& args) {
    return PluginResult::CONTINUE;
}

PluginResult Plugin::network_id_validated(const char* name, const char* network_id) {
    return PluginResult::CONTINUE;
}

void Plugin::on_query_cvar_value_finished(int cookie, Edict* ent, QueryCvarValueStatus status, const char* name, const char* value) {
    
}

void Plugin::on_edict_allocated(Edict* edict) {
    
}

void Plugin::on_edict_freed(const Edict* edict) {
    
}
