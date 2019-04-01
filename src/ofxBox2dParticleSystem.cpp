//
//  ofxBox2dParticleSystem.cpp
//
//  Created by Atsushi Tadokoro on 8/23/14.
//
//

#include "ofxBox2dParticleSystem.h"

ofxBox2dParticleSystem::ofxBox2dParticleSystem(){
    flag = b2_waterParticle;
    groupFlag = (b2ParticleGroupFlag)0;
}

void ofxBox2dParticleSystem::setup(b2World * _b2world){
    ofColor color;
    color.set(127, 200, 255);
    setup(_b2world, 10000, 0.0, 6.0, 4.0, color);
}

void ofxBox2dParticleSystem::setup(b2World * _b2world, int maxCount){
    ofColor color;
    color.set(127, 200, 255);
    setup(_b2world, maxCount, 0.0, 6.0, 4.0, color);
}

void ofxBox2dParticleSystem::setup(b2World * _b2world, int _maxCount, float _lifetime, float _radius, float _particleSize, ofColor _color){
    b2dworld = _b2world;
    particleSystemDef.radius = _radius / OFX_BOX2D_SCALE;
    particleSystemDef.maxCount = _maxCount;
    lifetime = _lifetime;
    particleSize = _particleSize;
    color = _color;
    
    particleSystem = b2dworld->CreateParticleSystem(&particleSystemDef);
}

void ofxBox2dParticleSystem::draw(){
    ofFill();
    
    int32 particleCount = particleSystem->GetParticleCount();
    b2Vec2 *positnon = particleSystem->GetPositionBuffer();
    b2ParticleColor *particleColor = particleSystem->GetColorBuffer();
    
    ofVboMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    for (int i = 0; i < particleCount; i++) {
        mesh.addVertex(glm::vec3(positnon[i].x, positnon[i].y, 0.f));
        mesh.addColor(ofFloatColor(particleColor[i].r / 255.0, particleColor[i].g / 255.0, particleColor[i].b / 255.0));
    }
    
    ofSetColor(255);
    ofEnablePointSprites();
    ofPushMatrix();
    ofScale(OFX_BOX2D_SCALE, OFX_BOX2D_SCALE);
    glPointSize(particleSize);
    if (useTexture) {
        textureImage.bind();
        mesh.drawFaces();
        textureImage.unbind();
    } else {
        mesh.draw();
    }
    ofPopMatrix();
    ofDisablePointSprites();
}

int32 ofxBox2dParticleSystem::createParticle(ofVec2f position , ofVec2f velocity){
    return createParticle(position.x, position.y, velocity.x, velocity.y);
}

int32 ofxBox2dParticleSystem::createParticle(float posx, float posy, float velx, float vely){
    b2ParticleDef pd;
    pd.flags = flag;
    b2Vec2 position = b2Vec2(posx / OFX_BOX2D_SCALE, posy / OFX_BOX2D_SCALE);
    pd.position = position;
    pd.velocity.Set(velx / OFX_BOX2D_SCALE, vely / OFX_BOX2D_SCALE);
    pd.color = b2ParticleColor(color.r, color.g, color.b, color.a);
    if (lifetime > 0.0) {
        pd.lifetime = lifetime;
    }
    return particleSystem->CreateParticle(pd);
}

void ofxBox2dParticleSystem::applyForce( int32 particle_index, const ofVec2f& force )
{
  applyForce(particle_index, force.x, force.y);
}

void ofxBox2dParticleSystem::applyForce( int32 particle_index, float force_x, float force_y )
{
  particleSystem->ParticleApplyForce( particle_index, b2Vec2( force_x, force_y ) );
}

b2ParticleGroup* ofxBox2dParticleSystem::createRectParticleGroup(ofVec2f position, ofVec2f size, ofColor color){
    b2PolygonShape rect;
    rect.SetAsBox(size.x / OFX_BOX2D_SCALE, size.y / OFX_BOX2D_SCALE);
    
    b2ParticleGroupDef pgd;
    pgd.flags = flag;
    pgd.groupFlags = groupFlag;
    pgd.position = b2Vec2(position.x / OFX_BOX2D_SCALE, position.y / OFX_BOX2D_SCALE);
    pgd.shape = &rect;
    pgd.color = b2ParticleColor(color.r, color.g, color.b, color.a);
    if (lifetime > 0.0) {
        pgd.lifetime = lifetime;
    }
    return particleSystem->CreateParticleGroup(pgd);
}

b2ParticleGroup* ofxBox2dParticleSystem::createCircleParticleGroup(ofVec2f position, float radius, ofColor color){
    b2CircleShape circle;
    circle.m_radius = radius / OFX_BOX2D_SCALE;
    
    b2ParticleGroupDef pgd;
    pgd.flags = flag;
    pgd.groupFlags = groupFlag;
    pgd.position = b2Vec2(position.x / OFX_BOX2D_SCALE, position.y / OFX_BOX2D_SCALE);
    pgd.shape = &circle;
    pgd.color = b2ParticleColor(color.r, color.g, color.b, color.a);
    if (lifetime > 0.0) {
        pgd.lifetime = lifetime;
    }
    return particleSystem->CreateParticleGroup(pgd);
}

void ofxBox2dParticleSystem::loadImage(string filename){
    ofDisableArbTex();
    textureImage.load(filename);
    useTexture = true;
}

//--------------------------------------------------------------
void ofxBox2dParticleSystem::setRadius(float radius){
    particleSystemDef.radius = radius / OFX_BOX2D_SCALE;
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

void ofxBox2dParticleSystem::setParticleGroupFlag(b2ParticleGroupFlag _groupFlag){
    groupFlag = _groupFlag;
}

int ofxBox2dParticleSystem::getParticleCount(){
    return particleSystem->GetParticleCount();
}
