//
//  common.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/23/13.
//
//

#ifndef super_anim_samples_common_h
#define super_anim_samples_common_h

#include "cocos2d.h"
using namespace cocos2d;

enum TestEntry {
	kTestEntryBasicAnim = 0,
	kTestEntryComplexAnim,
	kTestEntryResizedAnim,
	kTestEntrySpritesheetAnim,
	kTestEntryFlipAnim,
	kTestEntryTouchedAnim,
	kTestEntryBugFix,
	
	// keep last
	kTestEntryCnt
};

extern std::string getTestEntryName(TestEntry theEntry);

// animations used in our samples, which is located at "auto_sync_resource" folder
extern const char* SAM_BASIC;
extern const char* SAM_ATTACK_FRONT;
extern const char* SAM_FADEIN_TAP;
extern const char* SAM_FISH;
extern const char* SAM_FISH_SPRITESHEET;
extern const char* SAM_FISH_50;
extern const char* SAM_FISH_150;

enum HUDLayerButton{
	kHUDLayerButtonPre = 0,
	kHUDLayerButtonNext,
	kHUDLayerButtonMainmenu,
	
	// keep last
	kHUDLayerButtonCnt
};

class HUDLayerListener {
public:
	virtual void onHUDLayerButton(HUDLayerButton thePressedBtn){}
};

class HUDLayer : public CCLayer {
public:
	// weak reference
	CCMenuItemFont* mButtons[kHUDLayerButtonCnt];
	CCLabelTTF* mTitle;
	HUDLayerListener* mListener;
public:
	HUDLayer();
	static HUDLayer* create(HUDLayerListener* theListener);
	bool init();
	void onButton(CCObject* theSender);
};

#endif
