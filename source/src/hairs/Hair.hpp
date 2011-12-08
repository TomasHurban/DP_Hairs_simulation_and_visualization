/*!
* Hair.hpp
* Project Hair simulation and visualization using GPU
*/
#ifndef HAIR_H
#define HAIR_H

#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlGraphics/GLSL.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/Text.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vector>
#include <QtGlobal>
#include <iostream>

#include "CoreFunctions.hpp"

/**
* \class	Hair
* \brief	Hair object representation
* \author	Tomas Hurban
* \date		13.07.2011
*/
class Hair
{
	public:
		/**
		* \fn		public constructor Hair(unsigned int pId, float pLength, float pWidth, int pNumberOfElements, vl::fvec4 *pColor, vl::fvec3 *pStartPosition, vl::fvec3 *pDirection, int pType)
		* \brief	Creates new hair object
		* \param	pId											hair ID
		* \param	pLength										length of hair
		* \param	pWidth										width of hair
		* \param	pNumberOfElements							number of elements in one hair
		* \param	pColor										basic color of hair
		* \param	pStartPosition								starting position of hair
		* \param	pDirection									direction of next hair control points from start point
		* \param	pType										type of hair
		* \param	pControlPointsDistributionType				type of control points distribution in hair
		* \param	pControlPointsDistributionType3Multiplier	type of control points distribution in hair
		*/
		Hair(unsigned int pId, float pLength, float pWidth, int pNumberOfElements, vl::fvec4 *pColor, vl::fvec3 *pStartPosition, vl::fvec3 *pDirection, int pType, int pControlPointsDistributionType, float pControlPointsDistributionType3Multiplier);

		/**
		* \fn		public destructor Hair()
		* \brief	Destructor
		*/
		~Hair();

		/**
		* \fn		public void createHair(vl::RenderingAbstract *pRendering, unsigned int pHairInterpolatedPointsNumber)
		* \brief	Create hair object
		* \param	pRendering							rendering
		* \param	pHairInterpolatedPointsNumber		number of hair interpolated points
		*/
		void createHair(vl::RenderingAbstract *pRendering, unsigned int pHairInterpolatedPointsNumber);

		/**
		* \fn		public void repaintHair()
		* \brief	Repaint hair geometry
		*/
		void repaintHair();

		/**
		* \fn		public vl::Actor *getHair(vl::RenderingAbstract *pRendering)
		* \brief	Return hair object
		* \return	vl::Actor*		hair object
		*/
		vl::ref<vl::Actor> *getHair() { return &actor; };

		/**
		* \fn		public std::vector<vl::fvec3> *getControlPoints()
		* \brief	Return hair control points
		* \return	std::vector<vl::fvec3>*		hair control points
		*/
		std::vector<vl::fvec3> *getControlPoints() { return &controlPoints; };

		/**
		* \fn		public void setControlPoints(std::vector<vl::fvec3> *pControlPoints)
		* \brief	Set hair control points
		* \param	pControlPoints			control points
		*/
		void setControlPoints(std::vector<vl::fvec3> *pControlPoints) { controlPoints = *pControlPoints; };

		/**
		* \fn		public std::vector<vl::fvec3> *getInterpolationPoints()
		* \brief	Return hair interpolation points
		* \return	std::vector<vl::fvec3>*		hair interpolation points
		*/
		std::vector<vl::fvec3> *getInterpolationPoints() { return &interpolationPoints; };

		/**
		* \fn		public void setInterpolationPoints(std::vector<vl::fvec3> *pInterpolationPoints)
		* \brief	Set hair interpolation points
		* \param	pInterpolationPoints		interpolation points
		*/
		void setInterpolationPoints(std::vector<vl::fvec3> *pInterpolationPoints) { interpolationPoints = *pInterpolationPoints; };

		vl::Effect *getEffect();
		void setEffect(vl::Effect);
		vl::Geometry *getGeometry();
		void setGeometry(vl::Geometry);
		vl::Light *getLight();
		void setLight(vl::Light);
		vl::Material *getMaterial();
		void setMaterial(vl::Material);
		vl::Transform *getTransform();
		void setTransform(vl::Transform);

		int getNumberOfElements() { return numberOfElements; }
		void setNumberOfElements(int pNumberOfElements) { numberOfElements = pNumberOfElements; }

		unsigned int getId() { return id; }

	protected:

		void computeControlPoints();

		/**
		* \fn		protected void createMaterial()
		* \brief	Create material for hair
		*/
		void createMaterial();

		/**
		* \fn		protected void createLight()
		* \brief	Create light for hair
		*/
		void createLight();

		/**
		* \fn		protected void createTransform()
		* \brief	Create transform for hair
		*/
		void createTransform();

		/**
		* \fn		protected void createEffect()
		* \brief	Create effect for hair
		*/
		void createEffect();

		/**
		* vl::ref<vl::Actor> actor
		* \brief	Hair object representation
		*/
		vl::ref<vl::Actor> actor;

		/**
		* vl::fvec4 *color
		* \brief	Color of hair
		*/
		vl::fvec4 *color;

		/**
		* std::vector<vl::fvec3> controlPoints
		* \brief	Vector of hair control points 
		*/
		std::vector<vl::fvec3> controlPoints;

		/**
		* std::vector<vl::fvec3> interpolationPoints
		* \brief	Vector of hair interpolation control points 
		*/
		std::vector<vl::fvec3> interpolationPoints;

		/**
		* vl::fvec3 *direction
		* \brief	Direction of next hair control points from start point
		*/
		vl::fvec3 *direction;

		/**
		* vl::ref<vl::Effect> effect
		* \brief	Hair effect
		*/
		vl::ref<vl::Effect> effect;

		/**
		* vl::ref<vl::Geometry> geometry
		* \brief	Hair geometry
		*/
		vl::ref<vl::Geometry> geometry;

		/**
		* unsigned int id
		* \brief	Hair ID
		*/
		unsigned int id;

		/**
		* float length
		* \brief	Length of hair string
		*/
		float length;

		/**
		* vl::ref<vl::Light> light
		* \brief	Hair light
		*/
		vl::ref<vl::Light> light;

		/**
		* vl::ref<vl::Material> materialHair
		* \brief	Hair material
		*/
		vl::ref<vl::Material> material;

		/**
		* int numberOfElements
		* \brief	Number of elements in one hair string
		*/
		int numberOfElements;

		/**
		* vl::RenderingAbstract *rendering
		* \brief	Rendering
		*/
		vl::RenderingAbstract *rendering;

		/**
		* vl::fvec3 *startPosition
		* \brief	Starting position of hair
		*/
		vl::fvec3 *startPosition;

		/**
		* vl::ref<vl::Transform> transform
		* \brief	Hair transform
		*/
		vl::ref<vl::Transform> transform;

		/**
		* int type
		* \brief	Type of hair string (stright, curly, ...)
		*/
		int type;

		/**
		* int controlPointsDistributionType
		* \brief	Type of control points distribution in hair
		*/
		int controlPointsDistributionType;

		/**
		* float controlPointsDistributionType3Multiplier
		* \brief	Multiplier of control points distribution type 3
		*/
		float controlPointsDistributionType3Multiplier;

		/**
		* float width
		* \brief	Width of hair string
		*/
		float width;

		vl::ref<vl::ArrayFloat3> vertArray;

		CoreFunctions *core;
};

#endif
