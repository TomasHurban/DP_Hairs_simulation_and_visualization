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

#include <vlGraphics/GLSL.hpp>
#include <vlGraphics/OpenGL.hpp>
#include <vlCore/VLSettings.hpp>
#include <vlCore/VirtualFile.hpp>
#include <vlCore/Log.hpp>
#include <vlCore/Say.hpp>

using namespace vl;

//-----------------------------------------------------------------------------
// GLSLShader
//-----------------------------------------------------------------------------
GLSLShader::GLSLShader(EShaderType type, const String& source)
{
  VL_DEBUG_SET_OBJECT_NAME()
  mType = type;
  mHandle = 0;
  mCompiled = false;
  setSource(source);
}
//-----------------------------------------------------------------------------
GLSLShader::~GLSLShader()
{
  deleteShader();
}
//-----------------------------------------------------------------------------
void GLSLShader::setSource( const String& source )
{
  std::string new_src = "ERROR";

  if (vl::locateFile(source))
  {
    new_src = vl::String::loadText(source).toStdString();
    setObjectName( source.toStdString() );
  }
  else
  {
    int cn = source.count('\n');
    int cr = source.count('\r');
    int cf = source.count('\f');
    int line_count = vl::max( vl::max( cn, cr ), cf );
    if(line_count == 0)
    {
      Log::error("GLSLShader::setSource('" + source + "') error: file not found!\n");
      mSource = "";
      VL_TRAP();
    }
    else
      new_src = source.toStdString();
  }
  
  // update only if the source is actually different
  if (new_src != "ERROR" && new_src != mSource)
  {
    mSource = new_src;
    mCompiled = false;
  }
}
//-----------------------------------------------------------------------------
bool GLSLShader::compile()
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  if (mSource.empty())
  {
    Log::error("GLSLShader::compile() failed: shader source is empty!\n");
    VL_TRAP();
    return false;
  }

  if (!mCompiled)
  {
    // compile the shader

    if (!handle())
    {
      // createShader();
      mHandle = glCreateShader(mType);
    }

    // assign sources

    const GLchar* source[] = { mSource.c_str() };
    glShaderSource(handle(), 1, source, NULL);

    // compile the shader

    glCompileShader(handle());

    if ( compileStatus() )
    {
      mCompiled = true;
      #ifndef NDEBUG
        String log = infoLog();
        if (!log.empty())
          Log::warning( Say("%s\n%s\n\n") << objectName().c_str() << log );
      #endif
    }
    else
    {
      Log::bug( Say("\nGLSLShader::compile() failed! '%s':\n\n") << objectName().c_str() );
      // Log::bug( Say("Source:\n%s\n\n") << mSource.c_str() );
      Log::bug( Say("Info log:\n%s\n\n") << infoLog() );
      VL_TRAP()
    }
  }

  VL_CHECK_OGL();
  return mCompiled;
}
//-----------------------------------------------------------------------------
bool GLSLShader::compileStatus() const
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;
  VL_CHECK(handle())

  int status = 0;
  glGetShaderiv(handle(), GL_COMPILE_STATUS, &status); VL_CHECK_OGL();
  return status == GL_TRUE;
}
//-----------------------------------------------------------------------------
String GLSLShader::infoLog() const
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return "OpenGL Shading Language not supported.\n";
  VL_CHECK(handle())

  int max_length = 0;
  glGetShaderiv(handle(), GL_INFO_LOG_LENGTH, &max_length); VL_CHECK_OGL();
  if (max_length != 0)
  {
    std::vector<GLchar> log_buffer;
    log_buffer.resize(max_length);
    glGetShaderInfoLog(handle(), max_length, NULL, &log_buffer[0]); VL_CHECK_OGL();
    VL_CHECK_OGL();
    return &log_buffer[0];
  }
  else
    return String();
}
//-----------------------------------------------------------------------------
void GLSLShader::createShader()
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return;
  if (!handle())
  {
    mHandle = glCreateShader(mType);
    mCompiled = false;
  }
  VL_CHECK(handle());
  VL_CHECK_OGL();
}
//------------------------------------------------------------------------------
void GLSLShader::deleteShader()
{
  // VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return;
  if (handle())
  {
    glDeleteShader(handle()); // VL_CHECK_OGL();
    mHandle = 0;
    mCompiled = false;
  }
}
//------------------------------------------------------------------------------
// GLSLProgram
//------------------------------------------------------------------------------
GLSLProgram::GLSLProgram()
{
  VL_DEBUG_SET_OBJECT_NAME()
  mScheduleLink = true;
  mHandle = 0;
  mGeometryVerticesOut = 0;
  mGeometryInputType   = GIT_TRIANGLES;
  mGeometryOutputType  = GOT_TRIANGLE_STRIP;
  mProgramBinaryRetrievableHint = false;
  mProgramSeparable = false;
  m_vl_ModelViewMatrix = -1;
  m_vl_ProjectionMatrix = -1;
  m_vl_ModelViewProjectionMatrix = -1;
  m_vl_NormalMatrix = -1;
}
//-----------------------------------------------------------------------------
GLSLProgram::~GLSLProgram()
{
  if (handle())
    deleteProgram();
}
//-----------------------------------------------------------------------------
void GLSLProgram::createProgram()
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return;

  if (handle() == 0)
  {
    scheduleRelinking();
    mHandle = glCreateProgram(); VL_CHECK_OGL();
    VL_CHECK(handle())
  }
}
//-----------------------------------------------------------------------------
void GLSLProgram::deleteProgram()
{
  // VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return;
  if(handle())
  {
    glDeleteProgram(handle()); // VL_CHECK_OGL();
    mHandle = 0;
  }
  scheduleRelinking();
}
//-----------------------------------------------------------------------------
bool GLSLProgram::attachShader(GLSLShader* shader)
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  scheduleRelinking();

  #if 0
    if(std::find(mShaders.begin(), mShaders.end(), shader) != mShaders.end())
    {
      if ( shader->handle() )
        glDetachShader( handle(), shader->handle() ); VL_CHECK_OGL();
    }
    else
      mShaders.push_back(shader);
  #else
    detachShader(shader);
    mShaders.push_back(shader);
  #endif

  if ( shader->compile() )
  {
    createProgram();
    glAttachShader( handle(), shader->handle() ); VL_CHECK_OGL();
    return true;
  }

  VL_CHECK_OGL();
  return false;

}
//-----------------------------------------------------------------------------
void GLSLProgram::detachAllShaders()
{
  VL_CHECK_OGL();
  for(size_t i=mShaders.size(); i--;)
    detachShader(mShaders[i].get());
}
//-----------------------------------------------------------------------------
// detaching a shader that has not been attached is allowed, and is a No-Op
bool GLSLProgram::detachShader(GLSLShader* shader)
{
  VL_CHECK_OGL();

  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  if (!handle() || !shader->handle())
    return false;

  // if it fails the shader has never been attached to any GLSL program
  for(int i=0; i<(int)mShaders.size(); ++i)
  {
    if (mShaders[i] == shader)
    {
      if ( shader->handle() )
        glDetachShader( handle(), shader->handle() ); VL_CHECK_OGL();
      mShaders.erase(mShaders.begin() + i);
      break;
    }
  }

  return true;
}
//-----------------------------------------------------------------------------
void GLSLProgram::discardAllShaders()
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return;

  if (!handle())
    return;

  for(int i=0; i<(int)mShaders.size(); ++i)
  {
    if (mShaders[i]->handle())
    {
      glDetachShader( handle(), mShaders[i]->handle() ); VL_CHECK_OGL();
      mShaders[i]->deleteShader();
    }
  }

  mShaders.clear();
}
//-----------------------------------------------------------------------------
bool GLSLProgram::linkProgram(bool force_relink)
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  if (!linked() || force_relink)
  {
    if (shaderCount() == 0)
    {
      Log::bug("GLSLProgram::linkProgram() called on a GLSLProgram with no shaders! (" + String(objectName().c_str()) + ")\n");
      VL_TRAP()
      return false;
    }

    createProgram();

    // pre-link operations
    preLink();

    // link the program

    glLinkProgram(handle()); VL_CHECK_OGL();
    mScheduleLink = !linkStatus();

    // check link error
    if(linked())
    {
      // post-link operations
      postLink();

      #ifndef NDEBUG
        String log = infoLog();
        if (!log.empty())
          Log::warning( Say("%s\n%s\n\n") << objectName().c_str() << log );
      #endif
    }
    else
    {
      Log::bug("GLSLProgram::linkProgram() failed! (" + String(objectName().c_str()) + ")\n");
      Log::bug( Say("Info log:\n%s\n") << infoLog() );
      VL_TRAP()
      return false;
    }
  }

  return true;
}
//-----------------------------------------------------------------------------
void GLSLProgram::preLink()
{
  VL_CHECK_OGL();
  // fragment shader color number binding

  if (GLEW_EXT_gpu_shader4||GLEW_VERSION_3_0||GLEW_VERSION_4_0)
  {
    std::map<std::string, int>::iterator it = mFragDataLocation.begin();
    while(it != mFragDataLocation.end())
    {
      VL_glBindFragDataLocation( handle(), it->second, it->first.c_str() ); VL_CHECK_OGL();
      ++it;
    }
  }

  // Note that OpenGL 3 and 4 do not use glProgramParameter to define the layout of the 
  // input/output geometry but something like this in the geometry shader:
  //
  // layout(triangles) in;
  // layout(triangle_strip, max_vertices = 3) out;

  if (GLEW_Has_Geometry_Shader && geometryVerticesOut() )
  {
    // if there is at least one geometry shader applies the geometry shader parameters
    for(unsigned i=0; i<mShaders.size(); ++i)
    {
      if (mShaders[i]->type() == ST_GEOMETRY_SHADER)
      {
        VL_glProgramParameteri(handle(), GL_GEOMETRY_INPUT_TYPE_EXT,   geometryInputType()); VL_CHECK_OGL();
        VL_glProgramParameteri(handle(), GL_GEOMETRY_OUTPUT_TYPE_EXT,  geometryOutputType()); VL_CHECK_OGL();
        VL_glProgramParameteri(handle(), GL_GEOMETRY_VERTICES_OUT_EXT, geometryVerticesOut()); VL_CHECK_OGL();
        break;
      }
    }
  }

  // OpenGL 4 program parameters

  if(GLEW_ARB_get_program_binary)
  {
    VL_glProgramParameteri(handle(), GL_PROGRAM_BINARY_RETRIEVABLE_HINT, programBinaryRetrievableHint()?GL_TRUE:GL_FALSE); VL_CHECK_OGL();
  }

  if (GLEW_ARB_separate_shader_objects)
  {
    VL_glProgramParameteri(handle(), GL_PROGRAM_SEPARABLE, programSeparable()?GL_TRUE:GL_FALSE); VL_CHECK_OGL();
  }

  // automatically binds the specified attributes to the desired values

  for( std::map<std::string, int>::iterator it = mAutoAttribLocation.begin(); it != mAutoAttribLocation.end(); ++it)
  {
    glBindAttribLocation(handle(),it->second,it->first.c_str()); VL_CHECK_OGL();
  }
}
//-----------------------------------------------------------------------------
void GLSLProgram::postLink()
{
  VL_CHECK_OGL();

  // populate uniform binding map

  mActiveUniformLocation.clear();

  int uniform_count = 0;
  glGetProgramiv(handle(), GL_ACTIVE_UNIFORMS, &uniform_count); VL_CHECK_OGL();
  int uniform_len = 0;
  glGetProgramiv(handle(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniform_len); VL_CHECK_OGL();

  std::vector<char> name;
  name.resize(uniform_len);
  if (name.size())
  {
    for(int i=0; i<uniform_count; ++i)
    {
      GLenum type;
      int size;
      glGetActiveUniform(handle(), i, uniform_len, NULL, &size, &type, &name[0]); VL_CHECK_OGL();
      mActiveUniformLocation[&name[0]] = glGetUniformLocation(handle(), &name[0]);
    }
  }

  // check for the predefined glsl uniform variables

  m_vl_ModelViewMatrix           = glGetUniformLocation(handle(), "vl_ModelViewMatrix");
  m_vl_ProjectionMatrix          = glGetUniformLocation(handle(), "vl_ProjectionMatrix");
  m_vl_ModelViewProjectionMatrix = glGetUniformLocation(handle(), "vl_ModelViewProjectionMatrix");
  m_vl_NormalMatrix              = glGetUniformLocation(handle(), "vl_NormalMatrix");
}
//-----------------------------------------------------------------------------
bool GLSLProgram::linkStatus() const
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;
  
  VL_CHECK(handle())

  if (handle() == 0)
    return false;
  
  int status = 0;
  glGetProgramiv(handle(), GL_LINK_STATUS, &status); VL_CHECK_OGL();
  return status == GL_TRUE;
}
//-----------------------------------------------------------------------------
String GLSLProgram::infoLog() const
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return "OpenGL Shading Language not supported!\n";
  
  VL_CHECK(handle())

  if (handle() == 0)
    return "GLSLProgram::infoLog(): error! GLSL program object not yet created! (" + String(objectName().c_str()) + ")\n";

  int max_length = 0;
  glGetProgramiv(handle(), GL_INFO_LOG_LENGTH, &max_length); VL_CHECK_OGL();
  std::vector<GLchar> log_buffer;
  log_buffer.resize(max_length+1);
  glGetProgramInfoLog(handle(), max_length, NULL, &log_buffer[0]); VL_CHECK_OGL();
  return &log_buffer[0];
}
//-----------------------------------------------------------------------------
bool GLSLProgram::validateProgram() const
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  VL_CHECK(handle())

  if (handle() == 0)
    return false;

  glValidateProgram(handle());
  int status = 0;
  glGetProgramiv(handle(), GL_VALIDATE_STATUS, &status); VL_CHECK_OGL();
  return status == GL_TRUE;
}
//-----------------------------------------------------------------------------
void GLSLProgram::bindAttribLocation(unsigned int index, const std::string& name)
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )

  createProgram();
  scheduleRelinking();
  glBindAttribLocation(handle(), index, name.c_str()); VL_CHECK_OGL()
}
//-----------------------------------------------------------------------------
int GLSLProgram::maxVertexAttribs()
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return 0;

  int max = 0;
  glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &max ); VL_CHECK_OGL()
  return max;
}
//-----------------------------------------------------------------------------
bool GLSLProgram::useProgram() const
{
  VL_CHECK_OGL()
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  if (!handle())
  {
    Log::bug("GLSLProgram::useProgram() failed! GLSL program handle is null! (" + String(objectName().c_str()) + ")\n");
    VL_TRAP()
    return false;
  }

  if (!linked())
  {
    Log::bug("GLSLProgram::useProgram() failed! GLSL program not linked! (" + String(objectName().c_str()) + ")\n");
    VL_TRAP()
    return false;
  }

// The program validation should be done only after all the uniforms have been applied, just before rendering an object.
//#ifndef NDEBUG
//  if (!validateProgram())
//  {
//    Log::bug("GLSLProgram::useProgram() failed validation! (" + String(objectName().c_str()) + ")\n");
//    Log::bug( Say("Info log:\n%s\n") << infoLog() );
//    VL_TRAP();
//    return false;
//  }
//#endif

  // bind the GLSL program
  glUseProgram(handle()); VL_CHECK_OGL()

  return true;
}
//-----------------------------------------------------------------------------
void GLSLProgram::apply(const Camera*, OpenGLContext*) const
{
  VL_CHECK_OGL();
  if(GLEW_Has_Shading_Language_20)
  {
    if ( handle() )
      useProgram();
    else
      glUseProgram(0); VL_CHECK_OGL();
  }
}
//-----------------------------------------------------------------------------
bool GLSLProgram::applyUniformSet(const UniformSet* uniforms) const
{
  VL_CHECK_OGL();
  VL_CHECK( GLEW_Has_Shading_Language_20 )
  if( !GLEW_Has_Shading_Language_20 )
    return false;

  if(!uniforms)
    return false;
  
  if (!linked())
    return false;
  
  if (!handle())
    return false;

#ifndef NDEBUG
  int current_glsl_program = -1;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current_glsl_program); VL_CHECK_OGL();
  VL_CHECK(current_glsl_program == (int)handle())
#endif

  for(size_t i=0, count=uniforms->uniforms().size(); i<count; ++i)
  {
    Uniform* uniform = uniforms->uniforms()[i].get();

    #if 1
      std::map<std::string, int>::const_iterator it = mActiveUniformLocation.find(uniform->name());
      int location = it == mActiveUniformLocation.end() ? -1 : it->second;
    #else
      // for benchmarking purposes
      int location = glGetUniformLocation(handle(), uniform->name().c_str());
    #endif

    if (location == -1)
    {
      // Check the following:
      // (1) Is the uniform variable declared but not used in your GLSL program?
      // (2) Double-check the spelling of the uniform variable name.
      vl::Log::warning( vl::Say(
        "warning:\n"
        "GLSLProgram::applyUniformSet(): uniform '%s' not found!\n"
        "Is the uniform variable declared but not used in your GLSL program?\n"
        "Also double-check the spelling of the uniform variable name.\n") << uniform->name() );

      // VL_TRAP();
      // return false;
      continue;
    }

    // finally transmits the uniform
    // note: we don't perform delta binding per-uniform variable at the moment!

    VL_CHECK_OGL();
    switch(uniform->mType)
    {
      case UT_Int:     glUniform1iv(location, uniform->count(), uniform->intData()); VL_CHECK_OGL(); break;
      case UT_Int2:    glUniform2iv(location, uniform->count(), uniform->intData()); VL_CHECK_OGL(); break;
      case UT_Int3:    glUniform3iv(location, uniform->count(), uniform->intData()); VL_CHECK_OGL(); break;
      case UT_Int4:    glUniform4iv(location, uniform->count(), uniform->intData()); VL_CHECK_OGL(); break;

      case UT_UInt:    VL_glUniform1uiv(location, uniform->count(), uniform->uintData()); VL_CHECK_OGL(); break;
      case UT_UInt2:   VL_glUniform2uiv(location, uniform->count(), uniform->uintData()); VL_CHECK_OGL(); break;
      case UT_UInt3:   VL_glUniform3uiv(location, uniform->count(), uniform->uintData()); VL_CHECK_OGL(); break;
      case UT_UInt4:   VL_glUniform4uiv(location, uniform->count(), uniform->uintData()); VL_CHECK_OGL(); break;

      case UT_Float:   glUniform1fv(location, uniform->count(), uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Float2:  glUniform2fv(location, uniform->count(), uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Float3:  glUniform3fv(location, uniform->count(), uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Float4:  glUniform4fv(location, uniform->count(), uniform->floatData()); VL_CHECK_OGL(); break;

      case UT_Mat2F:   glUniformMatrix2fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat3F:   glUniformMatrix3fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat4F:   glUniformMatrix4fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;

      case UT_Mat2x3F: glUniformMatrix2x3fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat3x2F: glUniformMatrix3x2fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat2x4F: glUniformMatrix2x4fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat4x2F: glUniformMatrix4x2fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat3x4F: glUniformMatrix3x4fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;
      case UT_Mat4x3F: glUniformMatrix4x3fv(location, uniform->count(), GL_FALSE, uniform->floatData()); VL_CHECK_OGL(); break;

      case UT_Double:  glUniform1dv(location, uniform->count(), uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Double2: glUniform2dv(location, uniform->count(), uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Double3: glUniform3dv(location, uniform->count(), uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Double4: glUniform4dv(location, uniform->count(), uniform->doubleData()); VL_CHECK_OGL(); break;

      case UT_Mat2D:   glUniformMatrix2dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat3D:   glUniformMatrix3dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat4D:   glUniformMatrix4dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;

      case UT_Mat2x3D: glUniformMatrix2x3dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat3x2D: glUniformMatrix3x2dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat2x4D: glUniformMatrix2x4dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat4x2D: glUniformMatrix4x2dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat3x4D: glUniformMatrix3x4dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;
      case UT_Mat4x3D: glUniformMatrix4x3dv(location, uniform->count(), GL_FALSE, uniform->doubleData()); VL_CHECK_OGL(); break;

      default:
        // Probably you added a uniform to a Shader or Actor but you forgot to specify it's data!
        vl::Log::bug( vl::Say("GLSLProgram::applyUniformSet(): uniform '%s' does not contain any data!\n") << uniform->name() );
        VL_TRAP();
        break;
    }
  }

  VL_CHECK_OGL();
  return true;
}
//-----------------------------------------------------------------------------
void GLSLProgram::bindFragDataLocation(int color_number, const std::string& name)
{
  scheduleRelinking();
  mFragDataLocation[name] = color_number;
}
//-----------------------------------------------------------------------------
void GLSLProgram::unbindFragDataLocation(const std::string& name)
{
  scheduleRelinking();
  mFragDataLocation.erase(name);
}
//-----------------------------------------------------------------------------
int GLSLProgram::fragDataLocationBinding(const std::string& name) const
{
  std::map<std::string, int>::const_iterator it = mFragDataLocation.find(name);
  if (it != mFragDataLocation.end())
    return it->second;
  else
    return -1;
}
//-----------------------------------------------------------------------------
bool GLSLProgram::getProgramBinary(GLenum& binary_format, std::vector<unsigned char>& binary) const
{
  VL_CHECK_OGL();
  VL_CHECK(GLEW_ARB_get_program_binary)
  if (!GLEW_ARB_get_program_binary)
    return false;

  binary.clear();
  binary_format = (GLenum)-1;

  if (handle())
  {
    int status = 0;
    glGetProgramiv(handle(), GL_LINK_STATUS, &status); VL_CHECK_OGL();
    if (status == GL_FALSE)
      return false;
    GLint length = 0;
    glGetProgramiv(handle(), GL_PROGRAM_BINARY_LENGTH, &length); VL_CHECK_OGL();
    if (length)
    {
      binary.resize(length);
      glGetProgramBinary(handle(), length, NULL, &binary_format, &binary[0]); VL_CHECK_OGL();
    }
    return true;
  }
  else
  {
    VL_TRAP();
    return false;
  }
}
//-----------------------------------------------------------------------------
bool GLSLProgram::programBinary(GLenum binary_format, const void* binary, int length)
{
  VL_CHECK_OGL();
  VL_CHECK(GLEW_ARB_get_program_binary)
  if (!GLEW_ARB_get_program_binary)
    return false;

  createProgram();

  if (handle())
  {
    // pre-link operations
    preLink();
    
    // load glsl program and link
    glProgramBinary(handle(), binary_format, binary, length); VL_CHECK_OGL();
    mScheduleLink = !linkStatus();
    
    // log error
    if(linked())
    {
      // post-link operations
      postLink();

      #ifndef NDEBUG
        String log = infoLog();
        if (!log.empty())
          Log::warning( Say("%s\n%s\n\n") << objectName().c_str() << log );
      #endif
    }
    else
    {
      Log::bug("GLSLProgram::programBinary() failed! (" + String(objectName().c_str()) + ")\n");
      Log::bug( Say("Info log:\n%s\n") << infoLog() );
      VL_TRAP();
    }
    
    return linked();
  }
  else
  {
    VL_TRAP();
    return false;
  }
}
//-----------------------------------------------------------------------------
