#pragma once

#include <iostream>
#include "raylib.h"
#include "Polygon.h"
#include "PolygonManager.h"
#include "Point.h"
#include "Globals.h"

void mainLoop();

void UpdateShapePos(Polygon* selectedPolygon, const Vector2& mouseDelta);

void DeleteFunctions(float& heldTime, float deltaTime, float holdThreshold, Polygon*& selectedPolygon, Polygon& currentPolygon, Vector2& lastPos, std::vector<Polygon>& polygons);

void DeleteShape(std::vector<Polygon>& polygons, Polygon*& selectedPolygon);

void DeleteLastPoint(Polygon& currentPolygon, Vector2& lastPos);

void CloseShape(Polygon& currentPolygon, Color& currentColor, std::vector<Polygon>& polygons);

void SelectShape(const Vector2& mouse, Polygon*& selectedPolygon, std::vector<Polygon>& polygons);

void AddPoint(Vector2& lastPos, const Vector2& mouse, Polygon*& selectedPolygon, Polygon& currentPolygon, int& pointsCreated);

void Draw(Polygon& currentPolygon, const Vector2& lastPos, std::vector<Polygon>& polygons, std::vector<Point>& collisions, Vector2* collision, Color& collisionColor);

void MouseUpdate(Vector2& mouseDelta, Vector2& mouse, Polygon*& selectedPolygon, Polygon& currentPolygon, Vector2& lastPos);
