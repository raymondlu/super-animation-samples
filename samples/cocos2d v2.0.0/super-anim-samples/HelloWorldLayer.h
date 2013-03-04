//
//  HelloWorldLayer.h
//  super-anim-samples
//
//  Created by 卢 敬慧 on 3/4/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "SuperAnimNodeV2.h"
// HelloWorldLayer
@interface HelloWorldLayer : CCLayer <SuperAnimNodeListener>
{
	SuperAnimNode* mAnimNode;
}

// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;

@end
