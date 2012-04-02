#include "HairEffect.hpp"

using namespace vl;
using namespace std;

HairEffect::HairEffect()
{
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
			modelGlsl->attachShader( new vl::GLSLVertexShader("shaders/hair.vs") );
			//modelGlsl->attachShader( new vl::GLSLFragmentShader("shaders/hair.fs") );
			modelGlsl->attachShader( new vl::GLSLGeometryShader("shaders/hair.gs") );
			modelGlsl->setGeometryInputType(vl::GIT_TRIANGLES);
			modelGlsl->setGeometryOutputType(vl::GOT_TRIANGLE_STRIP);
			modelGlsl->setGeometryVerticesOut(3*3); //
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
	//material->setColorMaterial(vl::PF_FRONT_AND_BACK, vl::CM_AMBIENT);
	//material->setFlatColor(vl::gold); // hlavna farba
	///material->setShininess(0.9f);
	///material->setTransparency(0.7f); // priehladnost - musi byt nastavena az po vybere farby aby fungovala
}

void HairEffect::createLight()
{
	light = new vl::Light(0); 
	//light->setDiffuse(vl::yellow);
	//light->setPosition(vl::fvec4(0, 0, 0, 1)); 
    //light->setConstantAttenuation(1.0f);
    ///light->setLinearAttenuation(1.0f);
    ///light->setQuadraticAttenuation(1.0f);
	///light->followTransform(NULL); // sleduje kameru
	//light->setAmbient(fvec4(0.0f, 0.0f, 0.0f, 1.0f));
}