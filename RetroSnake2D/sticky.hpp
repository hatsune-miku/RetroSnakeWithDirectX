#include <string>
using namespace std;
class sticky {
public:
	int x;
	int y;
	int interval;
	wstring text;
	sticky(int x, int y, int interval, wstring text) {
		this->x = x;
		this->y = y;
		this->interval = interval;
		this->text = text;
	}
};
