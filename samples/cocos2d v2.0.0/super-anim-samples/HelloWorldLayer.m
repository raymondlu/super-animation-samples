//
//  HelloWorldLayer.m
//  super-anim-samples
//
//  Created by 卢 敬慧 on 3/4/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//


// Import the interfaces
#import "HelloWorldLayer.h"

// Needed to obtain the Navigation Controller
#import "AppDelegate.h"

const char* SAM_BASIC = "basic_transform/basic_transform.sam";
const char* SAM_ATTACK_FRONT = "attack_front/attack_front.sam";
const char* SAM_FADEIN_TAP = "fadein_tap/fadein-tap.sam";
const char* SAM_FISH = "fish/fish.sam";
const char* SAM_FISH_SPRITESHEET = "fish_spritesheet/fish.sam";
const char* SAM_FISH_50 = "fish_50/fish.sam";
const char* SAM_FISH_150 = "fish_150/fish.sam";

#pragma mark - HelloWorldLayer

// HelloWorldLayer implementation
@implementation HelloWorldLayer

// Helper class method that creates a Scene with the HelloWorldLayer as the only child.
+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	HelloWorldLayer *layer = [HelloWorldLayer node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
-(id) init
{
	// always call "super" init
	// Apple recommends to re-assign "self" with the "super's" return value
	if( (self=[super init]) ) {

		// ask director for the window size
		CGSize size = [[CCDirector sharedDirector] winSize];
		CCLayerColor* aBg = [CCLayerColor layerWithColor:ccc4(128, 128, 128, 255)];
		[self addChild: aBg];
		
		NSString* anAnimFileFullPath = [[CCFileUtils sharedFileUtils] fullPathFromRelativePath:[NSString stringWithCString:SAM_FISH_SPRITESHEET encoding:NSUTF8StringEncoding]];
		
		mAnimNode = [SuperAnimNode create:anAnimFileFullPath id:0 listener:self];
		[self addChild:mAnimNode];
		mAnimNode.position = ccp(size.width * 0.5f, size.height * 0.5f);
		[mAnimNode PlaySection:@"idle"];

	}
	return self;
}

// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
	// in case you have something to dealloc, do it in this method
	// in this particular example nothing needs to be released.
	// cocos2d will automatically release all the children (Label)
	
	// don't forget to call "super dealloc"
	[super dealloc];
}

- (void) OnAnimSectionEnd:(int)theId label:(NSString *)theLabelName{
	if ([theLabelName compare:@"idle"] == NSOrderedSame) {
		[mAnimNode PlaySection:@"active"];
	}
	if ([theLabelName compare:@"active"] == NSOrderedSame) {
		[mAnimNode PlaySection:@"idle"];
	}
}
@end
