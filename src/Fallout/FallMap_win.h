#pragma once

#include "SDL.h"
#include "../Utils/BaseWindow.h"
#include "FallMap.h"
#include <vector>
#include <string>

class FallMapWindow : public BaseWindow
{
public:
	FallMapWindow(bool visibility) : BaseWindow(visibility) { }
	void ExportFallMap(FallMap_t*& file);
	void DrawWin();
	void InitWin();
	void DestroyWin();
	void ProcessMenuBtn();
	void EnsureTilesLoaded();
private:
	std::string Filename = "test.map";
	FallMap_t* File = nullptr;
	std::vector<std::string> tiles_names;
};