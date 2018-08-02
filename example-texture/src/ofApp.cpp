#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackgroundHex(0x00000);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.setFPS(30.0);
    box2d.createBounds();
    
    ofColor color;
    color.set(255);
    //particles.particleSystemDef.
    particles.setParticleFlag(b2_tensileParticle);
    particles.loadImage("particle32.png");
    particles.setup(box2d.getWorld(), 20000, 60.0, 6.0, 42.0, color);
}

//--------------------------------------------------------------
void ofApp::update() {
    box2d.update();
}


//--------------------------------------------------------------
void ofApp::draw() {
    ofBackgroundGradient(ofColor(0), ofColor(63), OF_GRADIENT_LINEAR);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    particles.draw();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    string info = "";
    info += "Mouse Drag for particles\n";
    info += "Total Particles: "+ofToString(particles.getParticleCount())+"\n\n";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    ofSetHexColor(0xffffff);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    for (int i = 0; i < 20; i++) {
        float radius = ofRandom(60, 80);
        float x = cos(ofRandom(PI * 2.0)) * radius + mouseX;
        float y = sin(ofRandom(PI * 2.0)) * radius + mouseY;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(0, 0);
        ofColor color;
        int hue = int(ofGetFrameNum() / 4.0) % 255;
        color.setHsb(hue, 180, 200);
        particles.setColor(color);
        particles.createParticle(position, velocity);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
}

