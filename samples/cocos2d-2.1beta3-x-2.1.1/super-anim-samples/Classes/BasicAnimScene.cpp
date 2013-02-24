//
//  BasicAnimScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#include "BasicAnimScene.h"
#include "MainMenu.h"

BasicAnimScene::BasicAnimScene(){
	mHUDLayer = NULL;
	mAnim = NULL;
}

CCScene* BasicAnimScene::scene(){
	CCScene* aScene = CCScene::create();
	BasicAnimScene* aBasicAnim = new BasicAnimScene();
	if (aBasicAnim->init()) {
		aBasicAnim->autorelease();
		aScene->addChild(aBasicAnim);
		return aScene;
	}
	CC_SAFE_DELETE(aBasicAnim);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool BasicAnimScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_BASIC);
	mAnim = SuperAnimNode::create(anAnimFileFullPath, 0, this);
	addChild(mAnim);
	mAnim->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
	mAnim->PlaySection("fade");
	
	mHUDLayer = HUDLayer::create(this);
	addChild(mHUDLayer);
	mHUDLayer->mButtons[kHUDLayerButtonPre]->setEnabled(false);
	mHUDLayer->mButtons[kHUDLayerButtonNext]->setEnabled(false);
	mHUDLayer->mTitle->setString(getTestEntryName(kTestEntryBasicAnim).c_str());
	return true;
}

void BasicAnimScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
}

void BasicAnimScene::OnAnimSectionEnd(int theId, std::string theLabelName){
	// loop the animation
	if (theLabelName == "fade") {
		mAnim->PlaySection("mixed");
	}
	if (theLabelName == "mixed") {
		mAnim->PlaySection("fade");
	}
}