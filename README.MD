# Description
Usually, when we throw a grenade, the server logic releases it after 0.1 seconds. And since the grenade inherits the player’s speed, to achieve maximum vertical speed we must jump at the same moment, since later the gravity would come in, and the vertical speed would decrease.

This macro automatically throws a flashbang and jumps after a specified amount of time. By default, the maximum vertical speed is expected.

It is implemented as [client plugin](https://developer.valvesoftware.com/wiki/Client_plugins) so it can be quite convenient to use it.

# Setup
1. Place ``macro.dll`` inside ``cstrike`` folder.  
2. You should add ``--insecure`` lauch option in order to load it since the engine expects this.  
3. Enter ``plugin_load macro`` in the console being in the main menu. You may also add ``+plugin_load macro`` to the game launch parameters to automatically load it on startup.

# Usage
Activate by pressing MOUSE2 button (+attack2).  
To change the delay, there is ``macro`` console command, type ``macro {delay}``, e.g. *macro 0.08*.
