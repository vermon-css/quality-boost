#pragma once

#include "qangle.hpp"

class UserCmd {
public:
    virtual ~UserCmd();

    int command_number;
    int tick_count;
    QAngle view_angles;
    float forward_move;
    float side_move;
    float up_move;
    int buttons;
    unsigned char impulse;
    int weapon_select;
    int weapon_sub_type;
    int random_seed;
    short mouse_dx;
    short mouse_dy;
    bool has_been_predicted;
};
