//
//  BugFixScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#ifndef super_anim_samples_BugFixScene_h
#define super_anim_samples_BugFixScene_h

#include "cocos2d.h"
#include "common.h"
using namespace cocos2d;

enum BugFixSceneLayerID{
	kBugFixSceneLayerAlphaBlend1 = 0,
	kBugFixSceneLayerAlphaBlend2,
	kBugFixSceneLayerDepth1,
	kBugFixSceneLayerDepth2,
	
	// keep last
	kBugFixSceneLayerCnt
};

class BugFixScene : public CCLayer, public HUDLayerListener {
	// weak reference
	CCLayer* mCurLayer;
	BugFixSceneLayerID mCurLayerID;
	HUDLayer* mHUD;
public:
	BugFixScene();
	static CCScene* scene();
	bool init();
	void changeLayer(BugFixSceneLayerID theNewLayer);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
};

#endif
