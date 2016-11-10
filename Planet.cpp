
#include "Planet.h"

const string Planet::planet_images[] = { "MercuryTexture.jpg", "VenusTexture.jpg", "EarthTexture.jpg", "MarsTexture.jpg",
								 "SaturnTexture.jpg", "JupiterTexture.jpg", "NeptuneTexture.jpg", "UranusTexture.jpg" };

Planet::Planet(int pl_image, string pl_song) {
	sphere = new ofSpherePrimitive();
	image.loadImage(planet_images[pl_image]);
	sphere->mapTexCoords(0, 0, image.getWidth(), image.getHeight());
	float theta = ofRandom(0, 2 * M_PI);
	sphere->setPosition(0, 0, 0);
	center.set(MIN_RADIUS * sin(theta), MIN_RADIUS * cos(theta), MAX_DEPTH);
	sphere->setRadius(ofRandom(PLANET_MIN_RADIUS, PLANET_MAX_RADIUS));
	rotationState = 0;
	rotation = ofRandom(PLANET_MIN_ROTATION, PLANET_MAX_ROTATION);
	//soundPlayer.loadSound(pl_song);
	//soundPlayer.play();
}

Planet::~Planet() {
	//soundPlayer.stop();
	delete sphere;
}

void Planet::draw() {
	ofPushMatrix();
	ofTranslate(center);
	ofRotateY(rotationState);
	ofSetColor(255 * prop);
	image.bind();
	sphere->draw();
	image.unbind();
	ofPopMatrix();
}

void Planet::update(int speed) {
	center.set(center.x, center.y, center.z + speed);
	rotationState += rotation;
	float dist = abs(getPosition().z / (float) MAX_DEPTH);
	prop = 1.0 / (1.0 + pow(M_E, -STEEPNESS * (-dist + OFFSET)));
	//soundPlayer.setVolume(prop);
	//if (!soundPlayer.isPlaying()) soundPlayer.play();
}

ofPoint Planet::getPosition() {
	return center;
}

void Planet::setPosition(int x, int y, int z) {
	sphere->setPosition(x, y, z);
}