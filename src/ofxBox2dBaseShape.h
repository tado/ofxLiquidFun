#pragma once

#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dUtils.h"

class ofxBox2dBaseShape {
	
public:

	ofxBox2dBaseShape();	
	
	//----------------------------------------
	~ofxBox2dBaseShape();
	
	//----------------------------------------
	bool isBody();
	
	//----------------------------------------
    static bool shouldRemove(ofPtr<ofxBox2dBaseShape> shape);
    static bool shouldRemoveOffScreen(ofPtr<ofxBox2dBaseShape> shape);
	bool isFixed();
	bool isSleeping();
    
	//----------------------------------------
	b2World* getWorld();
    
    //----------------------------------------
    b2Body* getBody();
	
	//----------------------------------------
	virtual void create();
	
	//------------------------------------------------ 
	virtual void setBounce(float val);
	
	//------------------------------------------------ 
	virtual void setDensity(float val);
	
	//----------------------------------------
	virtual void setFriction(float val);
	
	//------------------------------------------------ 
	virtual void setPhysics(float density, float bounce, float friction);

    //------------------------------------------------
    void setBodyType(b2BodyType bodyType);
    b2BodyType getBodyType() const { return bodyDef.type; }

	//------------------------------------------------ 
	void* setData(void*data);
	
	//------------------------------------------------ 
	void* getData();
	
	//------------------------------------------------ 
	virtual void setFilterData(b2Filter filter);
	
	//------------------------------------------------ 
	virtual void enableGravity(bool b);
	
	//------------------------------------------------ 
	virtual void setFixedRotation(bool b);
	virtual void setRotationFriction(float f);
	float getRotation();
	void setRotation(float angle);
	
	//------------------------------------------------ 
	virtual void setPosition(float x, float y);
	virtual void setPosition(glm::vec2 p);
	
	//------------------------------------------------ 
	glm::vec2 getPosition();
	glm::vec2 getB2DPosition();

	//------------------------------------------------ 
	virtual void setVelocity(float x, float y);
	virtual void setVelocity(glm::vec2 p);
	glm::vec2 getVelocity();
	
	//------------------------------------------------ 
	virtual void setDamping(float f);
	virtual void setDamping(float fx, float fy);

	//------------------------------------------------
	virtual void addForce(glm::vec2 frc, float scale);
	
	//------------------------------------------------
	virtual void addImpulseForce(glm::vec2 pt, glm::vec2 amt);
	
	//------------------------------------------------
	virtual void addRepulsionForce(glm::vec2 pt, float radius, float amt);
	
	//------------------------------------------------
	virtual void destroy();
	
	//------------------------------------------------
	virtual void update();
	virtual void draw();

protected:
    b2FixtureDef	fixture;
    b2BodyDef		bodyDef;
    b2Body*			body;
    bool            bodyTypeSet;

    bool			alive;
    bool			setMassFromShape;

    float			density;
    float			bounce;
    float			friction;
};






