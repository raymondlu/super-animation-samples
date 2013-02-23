//
//  MainMenu.cpp
//  super-anim-samples
//
//  Created by 卢 敬慧 on 2/23/13.
//
//

#include "MainMenu.h"

CCScene* MainMenuScene::scene(){
	CCScene* aScene = CCScene::create();
	MainMenuScene* aMainMenu = new MainMenuScene();
	if (aMainMenu->init()) {
		aMainMenu->autorelease();
		aScene->addChild(aMainMenu);
		return aScene;
	}
	CC_SAFE_DELETE(aMainMenu);
	CC_SAFE_RELEASE(aScene);
	return NULL;
}

MainMenuScene::MainMenuScene(){
	for (int i = 0; i < kTestEntryCnt; i++) {
		mEntries[i] = NULL;
	}
	
	mEntryContainer = NULL;
}

#define ENTRY_HEIGHT (100)

bool MainMenuScene::init(){
	if (CCLayer::init() == false) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	
	mEntryContainer = CCMenu::create();
	addChild(mEntryContainer);
	mEntryContainer->setPosition(CCPointZero);
	
	int anOldFontSize = CCMenuItemFont::fontSize();
	CCMenuItemFont::setFontSize(48);
	for (int i = 0; i < kTestEntryCnt; i++) {
		mEntries[i] = CCMenuItemFont::create(getTestEntryName((TestEntry)i).c_str(), this, menu_selector(MainMenuScene::onEntry));
		mEntryContainer->addChild(mEntries[i]);
		mEntries[i]->setPosition(ccp(aScreenSize.width * 0.5f, aScreenSize.height - (i + 1) * ENTRY_HEIGHT));
	}
	CCMenuItemFont::setFontSize(anOldFontSize);
	setTouchEnabled(true);
	return true;
}

static CCPoint sTouchBeginPos;

void MainMenuScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	CCTouch* aTouch = (CCTouch*)(*pTouches->begin());
	sTouchBeginPos = aTouch->getLocation();
}
void MainMenuScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCTouch* aTouch = (CCTouch*)(*pTouches->begin());
	CCPoint aMovedPos = aTouch->getLocation();
	float aMovedY = aMovedPos.y - sTouchBeginPos.y;
	CCPoint aCurPos = mEntryContainer->getPosition();
	CCPoint aNextPos = ccp(aCurPos.x, aCurPos.y + aMovedY);
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	if (aNextPos.y < 0.0f) {
		aNextPos.y = 0.0f;
	}
	if (aNextPos.y > (kTestEntryCnt + 1) * ENTRY_HEIGHT - aScreenSize.height) {
		aNextPos.y = (kTestEntryCnt + 1) * ENTRY_HEIGHT - aScreenSize.height;
	}
	mEntryContainer->setPosition(aNextPos);
	sTouchBeginPos = aMovedPos;
}
void MainMenuScene::onEntry(CCObject* theSender){
	for (int i = 0; i < kTestEntryCnt; i++) {
		if (mEntries[i] == theSender) {
			CCLog("Main menu: entry %d is selected.", i);
		}
	}
}