#pragma once
#define resx 800
#define resy 600

#include "coregraphic.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "sticky.hpp"

#include <vector>
#include <string>
using namespace std;

class coregame {
private:
	struct dir {
		int dx;
		int dy;
		int x;
		int y;
		dir(int dx, int dy, int x, int y) {
			this->dx = dx;
			this->dy = dy;
			this->x = x;
			this->y = y;
		}
	};
	scene* game_scene;
	snake* player;
	vector<food> foods;
	vector<sticky> stickies;
	vector<pair<int, dir>> signal;
	char key[256];
	void init_snake() {
		if (player) {
			delete player;
			player = NULL;
		}
		player = new snake(1);
	}
	void drawframe() {
		DrawBox(0, 0, resx, resy,
			GetColor(188, 231, 241),
			1);
		DrawCircle(
			player->cells[0].x,
			player->cells[0].y,
			10,
			RGB(48, 48, 48),
			1,
			1);
		for (int i = 1; i < player->getCellCount(); i++) {
			DrawCircle(
				player->cells[i].x,
				player->cells[i].y,
				7,
				player->cells[i].color,
				1,
				1);
		}
		for (unsigned int i = 0; i < foods.size(); i++) {
			foods[i].r -= foods[i].fading;
			if (foods[i].fading && foods[i].r == 0) {
				foods.erase(foods.begin() + i, foods.begin() + i + 1);
				i--;
				continue;
			}
			if (foods[i].pending != foods[i].r
				&& !foods[i].fading)
				foods[i].r++;
			DrawCircle(
				foods[i].x,
				foods[i].y,
				foods[i].r,
				foods[i].color,
				1,
				1
			);
		}
		for (unsigned int i = 0; i < stickies.size(); i++) {
			stickies[i].interval--;
			if (stickies[i].interval == 0) {
				stickies.erase(stickies.begin() + i, stickies.begin() + i + 1);
				i--;
				continue;
			}
			DrawString(
				stickies[i].x,
				stickies[i].y,
				stickies[i].text.c_str(),
				RGB(0, 0, 0),
				0);
		}
	}
	int abs(int x) {
		return x < 0 ? -x : x;
	}
	void docellsmove() {
		for (unsigned int i = 0; i < signal.size(); i++) {
			if (player->cells[signal[i].first].x == signal[i].second.x
				&& player->cells[signal[i].first].y == signal[i].second.y) {
				player->cells[signal[i].first].dx = signal[i].second.dx;
				player->cells[signal[i].first].dy = signal[i].second.dy;
				signal[i].first++;
				if (signal[i].first >= player->getCellCount()) {
					signal.erase(signal.begin(), signal.begin() + 1);
					i--;
				}
			}
		}
		for (int i = 0; i < player->getCellCount(); i++) {
			player->cells[i].x += player->cells[i].dx * 3;
			player->cells[i].y += player->cells[i].dy * 3;
		}
	}
	void dofoodeating() {
		for (unsigned int i = 0; i < foods.size(); i++) {
			if (foods[i].fading == 0 
				&& abs(player->cells[0].x - foods[i].x) < 15
				&& abs(player->cells[0].y - foods[i].y) < 15) {
				// ate something
				foods[i].fading = 1;
				player->addcell(foods[i].color);
				addsticky(foods[i].x, foods[i].y, 100,
					L"Level Up!(｡･ω･｡)ﾉ♡");
			}
		}
	}
	void addsignal(int dx, int dy, int x, int y) {
		dir d(dx, dy, x, y);
		pair<int, dir> p(0, d);
		signal.push_back(p);
	}
	void addsticky(int x, int y, int interval, wstring text) {
		sticky s(x, y, interval, text);
		stickies.push_back(s);
	}
	void gameloop() {
		static int key_on[4] = { 0 };
		while (true) {
			GetHitKeyStateAll(key);
			if (!key_on[1] && !key_on[0] && key[KEY_INPUT_RIGHT]) {
				addsignal(1, 0, player->cells[0].x, player->cells[0].y);
				key_on[0] = 1;
				key_on[1] = key_on[2] = key_on[3] = 0;
			}
			else if (!key_on[0] && !key_on[1] && key[KEY_INPUT_LEFT]) {
				addsignal(-1, 0, player->cells[0].x, player->cells[0].y);
				key_on[1] = 1;
				key_on[0] = key_on[2] = key_on[3] = 0;
			}
			else if (!key_on[3] && !key_on[2] && key[KEY_INPUT_UP]) {
				addsignal(0, -1, player->cells[0].x, player->cells[0].y);
				key_on[2] = 1;
				key_on[1] = key_on[0] = key_on[3] = 0;
			}
			else if (!key_on[2] && !key_on[3] && key[KEY_INPUT_DOWN]) {
				addsignal(0, 1, player->cells[0].x, player->cells[0].y);
				key_on[3] = 1;
				key_on[1] = key_on[2] = key_on[0] = 0;
			}

			if (foods.size() < 7)
				foods.push_back(food::randfood(resx, resy));

			docellsmove();
			dofoodeating();
			Sleep(1);
			SetDrawScreen(DX_SCREEN_BACK);
			ClearDrawScreen();
			drawframe();
			ScreenFlip();
		}
	}
public:
	coregame() {
		game_scene = new scene(resx, resy);
		game_scene->create();
	}
	~coregame() {
		delete game_scene;
	}
	void game_start() {
		init_snake();
		DrawBox(0, 0,
			resx,
			resy,
			RGB(195, 195, 195),
			1);
		SetFontSize(16);
		DrawString(
			resx / 2 - 6 * 16,
			resy / 2 - 30,
			L"Press any key to start!", RGB(0, 0, 0));
		WaitKey();
		food::init();
		gameloop();
	}
};
