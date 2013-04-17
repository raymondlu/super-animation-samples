//
//  TimeEventScene.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 4/17/13.
//
//

#include "TimeEventScene.h"
#include "MainMenu.h"
#include "SuperAnimNodeV2.h"
using namespace SuperAnim;

class TimeEventAttackToDieLayer : public CCLayer, public SuperAnimNodeListener {
	enum AnimId{
		kAnimAttacker = 0,
		kAnimAttacked,
		
		// keep last
		kAnimIdCnt
	};
	
	enum TimeEventId{
		kTimeEventHit = 0,
		
		// keep last
		kTiemEventIdCnt
	};
	
	enum ButtonId{
		kButtonAddTimeEvent = 0,
		kButtonRemoveTimeEvent,
		
		// keep last
		kButtonIdCnt
	};
	
	enum Phase{
		kPhaseIdle = 0,
		kPhaseAddedTimeEvent,
		kPhaseRemovedTimeEvent,
		
		// keep last
		kPhaseCnt
	};
	
	SuperAnimNode* mAnimNode[kAnimIdCnt];
	CCMenuItemFont* mButtons[kButtonIdCnt];
	Phase mPhase;
public:
	TimeEventAttackToDieLayer(){
		CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
		std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(SAM_NO_FLICKER);
		
		mAnimNode[kAnimAttacker] = SuperAnimNode::create(anAnimFileFullPath, kAnimAttacker, this);
		addChild(mAnimNode[kAnimAttacker]);
		mAnimNode[kAnimAttacker]->setPosition(ccp(aScreenSize.width * 0.35f, aScreenSize.height * 0.5f));
		mAnimNode[kAnimAttacker]->PlaySection("right_idle");
		
		mAnimNode[kAnimAttacked] = SuperAnimNode::create(anAnimFileFullPath, kAnimAttacked, this);
		addChild(mAnimNode[kAnimAttacked]);
		mAnimNode[kAnimAttacked]->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.5f));
		mAnimNode[kAnimAttacked]->PlaySection("left_idle");
		
		mPhase = kPhaseIdle;
		
		mButtons[kButtonAddTimeEvent] = CCMenuItemFont::create("Add Attack Time Event", this, \
															   menu_selector(TimeEventAttackToDieLayer::onButton));
		mButtons[kButtonAddTimeEvent]->setPosition(ccp(aScreenSize.width * 0.25f, aScreenSize.height * 0.35f));
		
		mButtons[kButtonRemoveTimeEvent] = CCMenuItemFont::create("Remove Attack Time Event", this, \
															   menu_selector(TimeEventAttackToDieLayer::onButton));
		mButtons[kButtonRemoveTimeEvent]->setPosition(ccp(aScreenSize.width * 0.75f, aScreenSize.height * 0.35f));
		
		CCMenu* aMenu = CCMenu::create();
		for (int i = 0; i < kButtonIdCnt; i++) {
			aMenu->addChild(mButtons[i]);
		}
		addChild(aMenu);
		aMenu->setPosition(CCPointZero);
	
		changeUI();
	}
	
	static TimeEventAttackToDieLayer* create(){
		TimeEventAttackToDieLayer* aLayer = new TimeEventAttackToDieLayer();
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
	
	void OnAnimSectionEnd(int theId, std::string theLabelName){
		if (theId == kAnimAttacker) {
			// loop
			mAnimNode[kAnimAttacker]->PlaySection(theLabelName);
		}
		
		if (theId == kAnimAttacked) {
			if (theLabelName == "left_die") {
				// goto idle
				mAnimNode[kAnimAttacked]->PlaySection("left_idle");
			} else {
				// loop
				mAnimNode[kAnimAttacked]->PlaySection(theLabelName);
			}
		}
	}
	
	void OnTimeEvent(int theId, std::string theLabelName, int theEventId){
		if (theId == kAnimAttacker &&\
			theEventId == kTimeEventHit) {
			// time to play die aniamtion for the attacked
			mAnimNode[kAnimAttacked]->PlaySection("left_die");
		}
	}
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

		return true;
	}
	
	void changeUI(){
		if (mPhase == kPhaseIdle ||\
			mPhase == kPhaseRemovedTimeEvent) {
			mButtons[kButtonRemoveTimeEvent]->setEnabled(false);
			mButtons[kButtonAddTimeEvent]->setEnabled(true);
		} else {
			mButtons[kButtonRemoveTimeEvent]->setEnabled(true);
			mButtons[kButtonAddTimeEvent]->setEnabled(false);
		}
	}
	
	void onButton(CCObject* theSender){
		if (theSender == mButtons[kButtonAddTimeEvent]) {
			mAnimNode[kAnimAttacker]->registerTimeEvent("right_doubleattack", 0.9f, kTimeEventHit);
			mAnimNode[kAnimAttacker]->PlaySection("right_doubleattack");
			mPhase = kPhaseAddedTimeEvent;
		}
		if (theSender == mButtons[kButtonRemoveTimeEvent]) {
			mAnimNode[kAnimAttacker]->removeTimeEvent("right_doubleattack", kTimeEventHit);
			mAnimNode[kAnimAttacker]->PlaySection("right_idle");
			mPhase = kPhaseRemovedTimeEvent;
		}
		
		changeUI();
	}
};


TimeEventScene::TimeEventScene(){
	mCurLayer = NULL;
	mCurLayerID = kTimeEventSceneLayerCnt;
	mHUD = NULL;
}

CCScene* TimeEventScene::scene(){
	CCScene* aScene = CCScene::create();
	TimeEventScene* aComplexAnim = new TimeEventScene();
	if (aComplexAnim->init()) {
		aComplexAnim->autorelease();
		aScene->addChild(aComplexAnim);
		return aScene;
	}
	CC_SAFE_DELETE(aComplexAnim);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

bool TimeEventScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	// background
	addChild(CCLayerColor::create(ccc4(255, 128, 128, 255)));
	
	mHUD = HUDLayer::create(this);
	mHUD->mTitle->setString(getTestEntryName(kTestEntryTimeEvent).c_str());
	addChild(mHUD, 1);
	
	changeLayer(kTimeEventSceneLayerAttackToDie);
	return true;
}

void TimeEventScene::changeLayer(TimeEventSceneLayerID theNewLayer){
	if (mCurLayer) {
		mCurLayer->removeFromParentAndCleanup(true);
		mCurLayer = NULL;
		mCurLayerID = kTimeEventSceneLayerCnt;
	}

	 if (theNewLayer == kTimeEventSceneLayerAttackToDie) {
		 mCurLayerID = kTimeEventSceneLayerAttackToDie;
		 mCurLayer = TimeEventAttackToDieLayer::create();
		 addChild(mCurLayer);
	 }

}

void TimeEventScene::onHUDLayerButton(HUDLayerButton thePressedBtn){
	if (thePressedBtn == kHUDLayerButtonMainmenu) {
		CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
	}
	if (thePressedBtn == kHUDLayerButtonNext) {
		TimeEventSceneLayerID aNewLayerId;
		if (mCurLayerID + 1 == kTimeEventSceneLayerCnt) {
			aNewLayerId = kTimeEventSceneLayerAttackToDie;
		} else {
			aNewLayerId = (TimeEventSceneLayerID)(mCurLayerID + 1);
		}
		changeLayer(aNewLayerId);
	}
	if (thePressedBtn == kHUDLayerButtonPre) {
		TimeEventSceneLayerID aNewLayerId;
		if (mCurLayerID - 1 < 0) {
			aNewLayerId = (TimeEventSceneLayerID)(kTimeEventSceneLayerCnt - 1);
		} else {
			aNewLayerId = (TimeEventSceneLayerID)(mCurLayerID - 1);
		}
		changeLayer(aNewLayerId);
	}
}