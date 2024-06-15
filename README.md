# DayZ Simple ESP
A simple project to understand the basics of reverse engineering on memory to retrieve the correct offsets.

This project is based on the game DayZ in offline mode. It retrieves entities around the player to mark them on the screen. The project is in development. For now, it only displays the position of entities and the player in the debug menu. Translating the received data to display it as ESP is still in progress.

The offsets are based on version 1.25 of the official DayZ version. Offsets change with each version.


![Screenshot_3](https://github.com/Unknow-kernel/ESP/assets/63432221/e107574e-8b89-487f-b0de-1aea52ff4d01)

![Screenshot_4](https://github.com/Unknow-kernel/ESP/assets/63432221/7598be5f-3e06-4f2e-a174-51712c1c89e4)


### memory.hpp & memory.cpp 
- Functions to read and write into the game's process memory.
### Graphics.h & Graphics.cpp 
- DirectX and rendering management.
### ImGuiSetup.h & ImGuiSetup.cpp
- ImGui for the user interface.

### CheatFunctions.hpp & CheatFunctions.cpp 
- Management of functions including the display of entities.

### vector3.hpp & vector3.cpp 
- 3D vector management to represent entity positions.

### main.cpp 
- Main entry point, initializes the window, DirectX, ImGui, and the main loop.

### offsets.hpp 
- Offsets used to access specific data structures in the game's memory.
  
## Disclaimer
The project has no means to bypass BattleEye. Therefore, it is for educational purposes only. Running it without disabling BattleEye will simply result in a ban.

## Translations

- [Français (French)](README.fr.md)
