#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int u = ofGetFrameNum() * 3;
	for (int v = 0; v < 360; v += 3) {

		auto noise_location = this->make_point(300, 40, u, v);
		auto r = ofMap(ofNoise(glm::vec4(noise_location * 0.03, ofGetFrameNum() * .005)), 0, 1, 0, 120);

		vector<glm::vec3> vertices;

		vertices.push_back(this->make_point(300, r, u, v - 1));
		vertices.push_back(this->make_point(300, r, u, v + 1));
		vertices.push_back(this->make_point(300, r, u + 180, v + 1));
		vertices.push_back(this->make_point(300, r, u + 180, v - 1));

		ofFill();
		ofSetColor(0);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(255);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		u += 9;
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}