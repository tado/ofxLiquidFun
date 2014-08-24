#pragma once
#include "ofMain.h"
#include "ofxLiquidFun.h"

// -------------------------------------------------

class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void resized(int w, int h);
    
    ofxBox2d box2d;
    vector <ofPtr<ofxBox2dCircle> >	circles;
    vector <ofPtr<ofxBox2dRect> > boxes;
    ofxBox2dParticleSystem particles;       // LiquidFun particle system
};