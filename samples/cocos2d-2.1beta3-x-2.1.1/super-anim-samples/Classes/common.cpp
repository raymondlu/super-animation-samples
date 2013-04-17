//
//  common.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/23/13.
//
//

#include "common.h"

std::string gTestEntryNames[kTestEntryCnt] = {
	"Basic Animation",
	"Complex Animation",
	"Resized Animation",
	"Use Sprite Sheet",
	"Flip Animatiion",
	"Replace animation sprite",
	"Time Event",
	"Touch Event",
	"Bug Fix"
};

std::string getTestEntryName(TestEntry theEntry){
	if (theEntry == kTestEntryCnt) {
		CCAssert(false, "error");
		return "";
	}
	return gTestEntryNames[theEntry];
}

const char* SAM_BASIC = "basic_transform/basic_transform.sam";
const char* SAM_ATTACK_FRONT = "attack_front/attack_front.sam";
const char* SAM_FADEIN_TAP = "fadein_tap/fadein-tap.sam";
const char* SAM_FISH = "fish/fish.sam";
const char* SAM_FISH_SPRITESHEET = "fish_spritesheet/fish.sam";
const char* SAM_FISH_50 = "fish_50/fish.sam";
const char* SAM_FISH_150 = "fish_150/fish.sam";
const char* SAM_FRAME_BY_FRAME = "frame_by_frame/frame-by-frame.sam";
const char* SAM_NO_FLICKER = "no-flicker/no-flicker.sam";
// for rename sprite feature
const char* SAM_RENAME_NORMAL = "rename_sprite/normal/attack_front.sam";
const char* SAM_RENAME_1  = "rename_sprite/rename-1/attack_front.sam";
const char* SPRITE_RENAME_1_SWORD_ORIGIN = "rename_sprite/rename-1/sword.png";
const char* SPRITE_RENAME_1_SWORD_NEW = "rename_sprite/rename-1/sword_new.png";
const char* SAM_RENAME_ALL = "rename_sprite/rename-all/fadein-tap.sam";
const char* SPRITE_RENAME_ALL_1_ORIGIN = "rename_sprite/rename-all/_1.png";
const char* SPRITE_RENAME_ALL_2_ORIGIN = "rename_sprite/rename-all/_2.png";
const char* SPRITE_RENAME_ALL_3_ORIGIN = "rename_sprite/rename-all/_3.png";
const char* SPRITE_RENAME_ALL_1_NEW = "rename_sprite/rename-all/_1_new.png";
const char* SPRITE_RENAME_ALL_2_NEW = "rename_sprite/rename-all/_2_new.png";
const char* SPRITE_RENAME_ALL_3_NEW = "rename_sprite/rename-all/_3_new.png";
const char* SAM_RENAME_RESIZE = "rename_sprite/rename-resize/attack_front.sam";
const char* SPRITE_RENAME_RESIZE_HAT_HEAD_ORIGIN = "rename_sprite/rename-resize/hat_head.png";
const char* SPRITE_RENAME_RESIZE_HAT_HEAD_NEW = "rename_sprite/rename-resize/hat_head_new.png";
const char* SAM_RENAME_SPRITESHEET = "rename_sprite/rename-spritesheet/attack_front.sam";
const char* SPRITE_RENAME_SPRITESHEET_HAT_HEAD_ORIGIN = "rename_sprite/rename-spritesheet/hat_head.png";
const char* SPRITE_RENAME_SPRITESHEET_HAT_HEAD_NEW = "rename_sprite/rename-spritesheet/hat_head_new.png";


HUDLayer::HUDLayer(){
	for (int i = 0; i < kHUDLayerButtonCnt; i++) {
		mButtons[i] = NULL;
	}
	mTitle = NULL;
}

HUDLayer* HUDLayer::create(HUDLayerListener *theListener){
	HUDLayer* aHUDLayer = new HUDLayer();
	if (aHUDLayer->init()) {
		aHUDLayer->autorelease();
		aHUDLayer->mListener = theListener;
		return aHUDLayer;
	}
	
	CC_SAFE_DELETE(aHUDLayer);
	return NULL;
}

bool HUDLayer::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	float aPadding = 30.0f;
	mTitle = CCLabelTTF::create("", "Arial", 48);
	mTitle->setAnchorPoint(ccp(0.5f, 1.0f));
	mTitle->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height - aPadding));
	addChild(mTitle);
	
	aPadding = 24;
	int anOldFontSize = CCMenuItemFont::fontSize();
	CCMenuItemFont::setFontSize(48);
	mButtons[kHUDLayerButtonPre] = CCMenuItemFont::create("Pre", this, menu_selector(HUDLayer::onButton));
	mButtons[kHUDLayerButtonPre]->setPosition(ccp(160, aPadding));
	
	mButtons[kHUDLayerButtonNext] = CCMenuItemFont::create("Next", this, menu_selector(HUDLayer::onButton));
	mButtons[kHUDLayerButtonNext]->setPosition(ccp(aScreenSize.width - 60, aPadding));
	
	mButtons[kHUDLayerButtonMainmenu] = CCMenuItemFont::create("Mainmenu", this, menu_selector(HUDLayer::onButton));
	mButtons[kHUDLayerButtonMainmenu]->setPosition(ccp(aScreenSize.width * 0.5f, aPadding));
	
	CCMenuItemFont::setFontSize(anOldFontSize);
	
	CCMenu* aMenu = CCMenu::create(mButtons[kHUDLayerButtonPre], mButtons[kHUDLayerButtonMainmenu], mButtons[kHUDLayerButtonNext], NULL);
	addChild(aMenu);
	aMenu->setPosition(CCPointZero);
	
	return true;
}

void HUDLayer::onButton(cocos2d::CCObject *theSender){
	HUDLayerButton aPressedBtn = kHUDLayerButtonCnt;
	for (int i = 0; i < kHUDLayerButtonCnt; i++) {
		if (theSender == mButtons[i]) {
			CCLog("HUD layer: button %d is pressed.", i);
			aPressedBtn = (HUDLayerButton)i;
			break;
		}
	}
	if (aPressedBtn != kHUDLayerButtonCnt &&
		mListener) {
		mListener->onHUDLayerButton(aPressedBtn);
	}
}