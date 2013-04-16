//
//  ReplaceAnimSpriteScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 4/11/13.
//
//

#include "ReplaceAnimSpriteScene.h"
#include "MainMenu.h"
#include "SuperAnimNodeV2.h"
using namespace SuperAnim;

class ReplaceAnimSpriteLayerNormal : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
public:
	ReplaceAnimSpriteLayerNormal(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_RENAME_NORMAL);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("attack");
		
		CCLabelTTF* aTip = CCLabelTTF::create("Without replacing sprite", "Arial", 24);
		addChild(aTip);
		aTip->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.25f));
	}
	~ReplaceAnimSpriteLayerNormal(){
	}
	static ReplaceAnimSpriteLayerNormal* create(){
		ReplaceAnimSpriteLayerNormal* aLayer = new ReplaceAnimSpriteLayerNormal();
		aLayer->autorelease();
		return aLayer;
	}
	
	void onEnter(){
		CCLayer::onEnter();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	}
	
	void onExit(){
		CCLayer::onExit();
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
		// do nothing
		return true;
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// repeat
		mAnimNode->PlaySection("attack");
	}
};

class ReplaceAnimSpriteLayerRename1 : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
	bool mIsOrigin;
public:
	ReplaceAnimSpriteLayerRename1(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_RENAME_1);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("attack");
		mIsOrigin = true;
		
		CCLabelTTF* aTip = CCLabelTTF::create("Tap the screen to replace anim sprite\nReplace 1 sprite", "Arial", 24);
		addChild(aTip);
		aTip->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.25f));
	}
	~ReplaceAnimSpriteLayerRename1(){
	}
	static ReplaceAnimSpriteLayerRename1* create(){
		ReplaceAnimSpriteLayerRename1* aLayer = new ReplaceAnimSpriteLayerRename1();
		aLayer->autorelease();
		return aLayer;
	}
	
	void onEnter(){
		CCLayer::onEnter();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	}
	
	void onExit(){
		CCLayer::onExit();
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
		if (mIsOrigin) {
			mIsOrigin = false;
			// replace the anim sprite
			mAnimNode->replaceSprite(SPRITE_RENAME_1_SWORD_ORIGIN, SPRITE_RENAME_1_SWORD_NEW);
		} else {
			mIsOrigin = true;
			// resume the anim sprite
			mAnimNode->resumeSprite(SPRITE_RENAME_1_SWORD_ORIGIN);
		}
		return true;
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// repeat
		mAnimNode->PlaySection("attack");
	}
};

class ReplaceAnimSpriteLayerRenameAll : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
	bool mIsOrigin;
public:
	ReplaceAnimSpriteLayerRenameAll(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_RENAME_ALL);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("fadein");
		mIsOrigin = true;
		
		CCLabelTTF* aTip = CCLabelTTF::create("Tap the screen to replace anim sprite\nreplace all sprite", "Arial", 24);
		addChild(aTip);
		aTip->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.25f));
	}
	~ReplaceAnimSpriteLayerRenameAll(){
	}
	static ReplaceAnimSpriteLayerRenameAll* create(){
		ReplaceAnimSpriteLayerRenameAll* aLayer = new ReplaceAnimSpriteLayerRenameAll();
		aLayer->autorelease();
		return aLayer;
	}
	
	void onEnter(){
		CCLayer::onEnter();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	}
	
	void onExit(){
		CCLayer::onExit();
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
		if (mIsOrigin) {
			mIsOrigin = false;
			// replace the anim sprite
			mAnimNode->replaceSprite(SPRITE_RENAME_ALL_1_ORIGIN, SPRITE_RENAME_ALL_1_NEW);
			mAnimNode->replaceSprite(SPRITE_RENAME_ALL_2_ORIGIN, SPRITE_RENAME_ALL_2_NEW);
			mAnimNode->replaceSprite(SPRITE_RENAME_ALL_3_ORIGIN, SPRITE_RENAME_ALL_3_NEW);
		} else {
			mIsOrigin = true;
			// resume the anim sprite
			mAnimNode->resumeSprite(SPRITE_RENAME_ALL_1_ORIGIN);
			mAnimNode->resumeSprite(SPRITE_RENAME_ALL_2_ORIGIN);
			mAnimNode->resumeSprite(SPRITE_RENAME_ALL_3_ORIGIN);
		}
		return true;
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// repeat
		if (theLabelName == "fadein") {
			mAnimNode->PlaySection("tap");
		}
		if (theLabelName == "tap") {
			mAnimNode->PlaySection("fadein");
		}
	}
};


class ReplaceAnimSpriteLayerRenameResize : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
	bool mIsOrigin;
public:
	ReplaceAnimSpriteLayerRenameResize(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_RENAME_RESIZE);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("attack");
		mIsOrigin = true;
		
		CCLabelTTF* aTip = CCLabelTTF::create("Tap the screen to replace anim sprite\nReplace 1 sprite(Resize)", "Arial", 24);
		addChild(aTip);
		aTip->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.25f));
	}
	~ReplaceAnimSpriteLayerRenameResize(){
	}
	static ReplaceAnimSpriteLayerRenameResize* create(){
		ReplaceAnimSpriteLayerRenameResize* aLayer = new ReplaceAnimSpriteLayerRenameResize();
		aLayer->autorelease();
		return aLayer;
	}
	
	void onEnter(){
		CCLayer::onEnter();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	}
	
	void onExit(){
		CCLayer::onExit();
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
		if (mIsOrigin) {
			mIsOrigin = false;
			// replace the anim sprite
			mAnimNode->replaceSprite(SPRITE_RENAME_RESIZE_HAT_HEAD_ORIGIN, SPRITE_RENAME_RESIZE_HAT_HEAD_NEW);
		} else {
			mIsOrigin = true;
			// resume the anim sprite
			mAnimNode->resumeSprite(SPRITE_RENAME_RESIZE_HAT_HEAD_ORIGIN);
		}
		return true;
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// repeat
		mAnimNode->PlaySection("attack");
	}
};

class ReplaceAnimSpriteLayerRenameSprieSheet : public CCLayer, public SuperAnimNodeListener {
	SuperAnimNode* mAnimNode;
	bool mIsOrigin;
public:
	ReplaceAnimSpriteLayerRenameSprieSheet(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_RENAME_SPRITESHEET);
		mAnimNode = SuperAnimNode::create(anAnimFileFullPath, 0, this);
		addChild(mAnimNode);
		mAnimNode->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
		mAnimNode->PlaySection("attack");
		mIsOrigin = true;
		
		CCLabelTTF* aTip = CCLabelTTF::create("Tap the screen to replace anim sprite\nReplace 1 sprite(Sprite Sheet)", "Arial", 24);
		addChild(aTip);
		aTip->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height * 0.25f));
	}
	~ReplaceAnimSpriteLayerRenameSprieSheet(){
	}
	static ReplaceAnimSpriteLayerRenameSprieSheet* create(){
		ReplaceAnimSpriteLayerRenameSprieSheet* aLayer = new ReplaceAnimSpriteLayerRenameSprieSheet();
		aLayer->autorelease();
		return aLayer;
	}
	
	void onEnter(){
		CCLayer::onEnter();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
	}
	
	void onExit(){
		CCLayer::onExit();
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
		if (mIsOrigin) {
			mIsOrigin = false;
			// replace the anim sprite
			mAnimNode->replaceSprite(SPRITE_RENAME_SPRITESHEET_HAT_HEAD_ORIGIN, SPRITE_RENAME_SPRITESHEET_HAT_HEAD_NEW);
		} else {
			mIsOrigin = true;
			// resume the anim sprite
			mAnimNode->resumeSprite(SPRITE_RENAME_SPRITESHEET_HAT_HEAD_ORIGIN);
		}
		return true;
	}
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		// repeat
		mAnimNode->PlaySection("attack");
	}
};

/////////////////////////////////////////////////////////////////////
ReplaceAnimSpriteScene::ReplaceAnimSpriteScene(){
	mCurLayer = NULL;
	mCurLayerID = kReplaceAnimSpriteLayerIdCnt;
	mHUD = NULL;
}

CCScene* ReplaceAnimSpriteScene::scene(){
	CCScene* aScene = CCScene::create();
	ReplaceAnimSpriteScene* aLayer = new ReplaceAnimSpriteScene();
	if (aLayer->init()) {
		aLayer->autorelease();
		aScene->addChild(aLayer);
		return aScene;
	}
	
	CC_SAFE_RELEASE(aLayer);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool ReplaceAnimSpriteScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	// background
	addChild(CCLayerColor::create(ccc4(128, 128, 128, 255)));
	
	mHUD = HUDLayer::create(this);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryReplaceAnimSprite).c_str());
	addChild(mHUD, 1);
	
	changeLayer(kReplaceAnimSpriteLayerNormal);
	
	return true;
}

void ReplaceAnimSpriteScene::changeLayer(ReplaceAnimSpriteLayerId theNewLayer){
	if (mCurLayer) {
		mCurLayer->removeFromParentAndCleanup(true);
		mCurLayer = NULL;
		mCurLayerID = kReplaceAnimSpriteLayerIdCnt;
	}
	if (theNewLayer == kReplaceAnimSpriteLayerNormal) {
		mCurLayerID = kReplaceAnimSpriteLayerNormal;
		mCurLayer = ReplaceAnimSpriteLayerNormal::create();
		addChild(mCurLayer);
	}
	if (theNewLayer == kReplaceAnimSpriteLayerRename1) {
		mCurLayerID = kReplaceAnimSpriteLayerRename1;
		mCurLayer = ReplaceAnimSpriteLayerRename1::create();
		addChild(mCurLayer);
	}
	if (theNewLayer == kReplaceAnimSpriteLayerRenameAll) {
		mCurLayerID = kReplaceAnimSpriteLayerRenameAll;
		mCurLayer = ReplaceAnimSpriteLayerRenameAll::create();
		addChild(mCurLayer);
	}
	if (theNewLayer == kReplaceAnimSpriteLayerRenameResize) {
		mCurLayerID = kReplaceAnimSpriteLayerRenameResize;
		mCurLayer = ReplaceAnimSpriteLayerRenameResize::create();
		addChild(mCurLayer);
	}
	if (theNewLayer == kReplaceAnimSpriteLayerRenameSpriteSheet) {
		mCurLayerID = kReplaceAnimSpriteLayerRenameSpriteSheet;
		mCurLayer = ReplaceAnimSpriteLayerRenameSprieSheet::create();
		addChild(mCurLayer);
	}

}

void ReplaceAnimSpriteScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
	if (thePressedBtn == kHUDLayerButtonNext) {
		ReplaceAnimSpriteLayerId aNewLayerId;
		if (mCurLayerID + 1 == kReplaceAnimSpriteLayerIdCnt) {
			aNewLayerId = kReplaceAnimSpriteLayerNormal;
		} else {
			aNewLayerId = (ReplaceAnimSpriteLayerId)(mCurLayerID + 1);
		}
		changeLayer(aNewLayerId);
	}
	if (thePressedBtn == kHUDLayerButtonPre) {
		ReplaceAnimSpriteLayerId aNewLayerId;
		if (mCurLayerID - 1 < 0) {
			aNewLayerId = (ReplaceAnimSpriteLayerId)(kReplaceAnimSpriteLayerIdCnt - 1);
		} else {
			aNewLayerId = (ReplaceAnimSpriteLayerId)(mCurLayerID - 1);
		}
		changeLayer(aNewLayerId);
	}
}
