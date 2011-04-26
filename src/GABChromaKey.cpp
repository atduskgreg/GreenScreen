/*
 *  GABChromaKey.cpp
 *  thesisGreen
 *
 *  Created by Greg Borenstein on 4/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "GABChromaKey.h"

GABChromaKey::GABChromaKey() {

}

GABChromaKey::GABChromaKey(int _inputWidth, int _inputHeight) {
  inputWidth = _inputWidth;
  inputHeight = _inputHeight;
}


void GABChromaKey::setInput( unsigned char * _inputPixels ){
  inputPixels = _inputPixels;
  alphaWorkimage.allocate(inputWidth, inputHeight, OF_IMAGE_COLOR_ALPHA);
}

void GABChromaKey::setKeyColor(ofColor  _keyColor){
  keyColor = _keyColor;
}


void GABChromaKey::setThreshold(float _threshold){
  threshold = _threshold;
}

void GABChromaKey::performKey(){
  alphaWorkimage.setFromPixels(inputPixels, inputWidth, inputHeight, OF_IMAGE_COLOR_ALPHA, true);
  
  unsigned char * outputAlphaPixels = alphaWorkimage.getPixels();
  
  for (int i = 0; i < inputWidth*inputHeight; i++) {
    int deltaR = abs(inputPixels[i*3+0] - keyColor.r);
    int deltaG = abs(inputPixels[i*3+1] - keyColor.g);
    int deltaB = abs(inputPixels[i*3+2] - keyColor.b);
    
    
    outputAlphaPixels[i*4]     = inputPixels[i*3];
    outputAlphaPixels[i*4 + 1] = inputPixels[i*3 + 1];
    outputAlphaPixels[i*4 + 2] = inputPixels[i*3 + 2];
    
    
    // componentwise thresholding is for some reason superior
    if(deltaR <= threshold && deltaG <= threshold && deltaB <= threshold ){
      // set alpha to transparent
      outputAlphaPixels[i*4 + 3] = 0;
    } else {
      // set alpha to opaque
      outputAlphaPixels[i*4 + 3] = 255;
      
    }
    
    // copy the input rgb values into the output rgb values
    outputAlphaPixels[i*4]     = inputPixels[i*3];
    outputAlphaPixels[i*4 + 1] = inputPixels[i*3 + 1];
    outputAlphaPixels[i*4 + 2] = inputPixels[i*3 + 2];
  }
  
  alphaWorkimage.setFromPixels(outputAlphaPixels, inputWidth, inputHeight, OF_IMAGE_COLOR_ALPHA, true);
  
  inputPixels = alphaWorkimage.getPixels();

}

unsigned char * GABChromaKey::getOutput(){
  performKey();
  return inputPixels;
}