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
	//return CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, pSize);
	ssize_t size = 0;
	unsigned char* data = nullptr;
	data = FileUtils::getInstance()->getFileData(pszFileName, pszMode, &size);
	*pSize = size;
	return data;
}
//////////////////////////////////////////////////////////////////////////

namespace SuperAnim {
	class SuperAnimSprite
	{
	public:
		Texture2D *mTexture;
		V3F_C4B_T2F_Quad mQuad;
		std::string mStringId;
	public:
		SuperAnimSprite();
        SuperAnimSprite(Texture2D *theTexture, bool isRotated);
        SuperAnimSprite(Texture2D *theTexture, Rect theTextureRect, bool isRotated);
        ~SuperAnimSprite();
        
        void SetTexture(Texture2D *theTexture, bool isRotated);
        void SetTexture(Texture2D *theTexture, Rect theTextureRect, bool isRotated);
	};

	typedef std::map<SuperAnimSpriteId, SuperAnimSprite *> IdToSuperAnimSpriteMap;
	class SuperAnimSpriteMgr
	{
		IdToSuperAnimSpriteMap mSuperAnimSpriteMap;
		IdToSuperAnimSpriteMap::const_iterator mSuperAnimSpriteIterator;
	private:
		SuperAnimSpriteMgr();
		~SuperAnimSpriteMgr();

	public:
		static SuperAnimSpriteMgr *GetInstance();
		static void DestroyInstance();
		SuperAnimSpriteId LoadSuperAnimSprite(std::string theSpriteName);
		void UnloadSuperSprite(SuperAnimSpriteId theSpriteId);
		SuperAnimSprite * GetSpriteById(SuperAnimSpriteId theSpriteId);
		void BeginIterateSpriteId();
		bool IterateSpriteId(SuperAnimSpriteId &theCurSpriteId);
	};
}

//////////////////////////////////////////////////////////////////////////

SuperAnimSprite::SuperAnimSprite()
{
	mTexture = NULL;
	memset(&mQuad, 0, sizeof(mQuad));
}

SuperAnimSprite::SuperAnimSprite(Texture2D *theTexture, bool isRotated)
{
	mTexture = NULL;
	memset(&mQuad, 0, sizeof(mQuad));
	SetTexture(theTexture, isRotated);
}

SuperAnimSprite::SuperAnimSprite(Texture2D *theTexture, Rect theTextureRect, bool isRotated)
{
	mTexture = NULL;
	memset(&mQuad, 0, sizeof(mQuad));
	SetTexture(theTexture, theTextureRect, isRotated);
}

SuperAnimSprite::~SuperAnimSprite()
{
	if (mTexture != NULL)
	{
		mTexture->release();
		mTexture = NULL;
	}
}

void SuperAnimSprite::SetTexture(Texture2D *theTexture, bool isRotated)
{
	Rect aRect = Rect::ZERO;
	aRect.size = theTexture->getContentSize();
	SetTexture(theTexture, aRect, isRotated);
}

void SuperAnimSprite::SetTexture(Texture2D *theTexture, Rect theTextureRect,  bool isRotated)
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
	Rect theTexturePixelRect = CC_RECT_POINTS_TO_PIXELS(theTextureRect);
	float aTextureWidth = (float)mTexture->getPixelsWide();
	float aTextureHeight = (float)mTexture->getPixelsHigh();
	
	float aLeft, aRight, aTop, aBottom;
    
    if (isRotated) {
        
        aLeft = theTexturePixelRect.origin.x / aTextureWidth;
        aRight = (theTexturePixelRect.origin.x + theTexturePixelRect.size.height) / aTextureWidth;
        aTop = theTexturePixelRect.origin.y / aTextureHeight;
        aBottom = (theTexturePixelRect.origin.y + theTexturePixelRect.size.width) / aTextureHeight;
        
        mQuad.bl.texCoords.u = aLeft;
        mQuad.bl.texCoords.v = aTop;
        mQuad.br.texCoords.u = aLeft;
        mQuad.br.texCoords.v = aBottom;
        mQuad.tl.texCoords.u = aRight;
        mQuad.tl.texCoords.v = aTop;
        mQuad.tr.texCoords.u = aRight;
        mQuad.tr.texCoords.v = aBottom;
        
    }else {
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
    }
    
	
	// Set position
	//float x1 = 0;
	//float y1 = 0;
	//float x2 = x1 + theTextureRect.size.width;
	//float y2 = y1 + theTextureRect.size.height;
	
	float x1 = theTexturePixelRect.size.width * -0.5f;
	float y1 = theTexturePixelRect.size.height * -0.5f;
	float x2 = theTexturePixelRect.size.width * 0.5f;
	float y2 = theTexturePixelRect.size.height * 0.5f;
	
	mQuad.bl.vertices = Vec3(x1, y1, 0);
	mQuad.br.vertices = Vec3(x2, y1, 0);
	mQuad.tl.vertices = Vec3(x1, y2, 0);
	mQuad.tr.vertices = Vec3(x2, y2, 0);
	
	// Set color
	Color4B aDefaultColor = {255, 255, 255, 255};
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

void SuperAnimSpriteMgr::BeginIterateSpriteId(){
	mSuperAnimSpriteIterator = mSuperAnimSpriteMap.begin();
}
bool SuperAnimSpriteMgr::IterateSpriteId(SuperAnimSpriteId &theCurSpriteId){
	if (mSuperAnimSpriteIterator == mSuperAnimSpriteMap.end()) {
		theCurSpriteId = InvalidSuperAnimSpriteId;
		return false;
	}
	
	theCurSpriteId = mSuperAnimSpriteIterator->first;
	mSuperAnimSpriteIterator++;
	return true;
}

Texture2D* getTexture(std::string theImageFullPath, Rect& theTextureRect,bool *isRotated){
	// try to load from sprite sheet
	std::string anImageFileName;
	int aLastSlashIndex = MAX((int)theImageFullPath.find_last_of('/'), (int)theImageFullPath.find_last_of('\\'));
	if (aLastSlashIndex != std::string::npos) {
		anImageFileName = theImageFullPath.substr(aLastSlashIndex + 1);
	} else {
		anImageFileName = theImageFullPath;
	}
	//CCSpriteFrame *aSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(anImageFileName.c_str());
	SpriteFrame* aSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(anImageFileName);
	if (aSpriteFrame) {
		theTextureRect = aSpriteFrame->getRect();
        *isRotated = aSpriteFrame->isRotated();
		return aSpriteFrame->getTexture();
	}
	
	//Texture2D* aTexture = CCTextureCache::sharedTextureCache()->addImage(theImageFullPath.c_str());
	Texture2D* aTexture = Director::getInstance()->getTextureCache()->addImage(theImageFullPath);
	theTextureRect.origin = Vec2::ZERO;
	theTextureRect.size = aTexture->getContentSize();
    *isRotated = false;
	return aTexture;
}



SuperAnimSpriteId SuperAnimSpriteMgr::LoadSuperAnimSprite(std::string theSpriteName)
{
	// already load the sprite ?
	IdToSuperAnimSpriteMap::iterator anItr = mSuperAnimSpriteMap.begin();
	while (anItr != mSuperAnimSpriteMap.end())
	{
		if (anItr->second->mStringId == theSpriteName) {
			return anItr->first;
		}
		anItr++;
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
	Rect aTextureRect;
    bool isRotated = false;
	Texture2D *aTexture = getTexture(anImageFile.c_str(), aTextureRect,&isRotated);
	if (aTexture == NULL) {
		char aBuffer[256];
		sprintf(aBuffer, "%s is missing.", anImageFileName.c_str());
		MessageBox(aBuffer, "Error");
		return InvalidSuperAnimSpriteId;
	}
	
	// create new super animation sprite
	SuperAnimSprite *aSuperAnimSprite = new SuperAnimSprite(aTexture, aTextureRect, isRotated);
	// use the sprite name as the key
	aSuperAnimSprite->mStringId = theSpriteName;
	SuperAnimSpriteId anId = aSuperAnimSprite;
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
	
	_insideBounds = true;
}

SuperAnimNode::~SuperAnimNode()
{
	tryUnloadSpirteSheet();
	while (mReplacedSpriteMap.size() > 0) {
		SuperSpriteIdToSuperSpriteIdMap::iterator anIter = mReplacedSpriteMap.begin();
		SuperAnimSpriteMgr::GetInstance()->UnloadSuperSprite(anIter->second);
		mReplacedSpriteMap.erase(anIter);
	}
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
	//bool shouldPopupNoitify = CCFileUtils::sharedFileUtils()->isPopupNotify();
	bool shouldPopupNoitify = FileUtils::getInstance()->isPopupNotify();
	//CCFileUtils::sharedFileUtils()->setPopupNotify(false);
	FileUtils::getInstance()->setPopupNotify(false);
	//unsigned long aSize;
	ssize_t aSize;
	//unsigned char *aDataBuffer = CCFileUtils::sharedFileUtils()->getFileData(theFileFullPath.c_str(), "rb", &aSize);
	unsigned char *aDataBuffer = FileUtils::getInstance()->getFileData(theFileFullPath, "rb", &aSize);
    if (aDataBuffer != NULL) {
        CC_SAFE_DELETE_ARRAY(aDataBuffer);
        hasFile = true;
    }
	//CCFileUtils::sharedFileUtils()->setPopupNotify(shouldPopupNoitify);
	FileUtils::getInstance()->setPopupNotify(shouldPopupNoitify);
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
		MessageBox(aBuffer, "Error");
		return false;
	}

	setContentSize(CC_SIZE_PIXELS_TO_POINTS(Size(mAnimHandler.mWidth, mAnimHandler.mHeight)));

	mId = theId;
	mListener = theListener;
	mAnimState = kAnimStateInitialized;
	mIsFlipX = mIsFlipY = false;
	mSpeedFactor = 1.0f;
	mIsLoop = false;

	// shader program
	//setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
	setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
	scheduleUpdate();
	
	setAnchorPoint(Vec2(0.5f, 0.5f));

	return true;
}

void SuperAnimNode::tryLoadSpriteSheet(){
	if (hasFile(mSpriteSheetFileFullPath)) {
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(mSpriteSheetFileFullPath.c_str());
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(mSpriteSheetFileFullPath);
		std::string aTexturePath = mSpriteSheetFileFullPath.substr(0, mSpriteSheetFileFullPath.find_last_of('.') + 1) + "png";
		//mSpriteSheet = CCTextureCache::sharedTextureCache()->addImage(aTexturePath.c_str());
		mSpriteSheet = Director::getInstance()->getTextureCache()->addImage(aTexturePath);
		mUseSpriteSheet = true;
	}
}

void SuperAnimNode::tryUnloadSpirteSheet(){
	if (hasFile(mSpriteSheetFileFullPath)) {
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(mSpriteSheetFileFullPath.c_str());
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(mSpriteSheetFileFullPath);
	}
}

void SuperAnimNode::setFlipX(bool isFlip){
	mIsFlipX = isFlip;
}

void SuperAnimNode::setFlipY(bool isFlip){
	mIsFlipY = isFlip;
}

// Operator between matrix & vertex
inline Vec3 operator*(const SuperAnimMatrix3 &theMatrix3, const Vec3 &theVec)
{
	return Vec3(
				   theMatrix3.m00*theVec.x + theMatrix3.m01*theVec.y + theMatrix3.m02,
				   theMatrix3.m10*theVec.x + theMatrix3.m11*theVec.y + theMatrix3.m12,
				   theVec.z);
}

inline V3F_C4B_T2F_Quad operator*(const SuperAnimMatrix3 &theMatrix3, const V3F_C4B_T2F_Quad &theQuad)
{
	V3F_C4B_T2F_Quad aNewQuad = theQuad;
	aNewQuad.bl.vertices = theMatrix3 * theQuad.bl.vertices;
	aNewQuad.br.vertices = theMatrix3 * theQuad.br.vertices;
	aNewQuad.tl.vertices = theMatrix3 * theQuad.tl.vertices;
	aNewQuad.tr.vertices = theMatrix3 * theQuad.tr.vertices;
	return aNewQuad;
}

//void SuperAnimNode::draw()
//void SuperAnimNode::draw(Renderer *renderer, const Mat4& transform, bool transformUpdated){
void SuperAnimNode::draw(Renderer *renderer, const Mat4& transform, uint32_t flags){
	// Don't do calculate the culling if the transform was not updated
	_insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
	if(!_insideBounds){
		return;
	}
	
	_customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(SuperAnimNode::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void SuperAnimNode::onDraw(const Mat4 &transform, bool transformUpdated)
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
	static Vec3 sVertexBuffer[MAX_VERTEX_CNT];
	static Tex2F sTexCoorBuffer[MAX_VERTEX_CNT];
	static Color4B sColorBuffer[MAX_VERTEX_CNT];
	int anIndex = 0;
	
	static SuperAnimObjDrawInfo sAnimObjDrawnInfo;
	//float aPixelToPointScale = 1.0f / CC_CONTENT_SCALE_FACTOR();
	float anAnimContentHeightInPixel = getContentSize().height * CC_CONTENT_SCALE_FACTOR();
	BeginIterateAnimObjDrawInfo();
	while (IterateAnimObjDrawInfo(mAnimHandler, sAnimObjDrawnInfo)) {
		if (sAnimObjDrawnInfo.mSpriteId == InvalidSuperAnimSpriteId) {
			CCAssert(false, "Missing a sprite.");
			continue;
		}
		
		// check whether this sprite has been replaced
		SuperAnimSpriteId aCurSpriteId = sAnimObjDrawnInfo.mSpriteId;
		SuperSpriteIdToSuperSpriteIdMap::const_iterator anIter = mReplacedSpriteMap.find(aCurSpriteId);
		if (anIter != mReplacedSpriteMap.end()) {
			aCurSpriteId = anIter->second;
		}
			
		//SuperAnimSprite *aSprite = SuperAnimSpriteMgr::GetInstance()->GetSpriteById(aCurSpriteId);
		SuperAnimSprite *aSprite = (SuperAnimSprite*)aCurSpriteId;
		if (aSprite == NULL){
			CCAssert(false, "Missing a sprite.");
			continue;
		}
		
		// safe check!!
		if (mUseSpriteSheet) {
			CCAssert(mSpriteSheet == aSprite->mTexture, "must in the same texture!!");
		}
		
		// cocos2d the origin is located at left bottom, but is in left top in flash
		sAnimObjDrawnInfo.mTransform.mMatrix.m12 = anAnimContentHeightInPixel - sAnimObjDrawnInfo.mTransform.mMatrix.m12;
		// convert to point
		//sAnimObjDrawnInfo.mTransform.Scale(aPixelToPointScale, aPixelToPointScale);
		
		//sAnimObjDrawnInfo.mTransform.mMatrix.m12 *= -1;
				
		// Be sure that you call this macro every draw
		//CC_NODE_DRAW_SETUP();
		
		V3F_C4B_T2F_Quad aOriginQuad = aSprite->mQuad;
		aSprite->mQuad = sAnimObjDrawnInfo.mTransform.mMatrix * aSprite->mQuad;
		Color4B aColor = Color4B(sAnimObjDrawnInfo.mColor.mRed, sAnimObjDrawnInfo.mColor.mGreen, sAnimObjDrawnInfo.mColor.mBlue, sAnimObjDrawnInfo.mColor.mAlpha);
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
			getGLProgram()->use();
			getGLProgram()->setUniformsForBuiltins(transform);
			
			//GL::blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			if (!aSprite->mTexture->hasPremultipliedAlpha()) {
				GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			} else {
				GL::blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			}
			GL::bindTexture2D(aSprite->mTexture->getName());
			//
			// Attributes
			GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
			
			#define kQuadSize sizeof(aSprite->mQuad.bl)
			long offset = (long)&aSprite->mQuad;
			
			// vertex
			int diff = offsetof( V3F_C4B_T2F, vertices);
			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
			
			// texCoods
			diff = offsetof( V3F_C4B_T2F, texCoords);
			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
			
			// color
			diff = offsetof( V3F_C4B_T2F, colors);
			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
			
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
		//CC_NODE_DRAW_SETUP();
		
		getGLProgram()->use();
		getGLProgram()->setUniformsForBuiltins(transform);
		
		//GL::blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		if (!mSpriteSheet->hasPremultipliedAlpha()) {
			GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		} else {
			GL::blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}
		GL::bindTexture2D(mSpriteSheet->getName());
		//
		// Attributes
		GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
		
		// vertex
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, (void*) (sVertexBuffer));
		
		// texCoods
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sTexCoorBuffer));
		
		// color
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)(sColorBuffer));
		
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
	float anOriginFrameRate = mAnimHandler.mAnimRate;
	mAnimHandler.mAnimRate *= mSpeedFactor;
	IncAnimFrameNum(mAnimHandler, dt, isNewLabel);
	mAnimHandler.mAnimRate = anOriginFrameRate;
	
	float aTimeFactor = (mAnimHandler.mCurFrameNum - mAnimHandler.mFirstFrameNumOfCurLabel) / (float)(mAnimHandler.mLastFrameNumOfCurLabel - mAnimHandler.mFirstFrameNumOfCurLabel);
	for (TimeEventInfoArray::iterator anIter = mCurTimeEventInfoArray.begin(); anIter != mCurTimeEventInfoArray.end(); anIter++) {
		if (aTimeFactor >= anIter->mTimeFactor) {
			// trigger time event
			log("Trigger anim time event: %d, %s, %d", mId, anIter->mLabelName.c_str(), anIter->mEventId);
			if (mListener) {
				mListener->OnTimeEvent(mId, anIter->mLabelName, anIter->mEventId);
			}
			break;
		}
	}
	
	// remove obsolete time event
	for (TimeEventInfoArray::iterator anIter = mCurTimeEventInfoArray.begin(); anIter != mCurTimeEventInfoArray.end();) {
		if (aTimeFactor >= anIter->mTimeFactor) {
			anIter = mCurTimeEventInfoArray.erase(anIter);
		} else {
			anIter++;
		}
	}
	
	if (isNewLabel && mIsLoop) {
		PlaySection(mAnimHandler.mCurLabel, mIsLoop);
	}
	
	if (isNewLabel && mListener)
	{
		mListener->OnAnimSectionEnd(mId, mAnimHandler.mCurLabel);
	}
}

bool SuperAnimNode::HasSection(const std::string &theLabelName){
	return  SuperAnim::HasSection(mAnimHandler, theLabelName);
}

void SuperAnimNode::setSpeedFactor(float theNewSpeedFactor){
	mSpeedFactor = theNewSpeedFactor;
}

bool SuperAnimNode::PlaySection(const std::string &theLabel, bool isLoop)
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
		//CCDirector::sharedDirector()->setNextDeltaTimeZero(true);
		mIsLoop = isLoop;
		
		// set time event info for this run
		mCurTimeEventInfoArray.clear();
		LabelNameToTimeEventInfoArrayMap::const_iterator anIter = mLabelNameToTimeEventInfoArrayMap.find(theLabel);
		if (anIter != mLabelNameToTimeEventInfoArrayMap.end()) {
			mCurTimeEventInfoArray.insert(mCurTimeEventInfoArray.begin(), anIter->second.begin(), anIter->second.end());
		}
		
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

int SuperAnimNode::GetId(){
	return mId;
}

std::string SuperAnimNode::GetCurSectionName(){
	return mAnimHandler.mCurLabel;
}

void SuperAnimNode::replaceSprite(const std::string &theOriginSpriteName, const std::string &theNewSpriteName){
	SuperAnimSpriteId anOriginSpriteId = InvalidSuperAnimSpriteId;
	SuperAnimSpriteId aCurSpriteId;
	SuperAnimSpriteMgr::GetInstance()->BeginIterateSpriteId();
	while (SuperAnimSpriteMgr::GetInstance()->IterateSpriteId(aCurSpriteId)) {
		SuperAnimSprite* aSuperAnimSprite = (SuperAnimSprite*)aCurSpriteId;
		std::string aSpriteFullPath = aSuperAnimSprite->mStringId;
		if (aSpriteFullPath.substr(aSpriteFullPath.length() - theOriginSpriteName.length()) == theOriginSpriteName) {
			anOriginSpriteId = aCurSpriteId;
			break;
		}
	}
	
	if (anOriginSpriteId != InvalidSuperAnimSpriteId) {
		//SuperAnimSpriteId aNewSpriteId = SuperAnimSpriteMgr::GetInstance()->LoadSuperAnimSprite(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(theNewSpriteName.c_str()));
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(theNewSpriteName);
		SuperAnimSpriteId aNewSpriteId = SuperAnimSpriteMgr::GetInstance()->LoadSuperAnimSprite(fullPath);
		CCAssert(aNewSpriteId != InvalidSuperAnimSpriteId, "failed to create super anim sprite");
		mReplacedSpriteMap[anOriginSpriteId] = aNewSpriteId;
	} else{
		CCAssert(false, "Original sprite should exist.");
	}
}
void SuperAnimNode::resumeSprite(const std::string &theOriginSpriteName){
	SuperAnimSpriteId anOriginSpriteId = InvalidSuperAnimSpriteId;
	SuperAnimSpriteId aCurSpriteId;
	SuperAnimSpriteMgr::GetInstance()->BeginIterateSpriteId();
	while (SuperAnimSpriteMgr::GetInstance()->IterateSpriteId(aCurSpriteId)) {
		SuperAnimSprite* aSuperAnimSprite = (SuperAnimSprite*)aCurSpriteId;
		std::string aSpriteFullPath = aSuperAnimSprite->mStringId;
		if (aSpriteFullPath.substr(aSpriteFullPath.length() - theOriginSpriteName.length()) == theOriginSpriteName) {
			anOriginSpriteId = aCurSpriteId;
			break;
		}
	}
	if (anOriginSpriteId != InvalidSuperAnimSpriteId) {
		SuperSpriteIdToSuperSpriteIdMap::iterator anIter = mReplacedSpriteMap.find(anOriginSpriteId);
		if (anIter != mReplacedSpriteMap.end()) {
			// unload the replaced sprite
			SuperAnimSpriteMgr::GetInstance()->UnloadSuperSprite(anIter->second);
			mReplacedSpriteMap.erase(anIter);
		}
	}
}

// for time event
void SuperAnimNode::registerTimeEvent(const std::string &theLabel, float theTimeFactor, int theEventId){
	if (HasSection(theLabel) == false) {
		CCAssert(false, "Label not existed.");
		return;
	}
	
	theTimeFactor = clampf(theTimeFactor, 0.0f, 1.0f);
	TimeEventInfo aTimeEventInfo = {theLabel, theTimeFactor, theEventId};
	TimeEventInfoArray &aTimeEventInfoArray = mLabelNameToTimeEventInfoArrayMap[theLabel];
	aTimeEventInfoArray.push_back(aTimeEventInfo);
}
void SuperAnimNode::removeTimeEvent(const std::string &theLabel, int theEventId){
	if (HasSection(theLabel) == false) {
		CCAssert(false, "Label not existed.");
		return;
	}
	LabelNameToTimeEventInfoArrayMap::iterator anIter = mLabelNameToTimeEventInfoArrayMap.find(theLabel);
	if (anIter != mLabelNameToTimeEventInfoArrayMap.end()) {
		TimeEventInfoArray &aTimeEventInfoArray = anIter->second;
		for (TimeEventInfoArray::iterator i = aTimeEventInfoArray.begin(); i != aTimeEventInfoArray.end(); i++) {
			if (i->mEventId == theEventId) {
				aTimeEventInfoArray.erase(i);
				break;
			}
		}
	}
	
	// also remove in the current time event info array
	for (TimeEventInfoArray::iterator i = mCurTimeEventInfoArray.begin(); i != mCurTimeEventInfoArray.end(); i++) {
		if (i->mLabelName == theLabel &&\
			i->mEventId == theEventId) {
			mCurTimeEventInfoArray.erase(i);
			break;
		}
	}
}

bool SuperAnim::LoadAnimFileExt(const std::string &theAbsAnimFile){
	// try to load the sprite sheet file
	std::string aSpriteSheetFileFullPath = theAbsAnimFile.substr(0, theAbsAnimFile.find_last_of('.') + 1) + "plist";
	if (hasFile(aSpriteSheetFileFullPath)) {
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(aSpriteSheetFileFullPath.c_str());
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(aSpriteSheetFileFullPath);
	}
	return LoadAnimFile(theAbsAnimFile);
}

void SuperAnim::UnloadAnimFileExt(const std::string &theAbsAnimFile){
	// try to unload the sprite sheet file
	std::string aSpriteSheetFileFullPath = theAbsAnimFile.substr(0, theAbsAnimFile.find_last_of('.') + 1) + "plist";
	if (hasFile(aSpriteSheetFileFullPath)) {
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(aSpriteSheetFileFullPath.c_str());
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(aSpriteSheetFileFullPath);
	}
	return UnloadAnimFile(theAbsAnimFile);
}