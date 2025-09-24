#include "PolygonManager.h"

bool PointLineCollision(Line line, Vector2 point)
{
	float x0 = line.start.x;
	float y0 = line.start.y;
	float x1 = line.end.x;
	float y1 = line.end.y;

	bool isHigh = false;

	float dx;
	float dy;

	float xi = 1.0f;
	float yi = 1.0f;

	float temp = 0.0f;


	if (abs(y1 - y0) < abs(x1 - x0)) {
		isHigh = false;
		if (x0 > x1) {
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
	}
	else {
		isHigh = true;
		if (y0 > y1) {
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
	}

	dx = x1 - x0;
	dy = y1 - y0;
	if (isHigh) {

		xi = 1.0f;

		float x = 0.0f;

		float d = (2.0f * dx) - dy;

		if (dx < 0.0f) {
			xi = -1.0f;
			dx = -dx;
		}
		d = (2.0f * dx) - dy;
		x = x0;

		for (float y = y0; y <= y1; y++)
		{

			if (x == point.x && y == point.y) {
				return true;
			}
			if (d > 0.0f) {
				x = x + xi;
				d = d + (2.0f * (dx - dy));
			}
			else {
				d = d + 2.0f * dx;
			}
		}
	}
	else {
		yi = 1.0f;

		float y = 0.0f;

		float d = (2.0f * dx) - dy;

		if (dy < 0.0f) {
			yi = -1.0f;
			dy = -dy;
		}
		d = (2.0f * dy) - dx;
		y = y0;

		for (float x = x0; x <= x1; x++)
		{
			if (x == point.x && y == point.y) {
				return true;
			}
			if (d > 0.0f) {
				y = y + yi;
				d = d + (2.0f * (dy - dx));
			}
			else {
				d = d + 2.0f * dy;
			}
		}
	}
	return false;
}

bool LinesCollision(Line line0, Line line1, Vector2* collision)
{
	float x0 = line0.start.x;
	float y0 = line0.start.y;
	float x1 = line0.end.x;
	float y1 = line0.end.y;

	bool isHigh = false;

	float dx;
	float dy;

	float xi = 1.0f;
	float yi = 1.0f;

	float temp = 0.0f;


	if (abs(y1 - y0) < abs(x1 - x0)) {
		isHigh = false;
		if (x0 > x1) {
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
	}
	else {
		isHigh = true;
		if (y0 > y1) {
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
	}

	dx = x1 - x0;
	dy = y1 - y0;
	if (isHigh) {

		xi = 1.0f;

		float x = 0.0f;

		float d = (2.0f * dx) - dy;

		if (dx < 0.0f) {
			xi = -1.0f;
			dx = -dx;
		}
		d = (2.0f * dx) - dy;
		x = x0;

		for (float y = y0; y <= y1; y++)
		{

			if (PointLineCollision(line1, { (float)x,(float)y })) {
				collision->x = x;
				collision->y = y;
				return true;
			}
			if (d > 0.0f) {
				x = x + xi;
				d = d + (2.0f * (dx - dy));
			}
			else {
				d = d + 2.0f * dx;
			}
		}
	}
	else {
		yi = 1.0f;

		float y = 0.0f;

		float d = (2.0f * dx) - dy;

		if (dy < 0.0f) {
			yi = -1.0f;
			dy = -dy;
		}
		d = (2.0f * dy) - dx;
		y = y0;

		for (float x = x0; x <= x1; x++)
		{
			if (PointLineCollision(line1, { (float)x,(float)y })) {
				collision->x = x;
				collision->y = y;
				return true;
			}
			if (d > 0.0f) {
				y = y + yi;
				d = d + (2.0f * (dy - dx));
			}
			else {
				d = d + 2.0f * dy;
			}
		}
	}
	return false;
}

bool CircleLineCollision(Vector2 center, float radius, Line line)
{

	float x0 = line.start.x;
	float y0 = line.start.y;
	float x1 = line.end.x;
	float y1 = line.end.y;

	bool isHigh = false;

	float dx;
	float dy;

	float xi = 1.0f;
	float yi = 1.0f;

	float temp = 0.0f;


	if (abs(y1 - y0) < abs(x1 - x0)) {
		isHigh = false;
		if (x0 > x1) {
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
	}
	else {
		isHigh = true;
		if (y0 > y1) {
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
	}

	dx = x1 - x0;
	dy = y1 - y0;
	if (isHigh) {

		xi = 1.0f;

		float x = 0.0f;

		float d = (2.0f * dx) - dy;

		if (dx < 0.0f) {
			xi = -1.0f;
			dx = -dx;
		}
		d = (2 * dx) - dy;
		x = x0;

		for (float y = y0; y <= y1; y++)
		{

			if (PointsDistance(x, y, center.x, center.y) < radius) {
				return true;
			}
			if (d > 0.0f) {
				x = x + xi;
				d = d + (2.0f * (dx - dy));
			}
			else {
				d = d + 2.0f * dx;
			}
		}
	}
	else {
		yi = 1.0f;

		float y = 0.0f;

		float d = (2.0f * dx) - dy;

		if (dy < 0.0f) {
			yi = -1.0f;
			dy = -dy;
		}
		d = (2.0f * dy) - dx;
		y = y0;

		for (float x = x0; x <= x1; x++)
		{
			if (PointsDistance(x, y, center.x, center.y) < radius) {
				return true;
			}
			if (d > 0.0f) {
				y = y + yi;
				d = d + (2.0f * (dy - dx));
			}
			else {
				d = d + 2 * dy;
			}
		}
	}
	return false;
}

float PointsDistance(float x0, float y0, float x1, float y1)
{
	return sqrt(((abs(x0 - x1)) * abs(x0 - x1)) + ((abs(y0 - y1)) * abs(y0 - y1)));
}


float PointsDistance(Line line)
{
	return PointsDistance(line.start.x, line.start.y, line.end.x, line.end.y);
}
