//
//  TouchedAnimScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#ifndef super_anim_samples_TouchedAnimScene_h
#define super_anim_samples_TouchedAnimScene_h

#include "cocos2d.h"
#include "common.h"
#include "SuperAnimNodeV2.h"
using namespace cocos2d;
using namespace SuperAnim;

class TouchedAnimScene
: public CCLayer
, public SuperAnimNodeListener
, public HUDLayerListener
{	
	SuperAnimNode* mAnim;
	HUDLayer* mHUD;
public:
	TouchedAnimScene();
	static CCScene* scene();
	bool init();
	void draw();
	void OnAnimSectionEnd(int theId, std::string theLabelName);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
};

#endif
