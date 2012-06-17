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
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GLSL.hpp>

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
		* \fn		public constructor Hair(unsigned int pId, float pLength, float pWidth, int pNumberOfElements, vl::fvec4 *pColor, vl::fvec3 *pStartPosition, vl::fvec3 *pDirection, int pType, int pControlPointsDistributionType, float pControlPointsDistributionType3Multiplier)
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
		* \param	pControlPointsDistributionType3Multiplier	start value for control points distribution type 3
		*/
		Hair(unsigned int pId, float pLength, float pWidth, int pNumberOfElements, vl::fvec4 *pColor, vl::fvec3 *pStartPosition, vl::fvec3 *pDirection, int pType, int pControlPointsDistributionType, float pControlPointsDistributionType3Multiplier);

		/**
		* \fn		public destructor Hair()
		* \brief	Destructor
		*/
		~Hair();

		/**
		* \fn		public void createHair(vl::RenderingAbstract *pRendering, unsigned int pHairInterpolatedPointsNumber, vl::ref<vl::Effect>* pEffect)
		* \brief	Create hair object
		* \param	pRendering							actual rendering
		* \param	pHairInterpolatedPointsNumber		number of hair interpolated points
		* \param	pEffect								default hair effect
		*/
		void createHair(vl::RenderingAbstract* pRendering, unsigned int pHairInterpolatedPointsNumber, vl::ref<vl::Effect>* pEffect);

		/**
		* \fn		public void repaintHair()
		* \brief	Repaint hair geometry
		*/
		void repaintHair();

		/**
		* \fn		public vl::ref<vl::Actor>* getHair()
		* \brief	Return hair object
		* \return	vl::ref<vl::Actor>*		hair object
		*/
		vl::ref<vl::Actor>* getHair() { return &actor; };

		/**
		* \fn		public std::vector<vl::fvec3>* getControlPoints()
		* \brief	Return hair control points
		* \return	std::vector<vl::fvec3>*		hair control points vector
		*/
		std::vector<vl::fvec3>* getControlPoints() { return &controlPoints; };

		/**
		* \fn		public void setControlPoints(std::vector<vl::fvec3>* pControlPoints)
		* \brief	Set new hair control points
		* \param	pControlPoints			new hair control points
		*/
		void setControlPoints(std::vector<vl::fvec3>* pControlPoints) { controlPoints = *pControlPoints; };

		/**
		* \fn		public std::vector<vl::fvec3>* getInterpolationPoints()
		* \brief	Return hair interpolation points
		* \return	std::vector<vl::fvec3>*		hair interpolation points
		*/
		std::vector<vl::fvec3>* getInterpolationPoints() { return &interpolationPoints; };

		/**
		* \fn		public void setInterpolationPoints(std::vector<vl::fvec3>* pInterpolationPoints)
		* \brief	Set new hair interpolation points
		* \param	pInterpolationPoints		new interpolation points
		*/
		void setInterpolationPoints(std::vector<vl::fvec3>* pInterpolationPoints) { interpolationPoints = *pInterpolationPoints; };

		/**
		* \fn		public std::vector<vl::fvec3>* getFinalPoints()
		* \brief	Return hair final points
		* \return	std::vector<vl::fvec3>*		hair final points
		*/
		std::vector<vl::fvec3>* getFinalPoints() { return &finalPoints; };

		/**
		* \fn		public void setFinalPoints(std::vector<vl::fvec3>* pFinalPoints)
		* \brief	Set new hair final points
		* \param	pFinalPoints		new final points
		*/
		void setFinalPoints(std::vector<vl::fvec3>* pFinalPoints) { finalPoints = *pFinalPoints; };

		/**
		* \fn		public int getNumberOfElements()
		* \brief	Return number of hair elements
		* \return	int			number of hair elements
		*/
		int getNumberOfElements() { return numberOfElements; }

		/**
		* \fn		public void setNumberOfElements(int pNumberOfElements)
		* \brief	Set number of hair elements
		* \param	pNumberOfElements				number of hair elements
		*/
		void setNumberOfElements(int pNumberOfElements) { numberOfElements = pNumberOfElements; }

		/**
		* \fn		public unsigned int getId()
		* \brief	Return hair ID
		* \return	unsigned int		hair ID
		*/
		unsigned int getId() { return id; }

		/**
		* \fn		public void computeFinalPoints()
		* \brief	Compute hair final points
		*/
		void computeFinalPoints();

	protected:
		/**
		* \fn		protected void computeControlPoints()
		* \brief	Compute hair control  points
		*/
		void computeControlPoints();

		/**
		* \fn		protected void createTransform()
		* \brief	Create transform for hair
		*/
		void createTransform();

		/**
		* vl::ref<vl::Actor> actor
		* \brief	Hair object representation
		*/
		vl::ref<vl::Actor> actor;

		/**
		* vl::fvec4* color
		* \brief	Color of hair
		*/
		vl::fvec4* color;

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
		* std::vector<vl::fvec3> finalPoints
		* \brief	Vector of hair final points 
		*/
		std::vector<vl::fvec3> finalPoints;

		/**
		* vl::fvec3* direction
		* \brief	Direction of next hair control points from start point
		*/
		vl::fvec3* direction;

		/**
		* vl::ref<vl::Effect>* effect
		* \brief	Hair effect
		*/
		vl::ref<vl::Effect>* effect;

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
		* \brief	Width of hair model
		*/
		float width;

		/**
		* vl::ref<vl::ArrayFloat3> vertArray
		* \brief	Hair model vertex array
		*/
		vl::ref<vl::ArrayFloat3> vertArray;

		/**
		* CoreFunctions* core
		* \brief	CoreFunctions class instance
		*/
		CoreFunctions* core;
};

#endif
