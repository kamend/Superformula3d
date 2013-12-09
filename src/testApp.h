#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	
	ofxPanel gui;
	ofRectangle guiRect;
	ofxSlider<float> a1value;
	ofxSlider<float> a2value;
	ofxSlider<float> n1value;
	ofxSlider<float> n2value;
	ofxSlider<float> n3value;
	ofxSlider<float> n4value;
	ofxSlider<float> stepvalue;
	ofxToggle drawWire;
	ofxToggle drawPoints;
	
	bool showGui;
	
	float n1target, n2target, n3target, n4target,a1target,a2target;


	ofMesh mesh;	
	ofVec3f sf3d(float x, float y);
	ofEasyCam cam;
	
	ofLight light;
	
	vector<int> lastRow;
	
		
};
