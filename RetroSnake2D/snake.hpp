#include <vector>
using namespace std;
static int cell_type_head = 0;
static int cell_type_cell = 1;
static int cell_type_unknown = -1;
class snake {
private:
	int length = 0;
	int posx = 0;
	int posy = 0;
	int dx = 0;
	int dy = 0;
	struct cell {
		int type = cell_type_unknown;
		int color = 0;
		int x = 0;
		int y = 0;
		int dx = 0;
		int dy = 0;
		cell(int type, int color, int x, int y) {
			this->type = type;
			this->color = color;
			this->x = x;
			this->y = y;
		}
	};
public:
	vector<cell> cells;

	snake(int init_len) {
		length = init_len;
		for (int i = 0; i < length; i++) {
			addcell(RGB(48, 48, 48));
		}
		posx = 0;
		posy = 0;
	}
	void addcell(int color) {
		cell c(cell_type_cell, color, 0, 0);
		int i = cells.size();
		if (i == 0) {
			c.type = cell_type_head;
			c.dx = 1;
			c.dy = 0;
		}
		else {
			c.x = cells[i - 1].x - cells[i - 1].dx * 18;
			c.y = cells[i - 1].y - cells[i - 1].dy * 18;
			c.dx = cells[i - 1].dx;
			c.dy = cells[i - 1].dy;
		}
		cells.push_back(c);
	}
	int getCellCount() {
		return cells.size();
	}
};
