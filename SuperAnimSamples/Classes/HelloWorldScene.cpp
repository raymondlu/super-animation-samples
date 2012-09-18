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
	
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
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
