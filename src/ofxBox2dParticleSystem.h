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
    b2ParticleGroupFlag groupFlag;
    ofImage textureImage;
    bool useTexture;
    
    ofxBox2dParticleSystem();
    void setup(b2World * b2dworld);
    void setup(b2World * b2dworld, int maxCount);
    void setup(b2World * b2world, int maxCount, float lifetime, float radius, float particleSize, ofColor color);
    void draw();
    
    int32 createParticle(ofVec2f position, ofVec2f velocity);
    int32 createParticle(float position_x, float position_y, float velocisty_x, float velocisty_y);

    b2ParticleGroup* createRectParticleGroup(ofVec2f position, ofVec2f size, ofColor color);
    b2ParticleGroup* createCircleParticleGroup(ofVec2f position, float radius, ofColor color);
    
    void loadImage(string fileName);
    
    void setRadius(float radius);
    void setParticleLifetime(float lifetime);
    void setColor(ofColor color);
    void setParticleFlag(b2ParticleFlag flag);
    void setParticleGroupFlag(b2ParticleGroupFlag flag);

    int getParticleCount();

    void applyForce( int32 particle_index, const ofVec2f& force ); 
    void applyForce( int32 particle_index, float force_x, float force_y ); 

};
