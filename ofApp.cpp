#include "ofApp.h"

void ofApp::setup(){
	speed = DEFAULT_SPEED;

	//soundPlayer.loadSound("Slyde_Sumthang-160.mp3");
	//soundPlayer.play();

    // Sync video refresh rate for our computer
    ofSetVerticalSync(true);
    
    // Set background color black
    ofBackground(0, 0, 0);
    
    // Tell OpenFrameworks to use smooth edges
    ofEnableSmoothing();

	ofEnableDepthTest();

	//ofSetFullscreen(true);

	lasers[0] = new Laser(ofGetWindowWidth() * 0.33, ofGetWindowHeight());
	lasers[1] = new Laser(ofGetWindowWidth() * 0.67, ofGetWindowHeight());

	// Setup the sound stream
	soundStream.setup(this, 0, MY_CHANNELS, MY_SRATE, MY_BUFFERSIZE, MY_NBUFFERS);

	// Resize and initialize left and right (audio) buffers...
	left.resize(MY_BUFFERSIZE, 0);
	right.resize(MY_BUFFERSIZE, 0);

	// Setup the fft
	//fft = ofxFft::create(MY_BUFFERSIZE, OF_FFT_WINDOW_HAMMING);
	fft = ofxFft::create(512, OF_FFT_WINDOW_HAMMING);
}

void ofApp::update(){
	// copied from ofBokeh:

	// Normalize the left channel waveform
	float maxValue = 0;
	for (int i = 0; i < left.size(); i++) {
		if (abs(left[i]) > maxValue) { maxValue = abs(left[i]); }
	}
	for (int i = 0; i < left.size(); i++) { left[i] /= maxValue; }

	// Take the FFT of the left channel
	fft->setSignal(&left[0]);

	// Get the magnitudes and copy them to audioBins
	float* fftData = fft->getAmplitude();

	// Now normalize the FFT magnitude values
	maxValue = 0;
	for (int i = 0; i < fft->getBinSize(); i++) {
		if (abs(fftData[i]) > maxValue) { maxValue = abs(fftData[i]); }
	}
	for (int i = 0; i < fft->getBinSize(); i++) { fftData[i] /= maxValue; }

	// get spectral centroid:
	centroid = 0;
	float normalizer = 0;
	for (int i = 0; i < fft->getBinSize(); i++) {
		//cout << std::to_string(fftData[i]).substr(0, 5) << "\t";
		centroid += fftData[i] * i * MY_SRATE / (fft->getBinSize() * 2.0);
		normalizer += i * MY_SRATE / (fft->getBinSize() * 2.0);
	}
	centroid /= normalizer;
	//centroid /= CENTROID_NORMALIZER;
	cout << centroid << endl;

	

	// resume original code

	dashboard.update(speed);

	// Move existing rays back
	for (int i = rays.size() - 1; i >= 0; i--) {
		vector<ofPoint>::iterator it = rays.at(i)->begin();
		it->z += speed;
		(it + 1)->z += speed;
	}
	for (int i = planets.size() - 1; i >= 0; i--) {
		planets.at(i)->update(speed);
	}

	// Add a new ray at random location
	float theta = ofRandom(0, 2 * M_PI);
	float len = ofRandom(RAY_MIN_LEN, RAY_MAX_LEN);
	float radius = ofRandom(MIN_RADIUS, MAX_RADIUS);
	ofPolyline* newRay = new ofPolyline();
	newRay->addVertex(radius * sin(theta), radius * cos(theta), MAX_DEPTH);
	newRay->addVertex(radius * sin(theta), radius * cos(theta), MAX_DEPTH + len);
	rays.push_back(newRay);

	// Remove old rays and planets
	for (int i = rays.size() - 1; i >= 0; i--) {
		vector<ofPoint>::iterator it = rays.at(i)->begin();
		if (it->z > MIN_DEPTH) {
			delete rays.at(i);
			rays.erase(rays.begin() + i);
		}
	}
	for (int i = planets.size() - 1; i >= 0; i--) {
		if (planets.at(i)->getPosition().z > MIN_DEPTH) {
			delete planets.at(i);
			planets.erase(planets.begin() + i);
		}
	}

	if (ofRandom(0, 1) < PLANET_APPEAR_PROB * speed) {
		Planet* pl = new Planet((int)ofRandom(0, 8), "sine.wav");
		planets.push_back(pl);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){    
    int wh = ofGetWindowHeight();   
	int ww = ofGetWindowWidth();

	ofClear(0);

	ofPushStyle();
    ofPushMatrix();

		ofTranslate(ww * 0.5, wh * 0.5, 0);

		ofSetLineWidth(2);
		ofNoFill();

		ofPushStyle();

			for (int i = planets.size() - 1; i >= 0; i--) {
				planets.at(i)->draw();
			}
			for (int i = rays.size() - 1; i >= 0; i--) {
				ofPolyline* ray = rays.at(i);
				int alpha = (int) 255 * (1.0 - pow(ray->getVertices().at(0).z / (float) MAX_DEPTH, 0.4));
				ofSetColor(255, 255, 255, alpha);
				ray->draw();
			}

		ofPopStyle();

	ofPopStyle();
	ofPopMatrix();

	dashboard.draw();

	lasers[0]->draw(centroid * 255);
	lasers[1]->draw(centroid * 255);
}


//--------------------------------------------------------------
// audioIn() -- deal with incoming audio buffer
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	// Write incoming audio to buffer. Note: samples are interleaved.
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2];
		right[i] = input[i * 2 + 1];
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 357) { //up arrow
		speed += ACCELERATION;
	} else if (key == 359) { //down arrow
		speed -= ACCELERATION;
	} else if (key == 'p') {
		Planet* pl = new Planet((int) ofRandom(0, 8), "sine.wav");
		planets.push_back(pl);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	lasers[0]->update(x, y);
	lasers[1]->update(x, y);
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
