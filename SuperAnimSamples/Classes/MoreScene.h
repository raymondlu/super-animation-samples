//
//  MoreScene.h
//  SuperAnimSamples
//

#ifndef SuperAnimSamples_MoreScene_h
#define SuperAnimSamples_MoreScene_h

#include "cocos2d.h"
#include "SuperAnimNodeV2.h"

class MoreSample : public cocos2d::CCLayer, public SuperAnim::SuperAnimNodeListener {
	int mAnimState;
	std::map<int, SuperAnim::SuperAnimNode*> mAnimNodeMap;
	CCMenu* mMenu;
	CCLabelTTF* mTip;
public:
	bool init();
	static cocos2d::CCScene* scene();
	LAYER_CREATE_FUNC(MoreSample);
	
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void menuCallback(CCObject* pSender);
	// SuperAnimNodeListener
	void OnAnimSectionEnd(int theId, std::string theLabelName);
	
private:
	void setAnimState(int theNewState);
	// In fact, you don't have to load animation file before create a super animation node.
	// Super Animation Core will do it automatically
	void loadAnimFile();
	void addAnimInstance();
	void delAnimInstance();
	void unloadAnimFile();
};


#endif
