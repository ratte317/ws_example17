#include "ofApp.h"

void ofApp::setup(){
    ofBackground(255);
    ofSetBackgroundAuto(false);
    ofSetColor(0);
    ofSetLineWidth(2.0);
    ofNoFill();
    objectNum = 0;
    //ファイルを指定
    string inputFile = "face.ndjson";
    ifstream input(ofToDataPath(inputFile), ifstream::in);
    
    //JSONファイルを1行ずつ読み込む
    ofxJSONElement jsonElement;
    Json::Reader reader;
    string currentLine;
    //最終行に行くまで1行読み込み
    while(getline(input, currentLine)) {
        //JSONElement形式にパース
        reader.parse(currentLine, jsonElement);
        //読み込んだJSONデータを配列に追加
        drawDataJson.push_back(jsonElement);
    }
    //ログ表示
    cout << "Done : read " << drawDataJson.size() << " drawings!"<< endl;
    
    //オブジェクト、ストローク、頂点の数、スケール、位置を初期化
    objectNum = int(ofRandom(drawDataJson.size()));
    strokeNum = 0;
    vertexNum = 0;
    scale = 0.2;
    location = ofVec2f(ofRandom(ofGetWidth()) - 128 * scale,
                       ofRandom(ofGetHeight() - 128 * scale));
}

void ofApp::update(){
}

void ofApp::draw(){
    //描画スピードアップ
    for (int j = 0; j < 4; j++) {
        ofPushMatrix();
        //位置を中心に
        ofTranslate(location);
        ofBeginShape();
        //パスを描画
        for (int i = 0; i < vertexNum; i++) {
            int x = drawDataJson[objectNum]["drawing"][strokeNum][0][i].asInt();
            int y = drawDataJson[objectNum]["drawing"][strokeNum][1][i].asInt();
            ofVertex(x * scale, y * scale);
        }
        ofEndShape();
        ofPopMatrix();
        //頂点の数を1つ追加
        vertexNum++;
        //もし頂点の数が上限に達したら次のパスへ
        if (vertexNum > drawDataJson[objectNum]["drawing"][strokeNum][0].size()) {
            vertexNum = 0;
            strokeNum++;
            //もしパスの数が上限に達したら次のオブジェクトへ
            if (strokeNum > drawDataJson[objectNum]["drawing"].size()-1) {
                vertexNum = 0;
                strokeNum = 0;
                objectNum = int(ofRandom(drawDataJson.size()));
                location = ofVec2f(ofRandom(ofGetWidth()) - 128 * scale,
                                   ofRandom(ofGetHeight() - 128 * scale));
            }
        }
    }
}
