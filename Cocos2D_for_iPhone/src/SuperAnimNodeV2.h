//
//	SuperAnimNodeV2.h
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

//#import "SuperAnimCommon.h"
#import "cocos2d.h"

@protocol SuperAnimNodeListener
@required
-(void) OnAnimSectionEnd:(int) theId LabelName:(NSString*) theLabelName;
@end


@interface SuperAnimNode : CCNode
{
	int mId;
	id<SuperAnimNodeListener> mListener;
	// workaround
	int mAnimHandlerKey;
	int mAnimState;
}
//SuperAnimNode();
//~SuperAnimNode();
+(id) create:(NSString*)theAbsAnimFile Id:(int)theId Listener:(id<SuperAnimNodeListener>) theListener;
-(BOOL) Init:(NSString*)theAbsAnimFile Id:(int)theId Listener:(id<SuperAnimNodeListener>) theListener;
//void draw();
-(void) update:(ccTime) dt;
-(BOOL) PlaySection:(NSString*) theLabel;
-(void) Pause;
-(void) Resume;
-(BOOL) IsPause;
-(BOOL) IsPlaying;
-(int) GetCurFrame;
-(NSString*) GetCurSectionName;
-(BOOL) HasSection:(NSString*) theLabelName;
-(int) GetId;

// If you want to load super animation file before create super anim node,
// call this function.
+(BOOL) LoadAnimFile:(NSString*) theAbsAnimFile;

// super animation file is loaded automatically when creating super anim node, then stored in a cache.
// if you want to unload it, call this function.
// P.S.: the textures used in animation are still in memory after call the function.
// cocos2d keep a reference to these textures, call removeUnusedTextures by yourself
// to remove those texture.
+(void) UnloadAnimFile:(NSString*) theAbsAnimFile;
@end
