/*!
* HairEffect.cpp
* Project Hair simulation and visualization using GPU
*/
#include "HairEffect.hpp"

using namespace vl;
using namespace std;

HairEffect::HairEffect(float pColorR, float pColorG, float pColorB, float pColorA)
{
	colorR = pColorR;
	colorG = pColorG;
	colorB = pColorB;
	colorA = pColorA;

	uniR = new vl::Uniform;
	uniG = new vl::Uniform;
	uniB = new vl::Uniform;
	uniA = new vl::Uniform;

	createEffect();
}

HairEffect::~HairEffect()
{

}

void HairEffect::createEffect()
{
	effect = new vl::Effect;

	createMaterial();
	createLight();

	effect->shader()->enable(vl::EN_DEPTH_TEST);
	effect->shader()->enable(vl::EN_BLEND);
	effect->shader()->enable(vl::EN_POINT_SMOOTH);
	effect->shader()->enable(vl::EN_LINE_SMOOTH);
	effect->shader()->enable(vl::EN_POLYGON_SMOOTH);
	effect->shader()->enable(vl::EN_ALPHA_TEST);
	effect->shader()->enable(vl::EN_CULL_FACE);
	effect->shader()->enable(vl::EN_LIGHTING);

	effect->shader()->setRenderState( material.get() );
	effect->shader()->setRenderState( light.get() );

	// check shading language version
	if (GLEW_ARB_shading_language_100 || GLEW_VERSION_3_0)
	{
		vl::ref<vl::GLSLProgram> modelGlsl;

		// check geometry shaders support
		if (GLEW_Has_Geometry_Shader)
		{
			modelGlsl = effect->shader()->gocGLSLProgram();

			const float* color_r = &colorR;
			const float* color_g = &colorG;
			const float* color_b = &colorB;
			const float* color_a = &colorA;

			uniR->setName("color_r");
			uniR->setUniform1f(1, color_r); 
			uniG->setName("color_g");
			uniG->setUniform1f(1, color_g); 
			uniB->setName("color_b");
			uniB->setUniform1f(1, color_b); 
			uniA->setName("color_a");
			uniA->setUniform1f(1, color_a); 
		
			modelGlsl->setUniform(uniR);
			modelGlsl->setUniform(uniG);
			modelGlsl->setUniform(uniB);
			modelGlsl->setUniform(uniA);

			modelGlsl->attachShader( new vl::GLSLVertexShader("shaders/hair.vs") );
			//modelGlsl->attachShader( new vl::GLSLFragmentShader("shaders/hair.fs") );
			modelGlsl->attachShader( new vl::GLSLGeometryShader("shaders/hair.gs") );

			modelGlsl->setGeometryInputType(vl::GIT_TRIANGLES);
			modelGlsl->setGeometryOutputType(vl::GOT_TRIANGLE_STRIP);
			modelGlsl->setGeometryVerticesOut(3*10); 
		}
		else
		{
			vl::Log::print("GL_NV_geometry_shader4 not supported.\n");
		}
	}
}

void HairEffect::createMaterial()
{
	material = new vl::Material; 
	material->setColorMaterialEnabled(true);
}

void HairEffect::createLight()
{
	light = new vl::Light(0); 
}