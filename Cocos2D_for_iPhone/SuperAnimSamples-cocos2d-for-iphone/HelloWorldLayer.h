//
//  HelloWorldLayer.h
//  SuperAnimSamples-cocos2d-for-iphone
//
//  Created by 敬慧 卢 on 10/19/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

// When you import this file, you import all the cocos2d classes
#import "SuperAnimNodeV2.h"
#import "cocos2d.h"

// HelloWorldLayer
@interface HelloWorldLayer : CCLayer<SuperAnimNodeListener>
{
	SuperAnimNode* mAnimNode;
}

// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;

-(void) nextSceneCallback:(id)sender;
@end
