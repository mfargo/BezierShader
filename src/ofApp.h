#pragma once

#include "ofMain.h"
#include "BezierCurve.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);

private:
    
    ofEasyCam               _camera;
    ofShader                _shader;
    vector<BezierCurve *>   _curves;

    
};
