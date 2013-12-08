#include "testApp.h"
#include "ofxMeshUtils.h"

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
	
//	light.setDiffuseColor(ofColor(255,0,0));
	light.setDirectional();
	light.setOrientation(ofVec3f(30,60,60));
	
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
	mesh.clear();	
	int N_X = ceil((2.0*PI) / stepvalue);
	int N_Y = ceil(PI / stepvalue);
		
	for(int x=0;x<N_X;x++) {
		for(int y=0;y<N_Y;y++) {
			mesh.addVertex(sf3d(x,y));
			mesh.addColor(ofColor(255,30,30));
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
	

	glEnable(GL_DEPTH_TEST);
	ofEnableLighting();light.enable();
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	mesh.draw();
	light.disable();ofDisableLighting();

	mesh.clearColors();
	ofSetColor(30,30,30,255);
	mesh.drawWireframe();
	
	glDisable(GL_DEPTH_TEST);

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
