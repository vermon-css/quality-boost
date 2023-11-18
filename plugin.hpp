#include <sdk/server_plugin.hpp>

class Plugin : IServerPluginCallbacks {
    virtual bool load(create_interface_fn ef, create_interface_fn sf);
    virtual void unload();
    virtual void pause();
    virtual void unpause();
    virtual const char* get_plugin_description();
    virtual void level_init(const char* map_name);
    virtual void server_activate(Edict* edict_list, int edict_count, int max_clients);
    virtual void game_frame(bool simulating);
    virtual void level_shutdown();
    virtual void client_active(Edict* ent);
    virtual void client_disconnect(Edict* ent);
    virtual void client_put_in_server(Edict* ent, const char* player_name);
    virtual void set_command_client(int index);
    virtual void client_settings_changed(Edict* edict);
    virtual PluginResult client_connect(bool* allow_connect, Edict* ent, const char* name, const char* address, char* reject, int max_reject_len);
    virtual PluginResult client_command(Edict* ent, const Command& args);
    virtual PluginResult network_id_validated(const char* name, const char* network_id);
    virtual void on_query_cvar_value_finished(int cookie, Edict* ent, QueryCvarValueStatus status, const char* name, const char* value);
    virtual void on_edict_allocated(Edict* edict);
    virtual void on_edict_freed(const Edict* edict);
};
