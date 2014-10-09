#include "HelloWorldScene.h"

USING_NS_CC;

enum AnimTags{
	kAnimTagSpriteSheet = 101,
	kAnimTagNoSpriteSheet
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	
	std::string spritesheet_anim = FileUtils::getInstance()->fullPathForFilename("fish_spritesheet/fish.sam");
	SuperAnim::SuperAnimNode* animNode1 = SuperAnim::SuperAnimNode::create(spritesheet_anim, kAnimTagSpriteSheet, this);
    this->addChild(animNode1);
	animNode1->setTag(kAnimTagSpriteSheet);
	animNode1->setPosition(Vec2(visibleSize.width * 0.5f + origin.x - 150.0f, visibleSize.height * 0.5f + origin.y));
	animNode1->PlaySection("idle");
	
	std::string no_spritesheet_anim = FileUtils::getInstance()->fullPathForFilename("fish/fish_0.sam");
	SuperAnim::SuperAnimNode* animNode2 = SuperAnim::SuperAnimNode::create(no_spritesheet_anim, kAnimTagNoSpriteSheet, this);
    this->addChild(animNode2);
	animNode2->setTag(kAnimTagNoSpriteSheet);
	animNode2->setPosition(Vec2(visibleSize.width * 0.5f + origin.x + 150.0f, visibleSize.height * 0.5f + origin.y));
	animNode2->PlaySection("active");
	animNode2->setFlipX(true);
	
    return true;
}

void HelloWorld::OnAnimSectionEnd(int theId, std::string theLabelName){
	SuperAnim::SuperAnimNode* animNode = (SuperAnim::SuperAnimNode*)getChildByTag(theId);
	if (animNode == nullptr) {
		return;
	}
	// just loop
	animNode->PlaySection(theLabelName);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
