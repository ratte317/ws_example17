#pragma once

#include "ofMain.h"
#include "ofxCsv.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    ofxCsv csv;
    vector<string> timeStamp;
    vector<float> temperature;
    vector<float> humidityAir;
    vector<float> pressure;
    vector<float> illuminance;
    vector<float> humiditySoil;
    ofColor color[5];
    
    ofEasyCam cam;
    ofLight light;
};
