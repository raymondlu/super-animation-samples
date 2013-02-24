//
//  ResizedAnimScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#include "ResizedAnimScene.h"
#include "MainMenu.h"

ResizedAnimScene::ResizedAnimScene(){
	for (int i = 0; i < kAnimNodeCnt; i++) {
		mAnims[i] = NULL;
	}
	mHUD = NULL;
}

CCScene* ResizedAnimScene::scene(){
	CCScene* aScene = CCScene::create();
	ResizedAnimScene* aResizedAnims = new ResizedAnimScene();
	if (aResizedAnims->init()) {
		aResizedAnims->autorelease();
		aScene->addChild(aResizedAnims);
		return aScene;
	}
	
	CC_SAFE_DELETE(aResizedAnims);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool ResizedAnimScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	// bg
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)));
	// normal
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH);
	mAnims[kAnimNodeNormalFish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeNormalFish, this);
	addChild(mAnims[kAnimNodeNormalFish]);
	mAnims[kAnimNodeNormalFish]->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
	mAnims[kAnimNodeNormalFish]->PlaySection("idle");
	// half
	anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH_50);
	mAnims[kAnimNodeHalfFish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeHalfFish, this);
	addChild(mAnims[kAnimNodeHalfFish]);
	mAnims[kAnimNodeHalfFish]->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.5f));
	mAnims[kAnimNodeHalfFish]->PlaySection("idle");
	// 150 percent
	anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH_150);
	mAnims[kAnimNode150Fish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNode150Fish, this);
	addChild(mAnims[kAnimNode150Fish]);
	mAnims[kAnimNode150Fish]->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.5f));
	mAnims[kAnimNode150Fish]->PlaySection("idle");
	
	mHUD = HUDLayer::create(this);
	addChild(mHUD);
	mHUD->mButtons[kHUDLayerButtonPre]->setEnabled(false);
	mHUD->mButtons[kHUDLayerButtonNext]->setEnabled(false);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryResizedAnim).c_str());
	
	return true;
}

void ResizedAnimScene::OnAnimSectionEnd(int theId, std::string theLabelName){
	if (theLabelName == "idle") {
		mAnims[theId]->PlaySection("active");
	}
	if (theLabelName == "active") {
		mAnims[theId]->PlaySection("idle");
	}
}

void ResizedAnimScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
}