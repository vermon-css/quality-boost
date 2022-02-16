#include <cstring>
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

#include "plugin.hpp"
#include "offsets.hpp"
#include "command.hpp"

class BasePlayer;
class IClientMode;

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
    void* p = (std::strcmp(name, interface_version_server_plugin_callbacks) == 0) ? &plugin : nullptr;
    if (rc)
        *rc = (p ? InterfaceReturnStatus::OK : InterfaceReturnStatus::FAILED);
    return p;
}

bool __fastcall create_move(IClientMode* client_mode, void*, float input_sample_time, UserCmd* cmd) {
    if (!cmd->command_number)
        return original_create_move(client_mode, input_sample_time, cmd);

    auto active_weapon = *offset<BaseHandle>(*local_player, offsets::active_weapon);
    auto weapon = entity_list->get_client_entity_from_handle(active_weapon);

    if (!weapon)
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

void init(create_interface_fn ef, create_interface_fn sf) {
    engine_cvar = reinterpret_cast<ICvar*>(ef(interface_version_engine_cvar, nullptr));

    engine_cvar->register_con_command(&macro_command);

    auto client_module = GetModuleHandleA("client.dll");
    auto cf = reinterpret_cast<create_interface_fn>(GetProcAddress(client_module, "CreateInterface"));
    
    entity_list = reinterpret_cast<IClientEntityList*>(cf(interface_version_client_entity_list, nullptr));

    MODULEINFO client_module_info;
    GetModuleInformation(GetCurrentProcess(), client_module, &client_module_info, sizeof(MODULEINFO));

    DWORD old_protection;
    VirtualProtect(client_module_info.lpBaseOfDll, client_module_info.SizeOfImage, PAGE_EXECUTE_READWRITE, &old_protection);

    local_player = offset<BasePlayer*>(client_module_info.lpBaseOfDll, offsets::local_player);
    client_mode = *offset<IClientMode*>(client_module_info.lpBaseOfDll, offsets::client_mode);
    global_vars = *offset<GlobalVars*>(client_module_info.lpBaseOfDll, offsets::global_vars);

    original_create_move = reinterpret_cast<decltype(original_create_move)>((*reinterpret_cast<void***>(client_mode))[21]);
    (*reinterpret_cast<void***>(client_mode))[21] = reinterpret_cast<void*>(create_move);
}
