#pragma once

#include <iostream>
#include "raylib.h"
#include "Polygon.h"
#include "PolygonManager.h"
#include "Point.h"
#include "Globals.h"

void mainLoop();

void Draw(Polygon& currentPolygon, const Vector2& lastPos, std::vector<Polygon>& polygons, std::vector<Point>& collisions, Vector2* collision, Color& collisionColor);

void MouseUpdate(Vector2& mouseDelta, Vector2& mouse, Polygon*& selectedPolygon, Polygon& currentPolygon, Vector2& lastPos);
