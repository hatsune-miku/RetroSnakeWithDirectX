#include <cmath>
#include <ctime>
#include <DxLib.h>
class food {
public:
	int x;
	int y;
	int pending = 0;
	int fading = 0;
	int r = 10;
	int color;
	static void init() {
		srand((unsigned int)time((time_t)NULL));
	}
	static food randfood(int width, int height, int r) {
		width -= 30;
		height -= 30;
		food f(rand() % width + 20, 
			rand() % height + 20, 
			r,
			RGB(rand() % 255,
				rand() % 255,
				rand() % 255));
		return f;
	}
	static food randfood(int width, int height) {
		int r = rand() % 15 + 8;
		return randfood(width, height, r);
	}
	food(int x, int y, int r, int color) {
		this->x = x;
		this->y = y;
		this->r = 0;
		this->color = color;
		this->pending = r;
	}
};
