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
#ifndef SuperAnimNode_H
#define SuperAnimNode_H

#include "SuperAnimCommon.h"

#include "cocos2d.h"
using namespace cocos2d;

namespace SuperAnim
{
	class SuperAnimNodeListener
	{
	public:
		virtual void OnAnimSectionEnd(int theId, std::string theLabelName){}
	};
	class SuperAnimNode : public CCNode
	{
	private:
		int mId;
		SuperAnimNodeListener *mListener;
		SuperAnimHandler mAnimHandler;
		int mAnimState;
		// support sprite sheet
		std::string mSpriteSheetFileFullPath;
		bool mUseSpriteSheet;
		CCTexture2D* mSpriteSheet;
		bool mIsFlipX;
		bool mIsFlipY;
	public:
		SuperAnimNode();
		~SuperAnimNode();
		static SuperAnimNode *create(std::string theAbsAnimFile, int theId, SuperAnimNodeListener *theListener);

		bool Init(std::string theAbsAnimFile, int theId, SuperAnimNodeListener *theListener);
		void draw();
		void update(float dt);
		void setFlipX(bool isFlip);
		void setFlipY(bool isFlip);

		bool PlaySection(std::string theLabel);
		void Pause();
		void Resume();
		bool IsPause();
		bool IsPlaying();
		int GetCurFrame();
		std::string GetCurSectionName();
		bool HasSection(std::string theLabelName);
	private:
		// support sprite sheet
		void tryLoadSpriteSheet();
		void tryUnloadSpirteSheet();
	};
	
	// If you want to load super animation file before create super anim node,
	// call this function.
	extern bool LoadAnimFile(std::string theAbsAnimFile);
	
	// super animation file is loaded automatically when creating super anim node, then stored in a cache.
	// if you want to unload it, call this function.
	// P.S.: the textures used in animation are still in memory after call the function.
	// cocos2d keep a reference to these textures, call removeUnusedTextures by yourself
	// to remove those texture.
	extern void UnloadAnimFile(std::string theAbsAnimFile);
};

#endif