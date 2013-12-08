#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
	
	gui.setup("Superformula");
	gui.add(a1value.setup("a1value", 1,0,3));
	gui.add(a2value.setup("a2value", 1,0,3));
	gui.add(n1value.setup("n1value", 8,0,20));
	gui.add(n2value.setup("n2value", 1,0,3));
	gui.add(n3value.setup("n3value", 1,0,3));
	gui.add(n4value.setup("n4value", 1,0,3));
	gui.add(stepvalue.setup("stepvalue", 0.05,0.02,0.9));
	
	gui.loadFromFile("Superformula.xml");
	
	guiRect = ofRectangle(gui.getPosition().x, gui.getPosition().y, gui.getWidth(), gui.getHeight());
	
}

ofVec3f testApp::sf3d(float x, float y) {
	
	float i = -PI + x*stepvalue;
	float j = -PI/2.0 + y*stepvalue;
	
	
	
	
	float raux1 = pow(abs(1/a1value*abs(cos(n1value * i/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*i/4))),n4value);

	float r1=pow(abs(raux1),(-1/n2value));
	float raux2=pow(abs(1/a1value*abs(cos(n1value*j/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*j/4))),n4value);
	float r2=pow(abs(raux2),(-1/n2value));
	float xx=r1*cos(i)*r2*cos(j)*100;
	float yy=r1*sin(i)*r2*cos(j)*100;
	float zz=r2*sin(j)*100;
	

	
	return ofVec3f(xx,yy,zz);
}

//--------------------------------------------------------------
void testApp::update(){
	mesh.clear();	
	int N_X = 2*PI / stepvalue;
	int N_Y = PI / stepvalue;
		
	for(int x=0;x<N_X;x++) {
		
		for(int y=0;y<N_Y;y++) {

			mesh.addVertex(sf3d(x,y));
		}
	}

}

void testApp::exit() {
	gui.saveToFile("Superformula.xml");
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0);
	cam.begin();
	ofPushMatrix();
//	ofScale(100,100,100);
	mesh.setMode(OF_PRIMITIVE_POINTS);
	mesh.drawWireframe();
	ofPopMatrix();
	cam.end();
	
	gui.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(guiRect.inside(x,y)) {
		cam.disableMouseInput();
	} else {
		cam.enableMouseInput();
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
