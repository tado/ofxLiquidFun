//
//  ofxBox2dParticleSystem.cpp
//  example
//
//  Created by Atsushi Tadokoro on 8/23/14.
//
//

#include "ofxBox2dParticleSystem.h"

ofxBox2dParticleSystem::ofxBox2dParticleSystem(){
    particleSize = 4.0;
    lifetime = 0.0;
}

void ofxBox2dParticleSystem::setup(b2World * _b2dworld){
    b2dworld = _b2dworld;
    particleSystem = b2dworld->CreateParticleSystem(&particleSystemDef);
    alive = true;
}

void ofxBox2dParticleSystem::draw(){
    ofFill();
    
    int32 particleCount = particleSystem->GetParticleCount();
    b2Vec2 *positnon = particleSystem->GetPositionBuffer();
    
    ofVboMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    for (int i = 0; i < particleCount; i++) {
        mesh.addVertex(ofVec2f(positnon[i].x, positnon[i].y));
    }
    
    ofSetColor(127,200,255);
    ofPushMatrix();
    ofScale(OFX_BOX2D_SCALE, OFX_BOX2D_SCALE);
    glPointSize(4.0);
    mesh.draw();
    ofPopMatrix();
}

void ofxBox2dParticleSystem::createParticle(ofVec2f position , ofVec2f velocity){
    createParticle(position.x, position.y, velocity.x, velocity.y);
}

void ofxBox2dParticleSystem::createParticle(float posx, float posy, float velx, float vely){
    b2ParticleDef pd;
    pd.flags = b2_waterParticle;
    pd.color.Set(0, 0, 255, 255);
    b2Vec2 position = b2Vec2(posx/OFX_BOX2D_SCALE, posy/OFX_BOX2D_SCALE);
    pd.position = position;
    pd.velocity.Set(velx/OFX_BOX2D_SCALE, vely/OFX_BOX2D_SCALE);
    if (lifetime > 0.0) {
        pd.lifetime = lifetime;
    }
    particleSystem->CreateParticle(pd);
}

void ofxBox2dParticleSystem::setRadius(float radius){
    particleSystemDef.radius = radius / OFX_BOX2D_SCALE;
}

void ofxBox2dParticleSystem::setMaxCount(int maxCount){
    particleSystemDef.maxCount = maxCount;
}

void ofxBox2dParticleSystem::setParticleLifetime(float _lifetime){
    lifetime = _lifetime;
}