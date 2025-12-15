#include "PolygonManager.h"

bool LinesCollision(Line line0, Line line1, Vector2* collision)
{
	float x1 = line0.start.x, y1 = line0.start.y;
	float x2 = line0.end.x, y2 = line0.end.y;
	float x3 = line1.start.x, y3 = line1.start.y;
	float x4 = line1.end.x, y4 = line1.end.y;

	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	if (std::abs(den) < 1e-5f)
	{
		return false;
	}

	float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		if (collision != nullptr)
		{
			collision->x = x1 + t * (x2 - x1);
			collision->y = y1 + t * (y2 - y1);
		}
		return true;
	}

	return false;
}

bool CircleLineCollision(Vector2 center, float radius, Line line)
{
	float lineLen = PointsDistance(line);

	if (lineLen == 0)
	{
		return PointsDistance(center.x, center.y, line.start.x, line.start.y) <= radius;
	}

	float dx = line.end.x - line.start.x;
	float dy = line.end.y - line.start.y;

	float t = ((center.x - line.start.x) * dx + (center.y - line.start.y) * dy) / (lineLen * lineLen);

	t = std::max(0.0f, std::min(1.0f, t));

	float closestX = line.start.x + t * dx;
	float closestY = line.start.y + t * dy;

	return PointsDistance(center.x, center.y, closestX, closestY) <= radius;
}

float PointsDistance(float x0, float y0, float x1, float y1)
{
	return sqrt(((abs(x0 - x1)) * abs(x0 - x1)) + ((abs(y0 - y1)) * abs(y0 - y1)));
}


float PointsDistance(Line line)
{
	return PointsDistance(line.start.x, line.start.y, line.end.x, line.end.y);
}
