#pragma once

class SaveRestoreData;

struct GlobalVars {
    float real_time;
    int frame_count;
    float absolute_frame_time;
    float cur_time;
    float frame_time;
    int max_clients;
    int tick_count;
    float interval_per_tick;
    float interpolation_amount;
    int sim_ticks_this_frame;
    int network_protocol;
    SaveRestoreData* save_data;
};
