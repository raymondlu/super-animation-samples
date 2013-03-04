//
//	SuperAnimCommon.h
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
#ifndef SuperAnimationMath_h
#define SuperAnimationMath_h

#include <math.h>
#include <string>

namespace SuperAnim{

	class SuperAnimMatrix3
	{
	public:
		union
		{
			float m[3][3];
			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			};
		};

	public:
		SuperAnimMatrix3();
		void LoadIdentity();
		SuperAnimMatrix3 operator*(const SuperAnimMatrix3 &theMat) const;
	};
	//////////////////////////////////////////////////////////////////////////
	class SuperAnimTransform
	{
	public:
		SuperAnimMatrix3				mMatrix;

	public:
		SuperAnimTransform();
		void Scale(float sx, float sy);
		SuperAnimTransform				TransformSrc(const SuperAnimTransform& theSrcTransform);		
		SuperAnimTransform				InterpolateTo(const SuperAnimTransform& theNextTransform, float thePct);
	};
	//////////////////////////////////////////////////////////////////////////
	class Color
	{
	public:
		int mRed;
		int mGreen;
		int mBlue;
		int mAlpha;
	public:
		Color();
		Color(int theRed, int theGreen, int theBlue, int theAlpha);
		Color InterpolateTo(const Color& theNextColor, float thePct);
	};
	//////////////////////////////////////////////////////////////////////////
	// for sprite
	typedef std::string SuperAnimSpriteId;
	#define InvalidSuperAnimSpriteId ""
	
	// implemented by super animation node
	extern SuperAnimSpriteId LoadSuperAnimSprite(std::string theSpriteName);
	extern void UnloadSuperSprite(SuperAnimSpriteId theSpriteId);
	
	//////////////////////////////////////////////////////////////////////////
	// for animation main definition
	struct SuperAnimHandler{
		std::string mMainDefKey;
		std::string mCurLabel;
		float mCurFrameNum;
		float mAnimRate;
		float mWidth;
		float mHeight;
		bool mIsHandlerValid;
		
		SuperAnimHandler(){
			mCurFrameNum = 0.0f;
			mAnimRate = 0.0f;
			mWidth = 0.0f;
			mHeight = 0.0f;
			mIsHandlerValid = false;
		}
		
		bool IsValid() const{
			return mIsHandlerValid;
		}
	};
	
	struct SuperAnimObjDrawInfo{
		SuperAnimSpriteId mSpriteId;
		SuperAnimTransform mTransform;
		Color mColor;
		SuperAnimObjDrawInfo(){
			mSpriteId = InvalidSuperAnimSpriteId;
		}
	};
	
	// implemented by super animation core
	extern SuperAnimHandler GetSuperAnimHandler(std::string theAbsAnimFile);
	extern void BeginIterateAnimObjDrawInfo();
	extern bool IterateAnimObjDrawInfo(const SuperAnimHandler &theHandler, SuperAnimObjDrawInfo& theOutputObjDrawInfo);
	extern void IncAnimFrameNum(SuperAnimHandler &theMainDefHandler, float theDeltaTime, bool &hitNewFrame);
	extern bool HasSection(const SuperAnimHandler &theHandler, std::string theLabelName);
	extern bool PlayBySection(SuperAnimHandler &theHandler, std::string theLabelName);
};

// platform related functions
extern unsigned char* GetFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
#endif