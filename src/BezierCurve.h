//
//  BezierCurve.h
//  BezierShader
//
//  Created by Matthew Fargo on 2014/06/01.
//
//

#ifndef __BezierShader__BezierCurve__
#define __BezierShader__BezierCurve__

#include "ofMain.h"
#include "ofxTweener.h"

class BezierCurve {
public:
	BezierCurve(ofVec3f anchorA, ofVec3f anchorB, ofVec3f handleA, ofVec3f handleB, ofFloatColor startColor, ofFloatColor endColor);
	virtual ~BezierCurve();

    void    update();
    void    drawWithShader(ofShader * shader);
    
private:
    ofVec3f _anchorA;
    ofVec3f _anchorB;
    ofVec3f _handleA;
    ofVec3f _handleB;
    ofFloatColor _startColor;
    ofFloatColor _endColor;
    
    
    void    _nextTween(float * val);
    void    _onTweenComplete(TweenEvent & e);
    
    vector<float *>   _needsUpdate;
};

#endif /* defined(__BezierShader__BezierCurve__) */
