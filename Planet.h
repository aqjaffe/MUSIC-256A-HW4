
#include "ofMain.h"
#include "Constants.h"
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>


class Planet {
public:
    Planet();
    ~Planet();
    void draw();
    void update(int speed);
    ofPoint getPosition();
    void setPosition(int x, int y, int z);
    bool colorMatches(ofColor laserColor);
    bool mouseOver(int x, int y);
    
private:
    ofSpherePrimitive* sphere;
    ofPoint center;
    int rotation;
    int rotationState;
    float prop;
    int hue;
    ofColor color;
};

