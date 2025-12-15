#include "MainLoopManager.h"

void mainLoop()
{
	int screenWidth = 1600;
	int screenHeight = 900;
	int fps = 60;

	float deltaTime = 0.0f;

	float holdThreshold = 0.2f;
	float heldTime = 0;

	int pointsCreated = 0;

	InitWindow(screenWidth, screenHeight, "TP01 Algebra - Borja Lia - entrega final");
	SetTargetFPS(fps);

	std::vector<Polygon> polygons;
	Polygon currentPolygon;

	Polygon* selectedPolygon = nullptr;

	Vector2 mouse;
	Vector2 lastPos = { 0,0 };
	Vector2 mouseDelta = { 0,0 };

	std::vector <Vector2> points;

	std::vector <Point> collisions;
	Vector2* collision = new Vector2();
	Color collisionColor = RED;

	Color currentColor;
	currentColor.a = 255;

	while (WindowShouldClose() == false)
	{
		deltaTime = GetFrameTime();

		MouseUpdate(mouseDelta, mouse, selectedPolygon, currentPolygon, lastPos);

		AddPoint(lastPos, mouse, selectedPolygon, currentPolygon, pointsCreated);

		SelectShape(mouse, selectedPolygon, polygons);

		CloseShape(currentPolygon, currentColor, polygons);

		DeleteFunctions(heldTime, deltaTime, holdThreshold, selectedPolygon, currentPolygon, lastPos, polygons);

		UpdateShapePos(selectedPolygon, mouseDelta);

		Draw(currentPolygon, lastPos, polygons, collisions, collision, collisionColor);
	}
	delete collision;
	CloseWindow();
}

void UpdateShapePos(Polygon* selectedPolygon, const Vector2& mouseDelta)
{
	if (selectedPolygon != nullptr)
	{
		selectedPolygon->offsetPoints(mouseDelta);
	}
}

void DeleteFunctions(float& heldTime, float deltaTime, float holdThreshold, Polygon*& selectedPolygon, Polygon& currentPolygon, Vector2& lastPos, std::vector<Polygon>& polygons)
{
	if (IsKeyDown(KEY_BACKSPACE))
	{
		heldTime += deltaTime;

		if (heldTime >= holdThreshold)
		{
			if (selectedPolygon == nullptr)
			{
				DeleteLastPoint(currentPolygon, lastPos);
			}
			heldTime -= deltaTime * 2.0f;
		}
	}
	else if (IsKeyReleased(KEY_BACKSPACE))
	{
		heldTime = 0.0f;
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		if (selectedPolygon == nullptr)
		{
			DeleteLastPoint(currentPolygon, lastPos);
		}
		else
		{
			DeleteShape(polygons, selectedPolygon);
		}
	}
}

void DeleteShape(std::vector<Polygon>& polygons, Polygon*& selectedPolygon)
{
	for (int i = 0; i < polygons.size(); i++)
	{
		std::cout << "Trying to delete: " << i << std::endl;
		if ((*selectedPolygon).getId() == polygons[i].getId())
		{
			polygons.erase(polygons.begin() + i);
			selectedPolygon = nullptr;
			std::cout << "Delete complete" << std::endl;
			i = polygons.size();
		}
	}
}

void DeleteLastPoint(Polygon& currentPolygon, Vector2& lastPos)
{
	currentPolygon.deletePoint();
	if (currentPolygon.size() > 1)
	{
		lastPos = currentPolygon.getPoints()[currentPolygon.size() - 1];
	}
	else
	{
		lastPos = { -100,-100 };
	}
}

void CloseShape(Polygon& currentPolygon, Color& currentColor, std::vector<Polygon>& polygons)
{
	if (IsKeyPressed(KEY_ENTER))
	{

		if (currentPolygon.size() > 2)
		{

			if (currentPolygon.addPoint(currentPolygon.getPoints()[0]))
			{

				currentColor.r = rand() % 255;
				currentColor.g = rand() % 255;
				currentColor.b = rand() % 255;

				currentPolygon.addId();

				currentPolygon.setColor(currentColor);
				polygons.push_back(currentPolygon);

				currentPolygon.Clear();
			}
		}
	}
}

void SelectShape(const Vector2& mouse, Polygon*& selectedPolygon, std::vector<Polygon>& polygons)
{
	if (IsMouseButtonPressed(1))
	{
		DrawCircleV(mouse, 15, RAYWHITE);
		if (selectedPolygon == nullptr)
		{
			for (int i = 0; i < polygons.size();i++)
			{

				for (int j = 0; j < polygons[i].getPoints().size() - 1; j++)
				{

					if (CircleLineCollision(mouse, 15, { polygons[i].getPoints()[j], polygons[i].getPoints()[j + 1] }))
					{

						selectedPolygon = &polygons[i];
						std::cout << "Id: " << selectedPolygon->getId() << std::endl;
						std::cout << "size: " << selectedPolygon->size() << std::endl;
					}
				}
			}

		}
	}
	else if (IsMouseButtonReleased(1))
	{
		std::cout << "nullptr" << std::endl;
		selectedPolygon = nullptr;
	}
}

void AddPoint(Vector2& lastPos, const Vector2& mouse, Polygon*& selectedPolygon, Polygon& currentPolygon, int& pointsCreated)
{
	if (IsMouseButtonDown(0) && PointsDistance({ lastPos,mouse }) > 10)
	{
		if (selectedPolygon != nullptr)
		{
			selectedPolygon = nullptr;
		}
		else if (currentPolygon.addPoint(mouse))
		{
			pointsCreated++;
			std::cout << "New Point: " << pointsCreated << std::endl;
			lastPos = mouse;
		}
	}
	else
	{
		pointsCreated = 0;
	}
}

void Draw(Polygon& currentPolygon, const Vector2& lastPos, std::vector<Polygon>& polygons, std::vector<Point>& collisions, Vector2* collision, Color& collisionColor)
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (!currentPolygon.getPoints().empty())
	{
		DrawCircleV(lastPos, 10, RED);
		currentPolygon.Draw(WHITE);
	}

	for (int i = 0;i < polygons.size();i++)
	{
		polygons[i].Draw();
	}

	collisions.clear();

	for (int i = 0; i < polygons.size(); i++)
	{
		for (int j = i + 1; j < polygons.size(); j++)
		{
			Polygon& polyA = polygons[i];
			Polygon& polyB = polygons[j];

			for (int a = 0; a < polyA.size() - 1; a++)
			{
				for (int b = 0; b < polyB.size() - 1; b++)
				{
					Line lineA = { polyA.getPoints()[a], polyA.getPoints()[a + 1] };
					Line lineB = { polyB.getPoints()[b], polyB.getPoints()[b + 1] };

					if (LinesCollision(lineA, lineB, collision))
					{
						collisionColor.r = (polyA.getColor().r / 2) + (polyB.getColor().r / 2);
						collisionColor.g = (polyA.getColor().g / 2) + (polyB.getColor().g / 2);
						collisionColor.b = (polyA.getColor().b / 2) + (polyB.getColor().b / 2);

						collisions.push_back({ (*collision), collisionColor });
					}
				}
			}
		}
	}

	for (int i = 0; i < collisions.size();i++)
	{
		DrawCircleV(collisions[i].pos, 10, collisions[i].color);
	}

	EndDrawing();
}

void MouseUpdate(Vector2& mouseDelta, Vector2& mouse, Polygon*& selectedPolygon, Polygon& currentPolygon, Vector2& lastPos)
{
	mouseDelta = GetMouseDelta();
	mouse = GetMousePosition();

	if (IsKeyDown(KEY_SPACE))
	{
		if (selectedPolygon != nullptr)
		{
			selectedPolygon = nullptr;
		}
		else if (currentPolygon.addPoint(mouse))
		{
			lastPos = mouse;
		}
	}
}
