//
//  ResizedAnimScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#ifndef super_anim_samples_ResizedAnimScene_h
#define super_anim_samples_ResizedAnimScene_h

#include "cocos2d.h"
#include "common.h"
#include "SuperAnimNodeV2.h"
using namespace cocos2d;
using namespace SuperAnim;

class ResizedAnimScene
: public CCLayer
, public SuperAnimNodeListener
, public HUDLayerListener
{
	enum AnimNodeId{
		kAnimNodeNormalFish = 0,
		kAnimNodeHalfFish,
		kAnimNode150Fish,
		
		// keep last
		kAnimNodeCnt
	};
	
	SuperAnimNode* mAnims[kAnimNodeCnt];
	HUDLayer* mHUD;
public:
	ResizedAnimScene();
	static CCScene* scene();
	bool init();
	void OnAnimSectionEnd(int theId, std::string theLabelName);
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
};

#endif
