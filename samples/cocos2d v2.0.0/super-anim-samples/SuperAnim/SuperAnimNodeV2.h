//
//	SuperAnimNodeV2.h
//
//  Created by Raymond Lu(Raymondlu1105@qq.com)
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
#import "cocos2d.h"

@protocol SuperAnimNodeListener <NSObject>

-(void) OnAnimSectionEnd: (int)theId label:(NSString*) theLabelName;

@end

@interface SuperAnimNode : CCNode
{
	int mId;
	id<SuperAnimNodeListener> mListener;
	void *mAnimHandler;
	int mAnimState;
	// support sprite sheet
	NSString* mSpriteSheetFileFullPath;
	BOOL mUseSpriteSheet;
	CCTexture2D* mSpriteSheet;
	BOOL mIsFlipX;
	BOOL mIsFlipY;
	float mSpeedFactor;
}
@property (nonatomic,readwrite) BOOL flipX;
@property (nonatomic,readwrite) BOOL flipY;
@property (nonatomic,readwrite) float speedFactor;

+(id) create:(NSString*) theAbsAnimFile id:(int) theId listener:(id<SuperAnimNodeListener>) theListener;
-(id) initWithAnimFile:(NSString*) theAbsAnimFile id:(int) theId listener:(id<SuperAnimNodeListener>) theListener;
-(void)dealloc;
-(void) update: (ccTime) time;
-(BOOL) PlaySection:(NSString*)	theLabel;
-(void) Pause;
-(void) Resume;
-(BOOL) IsPause;
-(BOOL) IsPlaying;
-(int) GetCurFrame;
-(NSString*) GetCurSectionName;
-(BOOL) HasSection:(NSString*) theLabelName;
// support sprite sheet
-(void) tryLoadSpriteSheet;
-(void) tryUnloadSpirteSheet;

// If you want to load super animation file before create super anim node,
// call this function.
+(BOOL) LoadAnimFileExt:(const char*) theAbsAnimFile;
// super animation file is loaded automatically when creating super anim node, then stored in a cache.
// if you want to unload it, call this function.
// P.S.: the textures used in animation are still in memory after call the function.
// cocos2d keep a reference to these textures, call removeUnusedTextures by yourself
// to remove those texture.
+(void) UnloadAnimFileExt:(const char*) theAbsAnimFile;
@end

