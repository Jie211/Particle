//
//  Particle.cpp
//  OOF_Spring
//
//  Created by ChenGong on 2014/02/11.
//
//

#include "Particle.h"

Particle::Particle(){
    radius=5.0;
    friction=0.01;
    bFixed=false;
}

void Particle::setup(ofVec2f _position, ofVec2f _velocity){
    position=_position;
    velocity=_velocity;
}

void Particle::setup(float positionX, float positionY, float velocityX, float velocityY){
    position=ofVec2f(positionX,positionY);
    velocity=ofVec2f(velocityX,velocityY);
}

void Particle::resetForce(){
    force.set(0,0);
}

void Particle::addForce(ofVec2f _force){
    force+=_force;
}

void Particle::addForce(float forceX, float forceY){
    force+=ofVec2f(forceX,forceY);
}

void Particle::updateForce(){
    force-=velocity*friction;
}

void Particle::updatePos(){
    if(!bFixed){
        velocity+=force;
        position+=velocity;
    }
}

void Particle::update(){
    updateForce();
    updatePos();
}
void Particle::fadeout(float fade){
    force.set(force.x*fade,force.y*fade);
}

void Particle::bouceOffWalls(){
    bool bDampedOnCollision=false;
    bool bDidICollide=false;
    
    float minx=0;
    float miny=0;
    float maxx=ofGetWidth();
    float maxy=ofGetHeight();
    
    if (position.x > maxx) {
        position.x = maxx;
        velocity.x*=-1;
        bDidICollide=true;
    }else if (position.x < minx){
        position.x=minx;
        velocity.x*=-1;
        bDidICollide=true;
    }
    
    if (position.y > maxy) {
        position.y = maxy;
        velocity.y*=-1;
        bDidICollide=true;
    }else if (position.y < miny){
        position.y=minx;
        velocity.y*=-1;
        bDidICollide=true;
    }
    
    if (bDidICollide==true&&bDampedOnCollision==true) {
        velocity*=0.3;
    }
}

void Particle::bouceOffWalls(float _radius){
    bool bDampedOnCollision=false;
    bool bDidICollide=false;
    
    float minx=0+_radius;
    float miny=0+_radius;
    float maxx=ofGetWidth()-_radius;
    float maxy=ofGetHeight()-radius;
    
    if (position.x > maxx) {
        position.x = maxx;
        velocity.x*=-1;
        bDidICollide=true;
    }else if (position.x < minx){
        position.x=minx;
        velocity.x*=-1;
        bDidICollide=true;
    }
    
    if (position.y > maxy) {
        position.y = maxy;
        velocity.y*=-1;
        bDidICollide=true;
    }else if (position.y < miny){
        position.y=minx;
        velocity.y*=-1;
        bDidICollide=true;
    }
    
    if (bDidICollide==true&&bDampedOnCollision==true) {
        velocity*=0.3;
    }
}


void Particle::draw(){
    ofCircle(position, radius);
}

void Particle::addRepulsionForce(float x, float y, float radius, float scale){
    ofVec2f posOfForce;
    posOfForce.set(x,y);
    ofVec2f diff=position-posOfForce;
    float length=diff.length();
    bool bAMCloseEnough=true;
    if (radius>0) {
        if (length>radius) {
            bAMCloseEnough=false;
        }
    }
    if (bAMCloseEnough==true) {
        float pct=1-(length/radius);
        diff.normalize();
        force.x=force.x+diff.x*scale*pct;
        force.y=force.y+diff.x*scale*pct;
//        p.force.x=p.force.x-diff.x*scale*pct;
//        p.force.y=p.force.y-diff.x*scale*pct;
    }
}
void Particle::addRepulsionForce(Particle &p, float radius, float scale){
	ofVec2f posOfForce;
	posOfForce.set(p.position.x,p.position.y);
	ofVec2f diff	= position - posOfForce;
	float length	= diff.length();
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);
		diff.normalize();
		force.x = force.x + diff.x * scale * pct;
        force.y = force.y + diff.y * scale * pct;
//		p.force.x = p.force.x - diff.x * scale * pct;
//        p.force.y = p.force.y - diff.y * scale * pct;
    }
}

// 引き付けあう力
void Particle::addAttractionForce(float x, float y, float radius, float scale){
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	ofVec2f diff	= position - posOfForce;
	float length	= diff.length();
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);
		diff.normalize();
		force.x = force.x - diff.x * scale * pct;
        force.y = force.y - diff.y * scale * pct;
    }
}

void Particle::addAttractionForce(Particle &p, float radius, float scale){
	ofVec2f posOfForce;
	posOfForce.set(p.position.x, p.position.y);
	ofVec2f diff	= position - posOfForce;
	float length	= diff.length();
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);
		diff.normalize();
		force.x = force.x - diff.x * scale * pct;
        force.y = force.y - diff.y * scale * pct;
//		p.force.x = p.force.x + diff.x * scale * pct;
//        p.force.y = p.force.y + diff.y * scale * pct;
    }
}

void Particle::addCounterClockwiseForce(Particle &p, float radius, float scale){
	ofVec2f posOfForce;
	posOfForce.set(p.position.x,p.position.y);
    
	ofVec2f diff = position - posOfForce;
	float length = diff.length();
    
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);
		diff.normalize();
		force.x = force.x + diff.y * scale * pct;
        force.y = force.y - diff.x * scale * pct;
//		p.force.x = p.force.x - diff.y * scale * pct;
//        p.force.y = p.force.y + diff.x * scale * pct;
        
    }
}







