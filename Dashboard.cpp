#include "Dashboard.h"

Dashboard::Dashboard() {
	dash.setPosition(0, 0, 0);
	metal.loadImage("dirty-metal-surface.jpg");
	dash.mapTexCoords(0, 0, metal.getWidth(), metal.getHeight());

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

	/*
	ofPushMatrix();
	ofPushStyle();
	string v = "Velocity:\n" + std::to_string(speed * SPEED_CONVERSION + ofRandom(-SPEED_NOISE, SPEED_NOISE)) + " m/s";
	digital.drawString(v, ww - digital.stringWidth(v), 50);
	ofPopMatrix();
	ofPopStyle();
	*/
	
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(0, wh * (1 + DASH_HEIGHT), 0);
	dash.set(2 * ww, wh * (1 - DASH_HEIGHT));

	metal.bind();
	//dash.draw();
	metal.unbind();

	ofPopMatrix();
	ofPopStyle();

	string v = "Velocity:\n" + std::to_string(speed * SPEED_CONVERSION + ofRandom(-SPEED_NOISE, SPEED_NOISE)) + " m/s";
	digital.drawString(v, 0, 50);

	ofEnableDepthTest();
}