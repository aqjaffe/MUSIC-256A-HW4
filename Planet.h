
#include "ofMain.h"
#include "Constants.h"
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>


class Planet {
public:
	Planet(int pl_image, string pl_song);
	~Planet();
	void draw();
	void update(int speed);
	ofPoint getPosition();
	void setPosition(int x, int y, int z);

private:
	static string const planet_images[];
	ofSpherePrimitive* sphere;
	ofPoint center;
	ofImage image;
	int rotation;
	int rotationState;
	//ofSoundPlayer soundPlayer;
	float prop;
};

