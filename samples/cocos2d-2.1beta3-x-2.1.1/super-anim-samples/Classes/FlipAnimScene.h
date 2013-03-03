//
//  FlipAnimScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/25/13.
//
//

#ifndef super_anim_samples_FlipAnimScene_h
#define super_anim_samples_FlipAnimScene_h

#include "cocos2d.h"
#include "common.h"
#include "SuperAnimNodeV2.h"
using namespace cocos2d;
using namespace SuperAnim;

class FlipAnimScene
: public CCLayer
, public SuperAnimNodeListener
, public HUDLayerListener
{
	enum AnimNodeId{
		kAnimNodeNormalFish = 0,
		kAnimNodeFlipXFish,
		kAnimNodeFlipYFish,
		kAnimNodeFlipXYFish,
		
		// keep last
		kAnimNodeCnt
	};
	
	SuperAnimNode* mAnims[kAnimNodeCnt];
	HUDLayer* mHUD;
public:
	FlipAnimScene();
	static CCScene* scene();
	bool init();
	void draw();
	void OnAnimSectionEnd(int theId, std::string theLabelName);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
};

#endif
