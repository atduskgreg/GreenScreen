#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxControlPanel.h"
#include "ofxShader.h"

#include "GABChromaKey.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

  ofVideoGrabber laptop;
  ofVideoGrabber camera;

  
  ofVideoGrabber bendy;

  int videoWidth;
  int videoHeight;
  
  unsigned char * videoPixels;
  unsigned char * laptopPixels;
  unsigned char * videoAlphaPixels;
  
  
  GABChromaKey toiletKey;
  

  bool compare;
  
  int greenScreenThreshold;
  
  int texturePositionX;
  int texturePositionY;

  ofImage processedImage;
  
  ofColor colorGreenScreen;
  
  ofxControlPanel panel;		
	
  ofxShader shader;
  
  ofImage background;
  ofImage foreground;
  
  ofImage grayVideo;
  
  
  int backgroundWidth;
  int backgroundHeight;
  
};

#endif
