#pragma once

#include <cstdint>

enum class offsets {
    local_player = 0x4c88e8,
    active_weapon = 0x0d80,
    throw_time = 0x96c,
    client_mode = 0x50293c,
    global_vars = 0x49a278,
    tick_base = 0x10ec,
    next_primary_attack = 0x878,
    flags = 0x350,
    next_attack = 0x0c38
};

template<typename T, typename B, typename O>
T* offset(B base, O offset) {
    return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(base) + static_cast<std::uintptr_t>(offset));
}
