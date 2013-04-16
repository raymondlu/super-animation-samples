//
//  BugFixScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/24/13.
//
//

#include "BugFixScene.h"
#include "MainMenu.h"
#include "SuperAnimNodeV2.h"
using namespace SuperAnim;

class AlphaBlendLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
public:
	AlphaBlendLayer(BugFixSceneLayerID theLayerID){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode, 1);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("idle");
		
		CCSprite* aSprite = CCSprite::create("HelloWorld.png");
		if (theLayerID == kBugFixSceneLayerAlphaBlend1) {
			addChild(aSprite, 0);
			aSprite->setAnchorPoint(ccp(1.0f, 0.5f));
			aSprite->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		} else if (theLayerID == kBugFixSceneLayerAlphaBlend2){
			addChild(aSprite, 2);
			aSprite->setAnchorPoint(ccp(0.0f, 0.5f));
			aSprite->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));

		}
	}
	
	static AlphaBlendLayer* create(BugFixSceneLayerID theLayerID){
		AlphaBlendLayer* aLayer = new AlphaBlendLayer(theLayerID);
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

class DepthLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
	BugFixSceneLayerID mLayerId;
public:
	DepthLayer(BugFixSceneLayerID theLayerID){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		if (theLayerID == kBugFixSceneLayerDepth1) {
			mLayerId = kBugFixSceneLayerDepth1;
			std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_ATTACK_FRONT);
			mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
			addChild(mAnimNode);
			mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
			mAnimNode->PlaySection("attack");
			CCLabelTTF* aLayer = CCLabelTTF::create("Beard is OK", "Arial", 24);
			addChild(aLayer);
			aLayer->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.35f));
		} else if (theLayerID == kBugFixSceneLayerDepth2){
			mLayerId = kBugFixSceneLayerDepth2;
			std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FADEIN_TAP);
			mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
			addChild(mAnimNode);
			mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
			mAnimNode->PlaySection("fadein");
			CCLabelTTF* aLayer = CCLabelTTF::create("Tap animation must be played", "Arial", 24);
			addChild(aLayer);
			aLayer->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.35f));
		} else {
			CCAssert(false, "error");
		}
	}
	
	static DepthLayer* create(BugFixSceneLayerID theLayerID){
		DepthLayer* aDepthLayer = new DepthLayer(theLayerID);
		aDepthLayer->autorelease();
		return aDepthLayer;
	}
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		if (mLayerId == kBugFixSceneLayerDepth1) {
			if (theLabelName == "attack") {
				mAnimNode->PlaySection("attack");
			}
		}
		if (mLayerId == kBugFixSceneLayerDepth2) {
			if (theLabelName == "fadein") {
				mAnimNode->PlaySection("tap");
			}
			if (theLabelName == "tap") {
				mAnimNode->PlaySection("fadein");
			}
		}
	}
};

class SpriteSheetPerformanceLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode[30];
public:
	SpriteSheetPerformanceLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH_SPRITESHEET);
		for (int i = 0; i < 30; i++) {
			mAnimNode[i] = SuperAnimNode::create(anAnimFileFullPath, i, this);
			addChild(mAnimNode[i]);
			int aRow = i / 5;
			int aCol = i % 5;
			mAnimNode[i]->setPosition(ccp(aScreenSize.width * (0.25f + aCol * 0.1), aScreenSize.height * (0.25f + aRow * 0.1)));
			mAnimNode[i]->PlaySection("idle");
		}
		
		CCLabelTTF* aLayer = CCLabelTTF::create("Please check FPS", "Arial", 48);
		addChild(aLayer);
		aLayer->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.15f));
	}
	
	static SpriteSheetPerformanceLayer* create(){
		SpriteSheetPerformanceLayer* aLayer = new SpriteSheetPerformanceLayer();
		aLayer->autorelease();
		return aLayer;
	}
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// loop the animation
		if (theLabelName == "idle") {
			mAnimNode[theId]->PlaySection("active");
		}
		if (theLabelName == "active") {
			mAnimNode[theId]->PlaySection("idle");
		}
	}
};

/*
class FrameByFrameLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
public:
	FrameByFrameLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FRAME_BY_FRAME);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("run2");
		CCLabelTTF* aLayer = CCLabelTTF::create("Number 1 should be displayed.", "Arial", 48);
		addChild(aLayer);
		aLayer->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.25f));
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		mAnimNode->PlaySection("run2");
	}
	static FrameByFrameLayer* create(){
		FrameByFrameLayer* aLayer = new FrameByFrameLayer();
		aLayer->autorelease();
		return aLayer;
	}
};
*/

class VariableAnimSpeedLayer : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode[3];
public:
	VariableAnimSpeedLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_FISH_SPRITESHEET);
		for (int i = 0; i < 3; i++) {
			mAnimNode[i] = SuperAnimNode::create(anAnimFileFullPath, i, this);
			addChild(mAnimNode[i]);
			mAnimNode[i]->setPosition(ccp(aScreenSize.width * (0.25f + i * 0.2), aScreenSize.height * (0.45f)));
			mAnimNode[i]->PlaySection("idle");
			mAnimNode[i]->setSpeedFactor(0.5f * (i + 1));
		}
		
		CCLabelTTF* aLayer = CCLabelTTF::create("Speed factor: 0.5", "Arial", 24);
		addChild(aLayer);
		aLayer->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.35f));
		aLayer = CCLabelTTF::create("Speed factor: 1.0", "Arial", 24);
		addChild(aLayer);
		aLayer->setPosition(ccp(aScreenSize.width * 0.45f, aScreenSize.height * 0.35f));
		aLayer = CCLabelTTF::create("Speed factor: 1.5", "Arial", 24);
		addChild(aLayer);
		aLayer->setPosition(ccp(aScreenSize.width * 0.65f, aScreenSize.height * 0.35f));
	}
	
	static VariableAnimSpeedLayer* create(){
		VariableAnimSpeedLayer* aLayer = new VariableAnimSpeedLayer();
		aLayer->autorelease();
		return aLayer;
	}
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// loop the animation
		if (theLabelName == "idle") {
			mAnimNode[theId]->PlaySection("active");
		}
		if (theLabelName == "active") {
			mAnimNode[theId]->PlaySection("idle");
		}
	}
};


class NoFlickerLayer : public CCLayer, public SuperAnimNodeListener {
	enum Section{
		kSectionRightGo = 0,
		kSectionLeftGo,
		kSectionRightAttack,
		kSectionLeftAttack,
		kSectionRightAttack02,
		kSectionLeftAttack02,
		kSectionRightDoubleAttack,
		kSectionLeftDoubleAttack,
		kSectionRightDie,
		kSectionLeftDie,
		kSectionRightIdle,
		kSectionLeftIdle,
		
		// keep last
		kSectionCnt
	};
	
	const char* gSectionNames[kSectionCnt] = {
		"right_go",
		"left_go",
		"right_attack",
		"left_attack",
		"right_attack02",
		"left_attack02",
		"right_doubleattack",
		"left_doubleattack",
		"right_die",
		"left_die",
		"right_idle",
		"left_idle",
	};
	
	SuperAnimNode* mAnimNode;
	Section mCurSection;
	CCLabelTTF* mLabelCurSection;
public:
	NoFlickerLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_NO_FLICKER);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, \
								   aScreenSize.height * 0.5f));
		mCurSection = kSectionRightGo;
		mAnimNode->PlaySection(gSectionNames[mCurSection]);
		
		mLabelCurSection = CCLabelTTF::create(gSectionNames[mCurSection], "Arial", 24);
		addChild(mLabelCurSection);
		mLabelCurSection->setPosition(ccp(aScreenSize.width * 0.5f, \
										  aScreenSize.height * 0.85f));
		CCLabelTTF* aLabelTip = CCLabelTTF::create("Tap the screen to play next section.\n no section flicker.", "Arial", 24);
		addChild(aLabelTip);
		aLabelTip->setPosition(ccp(aScreenSize.width * 0.5f, \
								   aScreenSize.height * 0.25f));
		
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	}
	static NoFlickerLayer* create(){
		NoFlickerLayer* aLayer = new NoFlickerLayer();
		aLayer->autorelease();
		return aLayer;
	}
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
		mCurSection = (Section)((mCurSection + 1) % kSectionCnt);
		mAnimNode->PlaySection(gSectionNames[mCurSection]);
		mLabelCurSection->setString(gSectionNames[mCurSection]);
		return true;
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		mAnimNode->PlaySection(gSectionNames[mCurSection]);
	}
};


BugFixScene::BugFixScene(){
	mCurLayer = NULL;
	mCurLayerID = kBugFixSceneLayerCnt;
	mHUD = NULL;
}

CCScene* BugFixScene::scene(){
	CCScene* aScene = CCScene::create();
	BugFixScene* aComplexAnim = new BugFixScene();
	if (aComplexAnim->init()) {
		aComplexAnim->autorelease();
		aScene->addChild(aComplexAnim);
		return aScene;
	}
	CC_SAFE_DELETE(aComplexAnim);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool BugFixScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	// background
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)));
	
	mHUD = HUDLayer::create(this);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryBugFix).c_str());
	addChild(mHUD, 1);
	
	changeLayer(kBugFixSceneLayerAlphaBlend1);
	return true;
}

void BugFixScene::changeLayer(BugFixSceneLayerID theNewLayer){
	if (mCurLayer) {
		mCurLayer->removeFromParentAndCleanup(true);
		mCurLayer = NULL;
		mCurLayerID = kBugFixSceneLayerCnt;
	}
	if (theNewLayer == kBugFixSceneLayerAlphaBlend1) {
		mCurLayerID = theNewLayer;
		mCurLayer = AlphaBlendLayer::create(kBugFixSceneLayerAlphaBlend1);
		addChild(mCurLayer);
	}
	if (theNewLayer == kBugFixSceneLayerAlphaBlend2) {
		mCurLayerID = theNewLayer;
		mCurLayer = AlphaBlendLayer::create(kBugFixSceneLayerAlphaBlend2);
		addChild(mCurLayer);
	}
	if (theNewLayer == kBugFixSceneLayerDepth1) {
		mCurLayerID = theNewLayer;
		mCurLayer = DepthLayer::create(kBugFixSceneLayerDepth1);
		addChild(mCurLayer);
	}
	if (theNewLayer == kBugFixSceneLayerDepth2) {
		mCurLayerID = kBugFixSceneLayerDepth2;
		mCurLayer = DepthLayer::create(kBugFixSceneLayerDepth2);
		addChild(mCurLayer);
	}
	if (theNewLayer == kBugFixSceneLayerSpriteSheetPerformance) {
		mCurLayerID = kBugFixSceneLayerSpriteSheetPerformance;
		mCurLayer = SpriteSheetPerformanceLayer::create();
		addChild(mCurLayer);
	}
/*
	if (theNewLayer == kBugFixSceneLayerFrameByFrame) {
		mCurLayerID = kBugFixSceneLayerFrameByFrame;
		mCurLayer = FrameByFrameLayer::create();
		addChild(mCurLayer);
	}
*/	
	if (theNewLayer == kBugFixSceneLayerVairableSpeed) {
		mCurLayerID = kBugFixSceneLayerVairableSpeed;
		mCurLayer = VariableAnimSpeedLayer::create();
		addChild(mCurLayer);
	}
	
	if (theNewLayer == kBugFixSceneLayerNoFlicker) {
		mCurLayerID = kBugFixSceneLayerNoFlicker;
		mCurLayer = NoFlickerLayer::create();
		addChild(mCurLayer);
	}
}

void BugFixScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
	if (thePressedBtn == kHUDLayerButtonNext) {
		BugFixSceneLayerID aNewLayerId;
		if (mCurLayerID + 1 == kBugFixSceneLayerCnt) {
			aNewLayerId = kBugFixSceneLayerAlphaBlend1;
		} else {
			aNewLayerId = (BugFixSceneLayerID)(mCurLayerID + 1);
		}
		changeLayer(aNewLayerId);
	}
	if (thePressedBtn == kHUDLayerButtonPre) {
		BugFixSceneLayerID aNewLayerId;
		if (mCurLayerID - 1 < 0) {
			aNewLayerId = (BugFixSceneLayerID)(kBugFixSceneLayerCnt - 1);
		} else {
			aNewLayerId = (BugFixSceneLayerID)(mCurLayerID - 1);
		}
		changeLayer(aNewLayerId);
	}
}