#include "Hair.hpp"

using namespace vl;
using namespace std;

Hair::Hair(unsigned int pId, float pLength, float pWidth, int pNumberOfElements, vl::fvec4 *pColor, vl::fvec3 *pStartPosition, vl::fvec3 *pDirection, int pType, int pControlPointsDistributionType, float pControlPointsDistributionType3Multiplier)
{
	core = new CoreFunctions();

	id = pId;
	length = pLength;
	width = pWidth;
	numberOfElements = pNumberOfElements;
	color = pColor;
	startPosition = pStartPosition;
	direction = pDirection;
	type = pType;
	controlPointsDistributionType = pControlPointsDistributionType;
	controlPointsDistributionType3Multiplier = pControlPointsDistributionType3Multiplier;

	computeControlPoints();
}

Hair::~Hair()
{

}

void Hair::computeControlPoints()
{
	float lengthOfPart;
	controlPoints.clear();
	float x = startPosition->x();
	float y = startPosition->y();
	float z = startPosition->z();
	
	controlPoints.push_back(vl::fvec3(x, y, z));

	// type 1: uniform distribution of control points
	// type 2: gradually increasing the distance between points (arithmetically)
	// type 3: gradually increasing the distance between points (geometrically - based on controlPointsDistributionType3Multiplier variable value)
	if (controlPointsDistributionType == 1)
	{
		lengthOfPart = length / numberOfElements;

		for (int i=0; i<numberOfElements; i++)
		{
			x += direction->x() * lengthOfPart;
			y += direction->y() * lengthOfPart;
			z += direction->z() * lengthOfPart;

			controlPoints.push_back(vl::fvec3(x, y, z));
		}
	}
	else if (controlPointsDistributionType == 2)
	{
		float averageLengthOfPart = length / numberOfElements;
		float step = averageLengthOfPart / numberOfElements;

		// even number of hair parts
		if ((numberOfElements % 2) == 0)
		{
			lengthOfPart = averageLengthOfPart - ((numberOfElements / 2) * step);

			for (int i=0; i<numberOfElements; i++)
			{
				if (i == (numberOfElements / 2))
				{
					lengthOfPart += step;
				}

				x += direction->x() * lengthOfPart;
				y += direction->y() * lengthOfPart;
				z += direction->z() * lengthOfPart;

				controlPoints.push_back(vl::fvec3(x, y, z));
				
				lengthOfPart += step;
			}
		}
		else 
		{
			lengthOfPart = averageLengthOfPart - (((numberOfElements / 2) + 1) * step);

			for (int i=0; i<numberOfElements; i++)
			{
				x += direction->x() * lengthOfPart;
				y += direction->y() * lengthOfPart;
				z += direction->z() * lengthOfPart;

				controlPoints.push_back(vl::fvec3(x, y, z));
				
				lengthOfPart += step;
			}
		}
	}
	else if (controlPointsDistributionType == 3)
	{
		float multipliesSum = 0;
		float M = controlPointsDistributionType3Multiplier;

		for (int i=0; i<(numberOfElements - 1); i++)
		{
			multipliesSum += M;
			M = M * controlPointsDistributionType3Multiplier;
		}

		lengthOfPart = length / (1 + multipliesSum);

		for (int i=0; i<numberOfElements; i++)
		{
			x += direction->x() * lengthOfPart;
			y += direction->y() * lengthOfPart;
			z += direction->z() * lengthOfPart;

			controlPoints.push_back(vl::fvec3(x, y, z));

			lengthOfPart *= controlPointsDistributionType3Multiplier;
		}
	}
}

void Hair::createHair(vl::RenderingAbstract *pRendering, unsigned int pHairInterpolatedPointsNumber)
{		
	vertArray = new vl::ArrayFloat3;
	rendering = pRendering;

	createMaterial();
	createLight();
	// to create effect we must have material and light created first
	createEffect();
	createTransform();

	interpolatedPoints = core->computeInterpolatedPoints(&controlPoints, pHairInterpolatedPointsNumber);

	geometry = new vl::Geometry;
	geometry->setVertexArray(vertArray.get());
	*vertArray = interpolatedPoints;
	geometry->computeNormals();
	geometry->drawCalls()->push_back(new vl::DrawArrays(vl::PT_LINE_STRIP, 0, (int)vertArray->size()));

	actor = new vl::Actor(geometry.get(), effect.get(), transform.get());
}

void Hair::repaintHair()
{
	*vertArray = interpolatedPoints;
	geometry->updateVBOs();
}

// TODO
void Hair::createMaterial()
{
	material = new vl::Material; 
	material->setColorMaterialEnabled(true);
	//material->setColorMaterial(vl::PF_FRONT_AND_BACK, vl::CM_AMBIENT); // vyblednute vlasy
	//material->setFlatColor(vl::gold); // hlavna farba
	material->setShininess(0.9f);
	material->setTransparency(0.7f); // priehladnost - musi byt nastavena az po vybere farby aby fungovala
}

// TODO
void Hair::createLight()
{
	// priklad 13 - Create_App_Lights
	light = new vl::Light(0); 
	//light->setDiffuse(vl::yellow);
	//light->setPosition(vl::fvec4(0, 0, 0, 1)); 
    //light->setConstantAttenuation(1.0f);
    light->setLinearAttenuation(1.0f);
    light->setQuadraticAttenuation(1.0f);
	light->followTransform(NULL); // sleduje kameru
	//light->setAmbient(fvec4(0.0f, 0.0f, 0.0f, 1.0f));
}

// TODO
void Hair::createTransform()
{
	transform = new vl::Transform;

    /* shows how to use Transforms if they don't need to be dynamically
       animated: first of all you don't put them in the rendering()->as<vl::Rendering>()->transform()'s
       hierarchy like the other transforms; secondly you have to manually call
       computeWorldMatrix()/computeWorldMatrixRecursive() to compute
       the final matrix used for the rendering. This way the rendering pipeline
       won't call computeWorldMatrix()/computeWorldMatrixRecursive()
       continuously for the Transforms we know are not going to change over time,
       thus saving precious time. */

	// zrychlenie o cca 25 FPS ak nepridavame do rendering - example 10 Create_App_Transforms
	// riadok "rendering->as<vl::Rendering>()->transform()->addChild(transform.get());" nahradime "transform->computeWorldMatrix(NULL);"
	//rendering->as<vl::Rendering>()->transform()->addChild(transform.get());
	transform->computeWorldMatrix(NULL);
}

// TODO
void Hair::createEffect()
{
	effect = new vl::Effect;
	effect->shader()->enable(vl::EN_DEPTH_TEST);
	effect->shader()->enable(vl::EN_BLEND);
	effect->shader()->enable(vl::EN_POINT_SMOOTH);
	effect->shader()->enable(vl::EN_LINE_SMOOTH);
	effect->shader()->enable(vl::EN_POLYGON_SMOOTH);
	effect->shader()->enable(vl::EN_ALPHA_TEST);
	effect->shader()->enable(vl::EN_CULL_FACE);
	effect->shader()->enable(vl::EN_LIGHTING);
	//effect->shader()->gocMaterial()->setDiffuse( vl::gold );
	//effect->shader()->gocMaterial()->setAmbient( vl::yellow );
	///effect->shader()->gocMaterial()->setSpecular( vl::lightgray );
	///effect->shader()->gocMaterial()->setShininess( 600 );
	///effect->shader()->gocLightModel()->setTwoSide(true);
	effect->shader()->gocLineWidth()->set(width); // hair width

	effect->shader()->setRenderState( material.get() );
	effect->shader()->setRenderState( light.get() );

	// check shading language version
	if (GLEW_ARB_shading_language_100 || GLEW_VERSION_3_0)
	{
		vl::ref<vl::GLSLProgram> modelGlsl;

		// check geometry shaders support
		if (GLEW_Has_Geometry_Shader)
		{
			/*modelGlsl = effect->shader()->gocGLSLProgram();
			// a vertex shader is always needed when using geometry shaders
			modelGlsl->attachShader( new vl::GLSLVertexShader("/diffuse.vs") );
			modelGlsl->attachShader( new vl::GLSLGeometryShader("/triangle_fur.gs") );
			modelGlsl->setGeometryInputType(vl::GIT_TRIANGLES);
			modelGlsl->setGeometryOutputType(vl::GOT_TRIANGLE_STRIP);
			modelGlsl->setGeometryVerticesOut( 3*6 );*/
		}
		else
		{
			effect->shader()->gocMaterial()->setDiffuse(vl::red);
			vl::Log::print("GL_NV_geometry_shader4 not supported.\n");
		}
	}
}