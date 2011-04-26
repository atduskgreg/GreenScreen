#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
//  ofDisableArbTex();

  videoWidth = 640;
  videoHeight = 480;
  

  camera.listDevices();
  
  camera.setDeviceID(5);
  laptop.setDeviceID(7);
  bendy.setDeviceID(6);
  
  camera.initGrabber(videoWidth, videoHeight, true);
  laptop.initGrabber(1280, 720, true);
  bendy.initGrabber(videoWidth, videoHeight, true);


  panel.setup("Control Panel", ofGetWidth() - 300, 100, 300, 600);
  panel.addPanel("Chroma Key", 1, false);	
  panel.setWhichPanel("Chroma Key");
	panel.addSlider("toilet threshold", "toiletThreshold", 100, 0, 255, false);
	panel.addSlider("desk threshold", "deskThreshold", 100, 0, 255, false);

  
  vector<string> names;
  names.push_back("toilet");
  names.push_back("desk");
  
  
  panel.addMultiToggle("current key", "currentKey", 0, names);
  
  compare = false;

  bendyImage.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA);

  processedImage.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA);
  background.allocate(1280, 720, OF_IMAGE_COLOR);
    
  
  shader.setup("chromakey", "chromakey");
  shader.printActiveUniforms();

  
  toiletKey = GABChromaKey(videoWidth, videoHeight);
  deskKey = GABChromaKey(videoWidth, videoHeight);

}

//--------------------------------------------------------------
void testApp::update(){
  panel.update();

  camera.grabFrame();
  laptop.grabFrame();
  bendy.grabFrame();
  
  videoPixels = camera.getPixels();
  laptopPixels = laptop.getPixels();
bendyPixels = bendy.getPixels();
  
  toiletTheshold = panel.getValueF("toiletThreshold");
  deskThreshold = panel.getValueF("deskThreshold");

  currentKey = panel.getValueF("currentKey");
  
  toiletKey.setInput(videoPixels);
  toiletKey.setThreshold(toiletTheshold);
  
  deskKey.setInput(bendyPixels);
  deskKey.setThreshold(deskThreshold);
  
  
  background.setFromPixels(laptopPixels, 1280, 720, OF_IMAGE_COLOR, true);
  
  processedImage.setFromPixels(toiletKey.getOutput(), videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA, true);
  bendyImage.setFromPixels(deskKey.getOutput(), videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA, true);
   
  
  
}

//--------------------------------------------------------------
void testApp::draw(){

  background.draw(0,0, 1280, 720);
  //bendy.draw(480, 0);
  
  bendyImage.draw(480,0);
  processedImage.draw(0, 0, videoWidth, videoHeight);

  
  
  panel.draw();
  
 // 
// shader.begin();
//
//  // get texture associated with processedImage ready to go to GPU
//  processedImage.getTextureReference().bind();
//
//	//shader.setUniform("color",  ofMap(sin(ofGetElapsedTimef()*10), -1,1, 0,1)  );
//
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  
//  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, videoWidth, videoHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, processedImage.getPixels());
//
//  shader.setTexture("processedImage", processedImage, 0);
//
//	ofRect(texturePositionX,texturePositionY,640,480);
//	
//	shader.end();
 

  
  ofSetColor(255, 255, 255);
  
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  if(key == ' '){
    compare = !compare;
  }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
 /* if(key == 356){
  
    greenScreenThreshold -= 1;
  } else if(key == 358){
    greenScreenThreshold += 1;
    
  
  }
  
  cout << greenScreenThreshold << endl;
  */

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  
  
  if(compare){
    if(currentKey == 0){
      
      colorGreenScreen.r = videoPixels[3 * (videoWidth * y + x)];
      colorGreenScreen.g = videoPixels[3 * (videoWidth * y + x) + 1];
      colorGreenScreen.b = videoPixels[3 * (videoWidth * y + x) + 2];
      toiletKey.setKeyColor(colorGreenScreen);
    } else {
      
      
      colorGreenScreen.r = bendyPixels[3 * (videoWidth * y + (x-480))];
      colorGreenScreen.g = bendyPixels[3 * (videoWidth * y + (x-480)) + 1];
      colorGreenScreen.b = bendyPixels[3 * (videoWidth * y + (x-480)) + 2];
      deskKey.setKeyColor(colorGreenScreen);
    }
    
    
    
    ofBackground(colorGreenScreen.r, colorGreenScreen.g, colorGreenScreen.b);
    cout << "r: " << colorGreenScreen.r << " g: " << colorGreenScreen.g << " b: " << colorGreenScreen.b << endl;
    
  }
  

  
  panel.mousePressed(x,y,button);

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	panel.mouseDragged(x,y,button);
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

