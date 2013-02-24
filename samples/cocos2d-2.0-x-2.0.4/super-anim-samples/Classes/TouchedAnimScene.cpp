//
//  TouchedAnimScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#include "TouchedAnimScene.h"
#include "MainMenu.h"

TouchedAnimScene::TouchedAnimScene(){
	mAnim = NULL;
	mHUD = NULL;
}

CCScene* TouchedAnimScene::scene(){
	CCScene* aScene = CCScene::create();
	TouchedAnimScene* aTouchedAnim = new TouchedAnimScene();
	if (aTouchedAnim->init()) {
		aTouchedAnim->autorelease();
		aScene->addChild(aTouchedAnim);
		return aScene;
	}
	
	CC_SAFE_DELETE(aTouchedAnim);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool TouchedAnimScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	
	// bg
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)), -1);
	
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH);
	mAnim = SuperAnimNode::create(anAnimFileFullPath, 0, this);
	addChild(mAnim);
	mAnim->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
	mAnim->PlaySection("idle");
	
	CCLabelTTF *aLabel = CCLabelTTF::create("Touch in the rect to play next section", "Arial", 24);
	addChild(aLabel);
	aLabel->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.35f));
	
	mHUD = HUDLayer::create(this);
	addChild(mHUD);
	mHUD->mButtons[kHUDLayerButtonPre]->setEnabled(false);
	mHUD->mButtons[kHUDLayerButtonNext]->setEnabled(false);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryTouchedAnim).c_str());
	
	setTouchEnabled(true);
	
	return true;
}

void TouchedAnimScene::draw(){
	CCLayer::draw();
	
	if (mAnim) {
		CCRect aAnimRect = mAnim->boundingBox();
		CCSize s = aAnimRect.size;
		CCPoint offsetPix = aAnimRect.origin;
		CCPoint vertices[4] = {
			ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
			ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
		};
		ccDrawPoly(vertices, 4, true);
	}
}

void TouchedAnimScene::OnAnimSectionEnd(int theId, std::string theLabelName){
	if (theLabelName == "idle") {
		mAnim->PlaySection("idle");
	}
	if (theLabelName == "active") {
		mAnim->PlaySection("idle");
	}
}

void TouchedAnimScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
}

void TouchedAnimScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCTouch* aTouch = (CCTouch*)(*pTouches->begin());
	CCPoint aTouchedPoint = convertTouchToNodeSpace(aTouch);
	if (mAnim->boundingBox().containsPoint(aTouchedPoint)) {
		if (mAnim->GetCurSectionName() != "active") {
			// play active section of the animation
			mAnim->PlaySection("active");
		}
	}
}