//
//  TimeEventScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 4/17/13.
//
//

#ifndef super_anim_samples_TimeEventScene_h
#define super_anim_samples_TimeEventScene_h


#include "cocos2d.h"
#include "common.h"
using namespace cocos2d;

enum TimeEventSceneLayerID{
	kTimeEventSceneLayerAttackToDie = 0,
	//kTimeEventSceneLayerAttackToDamage,
	
	// keep last
	kTimeEventSceneLayerCnt
};

class TimeEventScene : public CCLayer, public HUDLayerListener {
	// weak reference
	CCLayer* mCurLayer;
	TimeEventSceneLayerID mCurLayerID;
	HUDLayer* mHUD;
public:
	TimeEventScene();
	static CCScene* scene();
	bool init();
	void changeLayer(TimeEventSceneLayerID theNewLayer);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
};

#endif
