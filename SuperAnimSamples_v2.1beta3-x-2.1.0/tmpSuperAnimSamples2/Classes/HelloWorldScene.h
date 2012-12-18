#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SuperAnimNodeV2.h"

class HelloWorld : public cocos2d::CCLayer, public SuperAnim::SuperAnimNodeListener
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject* pSender);

    // implement the "static node()" method manually
    static HelloWorld* create();
	
	void OnAnimSectionEnd(int theId, std::string theLabelName);
	
private:
	SuperAnim::SuperAnimNode* mAnimNode;
};

#endif // __HELLOWORLD_SCENE_H__
