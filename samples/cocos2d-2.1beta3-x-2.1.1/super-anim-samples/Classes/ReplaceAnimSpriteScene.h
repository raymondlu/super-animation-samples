//
//  ReplaceAnimSpriteScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 4/11/13.
//
//

#ifndef super_anim_samples_ReplaceAnimSpriteScene_h
#define super_anim_samples_ReplaceAnimSpriteScene_h

#include "cocos2d.h"
#include "common.h"
using namespace cocos2d;

enum ReplaceAnimSpriteLayerId {
	kReplaceAnimSpriteLayerNormal = 0,
	kReplaceAnimSpriteLayerRename1,
	kReplaceAnimSpriteLayerRenameAll,
	kReplaceAnimSpriteLayerRenameResize,
	kReplaceAnimSpriteLayerRenameSpriteSheet,	
	// keep last
	kReplaceAnimSpriteLayerIdCnt
};

class ReplaceAnimSpriteScene : public CCLayer, public HUDLayerListener {
	// weak reference
	CCLayer* mCurLayer;
	ReplaceAnimSpriteLayerId mCurLayerID;
	HUDLayer* mHUD;
public:
	ReplaceAnimSpriteScene();
	static CCScene* scene();
	bool init();
	void changeLayer(ReplaceAnimSpriteLayerId theNewLayer);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
};

#endif
