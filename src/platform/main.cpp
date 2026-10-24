#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>
#include <gameMain.h>
#include <asserts.h>




int main(void)
{

	extern int g_width;
	g_width = 128;

	extern int g_height;
	g_height = 128;

	extern bool hasChanged;
	hasChanged = false;

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE); //no log output to console by raylib
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 800, "Test Window");

	SetExitKey(KEY_NULL); //Disable Esc from closing window
	//large fps leads to small deltaTime so imprecisions in calculations
	SetTargetFPS(240);

#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;

#pragma endregion

	if (!initGame()) {
		return 0; 
	}

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(RED);

#pragma region imgui
		rlImGuiBegin();

		//docking stuff
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

#pragma endregion

		

#pragma region imgui windows

		ImGui::Begin("Window Size");


		ImGui::SliderInt("Width", &g_width, 0, 500);

		ImGui::SliderInt("height", &g_height, 0, 500);

		if (ImGui::Button("Resize", { 256, 64 })) {
			hasChanged = true;
		}

		ImGui::End();
#pragma endregion

		if (!updateGame()) {
			CloseWindow();
		}

#pragma region imgui
		rlImGuiEnd();

#pragma endregion

		EndDrawing();
	}

	CloseWindow();

	closeGame();

#pragma region imgui
	rlImGuiShutdown();
#pragma endregion

	return 0;
}