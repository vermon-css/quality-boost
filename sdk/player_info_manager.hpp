#pragma once

class IPlayerInfo;
struct GlobalVars;
class Edict;

class IPlayerInfoManager {
public:
    virtual IPlayerInfo* get_player_info(Edict* edict) = 0;
    virtual GlobalVars* get_global_vars() = 0;
};
