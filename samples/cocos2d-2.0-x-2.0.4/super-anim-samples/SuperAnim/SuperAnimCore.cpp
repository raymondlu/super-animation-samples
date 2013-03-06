//
//	SuperAnimCore.cpp
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
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include "SuperAnimCommon.h"

#define SAM_VERSION 1
#define TWIPS_PER_PIXEL (20.0f)
#define LONG_TO_FLOAT (65536.0f)

#define FRAMEFLAGS_REMOVES		0x01
#define FRAMEFLAGS_ADDS			0x02
#define FRAMEFLAGS_MOVES		0x04
#define FRAMEFLAGS_FRAME_NAME	0x08

#define MOVEFLAGS_ROTATE		0x4000
#define MOVEFLAGS_COLOR			0x2000
#define MOVEFLAGS_MATRIX		0x1000
#define MOVEFLAGS_LONGCOORDS	0x0800


#ifndef max
#define max(x,y) (((x) < (y)) ? (y) : (x))
#endif

namespace SuperAnim {
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	SuperAnimMatrix3::SuperAnimMatrix3()
	{
	}
	void SuperAnimMatrix3::LoadIdentity()
	{
		m01	= m02 = m10 = m12 = m20 = m21 = 0;
		m00 = m11 = m22 = 1;
	}
	
	SuperAnimMatrix3 SuperAnimMatrix3::operator*(const SuperAnimMatrix3 &theMat) const
	{
		SuperAnimMatrix3 aResult;
		aResult.m00 = m00*theMat.m00 + m01*theMat.m10 + m02*theMat.m20;
		aResult.m01 = m00*theMat.m01 + m01*theMat.m11 + m02*theMat.m21;
		aResult.m02 = m00*theMat.m02 + m01*theMat.m12 + m02*theMat.m22;
		aResult.m10 = m10*theMat.m00 + m11*theMat.m10 + m12*theMat.m20;
		aResult.m11 = m10*theMat.m01 + m11*theMat.m11 + m12*theMat.m21;
		aResult.m12 = m10*theMat.m02 + m11*theMat.m12 + m12*theMat.m22;
		aResult.m20 = m20*theMat.m00 + m21*theMat.m10 + m22*theMat.m20;
		aResult.m21 = m20*theMat.m01 + m21*theMat.m11 + m22*theMat.m21;
		aResult.m22 = m20*theMat.m02 + m21*theMat.m12 + m22*theMat.m22;
		return aResult;
	}
	
	//////////////////////////////////////////////////////////////////////////
	
	SuperAnimTransform::SuperAnimTransform()
	{
		mMatrix.LoadIdentity();
	}
	
	void SuperAnimTransform::Scale(float sx, float sy)
	{
		mMatrix.m00 *= sx;
		mMatrix.m01 *= sx;
		mMatrix.m02 *= sx;
		mMatrix.m10 *= sy;
		mMatrix.m11 *= sy;
		mMatrix.m12 *= sy;
	}
	
	SuperAnimTransform SuperAnimTransform::TransformSrc(const SuperAnimTransform& theSrcTransform)
	{	
		SuperAnimTransform aNewTransform;	
		
		aNewTransform.mMatrix.m00 = mMatrix.m00*theSrcTransform.mMatrix.m00 + mMatrix.m01*theSrcTransform.mMatrix.m10;
		aNewTransform.mMatrix.m01 = mMatrix.m00*theSrcTransform.mMatrix.m01 + mMatrix.m01*theSrcTransform.mMatrix.m11;
		aNewTransform.mMatrix.m10 = mMatrix.m10*theSrcTransform.mMatrix.m00 + mMatrix.m11*theSrcTransform.mMatrix.m10;
		aNewTransform.mMatrix.m11 = mMatrix.m10*theSrcTransform.mMatrix.m01 + mMatrix.m11*theSrcTransform.mMatrix.m11;
		aNewTransform.mMatrix.m02 = mMatrix.m02 + mMatrix.m00*theSrcTransform.mMatrix.m02 + mMatrix.m01*theSrcTransform.mMatrix.m12;
		aNewTransform.mMatrix.m12 = mMatrix.m12 + mMatrix.m10*theSrcTransform.mMatrix.m02 + mMatrix.m11*theSrcTransform.mMatrix.m12;
		
		return aNewTransform;
	}
	
	SuperAnimTransform SuperAnimTransform::InterpolateTo(const SuperAnimTransform& theNextTransform, float thePct)
	{
		SuperAnimTransform aNewTransform;
		
		aNewTransform.mMatrix.m00 = (mMatrix.m00 * (1.0f - thePct)) + (theNextTransform.mMatrix.m00 * thePct);
		aNewTransform.mMatrix.m01 = (mMatrix.m01 * (1.0f - thePct)) + (theNextTransform.mMatrix.m01 * thePct);
		aNewTransform.mMatrix.m10 = (mMatrix.m10 * (1.0f - thePct)) + (theNextTransform.mMatrix.m10 * thePct);
		aNewTransform.mMatrix.m11 = (mMatrix.m11 * (1.0f - thePct)) + (theNextTransform.mMatrix.m11 * thePct);
		
		aNewTransform.mMatrix.m02 = (mMatrix.m02 * (1.0f - thePct)) + (theNextTransform.mMatrix.m02 * thePct);
		aNewTransform.mMatrix.m12 = (mMatrix.m12 * (1.0f - thePct)) + (theNextTransform.mMatrix.m12 * thePct);
		
		return aNewTransform;
	}
	
	//////////////////////////////////////////////////////////////////////////
	
	Color::Color() :
	mRed(0),
	mGreen(0),
	mBlue(0),
	mAlpha(255)
	{
	}
	
	Color::Color(int theRed, int theGreen, int theBlue, int theAlpha) :
	mRed(theRed),
	mGreen(theGreen),
	mBlue(theBlue),
	mAlpha(theAlpha)
	{
	}
	
	Color Color::InterpolateTo(const Color& theNextColor, float thePct){
		return Color((int)(mRed * (1.0f - thePct) + theNextColor.mRed * thePct),
					 (int)(mGreen * (1.0f - thePct) + theNextColor.mGreen * thePct),
					 (int)(mBlue * (1.0f - thePct) + theNextColor.mBlue * thePct),
					 (int)(mAlpha * (1.0f - thePct) + theNextColor.mAlpha * thePct));
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Animation object definition
	
	class SuperAnimObject
	{
	public:
		int mObjectNum;
		int mResNum;
		SuperAnimTransform mTransform;
		Color mColor;
	};
	
	typedef std::vector<SuperAnimObject> SuperAnimObjectVector;
	typedef std::map<int, SuperAnimObject> IntToSuperAnimObjectMap;
	
	class SuperAnimImage
	{
	public:
		SuperAnimSpriteId mSpriteId;
		std::string mImageName;
		int mWidth;
		int mHeight;
		SuperAnimTransform mTransform;
	};
	typedef std::vector<SuperAnimImage> SuperAnimImageVector;
	
	class SuperAnimFrame
	{
	public:
		SuperAnimObjectVector mObjectVector;
	};
	typedef std::vector<SuperAnimFrame> SuperAnimFrameVector;
	typedef std::map<std::string, int> StringToIntMap;
	class SuperAnimMainDef
	{
	public:
		SuperAnimFrameVector mFrames;
		int mStartFrameNum;
		int mEndFrameNum;
		int mAnimRate;
		StringToIntMap mLabels;
		int mX;
		int mY;
		int mWidth;
		int mHeight;
		SuperAnimImageVector mImageVector;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////
	
	typedef std::map<std::string, SuperAnimMainDef> SuperAnimMainDefMap;
	class SuperAnimDefMgr
	{
	private:
		SuperAnimMainDefMap mMainDefCache;
	private:
		SuperAnimDefMgr();
		~SuperAnimDefMgr();
		
		// std::string theSuperAnimFile include the absolute path
		bool LoadSuperAnimMainDef(std::string theSuperAnimFile);
	public:
		static SuperAnimDefMgr *GetInstance();
		static void DestroyInstance();

		// std::string theSuperAnimFile include the absolute path
		SuperAnimMainDef *Load_GetSuperAnimMainDef(std::string theSuperAnimFile);
		void UnloadSuperAnimMainDef(std::string theName);
	};
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// implement extern functions
	SuperAnimHandler GetSuperAnimHandler(std::string theAbsAnimFile){
		SuperAnimHandler aSuperAnimHander;
		SuperAnimMainDef *aMainDef = SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(theAbsAnimFile);
		if (aMainDef) {
			aSuperAnimHander.mMainDefKey = theAbsAnimFile; // right now just use the animation file name as the key
			aSuperAnimHander.mAnimRate = aMainDef->mAnimRate;
			aSuperAnimHander.mWidth = aMainDef->mWidth;
			aSuperAnimHander.mHeight = aMainDef->mHeight;
			aSuperAnimHander.mCurFrameNum = aMainDef->mStartFrameNum;
			aSuperAnimHander.mIsHandlerValid = true;
		} else {
			aSuperAnimHander.mIsHandlerValid = false;
		}
		
		return aSuperAnimHander;
	}
	
	static int sAnimObjIndex = 0;
	static bool sShouldStartAnimObjDrawItr = false;
	void BeginIterateAnimObjDrawInfo(){
		sAnimObjIndex = 0;
		sShouldStartAnimObjDrawItr = true;
	}
	
	bool IterateAnimObjDrawInfo(const SuperAnimHandler &theHandler, SuperAnimObjDrawInfo& theOutputObjDrawInfo){
		if (!sShouldStartAnimObjDrawItr) {
			assert(false && "Forgot to call BeginIterateAnimObjDrawInfo?");
			return false;
		}
		
		if (!theHandler.IsValid()) {
			assert(false && "The Animation handler is not valid.");
			return false;
		}
		
		SuperAnimMainDef *aMainDef = SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(theHandler.mMainDefKey);
		if (aMainDef == NULL) {
			assert(false && "I can't find the Animation definition.");
			return false;
		}
		
		int aCurFrameNum = (int)theHandler.mCurFrameNum;
		SuperAnimFrame *aCurFrame = &aMainDef->mFrames[aCurFrameNum];
		if (sAnimObjIndex >= aCurFrame->mObjectVector.size()) {
			// we have iterated all objects in this frame
			sShouldStartAnimObjDrawItr = false;
			return false;
		}
		
		SuperAnimObject *aCurObject = &aCurFrame->mObjectVector[sAnimObjIndex];
		
		// find the image, fill the sprite id
		SuperAnimImage *aSuperAnimImage = &aMainDef->mImageVector[aCurObject->mResNum];
		theOutputObjDrawInfo.mSpriteId = aSuperAnimImage->mSpriteId;
		
		// do the interpolateion to next frame for transform & color
		if (aCurFrameNum == aMainDef->mEndFrameNum) {
			// reach the end frame, don't need to do any interpolation
			theOutputObjDrawInfo.mTransform = aCurObject->mTransform;
			theOutputObjDrawInfo.mColor = aCurObject->mColor;
		} else {
			int aNextFrameNum = aCurFrameNum + 1;
			bool finishedInterp = false;
			SuperAnimFrame *aNextFrame = &aMainDef->mFrames[aNextFrameNum];
			for (int i = 0; i < aNextFrame->mObjectVector.size(); ++i) {
				SuperAnimObject *anObj = &aNextFrame->mObjectVector[i];
				if (anObj->mObjectNum == aCurObject->mObjectNum &&
					anObj->mResNum == aCurObject->mResNum) {
					float anInterp = theHandler.mCurFrameNum - aCurFrameNum;
					theOutputObjDrawInfo.mTransform = aCurObject->mTransform.InterpolateTo(anObj->mTransform, anInterp);
					theOutputObjDrawInfo.mColor = aCurObject->mColor.InterpolateTo(anObj->mColor, anInterp);
					finishedInterp = true;
					break;
				}
			}
			if (!finishedInterp) {
				// we miss the object in next frame?
				// never mind
				theOutputObjDrawInfo.mTransform = aCurObject->mTransform;
				theOutputObjDrawInfo.mColor = aCurObject->mColor;
			}
		}
		
		theOutputObjDrawInfo.mTransform = theOutputObjDrawInfo.mTransform.TransformSrc(aSuperAnimImage->mTransform);
		SuperAnimMatrix3 aMatrix;
		aMatrix.LoadIdentity();
		aMatrix.m02 = aSuperAnimImage->mWidth * 0.5f;
		aMatrix.m12 = aSuperAnimImage->mHeight * 0.5f;
		theOutputObjDrawInfo.mTransform.mMatrix = theOutputObjDrawInfo.mTransform.mMatrix * aMatrix;
		
		sAnimObjIndex++;
		return true;
	}
	
	void IncAnimFrameNum(SuperAnimHandler &theMainDefHandler, float theDeltaTime, bool &hitNewLabel){
		
		if (!theMainDefHandler.IsValid()) {
			return;
		}
		
		int aLastFrameNum = (int)theMainDefHandler.mCurFrameNum;
		theMainDefHandler.mCurFrameNum += theDeltaTime * theMainDefHandler.mAnimRate;
		int aCurFrame = (int)theMainDefHandler.mCurFrameNum;
		
		if (aCurFrame != aLastFrameNum) // Reach new frame
		{
			// Check whether reach a new label frame
			bool aIsNewLabel = false;
			SuperAnimMainDef *aMainDef = SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(theMainDefHandler.mMainDefKey);
			if (aCurFrame >= aMainDef->mEndFrameNum)// reach the end??
			{
				theMainDefHandler.mCurFrameNum = aMainDef->mEndFrameNum;
				aIsNewLabel = true;
			}
			else
			{
				std::string aTempLabel;
				int aMaxFrameNum = -1;
				for (StringToIntMap::const_iterator it = aMainDef->mLabels.begin(); it != aMainDef->mLabels.end(); ++it)
				{
					if (aCurFrame + 1 >= it->second && it->second > aMaxFrameNum)
					{
						aMaxFrameNum = it->second;
						aTempLabel = it->first;
					}
				}
				if (aTempLabel != theMainDefHandler.mCurLabel) {
					aIsNewLabel = true;
				}
			}
			
			hitNewLabel = aIsNewLabel;
		}
	}
	
	bool HasSection(const SuperAnimHandler &theHandler, std::string theLabelName){
		SuperAnimMainDef *aMainDef = SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(theHandler.mMainDefKey);
		if (aMainDef == NULL) {
			return false;
		}
		for (StringToIntMap::const_iterator it = aMainDef->mLabels.begin(); it != aMainDef->mLabels.end(); ++it)
		{
			if (it->first == theLabelName)
				return true;
		}
		
		return false;
	}
	
	bool PlayBySection(SuperAnimHandler &theHandler, std::string theLabelName){	
		SuperAnimMainDef *aMainDef = SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(theHandler.mMainDefKey);
		if (aMainDef == NULL) {
			theHandler.mIsHandlerValid = false;
			return false;
		}
		for (StringToIntMap::const_iterator it = aMainDef->mLabels.begin(); it != aMainDef->mLabels.end(); ++it)
		{
			if (it->first == theLabelName)
			{
				theHandler.mCurFrameNum = it->second;
				theHandler.mCurLabel = theLabelName;
				theHandler.mIsHandlerValid = true;
				return true;
			}
		}
		
		theHandler.mIsHandlerValid = false;
		return false;
	}
	
	bool LoadAnimFile(std::string theAbsAnimFile){
		return SuperAnimDefMgr::GetInstance()->Load_GetSuperAnimMainDef(theAbsAnimFile) != NULL;
	}
	
	void UnloadAnimFile(std::string theAbsAnimFile){
		SuperAnimDefMgr::GetInstance()->UnloadSuperAnimMainDef(theAbsAnimFile);
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	typedef unsigned char uchar;
	typedef std::vector<uchar> ByteVector;
	
	class BufferReader
	{
	public:
		ByteVector				mData;
		int						mDataBitSize;
		mutable int				mReadBitPos;
		mutable int				mWriteBitPos;	
		
	public:
		BufferReader();
		virtual ~BufferReader();
		void					SetData(uchar* thePtr, int theCount);
		uchar*					GetDataPtr();
		int						GetDataLen() const;	
		void					Clear();
		
		uchar					ReadByte() const;
		bool					ReadBoolean() const;
		short					ReadShort() const;
		long					ReadLong() const;
		std::string				ReadString() const;	
	};
	
	
	BufferReader::BufferReader()
	{
		mDataBitSize = 0;
		mReadBitPos = 0;
		mWriteBitPos = 0;	
	}
	
	BufferReader::~BufferReader()
	{
	}
	
	void BufferReader::SetData(uchar* thePtr, int theCount)
	{
		mData.clear();
		mData.reserve(theCount);
		mData.insert(mData.begin(), thePtr, thePtr + theCount);
		mDataBitSize = mData.size() * 8;
	}
	
	uchar* BufferReader::GetDataPtr()
	{
		if (mData.size() == 0)
			return NULL;
		return &mData[0];
	}
	
	int BufferReader::GetDataLen() const
	{
		return (mDataBitSize + 7) / 8; // Round up
	}
	
	void BufferReader::Clear()
	{
		mReadBitPos = 0;
		mWriteBitPos = 0;
		mDataBitSize = 0;
		mData.clear();
	}
	
	uchar BufferReader::ReadByte() const
	{
		if ((mReadBitPos + 7)/8 >= (int)mData.size())
		{		
			return 0; // Underflow
		}
		
		if (mReadBitPos % 8 == 0)
		{
			uchar b = mData[mReadBitPos/8];
			mReadBitPos += 8;
			return b;
		}
		else
		{
			int anOfs = mReadBitPos % 8;
			
			uchar b = 0;
			
			b = mData[mReadBitPos/8] >> anOfs;
			b |= mData[(mReadBitPos/8)+1] << (8 - anOfs);
			
			mReadBitPos += 8;		
			
			return b;
		}
	}
	
	bool BufferReader::ReadBoolean() const
	{
		return ReadByte() != 0;
	}
	
	short BufferReader::ReadShort() const
	{
		short aShort = ReadByte();
		aShort |= ((short) ReadByte() << 8);
		return aShort;	
	}
	
	long BufferReader::ReadLong() const
	{
		long aLong = ReadByte();
		aLong |= ((long) ReadByte()) << 8;
		aLong |= ((long) ReadByte()) << 16;
		aLong |= ((long) ReadByte()) << 24;
		
		return aLong;
	}
	
	std::string	BufferReader::ReadString() const
	{
		std::string aString;
		int aLen = ReadShort();
		
		for (int i = 0; i < aLen; i++)
			aString += (char) ReadByte();
		
		return aString;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	
	static SuperAnimDefMgr *sInstance = NULL;
	
	SuperAnimDefMgr::SuperAnimDefMgr()
	{
		
	}
	
	SuperAnimDefMgr::~SuperAnimDefMgr()
	{
		mMainDefCache.clear();
	}
	
	SuperAnimDefMgr * SuperAnimDefMgr::GetInstance()
	{
		if (sInstance == NULL)
		{
			sInstance = new SuperAnimDefMgr();
		}
		
		return sInstance;
	}
	
	void SuperAnimDefMgr::DestroyInstance()
	{
		if (sInstance)
		{
			delete sInstance;
			sInstance = NULL;
		}
	}
		
	typedef std::map<int, SuperAnimObject> IntToSuperAnimObjectMap;
	
	bool SuperAnimDefMgr::LoadSuperAnimMainDef(std::string theSuperAnimFile)
	{
		std::string aFullPath = theSuperAnimFile;
		
		std::string aCurDir = "";
		int aLastSlash = max((int) theSuperAnimFile.rfind('\\'), (int) theSuperAnimFile.rfind('/'));
		if (aLastSlash != std::string::npos){
			aCurDir = theSuperAnimFile.substr(0, aLastSlash);
		}

		unsigned long aFileSize = 0;
		unsigned char *aFileBuffer = GetFileData(aFullPath.c_str(), "rb", &aFileSize);
		if (aFileBuffer == NULL)
		{
			assert(false && "Cannot allocate memory.");
			return false;
		}
		BufferReader aBuffer;
		aBuffer.SetData(aFileBuffer, aFileSize);
		// free memory
		delete[] aFileBuffer;
		
		if (aBuffer.ReadLong() != 0x2E53414D)
		{
			assert(false && "Bad file format.");
			return false;
		}
		
		int aVersion = aBuffer.ReadLong();
		
		if (aVersion != SAM_VERSION)
		{
			assert(false && "Wrong version.");
			return false;
		}
		
		SuperAnimMainDef &aMainDef = mMainDefCache[theSuperAnimFile]; 
		aMainDef.mAnimRate = aBuffer.ReadByte();
		aMainDef.mX = aBuffer.ReadLong() / TWIPS_PER_PIXEL;
		aMainDef.mY = aBuffer.ReadLong() / TWIPS_PER_PIXEL;
		aMainDef.mWidth = aBuffer.ReadLong() / TWIPS_PER_PIXEL;
		aMainDef.mHeight = aBuffer.ReadLong() / TWIPS_PER_PIXEL;
		
		int aNumImages = aBuffer.ReadShort();
		aMainDef.mImageVector.resize(aNumImages);
		for (int anImageNum = 0; anImageNum < aNumImages; ++anImageNum)
		{
			SuperAnimImage &aSuperAnimImage = aMainDef.mImageVector[anImageNum];
			aSuperAnimImage.mImageName = aBuffer.ReadString();
			aSuperAnimImage.mWidth = aBuffer.ReadShort();
			aSuperAnimImage.mHeight = aBuffer.ReadShort();
			
			aSuperAnimImage.mTransform.mMatrix.m00 = aBuffer.ReadLong() / (LONG_TO_FLOAT * TWIPS_PER_PIXEL);
			aSuperAnimImage.mTransform.mMatrix.m01 = -aBuffer.ReadLong() / (LONG_TO_FLOAT * TWIPS_PER_PIXEL);
			aSuperAnimImage.mTransform.mMatrix.m10 = -aBuffer.ReadLong() / (LONG_TO_FLOAT * TWIPS_PER_PIXEL);
			aSuperAnimImage.mTransform.mMatrix.m11 = aBuffer.ReadLong() / (LONG_TO_FLOAT * TWIPS_PER_PIXEL);
			aSuperAnimImage.mTransform.mMatrix.m02 = aBuffer.ReadShort() / TWIPS_PER_PIXEL;
			aSuperAnimImage.mTransform.mMatrix.m12 = aBuffer.ReadShort() / TWIPS_PER_PIXEL;
			
			std::string aImagePath;
			if (aCurDir.empty()) {
				aImagePath = aSuperAnimImage.mImageName;
			} else {
				aImagePath = aCurDir + '/' + aSuperAnimImage.mImageName;
			}
			
			aSuperAnimImage.mSpriteId = LoadSuperAnimSprite(aImagePath);
		}
		
		int aNumFrames = aBuffer.ReadShort();
		assert(aNumFrames > 0 && "We don't have valid frames.");
		aMainDef.mStartFrameNum = 0;
		aMainDef.mEndFrameNum = aNumFrames - 1;
		aMainDef.mFrames.resize(aNumFrames);
		IntToSuperAnimObjectMap aCurObjectMap;
		for (int aFrameNum = 0; aFrameNum < aNumFrames; ++aFrameNum)
		{
			SuperAnimFrame &aFrame = aMainDef.mFrames[aFrameNum];
			uchar aFrameFlags = aBuffer.ReadByte();
			
			if (aFrameFlags & FRAMEFLAGS_REMOVES)
			{
				int aNumRemoves = aBuffer.ReadByte();
				for (int aRemoveNum = 0; aRemoveNum < aNumRemoves; ++ aRemoveNum)
				{
					int anObjectId = aBuffer.ReadShort();
					IntToSuperAnimObjectMap::iterator anIt = aCurObjectMap.find(anObjectId);
					if (anIt != aCurObjectMap.end())
					{
						aCurObjectMap.erase(anIt);
					}
				}
			}
			
			if (aFrameFlags & FRAMEFLAGS_ADDS)
			{
				int aNumAdds = aBuffer.ReadByte();
				for(int anAddNum = 0; anAddNum < aNumAdds; ++anAddNum)
				{
					int anObjNum = (aBuffer.ReadShort() & 0x07FF);
					SuperAnimObject& aSuperAnimObject = aCurObjectMap[anObjNum];
					aSuperAnimObject.mObjectNum = anObjNum;
					aSuperAnimObject.mResNum = aBuffer.ReadByte();
					aSuperAnimObject.mColor = Color(255, 255, 255, 255);
				}
			}
			
			if (aFrameFlags & FRAMEFLAGS_MOVES)
			{
				int aNumMoves = aBuffer.ReadByte();
				for (int aMoveNum = 0; aMoveNum < aNumMoves; ++ aMoveNum)
				{
					unsigned short aFlagsAndObjectNum = aBuffer.ReadShort();
					int anObjectNum = aFlagsAndObjectNum & 0x03FF;
					
					IntToSuperAnimObjectMap::iterator anIt = aCurObjectMap.find(anObjectNum);
					if (anIt == aCurObjectMap.end())
						continue;
					SuperAnimObject &aSuperAnimObject = anIt->second;
					aSuperAnimObject.mTransform.mMatrix.LoadIdentity();
					
					if (aFlagsAndObjectNum & MOVEFLAGS_MATRIX)
					{
						aSuperAnimObject.mTransform.mMatrix.m00 = aBuffer.ReadLong() / LONG_TO_FLOAT;
						aSuperAnimObject.mTransform.mMatrix.m01 = -aBuffer.ReadLong() / LONG_TO_FLOAT;
						aSuperAnimObject.mTransform.mMatrix.m10 = -aBuffer.ReadLong() / LONG_TO_FLOAT;
						aSuperAnimObject.mTransform.mMatrix.m11 = aBuffer.ReadLong() / LONG_TO_FLOAT;
					}
					else if (aFlagsAndObjectNum & MOVEFLAGS_ROTATE)
					{
						float aRot = aBuffer.ReadShort() / 1000.0f;
						float sinRot = sinf(aRot);
						float cosRot = cosf(aRot);
						aSuperAnimObject.mTransform.mMatrix.m00 = cosRot;
						aSuperAnimObject.mTransform.mMatrix.m01 = sinRot;
						aSuperAnimObject.mTransform.mMatrix.m10 = -sinRot;
						aSuperAnimObject.mTransform.mMatrix.m11 = cosRot;
					}
					
					SuperAnimMatrix3 aMatrix;
					aMatrix.LoadIdentity();
					if (aFlagsAndObjectNum & MOVEFLAGS_LONGCOORDS)
					{
						aMatrix.m02 = aBuffer.ReadLong() / TWIPS_PER_PIXEL;
						aMatrix.m12 = aBuffer.ReadLong() / TWIPS_PER_PIXEL;
					}
					else
					{
						aMatrix.m02 = aBuffer.ReadShort() / TWIPS_PER_PIXEL;
						aMatrix.m12 = aBuffer.ReadShort() / TWIPS_PER_PIXEL;
					}
					aSuperAnimObject.mTransform.mMatrix = aMatrix * aSuperAnimObject.mTransform.mMatrix;
					
					if (aFlagsAndObjectNum & MOVEFLAGS_COLOR)
					{
						aSuperAnimObject.mColor.mRed = aBuffer.ReadByte();
						aSuperAnimObject.mColor.mGreen = aBuffer.ReadByte();
						aSuperAnimObject.mColor.mBlue = aBuffer.ReadByte();
						aSuperAnimObject.mColor.mAlpha = aBuffer.ReadByte();
					}
				}
			}
			
			if (aFrameFlags & FRAMEFLAGS_FRAME_NAME)
			{
				std::string aFrameName = aBuffer.ReadString();
				aMainDef.mLabels.insert(StringToIntMap::value_type(aFrameName, aFrameNum));
			}
			
			aFrame.mObjectVector.resize(aCurObjectMap.size());
			aFrame.mObjectVector.clear();
			for (IntToSuperAnimObjectMap::iterator anIt = aCurObjectMap.begin(); anIt != aCurObjectMap.end(); ++anIt)
			{
				SuperAnimObject &anObject = anIt->second;
				aFrame.mObjectVector.push_back(anObject);
			}

		}
		
		return true;
	}
	
	SuperAnimMainDef *SuperAnimDefMgr::Load_GetSuperAnimMainDef(std::string theSuperAnimFile)
	{
		SuperAnimMainDefMap::iterator anItr = mMainDefCache.find(theSuperAnimFile);
		if (anItr != mMainDefCache.end())
		{
			return &anItr->second;
		}
		
		if (LoadSuperAnimMainDef(theSuperAnimFile) == false)
			return NULL;
		
		return Load_GetSuperAnimMainDef(theSuperAnimFile);
	}
	
	void SuperAnimDefMgr::UnloadSuperAnimMainDef(std::string theName)
	{
		SuperAnimMainDefMap::iterator anItr = mMainDefCache.find(theName);
		if (anItr == mMainDefCache.end())
			return;
		
		// unload the sprites
		for (int i = 0; i < (int)anItr->second.mImageVector.size(); ++i)
		{
			SuperAnimImage anImage = anItr->second.mImageVector[i];
			UnloadSuperSprite(anImage.mSpriteId);
		}
		
		mMainDefCache.erase(anItr);
	}	
}// end namespace
