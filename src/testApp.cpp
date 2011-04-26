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

	panel.addSlider("chroma threshold", "greenScreenThreshold", 100, 0, 255, false);
  
  
  compare = false;
  
  
  processedImage.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA);
  background.allocate(1280, 720, OF_IMAGE_COLOR);
  //cout << "load? " << background.loadImage("background_3.jpg") << endl;
  //cout << "load? " << foreground.loadImage("foreground.png") << endl;
  
  grayVideo.allocate(videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA);
  
  
  shader.setup("chromakey", "chromakey");
  shader.printActiveUniforms();

  
  toiletKey = GABChromaKey(videoWidth, videoHeight);

}

//--------------------------------------------------------------
void testApp::update(){
  panel.update();

  camera.grabFrame();
  laptop.grabFrame();
  bendy.grabFrame();
  
  videoPixels = camera.getPixels();
  laptopPixels = laptop.getPixels();

  greenScreenThreshold = panel.getValueF("greenScreenThreshold");

  
  toiletKey.setInput(videoPixels);
  toiletKey.setThreshold(greenScreenThreshold);
  
  
  background.setFromPixels(laptopPixels, 1280, 720, OF_IMAGE_COLOR, true);

  //texturePositionX = panel.getValueF("texturePositionX");
  //texturePositionY = panel.getValueF("texturePositionY");

  /*processedImage.setFromPixels(videoPixels, videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA, true);

  
  
  videoAlphaPixels = processedImage.getPixels();

  for (int i = 0; i < videoWidth*videoHeight; i++) {
    int deltaR = abs(videoPixels[i*3+0] - colorGreenScreen.r);
    int deltaG = abs(videoPixels[i*3+1] - colorGreenScreen.g);
    int deltaB = abs(videoPixels[i*3+2] - colorGreenScreen.b);
    
    
    videoAlphaPixels[i*4] = videoPixels[i*3];
    videoAlphaPixels[i*4 + 1] = videoPixels[i*3 + 1];
    videoAlphaPixels[i*4 + 2] = videoPixels[i*3 + 2];
    
    

    if(deltaR <= greenScreenThreshold && deltaG <= greenScreenThreshold && deltaB <= greenScreenThreshold ){
     //float deltaSum = deltaR + deltaG + deltaB;
     //float alpha = ofMap(deltaSum, 0, 255 * 3, 0, 255, true);
     videoAlphaPixels[i*4 + 3] = 0;
    } else {
      videoAlphaPixels[i*4 + 3] = 255;

    }
    
  //  float ave = (videoPixels[i*3] + videoPixels[i*3 +1] + videoPixels[i*3 +2]) /3.0;
    
    videoAlphaPixels[i*4] = videoPixels[i*3];
    videoAlphaPixels[i*4 + 1] = videoPixels[i*3 + 1];
    videoAlphaPixels[i*4 + 2] = videoPixels[i*3 + 2];
  }
  */
  //processedImage.setFromPixels(videoAlphaPixels, videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA, true);
  
  processedImage.setFromPixels(toiletKey.getOutput(), videoWidth, videoHeight, OF_IMAGE_COLOR_ALPHA, true);
   
  

}

//--------------------------------------------------------------
void testApp::draw(){
  //laptop.draw(0,0);
  //camera.draw(0, 0);
  background.draw(0,0, 1280, 720);
  bendy.draw(480, 0);
  
 // foreground.draw(-180,-120, backgroundWidth*1.3, backgroundHeight*1.3);
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
  if(key == 356){
  
    greenScreenThreshold -= 1;
  } else if(key == 358){
    greenScreenThreshold += 1;
    
  
  }
  
  cout << greenScreenThreshold << endl;

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  
  
  if(x < videoWidth && y < videoHeight){
    if(compare){
      int i = y * videoWidth + x;
      cout << "current thresh: " << greenScreenThreshold << endl;
      cout << "diff: r: " << abs(videoPixels[i*3+0] - colorGreenScreen.r) << " g: "<< abs(videoPixels[i*3+1] - colorGreenScreen.g)  << " b: " << abs(videoPixels[i*3+2] - colorGreenScreen.b) << endl;
    }
    else {
      colorGreenScreen.r = videoPixels[3 * (videoWidth * y + x)];
      colorGreenScreen.g = videoPixels[3 * (videoWidth * y + x) + 1];
      colorGreenScreen.b = videoPixels[3 * (videoWidth * y + x) + 2];
    
      ofBackground(colorGreenScreen.r, colorGreenScreen.g, colorGreenScreen.b);
      cout << "r: " << colorGreenScreen.r << " g: " << colorGreenScreen.g << " b: " << colorGreenScreen.b << endl;
      
      toiletKey.setKeyColor(colorGreenScreen);

    }
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

