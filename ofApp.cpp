#include "ofApp.h"

#define NEW_RAY_FREQ 0.8

#define RAY_MAX_LEN 600
#define RAY_MIN_LEN 300

#define TUBE_MIN_RADIUS 600
#define TUBE_MAX_RADIUS 2400

#define MAX_DEPTH 10000

#define DEFAULT_SPEED 25;
#define SPEED_CONVERSION 11.343
#define SPEED_NOISE 1
#define ACCELERATION 5

#define CHAR_WIDTH 10

//#define _USE_MATH_DEFINES
//#include <math.h>


//--------------------------------------------------------------
// setup() -- Setup our application
//--------------------------------------------------------------
void ofApp::setup(){
	speed = DEFAULT_SPEED;

    // Sync video refresh rate for our computer
    ofSetVerticalSync(true);
    
    // Set background color grayish
    ofBackground(30, 30, 40);
    
    // Tell OpenFrameworks to use smooth edges
    ofEnableSmoothing();
    
}

//--------------------------------------------------------------
void ofApp::update(){

	// Move existing rays back
	for (int i = rays.size() - 1; i >= 0; i--) {
		vector<ofPoint>::iterator it = rays.at(i)->begin();
		it->z += speed;
		(it + 1)->z += speed;
	}

	// Add a new ray at random
	float r = ofRandom(0, 1);
	if (r < NEW_RAY_FREQ) {
		ofPoint frontPt, endPt;
		float theta = ofRandom(0, 2 * M_PI);
		float len = ofRandom(RAY_MIN_LEN, RAY_MAX_LEN);
		float radius = ofRandom(TUBE_MIN_RADIUS, TUBE_MAX_RADIUS);
		ofPolyline* newRay = new ofPolyline();
		newRay->addVertex(radius * sin(theta), radius * cos(theta), -MAX_DEPTH);
		newRay->addVertex(radius * sin(theta), radius * cos(theta), -MAX_DEPTH + len);
		rays.push_back(newRay);
	}

	// Remove old rays
	for (int i = rays.size() - 1; i >= 0; i--) {
		vector<ofPoint>::iterator it = rays.at(i)->begin();
		if (it->z > 0) rays.erase(rays.begin() + i);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){    
    int wh = ofGetWindowHeight();   
	int ww = ofGetWindowWidth();

	ofPushStyle();
	ofPushMatrix();

		ofClear(0);
		string v = "Velocity: " + std::to_string(speed * SPEED_CONVERSION + ofRandom(-SPEED_NOISE, SPEED_NOISE)) + " m/s";
		int margin = v.size() * CHAR_WIDTH;
		ofDrawBitmapString(v , ww - margin, 100);

	ofPopStyle();
	ofPopMatrix();

	ofPushStyle();
    ofPushMatrix();

		ofTranslate(ww * 0.5, wh * 0.5, 0);

		ofSetLineWidth(2);
		ofNoFill();

		ofPushStyle();

			for (int i = rays.size() - 1; i >= 0; i--) {
				ofPolyline* ray = rays.at(i);
				int alpha = (int) 255 * (1.0 - pow(-ray->getVertices().at(0).z / (float) MAX_DEPTH, 0.4));
				ofSetColor(255, 255, 255, alpha);
				ray->draw();
			}

		ofPopStyle();

	ofPopStyle();
	ofPopMatrix();
}


//--------------------------------------------------------------
// audioIn() -- deal with incoming audio buffer
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 357) {
		speed += ACCELERATION;
	} else if (key == 359) {
		speed -= ACCELERATION;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
