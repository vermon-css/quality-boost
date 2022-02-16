#pragma once

class Vector;
class SurfInfo;
class IMaterial;
struct Model;
struct PlayerInfo;
struct ClientTextMessage;

class IVEngineClient {
public:
    virtual int get_intersecting_surfaces(const Model* model, const Vector& center, const float radius, const bool only_visible_surfaces, SurfInfo* info, const int max_info) = 0;
    virtual Vector get_light_for_point(const Vector& pos, bool clamp) = 0;
    virtual IMaterial* trace_line_material_and_lighting(const Vector& start, const Vector& end, Vector& diff_use_light_color, Vector& base_color) = 0;
    virtual const char* parse_file(const char* data, char* token, int max_len) = 0;
    virtual bool copy_local_file(const char* source, const char* destination) = 0;
    virtual void get_screen_size(int& width, int& height) = 0;
    virtual void server_cmd(const char* s, bool reliable=true) = 0;
    virtual void client_cmd(const char* s) = 0;
    virtual bool get_player_info(int ent_num, PlayerInfo* info) = 0;
    virtual int get_player_for_user_id(int user_id) = 0;
    virtual ClientTextMessage* text_message_get(const char* name) = 0;
    virtual bool con_is_visible() = 0;
    virtual int get_local_player() = 0;
};
