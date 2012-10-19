//
//  MoreScene.h
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

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "SuperAnimNodeV2.h"


@interface MoreScene : CCLayer<SuperAnimNodeListener> {
    int mAnimState;
	NSMutableDictionary* mAnimNodeMap;
	CCMenu* mMenu;
	CCLabelTTF* mTip;
}

+(CCScene *) scene;
-(void) menuCallback:(id)sender;
-(void) setAnimState:(int)theNewState;
// In fact, you don't have to load animation file before create a super animation node.
// Super Animation Core will do it automatically
-(void) loadAnimFile;
-(void) addAnimInstance;
-(void) delAnimInstance;
-(void) unloadAnimFile;
@end
