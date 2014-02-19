#include "particle.h"
#include "ofMain.h"


//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.08f;

    age = 0;
    lifespan = floor( ofRandom(50,100) );
	dead = false;
}

//------------------------------------------------------------
particle::particle(ofVec2f pos, ofVec2f vel) {
	setInitialCondition(pos.x, pos.y, vel.x, vel.y);
	damping = 0.08f;
	
    age = 0;
    lifespan = floor( ofRandom(10,40) );
	dead = false;
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void particle::update(){	
	vel = vel + frc;
	pos = pos + vel;

    age++;
    if( age > lifespan ){
        dead = true;
    }
	
	resetForce();
}

//------------------------------------------------------------
void particle::draw(){
	//ofSetColor(255);
    ofCircle(pos.x, pos.y, 1.5);//
}

//------------------------------------------------------------
void particle::draw(ofImage *image){
	//ofSetColor(255);
	//image->draw(pos.x, pos.y);

	float angle = atan2(vel.x, vel.y) + PI;
	
	ofPushMatrix();
	{
		ofTranslate(pos.x, pos.y);
		ofRotate(-1 * ofRadToDeg(angle));
		
		image->draw(0, 0, 13, 13);
	}
	ofPopMatrix();
	
	
}


//------------------------------------------------------------
void particle::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}