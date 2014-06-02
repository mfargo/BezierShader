#include "ofApp.h"

const int NUM_CURVES = 600;

void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetVerticalSync(false);
	ofEnableAlphaBlending();
    _shader.setGeometryInputType(GL_LINES);
	_shader.setGeometryOutputType(GL_LINE_STRIP);
	_shader.setGeometryOutputCount(1024);
	_shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");

    float r_depth = 200.f;
    for (int i=0; i<NUM_CURVES; i++) {
        ofColor startColor = ofColor().fromHsb(160, 255.f, 255.f);
        ofColor endColor = ofColor().fromHsb(12.f+ofRandom(55.f), 255.f, 255.f);
        _curves.push_back(new BezierCurve(ofVec3f(0, ofGetHeight()/2.f, 0.f),
                                          ofVec3f(ofGetWidth(), ofRandom(ofGetHeight()), ofRandom(-r_depth, r_depth)),
                                          ofVec3f(ofRandom(ofGetWidth()/2.f), ofRandom(ofGetHeight()), ofRandom(-r_depth, r_depth)),
                                          ofVec3f(ofGetWidth()/2.f+ofRandom(ofGetWidth()/2.f), ofRandom(ofGetHeight()), ofRandom(-r_depth, r_depth)),
                                          ofFloatColor(ofFloatColor(startColor.r/255.f, startColor.g/255.f, startColor.b/255.f)), ofFloatColor(endColor.r/255.f, endColor.g/255.f, endColor.b/255.f, 0.0))
                          );
    }
}

void ofApp::update() {
    Tweener.update();
    for (int i=0; i<_curves.size(); i++) _curves[i]->update();
}

void ofApp::draw() {
    ofBackgroundGradient(ofColor(10, 10, 10), ofColor(20, 20,20 ));
    ofSetLineWidth(3.f);

    _camera.setPosition(ofGetWidth()/2.f, ofGetHeight()/2.f, 800);
    _camera.begin();
    _shader.begin();
    ofSetColor(255);
    _shader.setUniform1i("iterations", 60);
    for (int i=0; i<_curves.size(); i++)
        _curves[i]->drawWithShader(&_shader);
    _shader.end();
    _camera.end();
}

void ofApp::keyPressed(int key){

}
