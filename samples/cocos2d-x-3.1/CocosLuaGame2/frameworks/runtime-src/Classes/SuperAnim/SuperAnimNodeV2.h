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
		virtual void OnTimeEvent(int theId, std::string theLabelName, int theEventId){}
	};
	class SuperAnimNode : public Node
	{
	private:
		int mId;
		SuperAnimNodeListener *mListener;
		SuperAnimHandler mAnimHandler;
		bool mIsLoop;
		int mAnimState;
		// support sprite sheet
		std::string mSpriteSheetFileFullPath;
		bool mUseSpriteSheet;
		Texture2D* mSpriteSheet;
		bool mIsFlipX;
		bool mIsFlipY;
		float mSpeedFactor;
		
		
		typedef std::map<SuperAnimSpriteId, SuperAnimSpriteId> SuperSpriteIdToSuperSpriteIdMap;
		SuperSpriteIdToSuperSpriteIdMap mReplacedSpriteMap;
		
		// for time event
		struct TimeEventInfo{
			std::string mLabelName;
			float mTimeFactor;
			int mEventId;
		};
		typedef std::vector<TimeEventInfo> TimeEventInfoArray;
		typedef std::map<std::string, TimeEventInfoArray> LabelNameToTimeEventInfoArrayMap;
		LabelNameToTimeEventInfoArrayMap mLabelNameToTimeEventInfoArrayMap;
		TimeEventInfoArray mCurTimeEventInfoArray;
	public:
		SuperAnimNode();
		~SuperAnimNode();
		static SuperAnimNode *create(std::string theAbsAnimFile, int theId, SuperAnimNodeListener *theListener);

		bool Init(std::string theAbsAnimFile, int theId, SuperAnimNodeListener *theListener);
		//void draw();
		virtual void draw(Renderer *renderer, const Mat4& transform, bool transformUpdated);
		//renderer callback
		void onDraw(const Mat4 &transform, bool transformUpdated);
		void update(float dt);
		void setFlipX(bool isFlip);
		void setFlipY(bool isFlip);

		bool PlaySection(const std::string &theLabel, bool isLoop = false);
		void Pause();
		void Resume();
		bool IsPause();
		bool IsPlaying();
		int GetCurFrame();
		int GetId();
		std::string GetCurSectionName();
		bool HasSection(const std::string &theLabelName);
		void setSpeedFactor(float theNewSpeedFactor);
		
		// for replaceable sprite
		void replaceSprite(const std::string &theOriginSpriteName, const std::string &theNewSpriteName);
		void resumeSprite(const std::string &theOriginSpriteName);
		
		// for time event
		// theTimeFactor is in [0.0f, 1.0f],
		// theTimeFactor = 0.0f means the event will be triggered at the first frame,
		// theTimeFactor = 1.0f means the event will be triggered at the last frame
		void registerTimeEvent(const std::string &theLabel, float theTimeFactor, int theEventId);
		void removeTimeEvent(const std::string &theLabel, int theEventId);
	private:
		// support sprite sheet
		void tryLoadSpriteSheet();
		void tryUnloadSpirteSheet();
		
		bool _insideBounds;                     /// whether or not the sprite was inside bounds the previous frame
		CustomCommand _customCommand;
	};
	
	// If you want to load super animation file before create super anim node,
	// call this function.
	extern bool LoadAnimFileExt(const std::string &theAbsAnimFile);
	
	// super animation file is loaded automatically when creating super anim node, then stored in a cache.
	// if you want to unload it, call this function.
	// P.S.: the textures used in animation are still in memory after call the function.
	// cocos2d keep a reference to these textures, call removeUnusedTextures by yourself
	// to remove those texture.
	extern void UnloadAnimFileExt(const std::string &theAbsAnimFile);
};

#endif