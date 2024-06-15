#pragma once
#include "vector3.hpp"
#include <vector>
#include <windows.h>
#include "imgui.h"
#pragma once
#include "vector3.hpp"
#include <vector>
#include <windows.h>
#include "imgui.h"

struct Entity;

class MiniMap {
public:
    MiniMap(float width, float height);
    void Render(const vector3_t& playerPosition, const std::vector<Entity>& entities);

private:
    float width;
    float height;
    float range;
};

void DrawRectangle(float x, float y, float width, float height, ImU32 color);
void DrawLine(float x1, float y1, float x2, float y2, ImU32 color);
void DrawCircle(float x, float y, float radius, ImU32 color);
void DrawPoint(float x, float y, ImU32 color);
