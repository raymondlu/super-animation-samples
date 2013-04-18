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
const char* SAM_RENAME_SPRITESHEET = "rename_sprite/rename-spritesheet/attack_front.sam";
const char* SPRITE_RENAME_SPRITESHEET_HAT_HEAD_ORIGIN = "rename_sprite/rename-spritesheet/hat_head.png";
const char* SPRITE_RENAME_SPRITESHEET_HAT_HEAD_NEW = "rename_sprite/rename-spritesheet/hat_head_new.png";
const char* SAM_NO_FLICKER = "no-flicker/no-flicker.sam";

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
		CCLayerColor* aBg = [CCLayerColor layerWithColor:ccc4(128, 128, 255, 255)];
		[self addChild: aBg];
		
		NSString* anAnimFileFullPath = [[CCFileUtils sharedFileUtils] fullPathFromRelativePath:[NSString stringWithCString:SAM_NO_FLICKER encoding:NSUTF8StringEncoding]];
		
		mAnimNode[kAnimAttacker] = [SuperAnimNode create:anAnimFileFullPath id:kAnimAttacker listener:self];
		[self addChild:mAnimNode[kAnimAttacker]];
		mAnimNode[kAnimAttacker].position = ccp(size.width * 0.25f, size.height * 0.5f);
		[mAnimNode[kAnimAttacker] PlaySection:@"right_idle"];
		
		mAnimNode[kAnimAttacked] = [SuperAnimNode create:anAnimFileFullPath id:kAnimAttacked listener:self];
		[self addChild:mAnimNode[kAnimAttacked]];
		mAnimNode[kAnimAttacked].position = ccp(size.width * 0.5f, size.height * 0.5f);
		[mAnimNode[kAnimAttacked] PlaySection:@"left_idle"];
		
		CCLabelTTF* aTip = [CCLabelTTF labelWithString:@"Tap to add/remove time event" fontName:@"Arial" fontSize:24];
		[self addChild:aTip];
		aTip.position = ccp(size.width * 0.5f, size.height * 0.75f);
		
		[self registerWithTouchDispatcher];

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

- (void)ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
	static BOOL shouldAddTimeEvent = YES;
	
	if (shouldAddTimeEvent) {
		shouldAddTimeEvent = NO;
		[mAnimNode[kAnimAttacker] registerTimeEvent:@"right_doubleattack" timeFactor:0.9f timeEventId:0];
		[mAnimNode[kAnimAttacker] PlaySection:@"right_doubleattack"];
	} else if (!shouldAddTimeEvent){
		[mAnimNode[kAnimAttacker] removeTimeEvent:@"right_doubleattack" timeEventId:0];
		[mAnimNode[kAnimAttacker] PlaySection:@"right_idle"];
		shouldAddTimeEvent = YES;
	}
}

- (void) OnAnimSectionEnd:(int)theId label:(NSString *)theLabelName{
	if (theId == kAnimAttacker) {
		[mAnimNode[kAnimAttacker] PlaySection:theLabelName];
	}
	
	if (theId == kAnimAttacked) {
		if ([theLabelName compare:@"left_die"] == NSOrderedSame) {
			[mAnimNode[kAnimAttacked] PlaySection:@"left_idle"];
		} else {
			[mAnimNode[kAnimAttacked] PlaySection:theLabelName];
		}
	}
}

-(void) OnTimeEvent:(int) theId label:(NSString*)theLabelName eventId:(int) theEventId{
	if (theId == kAnimAttacker && theEventId == 0) {
		[mAnimNode[kAnimAttacked] PlaySection:@"left_die"];
	}
}
@end
