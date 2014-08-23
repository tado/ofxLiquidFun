//
//  ofxBox2dParticleSystem.h
//
//  Created by Atsushi Tadokoro on 8/23/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"

class ofxBox2dParticleSystem: public ofxBox2dBaseShape {
    
private:
    b2World * b2dworld;
    
public:
    b2ParticleSystemDef particleSystemDef;
    b2ParticleSystem* particleSystem;
	ofVboMesh mesh;
    float particleSize;
    float lifetime;
    ofColor color;
    b2ParticleFlag flag;
	
	ofxBox2dParticleSystem();
    void setup(b2World * b2dworld);
    void setup(b2World * b2world, int maxCount, float lifetime, float radius, float particleSize, ofColor color);
    void draw();

    void createParticle(ofVec2f position, ofVec2f velocity);
    void createParticle(float position_x, float position_y, float velocisty_x, float velocisty_y);
    void setRadius(float radius);
    void setMaxCount(int maxCount);
    void setParticleLifetime(float lifetime);
    void setColor(ofColor color);
    void setParticleFlag(b2ParticleFlag flag);
};
