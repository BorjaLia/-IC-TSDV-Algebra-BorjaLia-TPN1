#pragma once
#include "Globals.h"

bool PointLineCollision(Line line, Vector2 point);
bool LinesCollision(Line line0, Line line1, Vector2* collision);
bool CircleLineCollision(Vector2 center, float radius, Line line);
float PointsDistance(float x0, float y0, float x1, float y1);
float PointsDistance(Line line);