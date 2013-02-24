//
//  ComplexAnimScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#ifndef super_anim_samples_ComplexAnimScene_h
#define super_anim_samples_ComplexAnimScene_h

#include "cocos2d.h"
#include "common.h"
using namespace cocos2d;

class ComplexAnimScene : public CCLayer, public HUDLayerListener {
	enum LayerID{
		kLayerFishAnim = 0,
		kLayerAttackFront,
		kLayerFadeinTap,
		
		// keep last
		kLayerCnt
	};
	
	// weak reference
	CCLayer* mCurLayer;
	LayerID mCurLayerID;
	HUDLayer* mHUD;
public:
	ComplexAnimScene();
	static CCScene* scene();
	bool init();
	void changeLayer(LayerID theNewLayer);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
};

#endif
