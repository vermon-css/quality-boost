#include "plugin.hpp"

extern void init(create_interface_fn ef, create_interface_fn sf);

bool Plugin::load(create_interface_fn ef, create_interface_fn sf) {
    init(ef, sf);
    return true;
}

void Plugin::unload() {
    
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
