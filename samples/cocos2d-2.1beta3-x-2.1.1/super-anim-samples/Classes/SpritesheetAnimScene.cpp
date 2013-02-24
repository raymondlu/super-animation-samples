//
//  SpritesheetAnimScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#include "SpritesheetAnimScene.h"
#include "MainMenu.h"

SpritesheetAnimScene::SpritesheetAnimScene(){
	for (int i = 0; i < kAnimNodeCnt; i++) {
		mAnims[i] = NULL;
	}
	mHUD = NULL;
}

CCScene* SpritesheetAnimScene::scene(){
	CCScene* aScene = CCScene::create();
	SpritesheetAnimScene* aSpritesheetAnims = new SpritesheetAnimScene();
	if (aSpritesheetAnims->init()) {
		aSpritesheetAnims->autorelease();
		aScene->addChild(aSpritesheetAnims);
		return aScene;
	}
	
	CC_SAFE_DELETE(aSpritesheetAnims);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool SpritesheetAnimScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	// bg
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)));
	// no sprite sheet
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH);
	mAnims[kAnimNodeNoSpritesheet] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeNoSpritesheet, this);
	addChild(mAnims[kAnimNodeNoSpritesheet]);
	mAnims[kAnimNodeNoSpritesheet]->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.5f));
	mAnims[kAnimNodeNoSpritesheet]->PlaySection("idle");
	CCLabelTTF *aLabel = CCLabelTTF::create("No Sprite Sheet", "Arial", 36);
	addChild(aLabel);
	aLabel->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.35f));
	
	// sprite sheet
	anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH_SPRITESHEET);
	mAnims[kAnimNodeSpritesheet] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeSpritesheet, this);
	addChild(mAnims[kAnimNodeSpritesheet]);
	mAnims[kAnimNodeSpritesheet]->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.5f));
	mAnims[kAnimNodeSpritesheet]->PlaySection("idle");
	aLabel = CCLabelTTF::create("Sprite Sheet", "Arial", 36);
	addChild(aLabel);
	aLabel->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.35f));
	
	mHUD = HUDLayer::create(this);
	addChild(mHUD);
	mHUD->mButtons[kHUDLayerButtonPre]->setEnabled(false);
	mHUD->mButtons[kHUDLayerButtonNext]->setEnabled(false);
	mHUD->mTitle->setString(getTestEntryName(kTestEntrySpritesheetAnim).c_str());
	
	return true;
}

void SpritesheetAnimScene::OnAnimSectionEnd(int theId, std::string theLabelName){
	if (theLabelName == "idle") {
		mAnims[theId]->PlaySection("active");
	}
	if (theLabelName == "active") {
		mAnims[theId]->PlaySection("idle");
	}
}

void SpritesheetAnimScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
}