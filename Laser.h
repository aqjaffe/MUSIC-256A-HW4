#include "ofMain.h"
#include "Constants.h"

class Laser
{
public:
	Laser(int baseX, int baseY);
	~Laser();
	void draw(int hue);
	void update(int mouseX, int mouseY);

private:
	ofPolyline* rays[LASER_DIV];
	int baseX;
	int baseY;
	int baseZ;
	int mouseX;
	int mouseY;
	int mouseZ;
};

