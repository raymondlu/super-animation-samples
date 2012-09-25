//
//  MoreScene.cpp
//  SuperAnimSamples
//

#include "MoreScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* MoreSample::scene(){
	CCScene* aScene = CCScene::create();
	MoreSample* aLayer = MoreSample::create();
	aScene->addChild(aLayer);
	return aScene;
}

enum AnimState {
	kAnimStateInvalid = -1,
	kAnimStateLoaded,
	kAnimStateInstanceCreated,
	kAnimStateInstanceAllDestroyed,
	kAnimStateUnloaded
};

enum MenuItemTag {
	kMenuItemTagLoad = 0,
	kMenuItemTagCreateInstance,
	kMenuItemTagDestroyInstance,
	kMenuItemtagUnload,
	kMenuItemTagPreScene,
};

bool MoreSample::init(){
	if (!CCLayer::init()) {
		return false;
	}
	
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	
	// background
	CCLayerColor* aBackground = CCLayerColor::create(ccc4(128, 128, 128, 255), aScreenSize.width, aScreenSize.height);
	this->addChild(aBackground);
	
	mMenu = CCMenu::create();
	this->addChild(mMenu, 10);
	mMenu->setPosition(CCPointZero);
	
	float aMenuItemStartX = 10.0f;
	float aMenuItemStartY = aScreenSize.height - 80.0f;
	float aMenuItemHeight = 30;
	int anIndex = 0;
	ccColor3B aDisableColor = ccc3(64, 64, 64);
	CCMenuItemFont::setFontSize(18);
	CCMenuItemFont* aMenuItem = CCMenuItemFont::create("load anim file", this, menu_selector(MoreSample::menuCallback));
	aMenuItem->setTag(kMenuItemTagLoad);
	aMenuItem->setAnchorPoint(CCPointMake(0.0f, 1.0f));
	aMenuItem->setPosition(CCPointMake(aMenuItemStartX, aMenuItemStartY - anIndex++ * aMenuItemHeight));
	aMenuItem->setDisabledColor(aDisableColor);
	mMenu->addChild(aMenuItem);
	
	aMenuItem = CCMenuItemFont::create("add anim inst", this, menu_selector(MoreSample::menuCallback));
	aMenuItem->setTag(kMenuItemTagCreateInstance);
	aMenuItem->setAnchorPoint(CCPointMake(0.0f, 1.0f));
	aMenuItem->setPosition(CCPointMake(aMenuItemStartX, aMenuItemStartY - anIndex++ * aMenuItemHeight));
	aMenuItem->setDisabledColor(aDisableColor);
	mMenu->addChild(aMenuItem);
	
	aMenuItem = CCMenuItemFont::create("del anim inst", this, menu_selector(MoreSample::menuCallback));
	aMenuItem->setTag(kMenuItemTagDestroyInstance);
	aMenuItem->setAnchorPoint(CCPointMake(0.0f, 1.0f));
	aMenuItem->setPosition(CCPointMake(aMenuItemStartX, aMenuItemStartY - anIndex++ * aMenuItemHeight));
	aMenuItem->setDisabledColor(aDisableColor);
	mMenu->addChild(aMenuItem);
	
	aMenuItem = CCMenuItemFont::create("unload anim file", this, menu_selector(MoreSample::menuCallback));
	aMenuItem->setTag(kMenuItemtagUnload);
	aMenuItem->setAnchorPoint(CCPointMake(0.0f, 1.0f));
	aMenuItem->setPosition(CCPointMake(aMenuItemStartX, aMenuItemStartY - anIndex++ * aMenuItemHeight));
	aMenuItem->setDisabledColor(aDisableColor);
	mMenu->addChild(aMenuItem);
	
	CCMenuItemFont::setFontSize(kCCItemSize);
	aMenuItem = CCMenuItemFont::create("Pre Scene", this, menu_selector(MoreSample::menuCallback));
	aMenuItem->setTag(kMenuItemTagPreScene);
	aMenuItem->setAnchorPoint(CCPointMake(0.5f, 0.0f));
	aMenuItem->setPosition(CCPointMake(aScreenSize.width * 0.5f, 0.0f));
	mMenu->addChild(aMenuItem);
	
	mTip = CCLabelTTF::create("", "", 16);
	mTip->setAnchorPoint(CCPointMake(0.5f, 1.0f));
	mTip->setPosition(CCPointMake(aScreenSize.width * 0.5f, aScreenSize.height));
	mTip->setColor(ccc3(255, 64, 64));
	this->addChild(mTip, 10);
	
	setAnimState(kAnimStateInvalid);
	
	setTouchEnabled(true);
	
	return true;
}

void MoreSample::menuCallback(cocos2d::CCObject *pSender){
	CCMenuItemFont* aSelectedMenuItem = dynamic_cast<CCMenuItemFont*>(pSender);
	if (aSelectedMenuItem == NULL) {
		return;
	}
	
	int aSelectedMenuItemTag = aSelectedMenuItem->getTag();
	if (aSelectedMenuItemTag == kMenuItemTagLoad) {
		// load the animation file manually
		loadAnimFile();
	}
	
	if (aSelectedMenuItemTag == kMenuItemTagCreateInstance) {
		// create animation instace
		addAnimInstance();
	}
	
	if (aSelectedMenuItemTag == kMenuItemTagDestroyInstance) {
		// delete an an animation instace
		delAnimInstance();
	}
	
	if (aSelectedMenuItemTag == kMenuItemtagUnload) {
		// unload the animation file from the system
		unloadAnimFile();
	}
	
	if (aSelectedMenuItemTag == kMenuItemTagPreScene) {
		CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	}
}

void MoreSample::setAnimState(int theNewState){
	if (mAnimState == theNewState) {
		return;
	}
	
	mAnimState = theNewState;
	
	if (mAnimState == kAnimStateInvalid) {
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagLoad))->setEnabled(true);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagCreateInstance))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagDestroyInstance))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemtagUnload))->setEnabled(false);
	}
	
	if (mAnimState == kAnimStateLoaded) {
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagLoad))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagCreateInstance))->setEnabled(true);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagDestroyInstance))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemtagUnload))->setEnabled(true);
	}
	
	if (mAnimState == kAnimStateInstanceCreated) {
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagLoad))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagCreateInstance))->setEnabled(true);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagDestroyInstance))->setEnabled(true);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemtagUnload))->setEnabled(false);
		
		mTip->setString("Tap the fish!");
	}
	
	if (mAnimState == kAnimStateInstanceAllDestroyed) {
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagLoad))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagCreateInstance))->setEnabled(true);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagDestroyInstance))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemtagUnload))->setEnabled(true);
		
		mTip->setString("");
	}
	
	if (mAnimState == kAnimStateUnloaded) {
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagLoad))->setEnabled(true);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagCreateInstance))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemTagDestroyInstance))->setEnabled(false);
		((CCMenuItemFont*)mMenu->getChildByTag(kMenuItemtagUnload))->setEnabled(false);
	}
}

void MoreSample::loadAnimFile(){
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("fish.sam");
	if (SuperAnim::LoadAnimFile(anAnimFileFullPath)){
		setAnimState(kAnimStateLoaded);
		CCMessageBox("Load animation file sucessfully", "Good");
	} else {
		CCMessageBox("Fail to load animation file", "Error");
	}
}

void MoreSample::addAnimInstance(){
	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint aRandomPos = CCPointMake(CCRANDOM_0_1() * aScreenSize.width, CCRANDOM_0_1() * aScreenSize.height);
	static int sId = 0;
	// the full path of animation file is the key.
	// if the animation file not been loaded , the super animation system will load it automatically
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("fish.sam");
	SuperAnim::SuperAnimNode* aSuperAnimNode = SuperAnim::SuperAnimNode::create(anAnimFileFullPath, sId, this);
	aSuperAnimNode->setPosition(aRandomPos);
	this->addChild(aSuperAnimNode);
	aSuperAnimNode->PlaySection("idle");
	mAnimNodeMap[sId++] = aSuperAnimNode;
	setAnimState(kAnimStateInstanceCreated);
}

void MoreSample::delAnimInstance(){
	std::map<int, SuperAnim::SuperAnimNode*>::iterator anIter = mAnimNodeMap.begin();
	if (anIter != mAnimNodeMap.end()) {
		this->removeChild(anIter->second, true);
		mAnimNodeMap.erase(anIter);
	}
	
	if (mAnimNodeMap.size() == 0) {
		setAnimState(kAnimStateInstanceAllDestroyed);
	}
}

void MoreSample::unloadAnimFile(){
	// the full path of animation file is the key
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("fish.sam");
	SuperAnim::UnloadAnimFile(anAnimFileFullPath);
	setAnimState(kAnimStateUnloaded);
}

void MoreSample::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	if (mAnimNodeMap.size() == 0) {
		return;
	}
	
	for (CCSetIterator anIter = pTouches->begin(); anIter != pTouches->end(); anIter++) {
		CCTouch* aTouch = (CCTouch*)(*anIter);
		CCPoint aTouchedPos = this->convertTouchToNodeSpace(aTouch);
		
		// check you whether you tap an animation node
		for (std::map<int, SuperAnim::SuperAnimNode*>::iterator anAnimNodeIter = mAnimNodeMap.begin(); anAnimNodeIter != mAnimNodeMap.end(); anAnimNodeIter++) {
			SuperAnim::SuperAnimNode* anAnimNode = anAnimNodeIter->second;
			CCRect aBoundingRect = anAnimNode->boundingBox();
			if (aBoundingRect.containsPoint(aTouchedPos)) {
				// if you tap an animation, let the animation play "active" section to respond
				if (anAnimNode->GetCurSectionName() != "active") {
					anAnimNode->PlaySection("active");
				}
			}
		}
	}
}

void MoreSample::OnAnimSectionEnd(int theId, std::string theLabelName){
	std::map<int, SuperAnim::SuperAnimNode*>::iterator anIter = mAnimNodeMap.find(theId);
	if (anIter == mAnimNodeMap.end()) {
		return;
	}
	
	SuperAnim::SuperAnimNode* anAnimNode = anIter->second;
	if (theLabelName == "idle") {
		// play "idle" section loop
		anAnimNode->PlaySection("idle");
	}
	
	if (theLabelName == "active") {
		// recover to "idle"
		anAnimNode->PlaySection("idle");
	}
}