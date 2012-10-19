//
//  HelloWorldLayer.m
//  SuperAnimSamples-cocos2d-for-iphone
//
//  Created by 敬慧 卢 on 10/19/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//


// Import the interfaces
#import "HelloWorldLayer.h"

// Needed to obtain the Navigation Controller
#import "AppDelegate.h"

#import "MoreScene.h"

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
		
		// add a background
		CCLayerColor* aBackground = [CCLayerColor layerWithColor:ccc4(128, 128, 128, 255) width:size.width height:size.height];
		[self addChild:aBackground];
		
		// add super animation node
		NSString* anAnimFileFullPath = [[CCFileUtils sharedFileUtils]fullPathFromRelativePath:@"basic_transform.sam"];
		mAnimNode = [SuperAnimNode create:anAnimFileFullPath Id:0 Listener:self];
		mAnimNode.position = CGPointMake(size.width * 0.5f, size.height * 0.5f);
		[self addChild:mAnimNode];
		[mAnimNode PlaySection:@"mixed"];
		
		// Default font size will be 28 points.
		[CCMenuItemFont setFontSize:28];
		
		CCMenuItemFont* aNextSceneBtn = [CCMenuItemFont itemWithString:@"Next Scene" target:self selector:@selector(nextSceneCallback:)];
		aNextSceneBtn.anchorPoint = CGPointMake(0.5f, 0.0f);
		aNextSceneBtn.position = CGPointMake(size.width * 0.5f, 0.0f);
		
		CCMenu* aMenu = [CCMenu menuWithItems:aNextSceneBtn, nil];
		aMenu.position = CGPointZero;
		[self addChild:aMenu];

		// create and initialize a Label
		CCLabelTTF *label = [CCLabelTTF labelWithString:@"basic animation" fontName:@"Marker Felt" fontSize:64];
		label.anchorPoint = ccp(0.5f, 1.0f);
		label.position =  ccp( size.width * 0.5f , size.height );
		// add the label as a child to this Layer
		[self addChild: label];
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

- (void) OnAnimSectionEnd:(int)theId LabelName:(NSString *)theLabelName{
	if (theId == 0) {
		if ([theLabelName isEqualToString:@"mixed"]) {
			// goto fade section
			[mAnimNode PlaySection:@"fade"];
		} else if ([theLabelName isEqualToString:@"fade"]){
			// goto mixed section
			[mAnimNode PlaySection:@"mixed"];
		}
	}
}

- (void) nextSceneCallback:(id)sender{
	[[CCDirector sharedDirector] replaceScene:[MoreScene scene]];
}
@end
