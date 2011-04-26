/*
 *  GABChromaKey.h
 *  thesisGreen
 *
 *  Created by Greg Borenstein on 4/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class GABChromaKey {
public:
  GABChromaKey();
  GABChromaKey(int _inputWidth, int _inputHeight);
  
  void setInput( unsigned char * _inputPixels );
  void setThreshold( float _threshold );
  void setKeyColor( ofColor  _keyColor);
  
  void performKey();
  unsigned char * getOutput();
  
private:
  ofColor keyColor;
  float threshold;
  unsigned char * inputPixels;
  
  int inputWidth;
  int inputHeight;
  
  ofImage alphaWorkimage;
  
};

