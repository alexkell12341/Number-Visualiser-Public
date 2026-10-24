#include <iostream>
#include <raylib.h>
#include <fstream>
#include <vector>
#include <randomStuff.h>
#include <gameMap.h>

struct VisualiserData
{

	IntMap intMap;
	Camera2D camera;

}visData;


bool initGame() {

	int width = 800;
	int height = 800;

	visData.intMap.create(width, height);

	visData.camera.target = { 0,0 }; //world-space centre of view, we will use this as the camera position
	visData.camera.rotation = 0.0f;
	visData.camera.zoom = 500.0f;

	return true;
}

bool updateGame() {
	
	float deltaTime = GetFrameTime();
	//limits max deltaTime to 5 frames per second to prevent jumping
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	visData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	
	//7 blocks per second
	if (IsKeyDown(KEY_LEFT)) visData.camera.target.x -= 7.f * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) visData.camera.target.x += 7.f * deltaTime;
	if (IsKeyDown(KEY_UP)) visData.camera.target.y -= 7.f * deltaTime;
	if (IsKeyDown(KEY_DOWN)) visData.camera.target.y += 7.f * deltaTime;

	if (IsKeyDown(KEY_W)) { visData.camera.zoom  += 50.f * deltaTime; }
	if (IsKeyDown(KEY_S)) { visData.camera.zoom -= 50.f * deltaTime; }


	for (int y = 0; y < visData.intMap.h; ++y) {
		for (int x = 0; x < visData.intMap.w; ++x) {

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

	return true;
}

void closeGame() {
	std::cout << "\n\nCLOSED!!!!!!!\n\n";
}