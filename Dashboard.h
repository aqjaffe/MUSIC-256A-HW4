#include "ofMain.h"
#include "Constants.h"

class Dashboard
{
public:
	Dashboard();
	~Dashboard();
	void update(int speed);
	void draw();

private:
	ofPlanePrimitive dash;
	ofImage metal;
	ofTrueTypeFont digital;
	int speed;
};

