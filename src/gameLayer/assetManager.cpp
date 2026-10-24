#include "assetManager.h"

void AssetManager::loadAll() {
	textures = LoadTexture(RESOURCES_PATH "visualiserTextures.png");
}