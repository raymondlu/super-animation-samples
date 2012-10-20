//
//	SuperAnimNodeV2.cpp
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

#import "SuperAnimNodeV2.h"
#import "SuperAnimCommon.h"
#import "kazmath.h"
#import <map>
#import <set>
using namespace SuperAnim;
//////////////////////////////////////////////////////////////////////////
// Vertex shader for animation
const GLchar * ccSuperAnim_vert =
"                                                    \n\
attribute vec4 a_position;                            \n\
attribute vec2 a_texCoord;                            \n\
attribute vec4 a_color;                                \n\
\n\
uniform        mat4 u_MVPMatrix;                        \n\
uniform        mat4 u_animMatrix;                        \n\
uniform	vec4 u_animColor;                                \n\
\n\
#ifdef GL_ES                                        \n\
varying lowp vec4 v_fragmentColor;                    \n\
varying mediump vec2 v_texCoord;                    \n\
#else                                                \n\
varying vec4 v_fragmentColor;                        \n\
varying vec2 v_texCoord;                            \n\
#endif                                                \n\
\n\
void main()                                            \n\
{                                                    \n\
gl_Position = u_MVPMatrix * (u_animMatrix * a_position);            \n\
v_fragmentColor = u_animColor;                        \n\
v_texCoord = a_texCoord;                        \n\
}                                                    \n\
";

#define kCCShaderSuperAnimation        "ShaderSuperAnimation"
#define kCCUniformAnimMatrix            "u_animMatrix"
#define kCCUniformAnimColor            "u_animColor"

NSString* CStringToNSString(const char* theCString){
	return [NSString stringWithCString: theCString encoding:NSUTF8StringEncoding];
}

void LoadSuperAnimShader(){
	CCGLProgram* aProgram = [[CCGLProgram alloc] autorelease];
	
	[aProgram initWithVertexShaderByteArray:ccSuperAnim_vert fragmentShaderByteArray:ccPositionTextureColor_frag];
	[aProgram addAttribute:kCCAttributeNamePosition index:kCCVertexAttrib_Position];
	[aProgram addAttribute:kCCAttributeNameColor index:kCCVertexAttrib_Color];
	[aProgram addAttribute:kCCAttributeNameTexCoord index:kCCVertexAttrib_TexCoords];
	[aProgram link];
    [aProgram updateUniforms];
	
	[[CCShaderCache sharedShaderCache] addProgram:aProgram forKey:CStringToNSString(kCCShaderSuperAnimation)];
	//[aProgram release];
}
//////////////////////////////////////////////////////////////////////////
typedef std::map<int, SuperAnimHandler> KeyToSuperAnimHandlerMap;
class AnimHandlerKeyMgr {
	KeyToSuperAnimHandlerMap mKeyToHandlerMap;
	std::set<int> mLivingKeys;
private:
	AnimHandlerKeyMgr(){}
	~AnimHandlerKeyMgr(){}
public:
	static AnimHandlerKeyMgr* GetInstance();
	static void DestroyInstance();
	int GenerateKey(SuperAnimHandler theHandler);
	SuperAnimHandler GetHandler(int theKey);
	SuperAnimHandler* GetSuperAnimHandlerRef(int theKey);
	void DestroyKey(int theKey);
};
static AnimHandlerKeyMgr* sAnimHandlerKeyMgrInst = NULL;
AnimHandlerKeyMgr* AnimHandlerKeyMgr::GetInstance(){
	if (sAnimHandlerKeyMgrInst == NULL) {
		sAnimHandlerKeyMgrInst = new AnimHandlerKeyMgr();
	}
	return sAnimHandlerKeyMgrInst;
}
void AnimHandlerKeyMgr::DestroyInstance(){
	if (sAnimHandlerKeyMgrInst) {
		delete sAnimHandlerKeyMgrInst;
		sAnimHandlerKeyMgrInst = NULL;
	}
}
int AnimHandlerKeyMgr::GenerateKey(SuperAnimHandler theHandler){
	int aNewKey = 0;
	do {
		aNewKey = arc4random();
	} while (mLivingKeys.find(aNewKey) != mLivingKeys.end());
	mKeyToHandlerMap[aNewKey] = theHandler;
	mLivingKeys.insert(aNewKey);
	return aNewKey;
}
SuperAnimHandler AnimHandlerKeyMgr::GetHandler(int theKey){
	if (mLivingKeys.find(theKey) == mLivingKeys.end())
		return SuperAnimHandler();
	
	return mKeyToHandlerMap[theKey];
}
SuperAnimHandler* AnimHandlerKeyMgr::GetSuperAnimHandlerRef(int theKey){
	if (mLivingKeys.find(theKey) == mLivingKeys.end())
		return NULL;
	
	return &(mKeyToHandlerMap[theKey]);
}

void AnimHandlerKeyMgr::DestroyKey(int theKey){
	KeyToSuperAnimHandlerMap::iterator anIter = mKeyToHandlerMap.find(theKey);
	if (anIter != mKeyToHandlerMap.end()) {
		mKeyToHandlerMap.erase(anIter);
	}
	
	std::set<int>::iterator anTmpIter = mLivingKeys.find(theKey);
	if (anTmpIter != mLivingKeys.end()) {
		mLivingKeys.erase(anTmpIter);
	}
}
//////////////////////////////////////////////////////////////////////////

namespace SuperAnim {
	class SuperAnimSprite
	{
	protected:
		CCTexture2D *mTexture;
		ccV3F_C4B_T2F_Quad mQuad;
	public:
		SuperAnimSprite();
		SuperAnimSprite(CCTexture2D *theTexture);
		SuperAnimSprite(CCTexture2D *theTexture, CGRect theTextureRect);
		~SuperAnimSprite();
		
		void SetTexture(CCTexture2D *theTexture);
		void SetTexture(CCTexture2D *theTexture, CGRect theTextureRect);
		void Draw();
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
	mTexture = nil;
	memset(&mQuad, 0, sizeof(mQuad));
}

SuperAnimSprite::SuperAnimSprite(CCTexture2D *theTexture)
{
	mTexture = nil;
	memset(&mQuad, 0, sizeof(mQuad));
	SetTexture(theTexture);
}

SuperAnimSprite::SuperAnimSprite(CCTexture2D *theTexture, CGRect theTextureRect)
{
	mTexture = nil;
	memset(&mQuad, 0, sizeof(mQuad));
	SetTexture(theTexture, theTextureRect);
}

SuperAnimSprite::~SuperAnimSprite()
{
	if (mTexture != nil)
	{
		[mTexture release];
		mTexture = nil;
	}
}

void SuperAnimSprite::SetTexture(CCTexture2D *theTexture)
{
	if (theTexture == nil) {
		return;
	}
	CGRect aRect = CGRectZero;
	aRect.size = theTexture.contentSize;
	SetTexture(theTexture, aRect);
}

void SuperAnimSprite::SetTexture(CCTexture2D *theTexture, CGRect theTextureRect)
{
	if (theTexture == nil)
	{
		return;
	}
	
	if (mTexture != nil)
	{
		[mTexture release];
		mTexture = nil;
	}
	
	// retain this texture in case removed by removeUnusedTextures();
	[theTexture retain];
	mTexture = theTexture;
	
	// Set Texture coordinates
	CGRect theTexturePixelRect = CC_RECT_POINTS_TO_PIXELS(theTextureRect);
	float aTextureWidth = [mTexture pixelsWide];
	float aTextureHeight = [mTexture pixelsHigh];
	
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
	
	mQuad.bl.vertices = (ccVertex3F){x1, y1, 0};
	mQuad.br.vertices = (ccVertex3F){x2, y1, 0};
	mQuad.tl.vertices = (ccVertex3F){x1, y2, 0};
	mQuad.tr.vertices = (ccVertex3F){x2, y2, 0};
	
	// Set color
	ccColor4B aDefaultColor = {255, 255, 255, 255};
	mQuad.bl.colors = aDefaultColor;
	mQuad.br.colors = aDefaultColor;
	mQuad.tl.colors = aDefaultColor;
	mQuad.tr.colors = aDefaultColor;
}
void SuperAnimSprite::Draw()
{
	if (mTexture == NULL)
	{
		return;
	}
#if 1	
	ccGLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	
	ccGLBindTexture2D([mTexture name]);
	
	//
	// Attributes
	//
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
	
#define kQuadSize sizeof(mQuad.bl)
	long offset = (long)&mQuad;
	
	// vertex
	NSInteger diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
	
	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	
	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	CHECK_GL_ERROR_DEBUG();
	
	CC_INCREMENT_GL_DRAWS(1);
#endif
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
		// we need a custom shader to draw animation sprite
		LoadSuperAnimShader();
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
	CCTexture2D *aTexture = [[CCTextureCache sharedTextureCache] addImage:CStringToNSString(anImageFile.c_str())];
	if (aTexture == nil) {
		char aBuffer[256];
		sprintf(aBuffer, "Error:%s is missing.", anImageFileName.c_str());
		//CCMessageBox(aBuffer, "Error");
		CCLOG(CStringToNSString(aBuffer));
		return InvalidSuperAnimSpriteId;
	}
	
	// create new super animation sprite
	SuperAnimSprite *aSuperAnimSprite = new SuperAnimSprite(aTexture);
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

@implementation SuperAnimNode

+(id) create:(NSString*)theAbsAnimFile Id:(int)theId Listener:(id<SuperAnimNodeListener>)theListener{
	SuperAnimNode* aSuperAnimNode = [SuperAnimNode alloc];
	if (aSuperAnimNode == nil) {
		return nil;
	}
	if ([aSuperAnimNode Init:theAbsAnimFile Id:theId Listener:theListener] == NO) {
		[aSuperAnimNode dealloc];
		return nil;
	}
	
	[aSuperAnimNode autorelease];
	return aSuperAnimNode;
}

-(void) dealloc{
	AnimHandlerKeyMgr::GetInstance()->DestroyKey(mAnimHandlerKey);
	[super dealloc];
}

-(BOOL) Init:(NSString*)theAbsAnimFile Id:(int)theId Listener:(id<SuperAnimNodeListener>) theListener{
	if (self = [super init]) {
		std::string anAbsAnimFile = [theAbsAnimFile cStringUsingEncoding:NSUTF8StringEncoding];
		mAnimHandlerKey = AnimHandlerKeyMgr::GetInstance()->GenerateKey(GetSuperAnimHandler(anAbsAnimFile));
		SuperAnimHandler anAnimHandler = AnimHandlerKeyMgr::GetInstance()->GetHandler(mAnimHandlerKey);
		if (!anAnimHandler.IsValid()) {
			char aBuffer[256];
			sprintf(aBuffer, "Error:can't load the SuperAnim %s.", anAbsAnimFile.c_str());
			//CCMessageBox(aBuffer, "Error");
			CCLOG([NSString stringWithCString:aBuffer encoding:NSUTF8StringEncoding]);
			return NO;
		}
		self.contentSize = CGSizeMake(anAnimHandler.mWidth / CC_CONTENT_SCALE_FACTOR(), anAnimHandler.mHeight / CC_CONTENT_SCALE_FACTOR());
		mId = theId;
		mListener = theListener;
		mAnimState = kAnimStateInitialized;
		
		self.shaderProgram = [[CCShaderCache sharedShaderCache] programForKey:CStringToNSString(kCCShaderSuperAnimation)];
		[self scheduleUpdate];
		self.anchorPoint = CGPointMake(0.5f, 0.5f);
		return YES;
	}
	
	return NO;
}
-(void) draw{
	
	if (mAnimState == kAnimStateInvalid ||
		mAnimState == kAnimStateInitialized)
	{
		return;
	}
	
	SuperAnimHandler anAnimHandler = AnimHandlerKeyMgr::GetInstance()->GetHandler(mAnimHandlerKey);
	
	if (!anAnimHandler.IsValid()) {
		return;
	}
	
	static SuperAnimObjDrawInfo sAnimObjDrawnInfo;
	float aPixelToPointScale = 1.0f / CC_CONTENT_SCALE_FACTOR();
	float anAnimContentHeightInPixel = self.contentSize.height * CC_CONTENT_SCALE_FACTOR();
	BeginIterateAnimObjDrawInfo();
	while (IterateAnimObjDrawInfo(anAnimHandler, sAnimObjDrawnInfo)) {
		if (sAnimObjDrawnInfo.mSpriteId == InvalidSuperAnimSpriteId) {
			NSAssert(NO, CStringToNSString("Missing a sprite."));
			continue;
		}
		
		SuperAnimSprite *aSprite = SuperAnimSpriteMgr::GetInstance()->GetSpriteById(sAnimObjDrawnInfo.mSpriteId);
		if (aSprite == NULL){
			NSAssert(NO, CStringToNSString("Missing a sprite."));
			continue;
		}
		
		// cocos2d the origin is located at left bottom, but is in left top in flash
		sAnimObjDrawnInfo.mTransform.mMatrix.m12 = anAnimContentHeightInPixel - sAnimObjDrawnInfo.mTransform.mMatrix.m12;
		// convert to point
		sAnimObjDrawnInfo.mTransform.Scale(aPixelToPointScale, aPixelToPointScale);
		
		// Be sure that you call this macro every draw
		CC_NODE_DRAW_SETUP();
#if 1
		kmMat4 anAnimMatrix;
		kmMat4Identity(&anAnimMatrix);
		anAnimMatrix.mat[0] = sAnimObjDrawnInfo.mTransform.mMatrix.m00;
		anAnimMatrix.mat[4] = sAnimObjDrawnInfo.mTransform.mMatrix.m01;
		anAnimMatrix.mat[12] = sAnimObjDrawnInfo.mTransform.mMatrix.m02;
		anAnimMatrix.mat[1] = sAnimObjDrawnInfo.mTransform.mMatrix.m10;
		anAnimMatrix.mat[5] = sAnimObjDrawnInfo.mTransform.mMatrix.m11;
		anAnimMatrix.mat[13] = sAnimObjDrawnInfo.mTransform.mMatrix.m12;
		anAnimMatrix.mat[2] = sAnimObjDrawnInfo.mTransform.mMatrix.m20;
		anAnimMatrix.mat[6] = sAnimObjDrawnInfo.mTransform.mMatrix.m21;
		anAnimMatrix.mat[14] = sAnimObjDrawnInfo.mTransform.mMatrix.m22;
		ccColor4F anAnimColor = ccc4FFromccc4B(ccc4(sAnimObjDrawnInfo.mColor.mRed, sAnimObjDrawnInfo.mColor.mGreen, sAnimObjDrawnInfo.mColor.mBlue, sAnimObjDrawnInfo.mColor.mAlpha));
		int anAnimMatrixUinformLocation = glGetUniformLocation(self.shaderProgram->program_, kCCUniformAnimMatrix);
		int anAnimColorUinformLocation = glGetUniformLocation(self.shaderProgram->program_, kCCUniformAnimColor);
		//getShaderProgram()->setUniformLocationwithMatrix4fv(anAnimMatrixUinformLocation, anAnimMatrix.mat, 1);
		[self.shaderProgram setUniformLocation:anAnimMatrixUinformLocation withMatrix4fv:anAnimMatrix.mat count:1];
		//getShaderProgram()->setUniformLocationWith4fv(anAnimColorUinformLocation, &anAnimColor.r, 1);
		[self.shaderProgram setUniformLocation:anAnimColorUinformLocation with4fv:&anAnimColor.r count:1];
#endif
		aSprite->Draw();
	}
}
-(void) update:(ccTime) dt{
	if (mAnimState != kAnimStatePlaying)
	{
		return;
	}
	
	SuperAnimHandler* aRef = AnimHandlerKeyMgr::GetInstance()->GetSuperAnimHandlerRef(mAnimHandlerKey);
	if (aRef == NULL) {
		return;
	}
	
	bool isNewLabel = false;
	IncAnimFrameNum(*aRef, dt, isNewLabel);
	if (isNewLabel && mListener != nil)
	{
		[mListener OnAnimSectionEnd:mId LabelName:CStringToNSString(aRef->mCurLabel.c_str())];
	}
}
-(BOOL) PlaySection:(NSString*) theLabel{
	if (mAnimState == kAnimStateInvalid)
	{
		NSAssert(NO, CStringToNSString("The animation isn't ready."));
		return NO;
	}
	
	std::string aLabel = [theLabel cStringUsingEncoding:NSUTF8StringEncoding];
	
	if (aLabel.empty())
	{
		NSAssert(NO, CStringToNSString("Please specify an animation section label to play."));
		return NO;
	}
	
	SuperAnimHandler* aRef = AnimHandlerKeyMgr::GetInstance()->GetSuperAnimHandlerRef(mAnimHandlerKey);
	if (aRef == NULL) {
		return NO;
	}
	
	if (PlayBySection(*aRef, aLabel)){
		mAnimState = kAnimStatePlaying;
		[[CCDirector sharedDirector] setNextDeltaTimeZero:YES];
		return NO;
	}
	
	// we should not go here.
	// if we do that means you specify a wrong label
	NSAssert(NO, CStringToNSString("I cannot find the specified section label in animation."));
	return NO;
}
-(void) Pause{
	mAnimState = kAnimStatePause;
}
-(void) Resume{
	mAnimState = kAnimStatePlaying;
}
-(BOOL) IsPause{
	return mAnimState == kAnimStatePause;
}
-(BOOL) IsPlaying{
	return mAnimState == kAnimStatePlaying;
}
-(int) GetCurFrame{
	SuperAnimHandler anAnimHandler = AnimHandlerKeyMgr::GetInstance()->GetHandler(mAnimHandlerKey);
	return (int)anAnimHandler.mCurFrameNum;
}
-(NSString*) GetCurSectionName{
	SuperAnimHandler anAnimHandler = AnimHandlerKeyMgr::GetInstance()->GetHandler(mAnimHandlerKey);
	return [NSString stringWithCString:anAnimHandler.mCurLabel.c_str() encoding:NSUTF8StringEncoding];
}
-(BOOL) HasSection:(NSString*) theLabelName{
	SuperAnimHandler anAnimHandler = AnimHandlerKeyMgr::GetInstance()->GetHandler(mAnimHandlerKey);
	std::string aLabelName = [theLabelName cStringUsingEncoding:NSUTF8StringEncoding];
	return  SuperAnim::HasSection(anAnimHandler, aLabelName);
}

-(int) GetId{
	return mId;
}

+(BOOL) LoadAnimFile:(NSString*) theAbsAnimFile{
	std::string anAbsAnimFile = [theAbsAnimFile cStringUsingEncoding:NSUTF8StringEncoding];
	bool aResult = SuperAnim::LoadAnimFile(anAbsAnimFile);
	return aResult ? YES : NO;
}

+(void) UnloadAnimFile:(NSString*) theAbsAnimFile{
	std::string anAbsAnimFile = [theAbsAnimFile cStringUsingEncoding:NSUTF8StringEncoding];
	return SuperAnim::UnloadAnimFile(anAbsAnimFile);
}
@end
