# Quality Boost
Trikz macro to jump after a certain amount of time when you throw a flashbang. Maximum speed is expected by default.

It's implemented as a [client plugin](https://developer.valvesoftware.com/wiki/Client_plugins), so it's loaded by the game without any external software.

# Installation
1. Place ``macro.dll`` inside ``cstrike`` folder.  
2. Add the ``-insecure`` launch option, otherwise the plugin can't be loaded
3. Type ``plugin_load macro`` in the console while in the main menu. Alternatively, you can add ``+plugin_load macro`` to the game launch parameters to load it automatically on startup.

# Usage
Activate by pressing **MOUSE2** button (`+attack2`).  
To change the delay, use ``macro`` console command, for example **macro 0.08**.

# For developers
When throwing a grenade, the server logic typically [releases it after 0.1 seconds](https://github.com/lua9520/source-engine-2018-hl2_src/blob/3bf9df6b2785fa6d951086978a3e66f49427166a/game/shared/cstrike/weapon_basecsgrenade.cpp#L309). To achieve maximum vertical speed, it is important to jump at the same time, as the grenade [inherits the player's speed](https://github.com/lua9520/source-engine-2018-hl2_src/blob/3bf9df6b2785fa6d951086978a3e66f49427166a/game/shared/cstrike/weapon_basecsgrenade.cpp#L380). If you jump later, gravity will come into play, and the vertical speed will decrease.