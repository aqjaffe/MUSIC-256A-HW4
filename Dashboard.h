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
    ofPlanePrimitive dash, spectrum, screen;
    ofImage metal, colors;
    ofTrueTypeFont digital;
    int speed;
};

