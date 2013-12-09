#include "testApp.h"
#include "ofxMeshUtils.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	gui.setup("Superformula");
	gui.add(a1value.setup("a1value", 1,0,5));
	gui.add(a2value.setup("a2value", 1,0,5));
	gui.add(n1value.setup("n1value", 8,0,40));
	gui.add(n2value.setup("n2value", 1,0,5));
	gui.add(n3value.setup("n3value", 1,0,5));
	gui.add(n4value.setup("n4value", 1,0,5));
	gui.add(stepvalue.setup("stepvalue", 0.05,0.02,0.9));
	gui.add(drawWire.setup("Draw Wireframe", false));
	gui.add(drawPoints.setup("Draw Points", false));
	
	gui.loadFromFile("Superformula.xml");
	
	guiRect = ofRectangle(gui.getPosition().x, gui.getPosition().y, gui.getWidth(), gui.getHeight());
	

	light.setDirectional();
	light.setOrientation(ofVec3f(30,60,60));
	
	a1target = a1value;
	a2target = a2value;
	n1target = n1value;
	n2target = n2value;
	n3target = n3value;
	n4target = n4value;
	
	showGui = false;
	
}


float moveTowards(float current, float target, float step) {
	
	if(abs(current-target) < step) {
		current = target;
	} else {
		
		if(current > target) {
			current -= step;
		} else if(current < target) {
			current += step;
		}
	}
	
	return current;
}

ofVec3f testApp::sf3d(float x, float y) {
	
	float i = -PI + x*stepvalue;
	
	float j = -PI/2.0 + y*stepvalue;

	float raux1 = pow(abs(1/a1value*abs(cos(n1value * i/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*i/4))),n4value);

	float r1=pow(abs(raux1),(-1/n2value));
	float raux2=pow(abs(1/a1value*abs(cos(n1value*j/4))),n3value)+pow(abs(1/a2value*abs(sin(n1value*j/4))),n4value);
	float r2=pow(abs(raux2),(-1/n2value));
	float xx=r1*cos(i)*r2*cos(j)*100.0f;
	float yy=r1*sin(i)*r2*cos(j)*100.0f;
	float zz=r2*sin(j)*100.0f;

	return ofVec3f(xx,yy,zz);
}

//--------------------------------------------------------------
void testApp::update(){
	
	a1value = moveTowards(a1value, a1target, 0.02);
	a2value = moveTowards(a2value, a2target, 0.02);
	n1value = moveTowards(n1value, n1target, 0.02);
	n2value = moveTowards(n2value, n2target, 0.02);
	n3value = moveTowards(n3value, n3target, 0.02);
	n4value = moveTowards(n4value, n4target, 0.02);
	
	
	mesh.clear();	
	int N_X = ceil((2.0*PI) / stepvalue);
	int N_Y = ceil(PI / stepvalue);
		
	for(int x=0;x<N_X;x++) {
		for(int y=0;y<N_Y;y++) {
			mesh.addVertex(sf3d(x,y));
			mesh.addColor(ofColor(255,255,255,100));
		}
	}
	
	mesh.addVertex(sf3d(PI/stepvalue,PI/stepvalue));
	mesh.addColor(ofColor(255,30,30));
	
	
	lastRow.clear();
	
	for(int x=0;x<N_X;x++) {
		for(int y=0;y<N_Y-1;y++) {

			if(x == N_X-1) {
				
				int idx1 = x*N_Y+y;
				int idx2 = x*N_Y+y+1;
				
				int idx3 = y+1;
				int idx4 = y;
				
				mesh.addTriangle(idx1, idx2, idx3);
				mesh.addTriangle(idx1, idx3, idx4);
				
			} else {
				int idx1 = x*N_Y+y;
				int idx2 = x*N_Y+y+1;
				
				int idx3 = (x+1)*N_Y+y+1;
				int idx4 = (x+1)*N_Y+y;
				
				mesh.addTriangle(idx1, idx2, idx3);
				mesh.addTriangle(idx1, idx3, idx4);
				
				if(y == N_Y-2) {
					lastRow.push_back(idx2);
				}
			}

		}
	}
	
	int lastVertex = mesh.getNumVertices()-1;
	
	for(int i=0;i<lastRow.size()-1;i++) {
		mesh.addTriangle(lastRow[i], lastRow[i+1], lastVertex);
	}
	mesh.addTriangle(lastRow[0],lastRow[lastRow.size()-1], lastVertex);
	
	ofxMeshUtils::calcNormals(mesh);


}

void testApp::exit() {
	gui.saveToFile("Superformula.xml");
}

//--------------------------------------------------------------
void testApp::draw(){
		
	ofBackground(0);
	glShadeModel(GL_FLAT);
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

	cam.begin();
	ofPushMatrix();


	if(!drawPoints) {
		ofDisableAlphaBlending();
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		
		
		glEnable(GL_DEPTH_TEST);
		ofEnableLighting();light.enable();
		mesh.draw();
		light.disable();ofDisableLighting();
	} else {
		mesh.setMode(OF_PRIMITIVE_POINTS);
		
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_PROGRAM_POINT_SIZE_ARB);
		
		glPointSize(0.5f);
		mesh.clearColors();
		ofSetColor(255,255,255,100);
		ofEnableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		
		mesh.draw();
	}


	
	if(drawWire) {
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
		mesh.clearColors();
		ofSetColor(255,255,255,100);
		mesh.drawWireframe();
	}

	
	glDisable(GL_DEPTH_TEST);

	cam.end();

	if(showGui)
	gui.draw();

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'r') {
		a1target = ofRandomuf()*3.0f+0.5f;
		a2target = ofRandomuf()*3.0f+0.5f;
		n1target = ofRandomuf()*20.0f;
		n2target = ofRandomuf()*3.0f+0.5f;
		n3target = ofRandomuf()*3.0f+0.5f;
		n4target = ofRandomuf()*3.0f+0.5f;
	}
	
	if(key == 'p') {
		drawPoints = !drawPoints;
	}
	
	if(key == 'w') {
		drawWire = !drawWire;
	}
	
	if(key == 'g') {
		showGui = !showGui;
	}
	
	if(key == '1') {
		a1value = 0.5;
	}
	if(key == '2') {
		a2value = 0.5;
	}
	if(key == '3') {
		n1value = 0.5;
	}
	if(key == '4') {
		n2value = 0.5;
	}
	
	if(key == '5') {
		n3value = 0.5;
	}
	
	if(key == '6') {
		n4value = 0.5;
	}
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
