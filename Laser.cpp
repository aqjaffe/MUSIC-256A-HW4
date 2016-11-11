#include "Laser.h"

Laser::Laser(int baseX, int baseY) {
    this->baseX = baseX;
    this->baseY = baseY;
    baseZ = 0;
    for (int i = 0; i < LASER_DIV; i++) {
        rays[i] = new ofPolyline();
    }
}


Laser::~Laser() {
    for (int i = 0; i < LASER_DIV; i++) delete rays[i];
}

void Laser::draw(int hue) {
    ofEnableDepthTest();
    ofPushStyle();
    ofSetLineWidth(15);
    for (int i = 0; i < LASER_DIV; i++) {
        ofPushStyle();
        int alpha = 255 * (1 - i / (float)LASER_DIV);
        ofSetColor(ofColor::fromHsb(hue, SATURATION, BRIGHTNESS, alpha));
        rays[i]->draw();
        ofPopStyle();
    }
    ofPopStyle();
    ofDisableDepthTest();
}

void Laser::update(int mouseX, int mouseY) {
    for (int i = 0; i < LASER_DIV; i++) {
        rays[i]->clear();
    }
    this->mouseX = mouseX;
    this->mouseY = mouseY;
    mouseZ = LASER_CONTROL_DEPTH;
    int diffX = (mouseX - baseX) / LASER_DIV;
    int diffY = (mouseY - baseY) / LASER_DIV;
    int diffZ = LASER_CONTROL_DEPTH / LASER_DIV;
    for (int i = 0; i < LASER_DIV - 1; i++) {
        ofPoint pt(baseX + i * diffX, baseY + i * diffY, baseZ + i * diffZ);
        rays[i]->addVertex(pt);
        rays[i + 1]->addVertex(pt);
    }
}
