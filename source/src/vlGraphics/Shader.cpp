/**************************************************************************************/
/*                                                                                    */
/*  Visualization Library                                                             */
/*  http://www.visualizationlibrary.com                                               */
/*                                                                                    */
/*  Copyright (c) 2005-2010, Michele Bosi                                             */
/*  All rights reserved.                                                              */
/*                                                                                    */
/*  Redistribution and use in source and binary forms, with or without modification,  */
/*  are permitted provided that the following conditions are met:                     */
/*                                                                                    */
/*  - Redistributions of source code must retain the above copyright notice, this     */
/*  list of conditions and the following disclaimer.                                  */
/*                                                                                    */
/*  - Redistributions in binary form must reproduce the above copyright notice, this  */
/*  list of conditions and the following disclaimer in the documentation and/or       */
/*  other materials provided with the distribution.                                   */
/*                                                                                    */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND   */
/*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE            */
/*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR  */
/*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    */
/*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      */
/*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    */
/*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS     */
/*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      */
/*                                                                                    */
/**************************************************************************************/

#include <vlGraphics/Shader.hpp>
#include <vlGraphics/GLSL.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/ClipPlane.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlCore/Log.hpp>
#include <vlCore/Say.hpp>

using namespace vl;

//------------------------------------------------------------------------------
// Shader
//------------------------------------------------------------------------------
Shader::Shader()
{
  VL_DEBUG_SET_OBJECT_NAME()
  mLastUpdateTime = 0;
  // shader user data
  #if VL_SHADER_USER_DATA
    mShaderUserData = NULL;
  #endif
}
//------------------------------------------------------------------------------
Shader::~Shader()
{
}
//------------------------------------------------------------------------------
const GLSLProgram* Shader::getGLSLProgram() const 
{ 
  return dynamic_cast<const GLSLProgram*>( getRenderStateSet()->renderState( RS_GLSLProgram ) ); 
}
//------------------------------------------------------------------------------
GLSLProgram* Shader::getGLSLProgram() 
{ 
  return dynamic_cast<GLSLProgram*>( getRenderStateSet()->renderState( RS_GLSLProgram ) ); 
}
//------------------------------------------------------------------------------
// state getters
//------------------------------------------------------------------------------
#define GET_OR_CREATE(RS)\
  RS* rs = dynamic_cast<RS*>( gocRenderStateSet()->renderState( RS_##RS ) ); \
  if ( rs == NULL ) \
  { \
    rs = new RS; \
    gocRenderStateSet()->setRenderState( rs ); \
  } \
  return rs;
//------------------------------------------------------------------------------
#define GET_OR_CREATE_IDX(RS, index)\
  RS* rs = dynamic_cast<RS*>( gocRenderStateSet()->renderState( (ERenderState)(RS_##RS##0 + index) ) ); \
  if ( rs == NULL ) \
  { \
    rs = new RS(index); \
    gocRenderStateSet()->setRenderState( rs ); \
  } \
  return rs;
//------------------------------------------------------------------------------
GLSLProgram* Shader::gocGLSLProgram() { GET_OR_CREATE(GLSLProgram); }
//------------------------------------------------------------------------------
PixelTransfer* Shader::gocPixelTransfer() { GET_OR_CREATE(PixelTransfer) }
//------------------------------------------------------------------------------
Hint* Shader::gocHint() { GET_OR_CREATE(Hint) }
//------------------------------------------------------------------------------
CullFace* Shader::gocCullFace() { GET_OR_CREATE(CullFace) }
//------------------------------------------------------------------------------
FrontFace* Shader::gocFrontFace() { GET_OR_CREATE(FrontFace) }
//------------------------------------------------------------------------------
DepthFunc* Shader::gocDepthFunc() { GET_OR_CREATE(DepthFunc) }
//------------------------------------------------------------------------------
DepthMask* Shader::gocDepthMask() { GET_OR_CREATE(DepthMask) }
//------------------------------------------------------------------------------
ColorMask* Shader::gocColorMask() { GET_OR_CREATE(ColorMask) }
//------------------------------------------------------------------------------
PolygonMode* Shader::gocPolygonMode() { GET_OR_CREATE(PolygonMode) }
//------------------------------------------------------------------------------
ShadeModel* Shader::gocShadeModel() { GET_OR_CREATE(ShadeModel) }
//------------------------------------------------------------------------------
BlendEquation* Shader::gocBlendEquation() { GET_OR_CREATE(BlendEquation) }
//------------------------------------------------------------------------------
AlphaFunc* Shader::gocAlphaFunc() { GET_OR_CREATE(AlphaFunc) }
//------------------------------------------------------------------------------
Material* Shader::gocMaterial() { GET_OR_CREATE(Material) }
//------------------------------------------------------------------------------
LightModel* Shader::gocLightModel() { GET_OR_CREATE(LightModel) }
//------------------------------------------------------------------------------
Fog* Shader::gocFog() { GET_OR_CREATE(Fog) }
//------------------------------------------------------------------------------
PolygonOffset* Shader::gocPolygonOffset() { GET_OR_CREATE(PolygonOffset) }
//------------------------------------------------------------------------------
LogicOp* Shader::gocLogicOp() { GET_OR_CREATE(LogicOp) }
//------------------------------------------------------------------------------
DepthRange* Shader::gocDepthRange() { GET_OR_CREATE(DepthRange) }
//------------------------------------------------------------------------------
LineWidth* Shader::gocLineWidth() { GET_OR_CREATE(LineWidth) }
//------------------------------------------------------------------------------
PointSize* Shader::gocPointSize() { GET_OR_CREATE(PointSize) }
//------------------------------------------------------------------------------
LineStipple* Shader::gocLineStipple() { GET_OR_CREATE(LineStipple) }
//------------------------------------------------------------------------------
PolygonStipple* Shader::gocPolygonStipple() { GET_OR_CREATE(PolygonStipple) }
//------------------------------------------------------------------------------
PointParameter* Shader::gocPointParameter() { GET_OR_CREATE(PointParameter) }
//------------------------------------------------------------------------------
StencilFunc* Shader::gocStencilFunc() { GET_OR_CREATE(StencilFunc) }
//------------------------------------------------------------------------------
StencilOp* Shader::gocStencilOp() { GET_OR_CREATE(StencilOp) }
//------------------------------------------------------------------------------
StencilMask* Shader::gocStencilMask() { GET_OR_CREATE(StencilMask) }
//------------------------------------------------------------------------------
BlendColor* Shader::gocBlendColor() { GET_OR_CREATE(BlendColor) }
//------------------------------------------------------------------------------
BlendFunc* Shader::gocBlendFunc() { GET_OR_CREATE(BlendFunc) }
//------------------------------------------------------------------------------
SampleCoverage* Shader::gocSampleCoverage() { GET_OR_CREATE(SampleCoverage) }
//------------------------------------------------------------------------------
Light* Shader::gocLight(int light_index) { GET_OR_CREATE_IDX(Light, light_index) }
//------------------------------------------------------------------------------
const Light* Shader::getLight(int light_index) const { return dynamic_cast<const Light*>( getRenderStateSet()->renderState( (ERenderState)(RS_Light0+light_index) ) ); }
//------------------------------------------------------------------------------
Light* Shader::getLight(int light_index) { return dynamic_cast<Light*>( getRenderStateSet()->renderState( (ERenderState)(RS_Light0+light_index) ) ); }
//------------------------------------------------------------------------------
ClipPlane* Shader::gocClipPlane(int plane_index) { GET_OR_CREATE_IDX(ClipPlane, plane_index) }
//------------------------------------------------------------------------------
const ClipPlane* Shader::getClipPlane(int plane_index) const { return dynamic_cast<const ClipPlane*>( getRenderStateSet()->renderState( (ERenderState)(RS_ClipPlane0+plane_index) ) ); }
//------------------------------------------------------------------------------
ClipPlane* Shader::getClipPlane(int plane_index) { return dynamic_cast<ClipPlane*>( getRenderStateSet()->renderState( (ERenderState)(RS_ClipPlane0+plane_index) ) ); }
//------------------------------------------------------------------------------
TextureUnit* Shader::gocTextureUnit(int unit_index) { GET_OR_CREATE_IDX(TextureUnit, unit_index) }
//------------------------------------------------------------------------------
TexGen* Shader::gocTexGen(int unit_index) { GET_OR_CREATE_IDX(TexGen, unit_index) }
//------------------------------------------------------------------------------
TexEnv* Shader::gocTexEnv(int unit_index) { GET_OR_CREATE_IDX(TexEnv, unit_index) }
//------------------------------------------------------------------------------
TextureMatrix* Shader::gocTextureMatrix(int unit_index) { GET_OR_CREATE_IDX(TextureMatrix, unit_index) }
//------------------------------------------------------------------------------
// PixelTransfer
//------------------------------------------------------------------------------
void PixelTransfer::apply(const Camera*, OpenGLContext*) const
{
  glPixelTransferi(GL_MAP_COLOR, mapColor() ? GL_TRUE : GL_FALSE);
  glPixelTransferi(GL_MAP_STENCIL, mapStencil() ? GL_TRUE : GL_FALSE);
  glPixelTransferi(GL_INDEX_SHIFT, indexShift() );
  glPixelTransferi(GL_INDEX_OFFSET, indexOffset() );
  glPixelTransferf(GL_RED_SCALE, redScale() );  
  glPixelTransferf(GL_GREEN_SCALE, greenScale() ); 
  glPixelTransferf(GL_BLUE_SCALE, blueScale() ); 
  glPixelTransferf(GL_ALPHA_SCALE, alphaScale() );
  glPixelTransferf(GL_DEPTH_SCALE, depthScale() );
  glPixelTransferf(GL_RED_BIAS, redBias() );
  glPixelTransferf(GL_GREEN_BIAS, greenBias() );  
  glPixelTransferf(GL_BLUE_BIAS, blueBias() );
  glPixelTransferf(GL_ALPHA_BIAS, alphaBias() ); 
  glPixelTransferf(GL_DEPTH_BIAS, depthBias() );
  VL_CHECK_OGL()
  if (GLEW_ARB_imaging)
  {
    glPixelTransferf(GL_POST_COLOR_MATRIX_RED_SCALE, postColorMatrixRedScale() );
    glPixelTransferf(GL_POST_COLOR_MATRIX_GREEN_SCALE, postColorMatrixGreenScale() );
    glPixelTransferf(GL_POST_COLOR_MATRIX_BLUE_SCALE, postColorMatrixBlueScale() );
    glPixelTransferf(GL_POST_COLOR_MATRIX_ALPHA_SCALE, postColorMatrixAlphaScale() );
    glPixelTransferf(GL_POST_COLOR_MATRIX_RED_BIAS, postColorMatrixRedBias() );
    glPixelTransferf(GL_POST_COLOR_MATRIX_GREEN_BIAS, postColorMatrixGreenBias() ); 
    glPixelTransferf(GL_POST_COLOR_MATRIX_BLUE_BIAS, postColorMatrixBlueBias() );
    glPixelTransferf(GL_POST_COLOR_MATRIX_ALPHA_BIAS, postColorMatrixAlphaBias() );
    glPixelTransferf(GL_POST_CONVOLUTION_RED_SCALE, postConvolutionRedScale() );
    glPixelTransferf(GL_POST_CONVOLUTION_GREEN_SCALE, postConvolutionGreenScale() ); 
    glPixelTransferf(GL_POST_CONVOLUTION_BLUE_SCALE, postConvolutionBlueScale() );
    glPixelTransferf(GL_POST_CONVOLUTION_ALPHA_SCALE, postConvolutionAlphaScale() );
    glPixelTransferf(GL_POST_CONVOLUTION_RED_BIAS, postConvolutionRedBias() );
    glPixelTransferf(GL_POST_CONVOLUTION_GREEN_BIAS, postConvolutionGreenBias() );  
    glPixelTransferf(GL_POST_CONVOLUTION_BLUE_BIAS, postConvolutionBlueBias() );
    glPixelTransferf(GL_POST_CONVOLUTION_ALPHA_BIAS, postConvolutionAlphaBias() ); 
    VL_CHECK_OGL()
  }
}
//------------------------------------------------------------------------------
// Hint
//------------------------------------------------------------------------------
void Hint::apply(const Camera*, OpenGLContext* gl) const
{
  VL_CHECK_OGL()

  if( gl->isCompatible() )
  {
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, mPerspectiveCorrectionHint ); VL_CHECK_OGL()
    
    glHint( GL_FOG_HINT, mFogHint ); VL_CHECK_OGL()

    if (GLEW_SGIS_generate_mipmap || GLEW_VERSION_1_4)
    {
      glHint( GL_GENERATE_MIPMAP_HINT, mGenerateMipmapHint ); VL_CHECK_OGL()
    }
  }
  
  glHint( GL_POLYGON_SMOOTH_HINT, mPolygonSmoothHint ); VL_CHECK_OGL()
  glHint( GL_LINE_SMOOTH_HINT, mLineSmoothHint ); VL_CHECK_OGL()
  glHint( GL_POINT_SMOOTH_HINT, mPointSmoothHint ); VL_CHECK_OGL()
  
}
//------------------------------------------------------------------------------
// CullFace
//------------------------------------------------------------------------------
void CullFace::apply(const Camera*, OpenGLContext*) const
{
  glCullFace(mFaceMode); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// FrontFace
//------------------------------------------------------------------------------
void FrontFace::apply(const Camera*, OpenGLContext*) const
{
  glFrontFace(mFrontFace); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// DepthFunc
//------------------------------------------------------------------------------
void DepthFunc::apply(const Camera*, OpenGLContext*) const
{
  glDepthFunc(mDepthFunc); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// DepthMask
//------------------------------------------------------------------------------
void DepthMask::apply(const Camera*, OpenGLContext*) const
{
  glDepthMask(mDepthMask?GL_TRUE:GL_FALSE); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// PolygonMode
//------------------------------------------------------------------------------
void PolygonMode::apply(const Camera*, OpenGLContext*) const
{
  // required by GL 3.1 CORE
  if ( mFrontFace == mBackFace )
  {
    glPolygonMode(GL_FRONT_AND_BACK, mFrontFace); VL_CHECK_OGL()
  }
  else
  {
    glPolygonMode(GL_FRONT, mFrontFace); VL_CHECK_OGL()
    glPolygonMode(GL_BACK, mBackFace); VL_CHECK_OGL()
  }
}
//------------------------------------------------------------------------------
// ShadeModel
//------------------------------------------------------------------------------
void ShadeModel::apply(const Camera*, OpenGLContext*) const
{
  glShadeModel(mShadeModel); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// BlendFunc
//------------------------------------------------------------------------------
void BlendFunc::apply(const Camera*, OpenGLContext*) const
{
  if (GLEW_VERSION_1_4||GLEW_EXT_blend_func_separate)
    { VL_glBlendFuncSeparate(mSrcRGB, mDstRGB, mSrcAlpha, mDstAlpha); VL_CHECK_OGL() }
  else
    { glBlendFunc(mSrcRGB, mDstRGB); VL_CHECK_OGL() }// modifies rgb and alpha
}
//------------------------------------------------------------------------------
// BlendEquation
//------------------------------------------------------------------------------
void BlendEquation::apply(const Camera*, OpenGLContext*) const
{
  if (GLEW_VERSION_2_0||GLEW_EXT_blend_equation_separate)
    { VL_glBlendEquationSeparate(mModeRGB, mModeAlpha); VL_CHECK_OGL() }
  else
    { VL_glBlendEquation(mModeRGB); VL_CHECK_OGL() }
}
//------------------------------------------------------------------------------
// AlphaFunc
//------------------------------------------------------------------------------
void AlphaFunc::apply(const Camera*, OpenGLContext*) const
{
  glAlphaFunc(mAlphaFunc, mRefValue); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// Material
//------------------------------------------------------------------------------
Material::Material()
{
  VL_DEBUG_SET_OBJECT_NAME()
  mFrontAmbient = fvec4(0.2f, 0.2f, 0.2f, 1.0f);
  mFrontDiffuse = fvec4(0.8f, 0.8f, 0.8f, 1.0f);
  mFrontSpecular = fvec4(0.0f, 0.0f, 0.0f, 1.0f);
  mFrontEmission = fvec4(0.0f, 0.0f, 0.0f, 1.0f);
  mFrontShininess = 0;

  mBackAmbient = fvec4(0.2f, 0.2f, 0.2f, 1.0f);
  mBackDiffuse = fvec4(0.8f, 0.8f, 0.8f, 1.0f);
  mBackSpecular = fvec4(0.0f, 0.0f, 0.0f, 1.0f);
  mBackEmission = fvec4(0.0f, 0.0f, 0.0f, 1.0f);
  mBackShininess = 0;

  mColorMaterialEnabled = false;
  mColorMaterialFace = PF_FRONT_AND_BACK;
  mColorMaterial = CM_AMBIENT_AND_DIFFUSE;
}
//------------------------------------------------------------------------------
void Material::setTransparency(float alpha)
{
  mFrontAmbient.a()   = mBackAmbient.a()   = alpha;
  mFrontDiffuse.a()   = mBackDiffuse.a()   = alpha;
  mFrontSpecular.a()  = mBackSpecular.a()  = alpha;
  mFrontEmission.a()  = mBackEmission.a()  = alpha;
}
//------------------------------------------------------------------------------
void Material::setFrontTransparency(float alpha)
{
  mFrontAmbient.a()  = alpha;
  mFrontDiffuse.a()  = alpha;
  mFrontSpecular.a() = alpha;
  mFrontEmission.a() = alpha;
}
//------------------------------------------------------------------------------
void Material::setBackTransparency(float alpha)
{
  mBackAmbient.a()  = alpha;
  mBackDiffuse.a()  = alpha;
  mBackSpecular.a() = alpha;
  mBackEmission.a() = alpha;
}
//------------------------------------------------------------------------------
void Material::setFrontFlatColor(const fvec4& color)
{
  mFrontAmbient  = 0;
  mFrontDiffuse  = 0;
  mFrontSpecular = 0;
  mFrontEmission = color;
  mFrontShininess = 0;
  setFrontTransparency(color.a());
}
//------------------------------------------------------------------------------
void Material::setBackFlatColor(const fvec4& color)
{
  mBackAmbient  = 0;
  mBackDiffuse  = 0;
  mBackSpecular = 0;
  mBackEmission = color;
  mBackShininess = 0;
  setBackTransparency(color.a());
}
//------------------------------------------------------------------------------
void Material::setFlatColor(const fvec4& color)
{
  setFrontFlatColor(color);
  setBackFlatColor(color);
}
//------------------------------------------------------------------------------
void Material::apply(const Camera*, OpenGLContext*) const
{
  if (mColorMaterialEnabled)
  {
    glColorMaterial(colorMaterialFace(), colorMaterial());
    glEnable(GL_COLOR_MATERIAL);
  }
  else
    glDisable(GL_COLOR_MATERIAL);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mFrontAmbient.ptr()); 
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mFrontDiffuse.ptr()); 
  glMaterialfv(GL_FRONT, GL_SPECULAR, mFrontSpecular.ptr()); 
  glMaterialfv(GL_FRONT, GL_EMISSION, mFrontEmission.ptr()); 
  glMaterialf(GL_FRONT, GL_SHININESS, mFrontShininess); 

  glMaterialfv(GL_BACK, GL_AMBIENT, mBackAmbient.ptr());
  glMaterialfv(GL_BACK, GL_DIFFUSE, mBackDiffuse.ptr());
  glMaterialfv(GL_BACK, GL_SPECULAR, mBackSpecular.ptr());
  glMaterialfv(GL_BACK, GL_EMISSION, mBackEmission.ptr());
  glMaterialf(GL_BACK, GL_SHININESS, mBackShininess);
}
//------------------------------------------------------------------------------
// LightModel
//------------------------------------------------------------------------------
void LightModel::apply(const Camera*, OpenGLContext*) const
{
  if (GLEW_VERSION_1_2||GLEW_EXT_separate_specular_color)
    { glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, mColorControl); VL_CHECK_OGL() }

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, mAmbientColor.ptr()); VL_CHECK_OGL()
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, mLocalViewer?1:0); VL_CHECK_OGL()
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, mTwoSide?1:0); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// Fog
//------------------------------------------------------------------------------
void Fog::apply(const Camera*, OpenGLContext*) const
{
  glFogi(GL_FOG_MODE, mMode); VL_CHECK_OGL()
  glFogfv(GL_FOG_COLOR, mColor.ptr()); VL_CHECK_OGL()
  glFogf(GL_FOG_DENSITY, mDensity); VL_CHECK_OGL()
  glFogf(GL_FOG_START, mStart); VL_CHECK_OGL()
  glFogf(GL_FOG_END, mEnd); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// PolygonOffset
//------------------------------------------------------------------------------
void PolygonOffset::apply(const Camera*, OpenGLContext*) const
{
  glPolygonOffset(mFactor, mUnits); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// LogicOp
//------------------------------------------------------------------------------
void LogicOp::apply(const Camera*, OpenGLContext*) const
{
  glLogicOp(mLogicOp); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// DepthRange
//------------------------------------------------------------------------------
void DepthRange::apply(const Camera*, OpenGLContext*) const
{
  glDepthRange(mZNear, mZFar); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// LineWidth
//------------------------------------------------------------------------------
void LineWidth::apply(const Camera*, OpenGLContext*) const
{
  glLineWidth(mLineWidth); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// PointSize
//------------------------------------------------------------------------------
void PointSize::apply(const Camera*, OpenGLContext*) const
{
  glPointSize(mPointSize); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// PolygonStipple
//------------------------------------------------------------------------------
PolygonStipple::PolygonStipple()
{
  VL_DEBUG_SET_OBJECT_NAME()
  memset(mMask, 0xFF, sizeof(unsigned char)*32*32/8);
}
//------------------------------------------------------------------------------
PolygonStipple::PolygonStipple(const unsigned char* mask)
{
  VL_DEBUG_SET_OBJECT_NAME()
  set(mask);
}
//------------------------------------------------------------------------------
void PolygonStipple::set(const unsigned char* mask)
{
  memcpy(mMask, mask, sizeof(unsigned char)*32*32/8);
}
//------------------------------------------------------------------------------
void PolygonStipple::apply(const Camera*, OpenGLContext*) const
{
  glPolygonStipple(mask()); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// LineStipple
//------------------------------------------------------------------------------
void LineStipple::apply(const Camera*, OpenGLContext*) const
{
  glLineStipple(mFactor, mPattern); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// PointParameter
//------------------------------------------------------------------------------
void PointParameter::apply(const Camera*, OpenGLContext*) const
{
  if (GLEW_VERSION_1_4)
  {
    VL_glPointParameterf(GL_POINT_SIZE_MIN, mSizeMin); VL_CHECK_OGL()
    VL_glPointParameterf(GL_POINT_SIZE_MAX, mSizeMax); VL_CHECK_OGL()
    VL_glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, (const float*)mDistanceAttenuation.ptr()); VL_CHECK_OGL()
  }
  if (GLEW_VERSION_1_4||GLEW_VERSION_3_0)
  {
    VL_glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, mFadeThresholdSize); VL_CHECK_OGL()
  }
  if (GLEW_VERSION_2_0||GLEW_VERSION_3_0||GLEW_VERSION_4_0)
  {
    VL_glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, mPointSpriteCoordOrigin); VL_CHECK_OGL()
  }
}
//------------------------------------------------------------------------------
// StencilFunc
//------------------------------------------------------------------------------
void StencilFunc::apply(const Camera*, OpenGLContext*) const
{
  if(GLEW_VERSION_2_0)
  {
    VL_glStencilFuncSeparate(GL_FRONT, mFunction_Front, mRefValue_Front, mMask_Front); VL_CHECK_OGL()
    VL_glStencilFuncSeparate(GL_BACK,  mFunction_Back,  mRefValue_Back,  mMask_Back);  VL_CHECK_OGL()
  }
  else
  {
    glStencilFunc(mFunction_Front, mRefValue_Front, mMask_Front); VL_CHECK_OGL()
  }
}
//------------------------------------------------------------------------------
// StencilOp
//------------------------------------------------------------------------------
void StencilOp::apply(const Camera*, OpenGLContext*) const
{
  if(GLEW_VERSION_2_0)
  {
    VL_glStencilOpSeparate(GL_FRONT, mSFail_Front, mDpFail_Front, mDpPass_Front); VL_CHECK_OGL()
    VL_glStencilOpSeparate(GL_BACK,  mSFail_Back,  mDpFail_Back,  mDpPass_Back);  VL_CHECK_OGL()
  }
  else
  {
    glStencilOp(mSFail_Front, mDpFail_Front, mDpPass_Front); VL_CHECK_OGL()
  }
}
//------------------------------------------------------------------------------
// StencilMask
//------------------------------------------------------------------------------
void StencilMask::apply(const Camera*, OpenGLContext*) const
{
  if(GLEW_VERSION_2_0)
  {
    glStencilMaskSeparate(GL_FRONT, mMask_Front); VL_CHECK_OGL()
    glStencilMaskSeparate(GL_BACK,  mMask_Back);  VL_CHECK_OGL()
  }
  else
  {
    glStencilMask(mMask_Front); VL_CHECK_OGL()
  }
}
//------------------------------------------------------------------------------
// BlendColor
//------------------------------------------------------------------------------
void BlendColor::apply(const Camera*, OpenGLContext*) const
{
  VL_glBlendColor(mBlendColor.r(), mBlendColor.g(), mBlendColor.b(), mBlendColor.a()); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// ColorMask
//------------------------------------------------------------------------------
void ColorMask::apply(const Camera*, OpenGLContext*) const
{
  glColorMask(mRed?GL_TRUE:GL_FALSE, mGreen?GL_TRUE:GL_FALSE, mBlue?GL_TRUE:GL_FALSE, mAlpha?GL_TRUE:GL_FALSE); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// SampleCoverage
//------------------------------------------------------------------------------
void SampleCoverage::apply(const Camera*, OpenGLContext*) const
{
  VL_glSampleCoverage(mValue, mInvert?GL_TRUE:GL_FALSE); VL_CHECK_OGL()
}
//------------------------------------------------------------------------------
// TexParameter
//------------------------------------------------------------------------------
TexParameter::TexParameter()
{
  mDirty = true;
  setMinFilter(TPF_LINEAR);
  setMagFilter(TPF_LINEAR);
  setWrapS(TPW_REPEAT);
  setWrapT(TPW_REPEAT);
  setWrapR(TPW_REPEAT);
  setBorderColor(fvec4(0,0,0,0));
  setAnisotropy(1.0f);
  setGenerateMipmap(false);
  setTexCompareFunc(TCF_LEQUAL);
  setTexCompareMode(TCM_NONE);
  setDepthTextureMode(DTM_LUMINANCE);
}
//------------------------------------------------------------------------------
void TexParameter::setMagFilter(ETexParamFilter magfilter) 
{ 
  mDirty = true;

  switch(magfilter)
  {
    case TPF_LINEAR:
    case TPF_NEAREST:
    {
      mMagfilter = magfilter; 
      break;
    }
    default:
    {
      mMagfilter = TPF_LINEAR; 
      #ifndef NDEBUG
        Log::bug("TexParameter::setMagFilter() accepts only the following values: TPF_LINEAR, TPF_NEAREST.\n");
      #endif
    }
  }
}
//------------------------------------------------------------------------------
void TexParameter::apply(ETextureDimension dimension, OpenGLContext* gl) const
{
  VL_CHECK_OGL()

#ifndef NDEBUG
  if (dimension == TD_TEXTURE_RECTANGLE)
  {
    bool err = (wrapS() != GL_CLAMP && wrapS() != GL_CLAMP_TO_EDGE && wrapS() != GL_CLAMP_TO_BORDER) |
               (wrapT() != GL_CLAMP && wrapT() != GL_CLAMP_TO_EDGE && wrapT() != GL_CLAMP_TO_BORDER) |
               (wrapR() != GL_CLAMP && wrapR() != GL_CLAMP_TO_EDGE && wrapR() != GL_CLAMP_TO_BORDER);
    if (err)
    {
      Log::bug("ARB_texture_rectangle extension allows only the following wrapping modes: GL_CLAMP, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER.\n");
    }
  }

  if (wrapS() == GL_MIRRORED_REPEAT || wrapT() == GL_MIRRORED_REPEAT || wrapR() == GL_MIRRORED_REPEAT)
  {
    if( !(GLEW_VERSION_1_4 || GLEW_ARB_texture_mirrored_repeat || GLEW_IBM_texture_mirrored_repeat) )
      Log::bug("GL_MIRRORED_REPEAT not supported by your OpenGL implementation.\n");
  }

  if (wrapS() == GL_CLAMP_TO_EDGE || wrapT() == GL_CLAMP_TO_EDGE || wrapR() == GL_CLAMP_TO_EDGE)
  {
    if( !(GLEW_VERSION_1_2 || GLEW_EXT_texture_edge_clamp || GLEW_SGIS_texture_edge_clamp) )
      Log::bug("GL_CLAMP_TO_EDGE not supported by your OpenGL implementation.\n");
  }

  if (wrapS() == GL_CLAMP_TO_BORDER || wrapT() == GL_CLAMP_TO_BORDER || wrapR() == GL_CLAMP_TO_BORDER)
  {
    if( !(GLEW_VERSION_1_3 || GLEW_ARB_texture_border_clamp || GLEW_SGIS_texture_border_clamp) )
      Log::bug("GL_CLAMP_TO_BORDER not supported by your OpenGL implementation.\n");
  }
#endif

  // none of these are supported by texture buffers and multisample textures

  if (dimension != TD_TEXTURE_BUFFER && dimension != TD_TEXTURE_2D_MULTISAMPLE && dimension != TD_TEXTURE_2D_MULTISAMPLE_ARRAY)
  {
    glTexParameterfv(dimension, GL_TEXTURE_BORDER_COLOR, borderColor().ptr()); VL_CHECK_OGL()
    glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, minFilter()); VL_CHECK_OGL()
    glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, magFilter()); VL_CHECK_OGL()
    glTexParameteri(dimension, GL_TEXTURE_WRAP_S, wrapS()); VL_CHECK_OGL()
    glTexParameteri(dimension, GL_TEXTURE_WRAP_T, wrapT()); VL_CHECK_OGL()
    if (GLEW_VERSION_1_2) 
      glTexParameteri(dimension, GL_TEXTURE_WRAP_R, wrapR()); VL_CHECK_OGL()

    if (GLEW_EXT_texture_filter_anisotropic)
      glTexParameterf( dimension, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy() ); VL_CHECK_OGL()

    if (gl->isCompatible())
      if (GLEW_VERSION_1_4||GLEW_SGIS_generate_mipmap)
        if (dimension != TD_TEXTURE_RECTANGLE)
          glTexParameteri(dimension, GL_GENERATE_MIPMAP, generateMipmap() ? GL_TRUE : GL_FALSE); VL_CHECK_OGL()

    if (GLEW_VERSION_1_4||GLEW_ARB_shadow)
    {
      glTexParameteri(dimension, GL_TEXTURE_COMPARE_MODE, compareMode() ); VL_CHECK_OGL()
      glTexParameteri(dimension, GL_TEXTURE_COMPARE_FUNC, compareFunc() ); VL_CHECK_OGL()
      if(gl->isCompatible())
        glTexParameteri(dimension, GL_DEPTH_TEXTURE_MODE, depthTextureMode() ); VL_CHECK_OGL()
    }
  }

  mDirty = false;

  VL_CHECK_OGL()
}
namespace
{
  bool checkTextureUnit(const char* str, int unit)
  {
    int max_texture = 1, max_tmp = 0;

    if (GLEW_VERSION_1_3||GLEW_ARB_multitexture)
    {
      glGetIntegerv(GL_MAX_TEXTURE_UNITS, &max_tmp); VL_CHECK_OGL();
      max_texture = max_tmp > max_texture ? max_tmp : max_texture;
    }

    if (GLEW_VERSION_2_0)
    {
      glGetIntegerv(GL_MAX_TEXTURE_COORDS, &max_tmp); VL_CHECK_OGL();
      max_texture = max_tmp > max_texture ? max_tmp : max_texture;
    }

    if (GLEW_VERSION_2_0||GLEW_VERSION_3_0||GLEW_VERSION_4_0)
    {
      glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_tmp); VL_CHECK_OGL();
      max_texture = max_tmp > max_texture ? max_tmp : max_texture;
    }

    if (unit > max_texture-1)
    {
      Log::bug( Say("%s error: texture unit index #%n not supported by this OpenGL implementation. Max texture unit index is %n.\n") << str << unit << max_texture-1 );
      return false;
    }

    return true;
  }
}
//------------------------------------------------------------------------------
// TexEnv
//------------------------------------------------------------------------------
TexEnv::TexEnv(int texunit)
{
  VL_DEBUG_SET_OBJECT_NAME()

  mTextureUnit = texunit;
  mMode = TEM_MODULATE;
  mColor = fvec4(0,0,0,0);

  // combiner settings
  mRGBScale = 1.0f;
  mCombineRGB = TEM_REPLACE;
  mSource0RGB = TES_TEXTURE;
  mSource1RGB = TES_TEXTURE;
  mSource2RGB = TES_TEXTURE;
  mOperand0RGB = TEO_SRC_COLOR;
  mOperand1RGB = TEO_SRC_COLOR;
  mOperand2RGB = TEO_SRC_COLOR;

  mAlphaScale  = 1.0f;
  mCombineAlpha = TEM_REPLACE;
  mSource0Alpha = TES_TEXTURE;
  mSource1Alpha = TES_TEXTURE;
  mSource2Alpha = TES_TEXTURE;
  mOperand0Alpha = TEO_SRC_ALPHA;
  mOperand1Alpha = TEO_SRC_ALPHA;
  mOperand2Alpha = TEO_SRC_ALPHA;

  mLodBias = 0.0;
  mPointSpriteCoordReplace = false;
}
//------------------------------------------------------------------------------
void TexEnv::apply(const Camera*, OpenGLContext*) const
{
  VL_CHECK_OGL()
  VL_CHECK(textureUnit() < VL_MAX_TEXTURE_UNITS)
  VL_CHECK(checkTextureUnit("TexEnv::apply",textureUnit()));

  VL_glActiveTexture( GL_TEXTURE0 + textureUnit() );
  // if this fails probably you requested a texture unit index not supported by your OpenGL implementation.
  VL_CHECK_OGL();

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode()); VL_CHECK_OGL()

  // red book 1.4 p411
  if (mode() == TEM_BLEND)
  {
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color().ptr()); VL_CHECK_OGL()
  }

  // combiner settings
  // red book 1.4 p438
  if (mode() == TEM_COMBINE && (GLEW_EXT_texture_env_combine || GLEW_VERSION_1_3))
  {
    glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, rgbScale()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, combineRGB()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, source0RGB()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, source1RGB()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, operand0RGB()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, operand1RGB()); VL_CHECK_OGL()
    if (combineRGB() == TEM_INTERPOLATE)
    {
      glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, source2RGB()); VL_CHECK_OGL()
      glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, operand2RGB()); VL_CHECK_OGL()
    }

    glTexEnvf(GL_TEXTURE_ENV, GL_ALPHA_SCALE, alphaScale()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, combineAlpha()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, source0Alpha()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, source1Alpha()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, operand0Alpha()); VL_CHECK_OGL()
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, operand1Alpha()); VL_CHECK_OGL()
    if (combineAlpha() == TEM_INTERPOLATE)
    {
      glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA, source2Alpha()); VL_CHECK_OGL()
      glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA, operand2Alpha()); VL_CHECK_OGL()
    }
  }

  // no need to do it if point sprite is disabled but we cannot know it here
  if (GLEW_VERSION_2_0||GLEW_ARB_point_sprite)
  {
    glTexEnvi( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, mPointSpriteCoordReplace ? GL_TRUE : GL_FALSE ); VL_CHECK_OGL()
  }

  if (GLEW_VERSION_1_4||GLEW_EXT_texture_lod_bias)
  {
    glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, mLodBias); VL_CHECK_OGL()
  }
}
//-----------------------------------------------------------------------------
// TexGen
//-----------------------------------------------------------------------------
//! The eye and object planes are not transformed by any matrix (unlike usually with OpenGL),
//! which means that the object plane is specified in object coordinates and that,
//! the eye plane is specified in camera coordinates.
TexGen::TexGen(int texunit)
{
  VL_DEBUG_SET_OBJECT_NAME()
  mTextureUnit  = texunit;
  mEyePlaneS    = fvec4(1,0,0,0);
  mObjectPlaneS = fvec4(1,0,0,0);
  mEyePlaneT    = fvec4(0,1,0,0);
  mObjectPlaneT = fvec4(0,1,0,0);
  mEyePlaneR    = fvec4(0,0,1,0);
  mObjectPlaneR = fvec4(0,0,1,0);
  mEyePlaneQ    = fvec4(0,0,0,1);
  mObjectPlaneQ = fvec4(0,0,0,1);
  mGenModeS = TGM_DISABLED;
  mGenModeT = TGM_DISABLED;
  mGenModeR = TGM_DISABLED;
  mGenModeQ = TGM_DISABLED;
}
//-----------------------------------------------------------------------------
void TexGen::apply(const Camera*, OpenGLContext*) const
{
  VL_CHECK_OGL();

  VL_CHECK(textureUnit() < VL_MAX_TEXTURE_UNITS)
  VL_CHECK(checkTextureUnit("TexGen::apply",textureUnit()));

  VL_glActiveTexture( GL_TEXTURE0 + textureUnit() );
  // if this fails probably you requested a texture unit index not supported by your OpenGL implementation.
  VL_CHECK_OGL();

  if (genModeS() || genModeT() || genModeR() || genModeQ())
  {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    VL_CHECK_OGL();

    if (genModeS())
    {
      glEnable(GL_TEXTURE_GEN_S);
      glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, genModeS());
      if (genModeS() == TGM_OBJECT_LINEAR) glTexGenfv(GL_S, GL_OBJECT_PLANE, objectPlaneS().ptr());
      if (genModeS() == TGM_EYE_LINEAR)    glTexGenfv(GL_S, GL_EYE_PLANE,       eyePlaneS().ptr());
    }

    VL_CHECK_OGL();

    if (genModeT())
    {
      glEnable(GL_TEXTURE_GEN_T);
      glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, genModeT());
      if (genModeT() == TGM_OBJECT_LINEAR) glTexGenfv(GL_T, GL_OBJECT_PLANE, objectPlaneT().ptr());
      if (genModeT() == TGM_EYE_LINEAR)    glTexGenfv(GL_T, GL_EYE_PLANE,       eyePlaneT().ptr());
    }

    VL_CHECK_OGL();

    if (genModeR())
    {
      glEnable(GL_TEXTURE_GEN_R);
      glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, genModeR());
      if (genModeR() == TGM_OBJECT_LINEAR) glTexGenfv(GL_R, GL_OBJECT_PLANE, objectPlaneR().ptr());
      if (genModeR() == TGM_EYE_LINEAR)    glTexGenfv(GL_R, GL_EYE_PLANE,       eyePlaneR().ptr());
    }

    VL_CHECK_OGL();

    if (genModeQ())
    {
      glEnable(GL_TEXTURE_GEN_Q);
      glTexGeni( GL_Q, GL_TEXTURE_GEN_MODE, genModeQ());
      if (genModeQ() == TGM_OBJECT_LINEAR) glTexGenfv(GL_Q, GL_OBJECT_PLANE, objectPlaneQ().ptr());
      if (genModeQ() == TGM_EYE_LINEAR)    glTexGenfv(GL_Q, GL_EYE_PLANE,       eyePlaneQ().ptr());
    }

    glPopMatrix();
  }

  // these needs to be done here to apply a TexGen which has all components disabled
  // and to finish up the TexGen which mixed enabled/disabled components.

  if (!genModeS())
    glDisable(GL_TEXTURE_GEN_S);
  
  if (!genModeT())
    glDisable(GL_TEXTURE_GEN_T);
  
  if (!genModeR())
    glDisable(GL_TEXTURE_GEN_R);
  
  if (!genModeQ())
    glDisable(GL_TEXTURE_GEN_Q);

  VL_CHECK_OGL();
}
//-----------------------------------------------------------------------------
// TextureMatrix
//-----------------------------------------------------------------------------
void TextureMatrix::apply(const Camera* camera, OpenGLContext*) const
{
  VL_CHECK_OGL();
  VL_CHECK(textureUnit() < VL_MAX_TEXTURE_UNITS);
  VL_CHECK(checkTextureUnit("TextureMatrix::apply",textureUnit()));

  VL_glActiveTexture( GL_TEXTURE0 + textureUnit() );
  // if this fails probably you requested a texture unit index not supported by your OpenGL implementation.
  VL_CHECK_OGL();
  glMatrixMode(GL_TEXTURE);
  if (useCameraRotationInverse())
    VL_glLoadMatrix( (matrix()*camera->inverseViewMatrix().as3x3()).ptr() );
  else
    VL_glLoadMatrix( matrix().ptr() );
}
//-----------------------------------------------------------------------------
// TextureUnit
//-----------------------------------------------------------------------------
bool TextureUnit::hasTexture() const 
{ 
  return mTexture && mTexture->handle(); 
}
//------------------------------------------------------------------------------
void TextureUnit::apply(const Camera* camera, OpenGLContext* ctx) const
{
  VL_CHECK_OGL();
  VL_CHECK(textureUnit() < VL_MAX_TEXTURE_UNITS)
  VL_CHECK(checkTextureUnit("TextureUnit::apply",textureUnit()));

  // activate the appropriate texture unit
  VL_glActiveTexture( GL_TEXTURE0 + textureUnit() ); VL_CHECK_OGL()

  // disable and unbind previous active texture target on this texture unit.
  vl::ETextureDimension prev_tex_target = ctx->texUnitBinding( textureUnit() );
  if (prev_tex_target)
  {
    // this is not strictly necessary, it also avoids interaction witht FBOs etc.
    glBindTexture( prev_tex_target, 0 ); VL_CHECK_OGL()

    /* GL_TEXTURE_1D_ARRAY and GL_TEXTURE_2D_ARRAY are not supported by the OpenGL fixed function pipeline */
    if (ctx->isCompatible())
    {
      switch(prev_tex_target)
      {
        case TD_TEXTURE_1D_ARRAY:
        case TD_TEXTURE_2D_ARRAY:
        case TD_TEXTURE_2D_MULTISAMPLE:
        case TD_TEXTURE_2D_MULTISAMPLE_ARRAY:
        case TD_TEXTURE_BUFFER:
          break;
        default:
          glDisable( prev_tex_target ); VL_CHECK_OGL()
      }
    }
  }

  if (camera)
  {
    if( !hasTexture() )
    {
      Log::bug( Say("TextureUnit::apply() error: null texture! (%s) \n") << texture()->objectName() );
      VL_TRAP();
      return;
    }

    // bind the texture
    glBindTexture( texture()->dimension(), texture()->handle() ); VL_CHECK_OGL()

    // if we request mipmapped filtering then we must have a mip-mapped texture.
    #ifndef NDEBUG
    if (texture()->dimension() != TD_TEXTURE_BUFFER)
    {
      GLint width = 0;
      int tex_target = texture()->dimension() == vl::TD_TEXTURE_CUBE_MAP ? GL_TEXTURE_CUBE_MAP_POSITIVE_X : texture()->dimension();
      glGetTexLevelParameteriv( tex_target, 1, GL_TEXTURE_WIDTH, &width );
      VL_CHECK_OGL()
      if ( !width )
      {
        switch(texture()->getTexParameter()->minFilter())
        {
          case TPF_LINEAR_MIPMAP_LINEAR:
          case TPF_LINEAR_MIPMAP_NEAREST:
          case TPF_NEAREST_MIPMAP_LINEAR:
          case TPF_NEAREST_MIPMAP_NEAREST:
          {
            Log::bug( vl::Say("TextureUnit::apply() error: requested mipmapping texture filtering on a Texture with no mipmaps! (%s)\n") << texture()->objectName() );
            VL_TRAP()
            break;
          }

          default:
            break;
        }
      }
    }
    #endif

    // enable the texture
    if (ctx->isCompatible())
    {
      /* GL_TEXTURE_1D_ARRAY and GL_TEXTURE_2D_ARRAY are not supported by the OpenGL fixed function pipeline */
      switch(texture()->dimension())
      {
        case TD_TEXTURE_1D_ARRAY:
        case TD_TEXTURE_2D_ARRAY:
        case TD_TEXTURE_2D_MULTISAMPLE:
        case TD_TEXTURE_2D_MULTISAMPLE_ARRAY:
        case TD_TEXTURE_BUFFER:
          break;
        default:
          glEnable( texture()->dimension() ); VL_CHECK_OGL()
      }
    }

    // track currently used texture target
    ctx->setTexUnitBinding( textureUnit(), texture()->dimension() );

    // texture parameters
    if ( texture()->getTexParameter()->dirty() )
      texture()->getTexParameter()->apply( texture()->dimension(), ctx );
  }
}
//-----------------------------------------------------------------------------
