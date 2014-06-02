//
//  BezierCurve.cpp
//  BezierShader
//
//  Created by Matthew Fargo on 2014/06/01.
//
//

#include "BezierCurve.h"

BezierCurve::BezierCurve(ofVec3f anchorA, ofVec3f anchorB, ofVec3f handleA, ofVec3f handleB, ofFloatColor startColor, ofFloatColor endColor) {
    _anchorA = anchorA;
    _anchorB = anchorB;
    _handleA = handleA;
    _handleB = handleB;
    _startColor = startColor;
    _endColor = endColor;
    
    _nextTween(&_handleA.y);
    _nextTween(&_handleB.y);
    _nextTween(&_anchorB.y);
}
BezierCurve::~BezierCurve() {}

void BezierCurve::update() {
    for (int i=0; i<_needsUpdate.size(); i++)
        _nextTween(_needsUpdate[i]);
    _needsUpdate.clear();
}

void BezierCurve::drawWithShader(ofShader * shader) {
    shader->setUniform3f("handleA", _handleA.x, _handleA.y, _handleA.z);
    shader->setUniform3f("handleB", _handleB.x, _handleB.y, _handleB.z);
    glBegin(GL_LINES);
    glColor4f(_startColor.r, _startColor.g, _startColor.b, _startColor.a);
    glVertex3f(_anchorA.x, _anchorA.y, _anchorA.z);
    glColor4f(_endColor.r, _endColor.g, _endColor.b, _endColor.a);
    glVertex3f(_anchorB.x, _anchorB.y, _anchorB.z);
    glEnd();
}

void BezierCurve::_nextTween(float * val) {
    Tween * t = Tweener.addTween((*val), ofRandom(ofGetHeight()), 3.f + ofRandom(3.f), &ofxTransitions::easeInOutCubic, 0, ofRandom(ofGetHeight()));
    ofAddListener(t->ON_COMPLETE, this, &BezierCurve::_onTweenComplete);
}

void BezierCurve::_onTweenComplete(TweenEvent & e) {
    _needsUpdate.push_back(e.getValue());
}