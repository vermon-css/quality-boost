# Description
When throwing a grenade, the server logic typically [releases it after 0.1 seconds](https://github.com/lua9520/source-engine-2018-hl2_src/blob/3bf9df6b2785fa6d951086978a3e66f49427166a/game/shared/cstrike/weapon_basecsgrenade.cpp#L309). To achieve maximum vertical speed, it is important to jump at the same moment since the grenade [inherits the player's speed](https://github.com/lua9520/source-engine-2018-hl2_src/blob/3bf9df6b2785fa6d951086978a3e66f49427166a/game/shared/cstrike/weapon_basecsgrenade.cpp#L380). If you jump later, gravity will come into play, and the vertical speed will decrease.

This macro automatically throws a flashbang and jumps after a specified amount of time. By default, the maximum vertical speed is expected.

It is implemented as a [client plugin](https://developer.valvesoftware.com/wiki/Client_plugins) so it can be quite convenient to use it.

# Setup
1. Place ``macro.dll`` inside ``cstrike`` folder.  
2. Add the ``-insecure`` launch option as the engine expects it.  
3. Enter ``plugin_load macro`` in the console while in the main menu. Alternatively, you can add ``+plugin_load macro`` to the game launch parameters to load it automatically on startup.

# Usage
Activate by pressing MOUSE2 button (+attack2).  
To change the delay, there is the ``macro`` console command. Type ``macro {delay}``, for example, *macro 0.08*.
