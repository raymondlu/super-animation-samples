//
//  MainMenu.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/23/13.
//
//

#ifndef super_anim_samples_MainMenu_h
#define super_anim_samples_MainMenu_h

#include "cocos2d.h"
#include "common.h"
using namespace cocos2d;

class MainMenuScene: public CCLayer {
	// weak reference
	CCMenuItemFont* mEntries[kTestEntryCnt];
	CCMenu* mEntryContainer;
public:
	MainMenuScene();
	static CCScene* scene();
	bool init();
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void onEntry(CCObject* theSender);
};

#endif
