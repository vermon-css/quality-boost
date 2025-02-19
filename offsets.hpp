#pragma once

#include <cstdint>

namespace offsets {
    enum class vtable {
        get_active_weapon = 227,
        get_weapon_name = 316,
        create_move = 21
    };

    enum class members {
        tick_base = 0x16b0,
        flags = 0x440,
        next_attack = 0x1058
    };

    enum class globals {
        local_player = 0x5f4b68,
        client_mode = 0x68cfe8,
        global_vars = 0x5ae280,
    };
}

template<typename T, typename B, typename O>
T& offset(B base, O offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(base) + static_cast<std::uintptr_t>(offset));
}

template<typename T, typename B, typename O>
T& vtable_offset(B base, O offset) {
    return *reinterpret_cast<T*>(&reinterpret_cast<void**>(base)[static_cast<std::size_t>(offset)]);
}

template<typename T, typename I, typename O>
auto& instance_vtable_offset(I inst, O offset) {
    return vtable_offset<T>(*reinterpret_cast<void**>(inst), static_cast<std::size_t>(offset));
}
