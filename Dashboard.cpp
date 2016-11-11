#include "Dashboard.h"

Dashboard::Dashboard() {
    dash.setPosition(0, 0, 0);
    spectrum.setPosition(300, -235, 0);
    screen.setPosition(800, -235, 0);
    metal.loadImage("dirty-metal-surface.jpg");
    colors.loadImage("color-spectrum.png");
    dash.mapTexCoords(0, 0, metal.getWidth(), metal.getHeight());
    spectrum.mapTexCoords(0, 0.33 * colors.getHeight(),
                          colors.getWidth(), 0.67 * colors.getHeight());
    digital.loadFont("DS-DIGI.ttf", 32);
}

Dashboard::~Dashboard() {
    //s
}

void Dashboard::update(int speed) {
    this->speed = speed;
}

void Dashboard::draw() {
    ofDisableDepthTest();
    int wh = ofGetWindowHeight();
    int ww = ofGetWindowWidth();
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(0, wh * (1 + DASH_HEIGHT), 0);
    dash.set(2 * ww, wh * (1 - DASH_HEIGHT));
    spectrum.set(0.4 * ww, wh * 0.14);
    screen.set(0.4 * ww, wh * 0.14);
    
    metal.bind();
    dash.draw();
    metal.unbind();
    
    colors.bind();
    spectrum.draw();
    colors.unbind();
    
    ofSetColor(0, 0, 20);
    screen.draw();
    
    ofSetColor(255, 255, 255);
    string v = "Velocity:\n" + std::to_string(speed * SPEED_CONVERSION + ofRandom(-SPEED_NOISE, SPEED_NOISE)) + " m/s";
    digital.drawString(v, 650, -240);
    
    ofPopMatrix();
    ofPopStyle();
    
    ofEnableDepthTest();
}