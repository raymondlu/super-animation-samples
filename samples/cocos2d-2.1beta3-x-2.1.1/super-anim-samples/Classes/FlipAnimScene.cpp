//
//  FlipAnimScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/25/13.
//
//

#include "FlipAnimScene.h"

#include "MainMenu.h"

FlipAnimScene::FlipAnimScene(){
	for (int i = 0; i < kAnimNodeCnt; i++) {
		mAnims[i] = NULL;
	}
	mHUD = NULL;
}

CCScene* FlipAnimScene::scene(){
	CCScene* aScene = CCScene::create();
	FlipAnimScene* aFlipAnims = new FlipAnimScene();
	if (aFlipAnims->init()) {
		aFlipAnims->autorelease();
		aScene->addChild(aFlipAnims);
		return aScene;
	}
	
	CC_SAFE_DELETE(aFlipAnims);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool FlipAnimScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	// bg
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)), -1);
	// normal
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH_SPRITESHEET);
	mAnims[kAnimNodeNormalFish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeNormalFish, this);
	addChild(mAnims[kAnimNodeNormalFish]);
	mAnims[kAnimNodeNormalFish]->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.25f));
	mAnims[kAnimNodeNormalFish]->PlaySection("idle");
	// flip x
	mAnims[kAnimNodeFlipXFish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeFlipXFish, this);
	addChild(mAnims[kAnimNodeFlipXFish]);
	mAnims[kAnimNodeFlipXFish]->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.25f));
	mAnims[kAnimNodeFlipXFish]->PlaySection("idle");
	mAnims[kAnimNodeFlipXFish]->setFlipX(true);
	// flip y
	mAnims[kAnimNodeFlipYFish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeFlipYFish, this);
	addChild(mAnims[kAnimNodeFlipYFish]);
	mAnims[kAnimNodeFlipYFish]->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.75f));
	mAnims[kAnimNodeFlipYFish]->PlaySection("idle");
	mAnims[kAnimNodeFlipYFish]->setFlipY(true);
	// flip xy
	mAnims[kAnimNodeFlipXYFish] = SuperAnimNode::create(anAnimFileFullPath.c_str(), kAnimNodeFlipXYFish, this);
	addChild(mAnims[kAnimNodeFlipXYFish]);
	mAnims[kAnimNodeFlipXYFish]->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.75f));
	mAnims[kAnimNodeFlipXYFish]->PlaySection("idle");
	mAnims[kAnimNodeFlipXYFish]->setFlipX(true);
	mAnims[kAnimNodeFlipXYFish]->setFlipY(true);
	
	mHUD = HUDLayer::create(this);
	addChild(mHUD);
	mHUD->mButtons[kHUDLayerButtonPre]->setEnabled(false);
	mHUD->mButtons[kHUDLayerButtonNext]->setEnabled(false);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryFlipAnim).c_str());
	
	return true;
}

void FlipAnimScene::draw(){
	CCLayer::draw();
	
	for (int i = 0; i < kAnimNodeCnt; i++) {
		if (mAnims[i]) {
			CCRect aAnimRect = mAnims[i]->boundingBox();
			CCSize s = aAnimRect.size;
			CCPoint offsetPix = aAnimRect.origin;
			CCPoint vertices[4] = {
				ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
				ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
			};
			ccDrawPoly(vertices, 4, true);
		}

	}
}

void FlipAnimScene::OnAnimSectionEnd(int theId, std::string theLabelName){
	if (theLabelName == "idle") {
		mAnims[theId]->PlaySection("active");
	}
	if (theLabelName == "active") {
		mAnims[theId]->PlaySection("idle");
	}
}

void FlipAnimScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
}