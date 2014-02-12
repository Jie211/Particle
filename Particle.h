//
//  Particle.h
//  OOF_Spring
//
//  Created by ChenGong on 2014/02/11.
//
//

#ifndef __OOF_Spring__Particle__
#define __OOF_Spring__Particle__

#include <iostream>
#include "ofMain.h"

class Particle{
public:
    //コンストラクタ
    Particle();
    //初期設定
    void setup(ofVec2f position,ofVec2f velocity);
    void setup(float positionX,float positionY,float velocityX,float velocityY);
    //力をリセット
    void resetForce();
    //力を加え
    void addForce(ofVec2f force);
    void addForce(float forceX,float forceY);
    //力を更新
    void updateForce();
    //位置を更新
    void updatePos();
    //力と位置を一緒に更新
    void update();
    //リバウンド
    void bouceOffWalls();
    void bouceOffWalls(float radius);
    //描画
    void draw();
    
    void fadeout(float fade);
    
    //反発する力
    void addRepulsionForce(float x,float y,float radius,float scale);
    void addRepulsionForce(Particle &p,float radius,float scale);
    
    //引きつけ合う力
    void addAttractionForce(float x,float y,float radius,float scale);
    void addAttractionForce(Particle &p,float radius,float scale);
    
    //時計回りに働く力
    void addCounterClockwiseForce(Particle &p,float radius,float scale);
    
    //位置ベクトルの配列
    ofVec2f position;
    //速度ベクトルの配列
    ofVec2f velocity;
    //力ベクトルの配列
    ofVec2f force;
    //摩擦係数
    float friction;
    //パーティクルの半径
    float radius;
    //固定するか
    bool bFixed;
};

#endif /* defined(__OOF_Spring__Particle__) */
