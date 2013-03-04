//
//	SuperAnimNodeV2.cpp
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

#include "SuperAnimNodeV2.h"
using namespace SuperAnim;
//////////////////////////////////////////////////////////////////////////
// platform functions needed by SuperAnimCore
unsigned char* GetFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize){
	return CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, pSize);
}
//////////////////////////////////////////////////////////////////////////

namespace SuperAnim {
	class SuperAnimSprite
	{
	public:
		CCTexture2D *mTexture;
		ccV3F_C4B_T2F_Quad mQuad;
	public:
		SuperAnimSprite();
		SuperAnimSprite(CCTexture2D *theTexture);
		SuperAnimSprite(CCTexture2D *theTexture, CCRect theTextureRect);
		~SuperAnimSprite();
		
		void SetTexture(CCTexture2D *theTexture);
		void SetTexture(CCTexture2D *theTexture, CCRect theTextureRect);
	};

	typedef std::map<SuperAnimSpriteId, SuperAnimSprite *> IdToSuperAnimSpriteMap;
	class SuperAnimSpriteMgr
	{
		IdToSuperAnimSpriteMap mSuperAnimSpriteMap;
	private:
		SuperAnimSpriteMgr();
		~SuperAnimSpriteMgr();

	public:
		static SuperAnimSpriteMgr *GetInstance();
		static void DestroyInstance();
		SuperAnimSpriteId LoadSuperAnimSprite(std::string theSpriteName);
		void UnloadSuperSprite(SuperAnimSpriteId theSpriteId);
		SuperAnimSprite * GetSpriteById(SuperAnimSpriteId theSpriteId);
	};
}

//////////////////////////////////////////////////////////////////////////

SuperAnimSprite::SuperAnimSprite()
{
	mTexture = NULL;
	memset(&mQuad, 0, sizeof(mQuad));
}

SuperAnimSprite::SuperAnimSprite(CCTexture2D *theTexture)
{
	mTexture = NULL;
	memset(&mQuad, 0, sizeof(mQuad));
	SetTexture(theTexture);
}

SuperAnimSprite::SuperAnimSprite(CCTexture2D *theTexture, CCRect theTextureRect)
{
	mTexture = NULL;
	memset(&mQuad, 0, sizeof(mQuad));
	SetTexture(theTexture, theTextureRect);
}

SuperAnimSprite::~SuperAnimSprite()
{
	if (mTexture != NULL)
	{
		mTexture->release();
		mTexture = NULL;
	}
}

void SuperAnimSprite::SetTexture(CCTexture2D *theTexture)
{
	CCRect aRect = CCRectZero;
	aRect.size = theTexture->getContentSize();
	SetTexture(theTexture, aRect);
}

void SuperAnimSprite::SetTexture(CCTexture2D *theTexture, CCRect theTextureRect)
{
	if (theTexture == NULL)
	{
		return;
	}
	
	if (mTexture != NULL)
	{
		mTexture->release();
		mTexture = NULL;
	}
	
	// retain this texture in case removed by removeUnusedTextures();
	theTexture->retain();
	mTexture = theTexture;
	
	// Set Texture coordinates
	CCRect theTexturePixelRect = CC_RECT_POINTS_TO_PIXELS(theTextureRect);
	float aTextureWidth = (float)mTexture->getPixelsWide();
	float aTextureHeight = (float)mTexture->getPixelsHigh();
	
	float aLeft, aRight, aTop, aBottom;
	aLeft = theTexturePixelRect.origin.x / aTextureWidth;
	aRight = (theTexturePixelRect.origin.x + theTexturePixelRect.size.width) / aTextureWidth;
	aTop = theTexturePixelRect.origin.y / aTextureHeight;
	aBottom = (theTexturePixelRect.origin.y + theTexturePixelRect.size.height) / aTextureHeight;
	
	mQuad.bl.texCoords.u = aLeft;
	mQuad.bl.texCoords.v = aBottom;
	mQuad.br.texCoords.u = aRight;
	mQuad.br.texCoords.v = aBottom;
	mQuad.tl.texCoords.u = aLeft;
	mQuad.tl.texCoords.v = aTop;
	mQuad.tr.texCoords.u = aRight;
	mQuad.tr.texCoords.v = aTop;
	
	// Set position
	//float x1 = 0;
	//float y1 = 0;
	//float x2 = x1 + theTextureRect.size.width;
	//float y2 = y1 + theTextureRect.size.height;
	
	float x1 = theTexturePixelRect.size.width * -0.5f;
	float y1 = theTexturePixelRect.size.height * -0.5f;
	float x2 = theTexturePixelRect.size.width * 0.5f;
	float y2 = theTexturePixelRect.size.height * 0.5f;
	
	mQuad.bl.vertices = vertex3(x1, y1, 0);
	mQuad.br.vertices = vertex3(x2, y1, 0);
	mQuad.tl.vertices = vertex3(x1, y2, 0);
	mQuad.tr.vertices = vertex3(x2, y2, 0);
	
	// Set color
	ccColor4B aDefaultColor = {255, 255, 255, 255};
	mQuad.bl.colors = aDefaultColor;
	mQuad.br.colors = aDefaultColor;
	mQuad.tl.colors = aDefaultColor;
	mQuad.tr.colors = aDefaultColor;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// implement extern functions
SuperAnimSpriteId SuperAnim::LoadSuperAnimSprite(std::string theSpriteName){
	return SuperAnimSpriteMgr::GetInstance()->LoadSuperAnimSprite(theSpriteName);
}
void SuperAnim::UnloadSuperSprite(SuperAnimSpriteId theSpriteId){
	SuperAnimSpriteMgr::GetInstance()->UnloadSuperSprite(theSpriteId);
}

static SuperAnimSpriteMgr * sInstance = NULL;
SuperAnimSpriteMgr::SuperAnimSpriteMgr()
{
}

SuperAnimSpriteMgr::~SuperAnimSpriteMgr()
{
	for (IdToSuperAnimSpriteMap::iterator anItr = mSuperAnimSpriteMap.begin();
		 anItr != mSuperAnimSpriteMap.end(); ++anItr)
	{
		delete anItr->second;
	}
	mSuperAnimSpriteMap.clear();
}

SuperAnimSpriteMgr *SuperAnimSpriteMgr::GetInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new SuperAnimSpriteMgr();
	}
	
	return sInstance;
}

void SuperAnimSpriteMgr::DestroyInstance()
{
	if (sInstance)
	{
		delete sInstance;
		sInstance = NULL;
	}
}

CCTexture2D* getTexture(std::string theImageFullPath, CCRect& theTextureRect){
	// try to load from sprite sheet
	std::string anImageFileName;
	int aLastSlashIndex = MAX((int)theImageFullPath.find_last_of('/'), (int)theImageFullPath.find_last_of('\\'));
	if (aLastSlashIndex != std::string::npos) {
		anImageFileName = theImageFullPath.substr(aLastSlashIndex + 1);
	} else {
		anImageFileName = theImageFullPath;
	}
	CCSpriteFrame *aSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(anImageFileName.c_str());
	if (aSpriteFrame) {
		theTextureRect = aSpriteFrame->getRect();
		return aSpriteFrame->getTexture();
	}
	
	CCTexture2D* aTexture = CCTextureCache::sharedTextureCache()->addImage(theImageFullPath.c_str());
	theTextureRect.origin = CCPointZero;
	theTextureRect.size = aTexture->getContentSize();
	return CCTextureCache::sharedTextureCache()->addImage(theImageFullPath.c_str());
}



SuperAnimSpriteId SuperAnimSpriteMgr::LoadSuperAnimSprite(std::string theSpriteName)
{
	// already load the sprite ?
	IdToSuperAnimSpriteMap::iterator anItr = mSuperAnimSpriteMap.find(theSpriteName);
	if (anItr != mSuperAnimSpriteMap.end())
	{
		return anItr->first;
	}
	
	std::string anImageFileName;
	std::string anImageFile;
	int aLastSlashIndex = MAX((int)theSpriteName.find_last_of('/'), (int)theSpriteName.find_last_of('\\'));
	if (aLastSlashIndex != std::string::npos) {
		anImageFileName = theSpriteName.substr(aLastSlashIndex + 1);
	} else {
		anImageFileName = theSpriteName;
	}
	
	bool hasFileExt = anImageFileName.find('.') != std::string::npos;
	if (!hasFileExt) {
		// PNG by default if not specified format
		anImageFile = theSpriteName + ".png";
	} else {
		anImageFile = theSpriteName;
	}
	// load the physical sprite
	CCRect aTextureRect;
	CCTexture2D *aTexture = getTexture(anImageFile.c_str(), aTextureRect);
	if (aTexture == NULL) {
		char aBuffer[256];
		sprintf(aBuffer, "%s is missing.", anImageFileName.c_str());
		CCMessageBox(aBuffer, "Error");
		return InvalidSuperAnimSpriteId;
	}
	
	// create new super animation sprite
	SuperAnimSprite *aSuperAnimSprite = new SuperAnimSprite(aTexture, aTextureRect);
	// use the sprite name as the key
	SuperAnimSpriteId anId = theSpriteName;
	mSuperAnimSpriteMap[anId] = aSuperAnimSprite;
	
	return anId;
}

void SuperAnimSpriteMgr::UnloadSuperSprite(SuperAnimSpriteId theSpriteId)
{
	IdToSuperAnimSpriteMap::iterator anItr = mSuperAnimSpriteMap.find(theSpriteId);
	if (anItr != mSuperAnimSpriteMap.end())
	{
		delete anItr->second;
		mSuperAnimSpriteMap.erase(anItr);
	}
}

SuperAnimSprite * SuperAnimSpriteMgr::GetSpriteById(SuperAnimSpriteId theSpriteId)
{
	IdToSuperAnimSpriteMap::iterator anItr = mSuperAnimSpriteMap.find(theSpriteId);
	if (anItr != mSuperAnimSpriteMap.end())
	{
		return anItr->second;
	}
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
enum AnimState
{
	kAnimStateInvalid = -1,
	kAnimStateInitialized,
	kAnimStatePlaying,
	kAnimStatePause
};

SuperAnimNode::SuperAnimNode()
{
	mId = -1;
	mListener = NULL;
	mAnimState = kAnimStateInvalid;
	mUseSpriteSheet = false;
	mSpriteSheet = NULL;
	mIsFlipX = mIsFlipY = false;
}

SuperAnimNode::~SuperAnimNode()
{
	tryUnloadSpirteSheet();
}


SuperAnimNode *SuperAnimNode::create(std::string theAbsAnimFile, int theId, SuperAnimNodeListener *theListener)
{
	SuperAnimNode *aSuperAnimNode = new SuperAnimNode();
	if (aSuperAnimNode == NULL)
	{
		return NULL;
	}
	if (aSuperAnimNode->Init(theAbsAnimFile, theId, theListener) == false)
	{
		delete aSuperAnimNode;
		return NULL;
	}
	aSuperAnimNode->autorelease();
	return aSuperAnimNode;
}

bool hasFile(std::string theFileFullPath){
	bool hasFile = false;
	bool shouldPopupNoitify = CCFileUtils::sharedFileUtils()->isPopupNotify();
	CCFileUtils::sharedFileUtils()->setPopupNotify(false);
	unsigned long aSize;
	unsigned char *aDataBuffer = CCFileUtils::sharedFileUtils()->getFileData(theFileFullPath.c_str(), "rb", &aSize);
    if (aDataBuffer != NULL) {
        CC_SAFE_DELETE_ARRAY(aDataBuffer);
        hasFile = true;
    }
	CCFileUtils::sharedFileUtils()->setPopupNotify(shouldPopupNoitify);
    return hasFile;
}

bool SuperAnimNode::Init(std::string theAbsAnimFile, int theId, SuperAnimNodeListener *theListener)
{
	// try to load the sprite sheet file
	mSpriteSheetFileFullPath = theAbsAnimFile.substr(0, theAbsAnimFile.find_last_of('.') + 1) + "plist";
	tryLoadSpriteSheet();
	
	mAnimHandler = GetSuperAnimHandler(theAbsAnimFile);
	if (!mAnimHandler.IsValid())
	{
		char aBuffer[256];
		sprintf(aBuffer, "Can't load the SuperAnim %s.", theAbsAnimFile.c_str());
		CCMessageBox(aBuffer, "Error");
		return false;
	}

	setContentSize(CC_SIZE_PIXELS_TO_POINTS(CCSizeMake(mAnimHandler.mWidth, mAnimHandler.mHeight)));

	mId = theId;
	mListener = theListener;
	mAnimState = kAnimStateInitialized;
	mIsFlipX = mIsFlipY = false;

	// shader program
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
	scheduleUpdate();
	
	setAnchorPoint(ccp(0.5f, 0.5f));

	return true;
}

void SuperAnimNode::tryLoadSpriteSheet(){
	if (hasFile(mSpriteSheetFileFullPath)) {
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(mSpriteSheetFileFullPath.c_str());
		std::string aTexturePath = mSpriteSheetFileFullPath.substr(0, mSpriteSheetFileFullPath.find_last_of('.') + 1) + "png";
		mSpriteSheet = CCTextureCache::sharedTextureCache()->addImage(aTexturePath.c_str());
		mUseSpriteSheet = true;
	}
}

void SuperAnimNode::tryUnloadSpirteSheet(){
	if (hasFile(mSpriteSheetFileFullPath)) {
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(mSpriteSheetFileFullPath.c_str());
	}
}

void SuperAnimNode::setFlipX(bool isFlip){
	mIsFlipX = isFlip;
}

void SuperAnimNode::setFlipY(bool isFlip){
	mIsFlipY = isFlip;
}

// Operator between matrix & vertex
inline ccVertex3F operator*(const SuperAnimMatrix3 &theMatrix3, const ccVertex3F &theVec)
{
	return vertex3(
				   theMatrix3.m00*theVec.x + theMatrix3.m01*theVec.y + theMatrix3.m02,
				   theMatrix3.m10*theVec.x + theMatrix3.m11*theVec.y + theMatrix3.m12,
				   theVec.z);
}

inline ccV3F_C4B_T2F_Quad operator*(const SuperAnimMatrix3 &theMatrix3, const ccV3F_C4B_T2F_Quad &theQuad)
{
	ccV3F_C4B_T2F_Quad aNewQuad = theQuad;
	aNewQuad.bl.vertices = theMatrix3 * theQuad.bl.vertices;
	aNewQuad.br.vertices = theMatrix3 * theQuad.br.vertices;
	aNewQuad.tl.vertices = theMatrix3 * theQuad.tl.vertices;
	aNewQuad.tr.vertices = theMatrix3 * theQuad.tr.vertices;
	return aNewQuad;
}

void SuperAnimNode::draw()
{
	if (mAnimState == kAnimStateInvalid ||
		mAnimState == kAnimStateInitialized)
	{
		return;
	}
	
	if (!mAnimHandler.IsValid()) {
		return;
	}
	
	#define MAX_VERTEX_CNT 4096
	static ccVertex3F sVertexBuffer[MAX_VERTEX_CNT];
	static ccTex2F sTexCoorBuffer[MAX_VERTEX_CNT];
	static ccColor4B sColorBuffer[MAX_VERTEX_CNT];
	int anIndex = 0;
	
	static SuperAnimObjDrawInfo sAnimObjDrawnInfo;
	float aPixelToPointScale = 1.0f / CC_CONTENT_SCALE_FACTOR();
	float anAnimContentHeightInPixel = getContentSize().height * CC_CONTENT_SCALE_FACTOR();
	BeginIterateAnimObjDrawInfo();
	while (IterateAnimObjDrawInfo(mAnimHandler, sAnimObjDrawnInfo)) {
		if (sAnimObjDrawnInfo.mSpriteId == InvalidSuperAnimSpriteId) {
			CCAssert(false, "Missing a sprite.");
			continue;
		}
			
		SuperAnimSprite *aSprite = SuperAnimSpriteMgr::GetInstance()->GetSpriteById(sAnimObjDrawnInfo.mSpriteId);
		if (aSprite == NULL){
			CCAssert(false, "Missing a sprite.");
			continue;
		}
		
		// cocos2d the origin is located at left bottom, but is in left top in flash
		sAnimObjDrawnInfo.mTransform.mMatrix.m12 = anAnimContentHeightInPixel - sAnimObjDrawnInfo.mTransform.mMatrix.m12;
		// convert to point
		sAnimObjDrawnInfo.mTransform.Scale(aPixelToPointScale, aPixelToPointScale);
		
		//sAnimObjDrawnInfo.mTransform.mMatrix.m12 *= -1;
				
		// Be sure that you call this macro every draw
		CC_NODE_DRAW_SETUP();
		
		ccV3F_C4B_T2F_Quad aOriginQuad = aSprite->mQuad;
		aSprite->mQuad = sAnimObjDrawnInfo.mTransform.mMatrix * aSprite->mQuad;
		ccColor4B aColor = ccc4(sAnimObjDrawnInfo.mColor.mRed, sAnimObjDrawnInfo.mColor.mGreen, sAnimObjDrawnInfo.mColor.mBlue, sAnimObjDrawnInfo.mColor.mAlpha);		
		aSprite->mQuad.bl.colors = aColor;
		aSprite->mQuad.br.colors = aColor;
		aSprite->mQuad.tl.colors = aColor;
		aSprite->mQuad.tr.colors = aColor;
		
		if (mIsFlipX) {
			float aWidthinPixel = getContentSize().width * CC_CONTENT_SCALE_FACTOR();
			aSprite->mQuad.bl.vertices.x = aWidthinPixel - aSprite->mQuad.bl.vertices.x;
			aSprite->mQuad.br.vertices.x = aWidthinPixel - aSprite->mQuad.br.vertices.x;
			aSprite->mQuad.tl.vertices.x = aWidthinPixel - aSprite->mQuad.tl.vertices.x;
			aSprite->mQuad.tr.vertices.x = aWidthinPixel - aSprite->mQuad.tr.vertices.x;
		}
		
		if (mIsFlipY) {
			float aHeightinPixel = getContentSize().height * CC_CONTENT_SCALE_FACTOR();
			aSprite->mQuad.bl.vertices.y = aHeightinPixel - aSprite->mQuad.bl.vertices.y;
			aSprite->mQuad.br.vertices.y = aHeightinPixel - aSprite->mQuad.br.vertices.y;
			aSprite->mQuad.tl.vertices.y = aHeightinPixel - aSprite->mQuad.tl.vertices.y;
			aSprite->mQuad.tr.vertices.y = aHeightinPixel - aSprite->mQuad.tr.vertices.y;
		}
		
		// draw
		if (!mUseSpriteSheet)
		{
			ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			ccGLBindTexture2D(aSprite->mTexture->getName());
			//
			// Attributes
			ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
			
			#define kQuadSize sizeof(aSprite->mQuad.bl)
			long offset = (long)&aSprite->mQuad;
			
			// vertex
			int diff = offsetof( ccV3F_C4B_T2F, vertices);
			glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
			
			// texCoods
			diff = offsetof( ccV3F_C4B_T2F, texCoords);
			glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
			
			// color
			diff = offsetof( ccV3F_C4B_T2F, colors);
			glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
			
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		} else {
			// 0
			sVertexBuffer[anIndex] = aSprite->mQuad.bl.vertices;
			sTexCoorBuffer[anIndex] = aSprite->mQuad.bl.texCoords;
			sColorBuffer[anIndex++] = aSprite->mQuad.bl.colors;
			// 1
			sVertexBuffer[anIndex] = aSprite->mQuad.tl.vertices;
			sTexCoorBuffer[anIndex] = aSprite->mQuad.tl.texCoords;
			sColorBuffer[anIndex++] = aSprite->mQuad.tl.colors;
			// 2
			sVertexBuffer[anIndex] = aSprite->mQuad.br.vertices;
			sTexCoorBuffer[anIndex] = aSprite->mQuad.br.texCoords;
			sColorBuffer[anIndex++] = aSprite->mQuad.br.colors;
			// 3
			sVertexBuffer[anIndex] = aSprite->mQuad.tl.vertices;
			sTexCoorBuffer[anIndex] = aSprite->mQuad.tl.texCoords;
			sColorBuffer[anIndex++] = aSprite->mQuad.tl.colors;
			// 4
			sVertexBuffer[anIndex] = aSprite->mQuad.tr.vertices;
			sTexCoorBuffer[anIndex] = aSprite->mQuad.tr.texCoords;
			sColorBuffer[anIndex++] = aSprite->mQuad.tr.colors;
			// 5
			sVertexBuffer[anIndex] = aSprite->mQuad.br.vertices;
			sTexCoorBuffer[anIndex] = aSprite->mQuad.br.texCoords;
			sColorBuffer[anIndex++] = aSprite->mQuad.br.colors;
			
			CCAssert(anIndex < MAX_VERTEX_CNT, "buffer is not enough");
		}
		
		aSprite->mQuad = aOriginQuad;
	}
	
	if (mUseSpriteSheet) {
		// Be sure that you call this macro every draw
		CC_NODE_DRAW_SETUP();
		
		ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		ccGLBindTexture2D(mSpriteSheet->getName());
		//
		// Attributes
		ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
		
		// vertex
		glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sVertexBuffer));
		
		// texCoods
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sTexCoorBuffer));
		
		// color
		glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)(sColorBuffer));
		
		glDrawArrays(GL_TRIANGLES, 0, anIndex);
	}
}

void SuperAnimNode::update(float dt)
{
	if (mAnimState != kAnimStatePlaying)
	{
		return;
	}
	
	bool isNewLabel = false;
	IncAnimFrameNum(mAnimHandler, dt, isNewLabel);
	if (isNewLabel && mListener)
	{
		mListener->OnAnimSectionEnd(mId, mAnimHandler.mCurLabel);
	}
}

bool SuperAnimNode::HasSection(std::string theLabelName){
	return  SuperAnim::HasSection(mAnimHandler, theLabelName);
}

bool SuperAnimNode::PlaySection(std::string theLabel)
{
	if (mAnimState == kAnimStateInvalid)
	{
		CCAssert(false, "The animation isn't ready.");
		return false;
	}

	if (theLabel.empty())
	{
		CCAssert(false, "Please specify an animation section label to play.");
		return false;
	}
	
	if (PlayBySection(mAnimHandler, theLabel)){
		mAnimState = kAnimStatePlaying;
		CCDirector::sharedDirector()->setNextDeltaTimeZero(true);
		return true;
	}

	// we should not go here.
	// if we do that means you specify a wrong label
	CCAssert(false, "I cannot find the specified section label in animation.");
	return false;
}

void SuperAnimNode::Pause()
{
	mAnimState = kAnimStatePause;
}

void SuperAnimNode::Resume()
{
	mAnimState = kAnimStatePlaying;
}

bool SuperAnimNode::IsPause(){
	return mAnimState == kAnimStatePause;
}

bool SuperAnimNode::IsPlaying(){
	return mAnimState == kAnimStatePlaying;
}

int SuperAnimNode::GetCurFrame(){
	return (int)mAnimHandler.mCurFrameNum;
}

std::string SuperAnimNode::GetCurSectionName(){
	return mAnimHandler.mCurLabel;
}