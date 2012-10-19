//
//  MoreScene.m
//
//  Created by Raymond Lu(Raymond-Lu@live.com)
//  
//  All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import "MoreScene.h"
#import "HelloWorldLayer.h"
enum AnimState {
	kAnimStateInvalid = -1,
	kAnimStateLoaded,
	kAnimStateInstanceCreated,
	kAnimStateInstanceAllDestroyed,
	kAnimStateUnloaded
};

enum MenuItemTag {
	kMenuItemTagLoad = 0,
	kMenuItemTagCreateInstance,
	kMenuItemTagDestroyInstance,
	kMenuItemtagUnload,
	kMenuItemTagPreScene,
	kMenuItemTagCnt
};

NSString* gMenuItemName[kMenuItemTagCnt] = {
	@"load anim file",
	@"add anim inst",
	@"del anim inst",
	@"unload anim file",
	@"Pre Screen"
};

@implementation MoreScene
+(CCScene*) scene{
	CCScene *scene = [CCScene node];
	MoreScene* layer = [MoreScene node];
	[scene addChild: layer];
	return scene;
}

-(id) init
{
	// always call "super" init
	// Apple recommends to re-assign "self" with the "super's" return value
	if( (self=[super init]) ) {
		CGSize aScreenSize = [[CCDirector sharedDirector] winSize];
		
		// background
		CCLayerColor* aBackground = [CCLayerColor layerWithColor:ccc4(128, 128, 128, 255) width:aScreenSize.width height:aScreenSize.height];
		[self addChild:aBackground];
		
		mMenu = [[[CCMenu alloc] init] autorelease];
		mMenu.position = CGPointZero;
		[self addChild:mMenu z:10];
		
		float aMenuItemStartX = 10.0f;
		float aMenuItemStartY = aScreenSize.height - 180.0f;
		float aMenuItemHeight = 60;
		ccColor3B aDisableColr = ccc3(64, 64, 64);
		[CCMenuItemFont setFontSize:28];
		for (int i = 0; i < kMenuItemTagCnt; i++) {
			CCMenuItemFont* aMenuItem = [CCMenuItemFont itemWithString:gMenuItemName[i] target:self selector:@selector(menuCallback:)];
			[aMenuItem setTag:i];
			if (i != kMenuItemTagPreScene) {
				[aMenuItem setAnchorPoint:CGPointMake(0.0f, 1.0f)];
				[aMenuItem setPosition:CGPointMake(aMenuItemStartX, aMenuItemStartY - i * aMenuItemHeight)];
			} else {
				[aMenuItem setAnchorPoint:CGPointMake(0.5f, 0.0f)];
				[aMenuItem setPosition:CGPointMake(aScreenSize.width * 0.5f, 0.0f)];
			}
			[aMenuItem setDisabledColor:aDisableColr];
			[mMenu addChild:aMenuItem];
		}
		
		mTip = [CCLabelTTF labelWithString:@"" fontName:@"Marker Felt" fontSize:48];
		[mTip setAnchorPoint:ccp(0.5f, 1.0f)];
		[mTip setPosition:ccp(aScreenSize.width * 0.5f, aScreenSize.height - 10.0f)];
		[mTip setColor:ccc3(255, 64, 64)];
		[self addChild:mTip z:10];
		
		[self setAnimState:kAnimStateInvalid];
		[self setIsTouchEnabled:YES];
		
		mAnimNodeMap = [[NSMutableDictionary alloc] initWithCapacity:100];
	}
	
	return self;
}

-(void) dealloc{
	[mAnimNodeMap removeAllObjects];
	[mAnimNodeMap release];
	[super dealloc];
}

-(void) menuCallback:(id)sender{
	CCMenuItemFont* aSelectedMenuItem = sender;
	int aSelectedMenuItemTag = aSelectedMenuItem.tag;
	if (aSelectedMenuItemTag == kMenuItemTagLoad) {
		// load the animation file manually
		[self loadAnimFile];
	}
	
	if (aSelectedMenuItemTag == kMenuItemTagCreateInstance) {
		// create animation instace
		[self addAnimInstance];
	}
	
	if (aSelectedMenuItemTag == kMenuItemTagDestroyInstance) {
		// delete an an animation instace
		[self delAnimInstance];
	}
	
	if (aSelectedMenuItemTag == kMenuItemtagUnload) {
		// unload the animation file from the system
		[self unloadAnimFile];
	}
	
	if (aSelectedMenuItemTag == kMenuItemTagPreScene) {
		[[CCDirector sharedDirector] replaceScene:[HelloWorldLayer scene]];
	}
}

-(void) setAnimState:(int)theNewState{
	mAnimState = theNewState;
	
	if (mAnimState == kAnimStateInvalid) {
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagLoad]) setIsEnabled:YES];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagCreateInstance]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagDestroyInstance]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemtagUnload]) setIsEnabled:NO];
	}
	
	if (mAnimState == kAnimStateLoaded) {
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagLoad]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagCreateInstance]) setIsEnabled:YES];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagDestroyInstance]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemtagUnload]) setIsEnabled:YES];
	}
	
	if (mAnimState == kAnimStateInstanceCreated) {
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagLoad]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagCreateInstance]) setIsEnabled:YES];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagDestroyInstance]) setIsEnabled:YES];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemtagUnload]) setIsEnabled:NO];
		
		[mTip setString:@"Tap the fish!"];
	}
	
	if (mAnimState == kAnimStateInstanceAllDestroyed) {
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagLoad]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagCreateInstance]) setIsEnabled:YES];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagDestroyInstance]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemtagUnload]) setIsEnabled:YES];
		
		[mTip setString:@""];
	}
	
	if (mAnimState == kAnimStateUnloaded) {
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagLoad]) setIsEnabled:YES];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagCreateInstance]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemTagDestroyInstance]) setIsEnabled:NO];
		[((CCMenuItemFont*)[mMenu getChildByTag:kMenuItemtagUnload]) setIsEnabled:NO];
	}
}

-(void) loadAnimFile{
	NSString* anAnimFileFullPath = [[CCFileUtils sharedFileUtils] fullPathFromRelativePath:@"fish.sam"];
	if ([SuperAnimNode LoadAnimFile:anAnimFileFullPath]){
		[self setAnimState:kAnimStateLoaded];
		[mTip setString:@"Load animation file sucessfully"];
	} else {
		[mTip setString:@"Fail to load animation file"];
	}
}
-(void) addAnimInstance{
	CGSize aScreenSize = [[CCDirector sharedDirector] winSize];
	CGPoint aRandomPos = CGPointMake(CCRANDOM_0_1() * aScreenSize.width, CCRANDOM_0_1() * aScreenSize.height);
	static int sId = 0;
	// the full path of animation file is the key.
	// if the animation file not been loaded , the super animation system will load it automatically
	NSString* anAnimFileFullPath = [[CCFileUtils sharedFileUtils] fullPathFromRelativePath:@"fish.sam"];
	SuperAnimNode* aSuperAnimNode = [SuperAnimNode create:anAnimFileFullPath Id:sId Listener:self];
	[aSuperAnimNode setPosition:aRandomPos];
	[self addChild:aSuperAnimNode];
	[aSuperAnimNode PlaySection:@"idle"];
	[mAnimNodeMap setObject:aSuperAnimNode forKey:[NSString stringWithFormat:@"%d", sId++]];
	[self setAnimState:kAnimStateInstanceCreated];
}
-(void) delAnimInstance{
	NSArray *keys = [mAnimNodeMap allKeys];
	for( id key in keys ) {
		SuperAnimNode* anAnimNode = [mAnimNodeMap objectForKey:key];
		if (anAnimNode != nil) {
			[self removeChild:anAnimNode cleanup:YES];
			[mAnimNodeMap removeObjectForKey:[NSString stringWithFormat:@"%d", [anAnimNode GetId]]];
			break;
		}
	}
	
	if ([mAnimNodeMap count] == 0) {
		[self setAnimState:kAnimStateInstanceAllDestroyed];
	}
}
-(void) unloadAnimFile{
	NSString* anAnimFileFullPath = [[CCFileUtils sharedFileUtils] fullPathFromRelativePath:@"fish.sam"];
	[SuperAnimNode UnloadAnimFile:anAnimFileFullPath];
	[self setAnimState:kAnimStateUnloaded];
}
-(void) ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
	if ([mAnimNodeMap count] == 0) {
		return;
	}
	
	for (id aTouch in touches) {
		CGPoint aTouchedPos = [self convertTouchToNodeSpace:aTouch];
		NSArray *keys = [mAnimNodeMap allKeys];
		for( id key in keys ) {
			SuperAnimNode* anAnimNode = [mAnimNodeMap objectForKey:key];
			if (anAnimNode != nil) {
				CGRect aBoundingBox = [anAnimNode boundingBox];
				if (CGRectContainsPoint(aBoundingBox, aTouchedPos)) {
					// if you tap an animation, make the animation play "active" section to respond
					if (![[anAnimNode GetCurSectionName] isEqualToString:@"active"]) {
						[anAnimNode PlaySection:@"active"];
					}
				}
			}
		}
	}
}

-(void) OnAnimSectionEnd:(int)theId LabelName:(NSString *)theLabelName{
	NSArray *keys = [mAnimNodeMap allKeys];
	for( id key in keys ) {
		SuperAnimNode* anAnimNode = [mAnimNodeMap objectForKey:key];
		if (anAnimNode != nil && [anAnimNode GetId] == theId) {
			if ([theLabelName isEqualToString:@"idle"]) {
				// play "idle" section loop
				[anAnimNode PlaySection:@"idle"];
			}
			
			if ([theLabelName isEqualToString:@"active"]) {
				// recover to "idle"
				[anAnimNode PlaySection:@"idle"];
			}
		}
	}
}
@end
