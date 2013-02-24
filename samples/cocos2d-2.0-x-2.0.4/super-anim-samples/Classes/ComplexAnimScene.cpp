//
//  ComplexAnimScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#include "ComplexAnimScene.h"
#include "MainMenu.h"
#include "SuperAnimNodeV2.h"
using namespace SuperAnim;

class FishAnimLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
public:
	FishAnimLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("idle");
	}
	
	static FishAnimLayer* create(){
		FishAnimLayer* aLayer = new FishAnimLayer();
		aLayer->autorelease();
		return aLayer;
	}
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// loop the animation
		if (theLabelName == "idle") {
			mAnimNode->PlaySection("active");
		}
		if (theLabelName == "active") {
			mAnimNode->PlaySection("idle");
		}
	}
};

class AttackAnimLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
public:
	AttackAnimLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_ATTACK_FRONT);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("attack");
	}
	
	static AttackAnimLayer* create(){
		AttackAnimLayer* aLayer = new AttackAnimLayer();
		aLayer->autorelease();
		return aLayer;
	}
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// loop the animation
		if (theLabelName == "attack") {
			mAnimNode->PlaySection("attack");
		}
	}
};

class FadeinTapAnimLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
public:
	FadeinTapAnimLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FADEIN_TAP);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("fadein");
	}
	
	static FadeinTapAnimLayer* create(){
		FadeinTapAnimLayer* aLayer = new FadeinTapAnimLayer();
		aLayer->autorelease();
		return aLayer;
	}
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// loop the animation
		if (theLabelName == "fadein") {
			mAnimNode->PlaySection("tap");
		}
		if (theLabelName == "tap") {
			mAnimNode->PlaySection("tap");
		}
	}
};

ComplexAnimScene::ComplexAnimScene(){
	mCurLayer = NULL;
	mCurLayerID = kLayerCnt;
	mHUD = NULL;
}

CCScene* ComplexAnimScene::scene(){
	CCScene* aScene = CCScene::create();
	ComplexAnimScene* aComplexAnim = new ComplexAnimScene();
	if (aComplexAnim->init()) {
		aComplexAnim->autorelease();
		aScene->addChild(aComplexAnim);
		return aScene;
	}
	CC_SAFE_DELETE(aComplexAnim);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool ComplexAnimScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	// background
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)));
	
	mHUD = HUDLayer::create(this);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryComplexAnim).c_str());
	addChild(mHUD, 1);
	
	changeLayer(kLayerFishAnim);
	return true;
}

void ComplexAnimScene::changeLayer(ComplexAnimScene::LayerID theNewLayer){
	if (mCurLayer) {
		mCurLayer->removeFromParentAndCleanup(true);
		mCurLayer = NULL;
		mCurLayerID = kLayerCnt;
	}
	if (theNewLayer == kLayerFishAnim) {
		mCurLayerID = theNewLayer;
		mCurLayer = FishAnimLayer::create();
		addChild(mCurLayer);
	}
	if (theNewLayer == kLayerAttackFront) {
		mCurLayerID = theNewLayer;
		mCurLayer = AttackAnimLayer::create();
		addChild(mCurLayer);
	}
	if (theNewLayer == kLayerFadeinTap) {
		mCurLayerID = theNewLayer;
		mCurLayer = FadeinTapAnimLayer::create();
		addChild(mCurLayer);
	}
}

void ComplexAnimScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
	if (thePressedBtn == kHUDLayerButtonNext) {
		LayerID aNewLayerId;
		if (mCurLayerID + 1 == kLayerCnt) {
			aNewLayerId = kLayerFishAnim;
		} else {
			aNewLayerId = (LayerID)(mCurLayerID + 1);
		}
		changeLayer(aNewLayerId);
	}
	if (thePressedBtn == kHUDLayerButtonPre) {
		LayerID aNewLayerId;
		if (mCurLayerID - 1 < 0) {
			aNewLayerId = (LayerID)(kLayerCnt - 1);
		} else {
			aNewLayerId = (LayerID)(mCurLayerID - 1);
		}
		changeLayer(aNewLayerId);
	}
}