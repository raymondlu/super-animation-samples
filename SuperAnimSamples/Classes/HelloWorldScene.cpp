#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize aScreenSize = CCDirector::sharedDirector()->getWinSize();
	
	std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("basic_transform.sam");
    mAnimNode = SuperAnim::SuperAnimNode::create(anAnimFileFullPath, 0, this);
	mAnimNode->setPosition(CCPointMake(aScreenSize.width * 0.5f, aScreenSize.height * 0.5f));
	this->addChild(mAnimNode);
	mAnimNode->PlaySection("mixed");
	
	// add a menu item to next sample
	CCMenuItemFont* aNextSampleMenuItem = CCMenuItemFont::create("Next", this, menu_selector(HelloWorld::menuCallback));
	aNextSampleMenuItem->setAnchorPoint(CCPointMake(1.0f, 0.0f));
	aNextSampleMenuItem->setPosition(CCPointMake(aScreenSize.width, 0.0f));
	CCMenu* aMenu = CCMenu::createWithItem(aNextSampleMenuItem);
	this->addChild(aMenu);
	aMenu->setPosition(CCPointZero);
	
	// add a title
	CCLabelTTF* aTitle = CCLabelTTF::create("basic animation", "", 18);
	aTitle->setAnchorPoint(CCPointMake(0.5f, 1.0f));
	aTitle->setPosition(CCPointMake(aScreenSize.width * 0.5f, aScreenSize.height));
	this->addChild(aTitle);
	
    return true;
}

void HelloWorld::menuCallback(CCObject* pSender)
{

}

void HelloWorld::OnAnimSectionEnd(int theId, std::string theLabelName){
	if (theId == 0) {
		if (theLabelName == "mixed") {
			// goto fade section
			mAnimNode->PlaySection("fade");
		} else if (theLabelName == "fade"){
			// goto mixed section
			mAnimNode->PlaySection("mixed");
		}
	}
}
