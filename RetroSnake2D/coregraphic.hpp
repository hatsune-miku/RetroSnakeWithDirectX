#pragma once
#include <DxLib.h>
class scene {
private:
	int res_width;
	int res_height;
public:
	scene(int width, int height) {
		res_width = width;
		res_height = height;
	}
	int getResX() {
		return res_width;
	}
	int getResY() {
		return res_height;
	}
	bool create() {
		if (-1 == SetGraphMode(res_width, res_height, 32, 60))
			return false;
		ChangeWindowMode(TRUE);
		SetOutApplicationLogValidFlag(FALSE);
		if (-1 == DxLib_Init())
			return false;
		SetMainWindowText(L"RETRO SNAKE BY EGGTART");
		return true;
	}
};
