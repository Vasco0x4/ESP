# DayZ Simple ESP
A simple project to understand the basics of reverse engineering on memory to retrieve the correct offsets.

This project is based on the game DayZ in offline mode. It retrieves entities around the player to mark them on the screen. The project is in development. For now, it only displays the position of entities and the player in the debug menu. Translating the received data to display it as ESP is still in progress.

The offsets are based on version 1.25 of the official DayZ version. Offsets change with each version.


![image](https://github.com/Unknow-kernel/ESP/assets/63432221/63207782-4e37-42f7-a949-9b2f0c0c7f32)


![image](https://github.com/Unknow-kernel/ESP/assets/63432221/4e668744-e420-4741-9756-d39940e7dc78)


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
