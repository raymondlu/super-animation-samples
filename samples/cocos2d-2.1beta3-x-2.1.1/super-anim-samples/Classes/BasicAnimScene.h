//
//  BasicAnimScene.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#ifndef super_anim_samples_BasicAnimScene_h
#define super_anim_samples_BasicAnimScene_h

#include "cocos2d.h"
#include "common.h"
#include "SuperAnimNodeV2.h"
using namespace cocos2d;
using namespace SuperAnim;

class BasicAnimScene
: public CCLayer
, public HUDLayerListener
, public SuperAnimNodeListener
{
	HUDLayer* mHUDLayer;
	SuperAnimNode* mAnim;
public:
	BasicAnimScene();
	static CCScene* scene();
	bool init();
	void onHUDLayerButton(HUDLayerButton thePressedBtn);
	void OnAnimSectionEnd(int theId, std::string theLabelName);
};

#endif
