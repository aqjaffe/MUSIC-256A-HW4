
#include "Planet.h"

Planet::Planet() {
    hue = ofRandom(0, 255);
    sphere = new ofSpherePrimitive();
    float theta = ofRandom(0, 2 * M_PI);
    sphere->setPosition(0, 0, 0);
    center.set(MIN_RADIUS * sin(theta), MIN_RADIUS * cos(theta), MAX_DEPTH);
    sphere->setRadius(ofRandom(PLANET_MIN_RADIUS, PLANET_MAX_RADIUS));
    rotationState = 0;
    rotation = ofRandom(PLANET_MIN_ROTATION, PLANET_MAX_ROTATION);
}

Planet::~Planet() {
    delete sphere;
}

void Planet::draw() {
    ofPushMatrix();
    ofTranslate(center);
    ofRotateY(rotationState);
    ofSetColor(color);
    sphere->draw();
    ofPopMatrix();
}

void Planet::update(int speed) {
    color = ofColor::fromHsb(hue, SATURATION, BRIGHTNESS, 255 * prop);
    center.set(center.x, center.y, center.z + speed);
    rotationState += rotation;
    float dist = abs(getPosition().z / (float) MAX_DEPTH);
    prop = 1.0 / (1.0 + pow(M_E, -STEEPNESS * (-dist + OFFSET)));
}

ofPoint Planet::getPosition() {
    return center;
}

void Planet::setPosition(int x, int y, int z) {
    sphere->setPosition(x, y, z);
}

bool Planet::colorMatches(ofColor laserColor) {
    return abs(laserColor.getHue() - color.getHue()) < COLOR_DIFF;
}

bool Planet::mouseOver(int x, int y) {
    return sqrt(pow(center.x + 0.5 * ofGetWindowWidth() - x, 2)
                + pow(center.y + 0.5 * ofGetWindowHeight() - y, 2)
                + pow((center.z - MAX_DEPTH)/MAX_DEPTH, 2)) < MOUSE_DIST;
}