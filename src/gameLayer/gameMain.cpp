#include <iostream>
#include <raylib.h>
#include <fstream>
#include <vector>
#include <randomStuff.h>
#include <gameMap.h>


#include <raymath.h>

struct VisualiserData
{

	IntMap intMap;
	Camera2D camera;

}visData;


bool initGame() {

	int width = 128;
	int height = 128;

	visData.intMap.create(width, height);

	visData.camera.target = { 0,0 }; //world-space centre of view, we will use this as the camera position
	visData.camera.rotation = 0.0f;
	visData.camera.zoom = 50.0f;

	return true;
}

bool updateGame() {
	
	float deltaTime = GetFrameTime();
	//limits max deltaTime to 5 frames per second to prevent jumping
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	visData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	
	//20 blocks per second
	if (IsKeyDown(KEY_LEFT)) visData.camera.target.x -= 20.f * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) visData.camera.target.x += 20.f * deltaTime;
	if (IsKeyDown(KEY_UP)) visData.camera.target.y -= 20.f * deltaTime;
	if (IsKeyDown(KEY_DOWN)) visData.camera.target.y += 20.f * deltaTime;

	if (IsKeyDown(KEY_W)) { visData.camera.zoom  += 20.f * deltaTime; }
	if (IsKeyDown(KEY_S)) { visData.camera.zoom -= 20.f * deltaTime; }

	BeginMode2D(visData.camera);

	Vector2 topLeftView = GetScreenToWorld2D({ 0, 0 }, visData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({ (float)GetScreenWidth(), (float)GetScreenHeight() }, visData.camera);

	//adds padding so covers a little more than the visible area
	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x + 1);
	int startYView = (int)floorf(topLeftView.y - 1);
	int endYView = (int)ceilf(bottomRightView.y + 1);

	//makes sure values wont exceed max and min bounds, all clmap does is places the values within these bounds
	startXView = Clamp(startXView, 0, visData.intMap.w - 1); //Clamp(value, min, max)
	endXView = Clamp(endXView, 0, visData.intMap.w - 1);

	startYView = Clamp(startYView, 0, visData.intMap.h - 1);
	endYView = Clamp(endYView, 0, visData.intMap.h - 1);

	for (int y = startYView; y < endYView; ++y) {
		for (int x = startXView; x < endXView; ++x) {

			auto& i = visData.intMap.getIntUnsafe(x, y);

			std::ranlux24_base rng(hash(x, y));

			i = getRandomInt(rng, 0, 1);

			if (i == 0) {

				DrawRectangle(x, y, 1, 1, BLACK);
			}
			else if (i = 1) {
				
				DrawRectangle(x, y, 1, 1, WHITE);
			}
		}
	}
	
	EndMode2D();

	DrawFPS(10, 10);

	return true;
}

void closeGame() {
	std::cout << "\n\nCLOSED!!!!!!!\n\n";
}