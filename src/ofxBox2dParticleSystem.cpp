//
//  ofxBox2dParticleSystem.cpp
//
//  Created by Atsushi Tadokoro on 8/23/14.
//
//

#include "ofxBox2dParticleSystem.h"

ofxBox2dParticleSystem::ofxBox2dParticleSystem(){
    flag = b2_waterParticle;
}

void ofxBox2dParticleSystem::setup(b2World * _b2world){
    ofColor color;
    color.set(127, 200, 255);
    setup(_b2world, 10000, 0.0, 6.0, 4.0, color);
}

void ofxBox2dParticleSystem::setup(b2World * _b2world, int _maxCount, float _lifetime, float _radius, float _particleSize, ofColor _color){
    b2dworld = _b2world;
    particleSystemDef.radius = _radius / OFX_BOX2D_SCALE;
    particleSystemDef.maxCount = _maxCount;
    lifetime = _lifetime;
    color = _color;

    particleSystem = b2dworld->CreateParticleSystem(&particleSystemDef);
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
    
    ofSetColor(color);
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
    pd.flags = flag;
    b2Vec2 position = b2Vec2(posx / OFX_BOX2D_SCALE, posy / OFX_BOX2D_SCALE);
    pd.position = position;
    pd.velocity.Set(velx / OFX_BOX2D_SCALE, vely / OFX_BOX2D_SCALE);
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
void ofxBox2dParticleSystem::setColor(ofColor _color){
    color = _color;
}
void ofxBox2dParticleSystem::setParticleFlag(b2ParticleFlag _flag){
    flag = _flag;
}


int ofxBox2dParticleSystem::getParticleCount(){
    return particleSystem->GetParticleCount();
}