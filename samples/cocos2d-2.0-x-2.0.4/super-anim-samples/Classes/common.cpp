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
	"Touch Event in Animation",
	"Flip Animation",
	"Set Transparent for Animation",
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
	float aPadding = 10.0f;
	
	mTitle = CCLabelTTF::create("", "Arial", 18);
	mTitle->setAnchorPoint(ccp(0.5f, 1.0f));
	mTitle->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height - aPadding));
	addChild(mTitle);
	
	int anOldFontSize = CCMenuItemFont::fontSize();
	CCMenuItemFont::setFontSize(24);
	mButtons[kHUDLayerButtonPre] = CCMenuItemFont::create("Pre", this, menu_selector(HUDLayer::onButton));
	mButtons[kHUDLayerButtonPre]->setAnchorPoint(ccp(0.0f, 0.0f));
	mButtons[kHUDLayerButtonPre]->setPosition(ccp(aPadding, aPadding));
	
	mButtons[kHUDLayerButtonNext] = CCMenuItemFont::create("Next", this, menu_selector(HUDLayer::onButton));
	mButtons[kHUDLayerButtonNext]->setAnchorPoint(ccp(1.0f, 0.0f));
	mButtons[kHUDLayerButtonPre]->setPosition(ccp(aScreenSize.width - aPadding, aPadding));
	
	mButtons[kHUDLayerButtonMainmenu] = CCMenuItemFont::create("Mainmenu", this, menu_selector(HUDLayer::onButton));
	mButtons[kHUDLayerButtonMainmenu]->setAnchorPoint(ccp(0.5f, 0.0f));
	mButtons[kHUDLayerButtonMainmenu]->setPosition(ccp(aScreenSize.width * 0.5f, aPadding));
	
	CCMenuItemFont::setFontSize(anOldFontSize);
	
	CCMenu* aMenu = CCMenu::create(mButtons[kHUDLayerButtonPre], mButtons[kHUDLayerButtonMainmenu], mButtons[kHUDLayerButtonNext], NULL);
	addChild(aMenu);
	
	return true;
}

void HUDLayer::onButton(cocos2d::CCObject *theSender){
	HUDLayerButton aPressedBtn = kHUDLayerButtonCnt;
	for (int i = 0; i < kHUDLayerButtonCnt; i++) {
		if (theSender == mButtons[kHUDLayerButtonPre]) {
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