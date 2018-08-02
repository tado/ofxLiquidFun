/*
 *  ofxBox2dWeldJoint.cpp
 *  jointExample
 *
 *  Created by Nick Hardeman on 1/19/11.
 *  Copyright 2011 Nick Hardeman. All rights reserved.
 *
 */

#include "ofxBox2dWeldJoint.h"

//----------------------------------------
ofxBox2dWeldJoint::ofxBox2dWeldJoint() {
	world = NULL;
	joint = NULL;
	alive = false;
}

//----------------------------------------
ofxBox2dWeldJoint::ofxBox2dWeldJoint(b2World* b2world, b2Body* body1, b2Body* body2, float frequencyHz, float damping, bool bCollideConnected) {
	ofxBox2dWeldJoint();
	setup(b2world, body1, body2, frequencyHz, damping, bCollideConnected);
}

//----------------------------------------
ofxBox2dWeldJoint::ofxBox2dWeldJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, float frequencyHz, float damping, bool bCollideConnected) {
	ofxBox2dWeldJoint();
	setup(b2world, body1, body2, anchor, frequencyHz, damping, bCollideConnected);
}

//----------------------------------------
void ofxBox2dWeldJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, float frequencyHz, float damping, bool bCollideConnected) {
	
	if(body1 == NULL || body2 == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: setup : - box2d body is NULL -");
		return;
	}
	
    b2Vec2 a1;
	a1 = body1->GetWorldCenter();

	setup(b2world, body1, body2, a1, frequencyHz, damping, bCollideConnected);
    
    alive = true;
}

//----------------------------------------
void ofxBox2dWeldJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, float frequencyHz, float damping, bool bCollideConnected) {

	setWorld(b2world);

	if(body1 == NULL || body2 == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: setup : - box2d body is NULL -");
		return;
	}

	b2WeldJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor);
	jointDef.collideConnected	= bCollideConnected;
	jointDef.frequencyHz		= frequencyHz;
	jointDef.dampingRatio		= damping;	
	joint						= (b2WeldJoint*)world->CreateJoint(&jointDef);
	
	alive						= true;
}

//----------------------------------------
void ofxBox2dWeldJoint::setWorld(b2World* w) {
	if(w == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: setWorld : - box2d world needed -");
		return;
	}
	world = w;
}

//----------------------------------------
bool ofxBox2dWeldJoint::isSetup() {
	if (world == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: world must be set!");
		return false;
	}
	if (joint == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: setup function must be called!");
		return false;
	}
	return true;
}


//----------------------------------------
void ofxBox2dWeldJoint::draw() {
	if(!alive) return;
	
	b2Vec2 p1 = joint->GetAnchorA();
	b2Vec2 p2 = joint->GetAnchorB();
	
	p1 *= OFX_BOX2D_SCALE;
	p2 *= OFX_BOX2D_SCALE;
	ofDrawLine(p1.x, p1.y, p2.x, p2.y);
}

//----------------------------------------
void ofxBox2dWeldJoint::destroy() {
	if (!isSetup()) return;
	if(joint) {
		world->DestroyJoint(joint);
	}
	joint = NULL;
	alive = false;
}


/*
//----------------------------------------
void ofxBox2dWeldJoint::setLength(float len) {
	if(joint) {
		joint->SetLength((float32)b2dNum(len));
	}
}
float ofxBox2dWeldJoint::getLength() {
	if(joint) {
		return (float)joint->GetLength();
	}
	return 0;
}
 */

//----------------------------------------
void ofxBox2dWeldJoint::setFrequency(float freq) {
	if(joint) {
		joint->SetFrequency((float32)freq);
	}
}
float ofxBox2dWeldJoint::getFrequency() {
	if(joint) {
		return (float)joint->GetFrequency();
	}
	return 0;
}

//----------------------------------------
void ofxBox2dWeldJoint::setDamping(float ratio) {
	if(joint) {
		joint->SetDampingRatio((float32)ratio);
	}
}
float ofxBox2dWeldJoint::getDamping() {
	if(joint) {
		return (float)joint->GetDampingRatio();
	}
	return 0;
}


//----------------------------------------
ofVec2f ofxBox2dWeldJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dWeldJoint::getReactionForceB2D(float inv_dt) const {
	if(joint) {
		return joint->GetReactionForce(inv_dt);
	}
	return b2Vec2(0, 0);
}
float ofxBox2dWeldJoint::getReactionTorque(float inv_dt) const {
	if(joint) {
		return (float)joint->GetReactionTorque(inv_dt);
	}
	return 0;
}




