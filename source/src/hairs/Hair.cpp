/*!
* Hair.cpp
* Project Hair simulation and visualization using GPU
*/
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

void Hair::createHair(vl::RenderingAbstract *pRendering, unsigned int pHairInterpolationPointsNumber, vl::ref<vl::Effect>* pEffect)
{		
	vertArray = new vl::ArrayFloat3;
	rendering = pRendering;
	effect = pEffect;

	createTransform();

	interpolationPoints = core->computeInterpolationPoints(&controlPoints, pHairInterpolationPointsNumber);
	computeFinalPoints();

	geometry = new vl::Geometry;
	geometry->setDisplayListEnabled(false);

	geometry->setVertexArray(vertArray.get());
	*vertArray = finalPoints;
	geometry->computeNormals();
	geometry->drawCalls()->push_back(new vl::DrawArrays(vl::PT_TRIANGLE_STRIP, 0, (int)vertArray->size()));

	actor = new vl::Actor(geometry.get(), effect->get(), transform.get());
}

void Hair::computeFinalPoints()
{
	// for every interpolation point we create three points (triangle)
	finalPoints = core->computeFinalPoints(&interpolationPoints, width);
}

void Hair::repaintHair()
{
	*vertArray = finalPoints;
	geometry->updateVBOs();
}

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