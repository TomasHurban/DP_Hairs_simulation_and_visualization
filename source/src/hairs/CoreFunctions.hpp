/*!
* CoreFunctions.hpp
* Project Hair simulation and visualization using GPU
*/
#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/Text.hpp>
#include <vlGraphics/FontManager.hpp>
#include <vlCore/CatmullRomInterpolator.hpp>
#include <vlCore/LinearInterpolator.hpp>
#include <vlGraphics/Extrusion.hpp>
#include <QtGlobal>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <math.h>
#include <time.h>
#include <fstream>

#include "Settings.hpp"

/**
* \class	CoreFunctions
* \brief	Core functions
* \author	Tomas Hurban
* \date		24.07.2011
*/
class CoreFunctions
{
	public:
		/**
		* \fn		public constructor CoreFunctions()
		* \brief	Constructor
		*/
		CoreFunctions();

		/**
		* \fn		public destructor ~CoreFunctions()
		* \brief	Destructor
		*/
		~CoreFunctions();

		/**
		* \fn		public std::list<vl::fvec3> getStartingPositions(qlonglong pNumberOfPositions, vl::fvec3 *pSphereCenterPosition, float pRadius, vl::fvec3 *pPlanePoint)
		* \brief	Computes random hair starting points positions on the part of a sphere surface
		* \param	pNumberOfPositions		number of positions to be return
		* \param	pSphereCenterPosition	position of a sphere center
		* \param	pRadius					radius of a sphere
		* \param	pPlanePoint				position of a point of plane which cut the sphere on radius line
		* \return	std::list<vl::fvec3>	list of hairs starting positions
		*/
		std::list<vl::fvec3> getStartingPositions(qlonglong pNumberOfPositions, vl::fvec3 *pSphereCenterPosition, float pRadius, vl::fvec3 *pPlanePoint);

		std::list<vl::fvec3> getStartingPositions(std::string pFileName);

		std::list<vl::fvec3> getStartingPositions(std::map<std::list<vl::fvec3>, unsigned int> pArea, bool pStartingPositionsInCorners);

		/**
		* \fn		public float computeDistance(vl::fvec3 *pStartPosition, vl::fvec3 *pEndPosition)
		* \brief	Computes distance from one point to another
		* \param	pStartPosition	position of start point
		* \param	pEndPosition	position of end point
		* \return	float			distance between two points
		*/
		float computeDistance(vl::fvec3 *pStartPosition, vl::fvec3 *pEndPosition);

		/**
		* \fn		public float computeDistance(float x1, float y1, float x2, float y2)
		* \brief	Computes distance from one point to another
		* \param	x1		x position of first point 
		* \param	y1		y position of first point 
		* \param	x2		x position of second point 
		* \param	y2		y position of second point 
		* \return	float	distance between two points
		*/
		float computeDistance(float x1, float y1, float x2, float y2);

		/**
		* \fn		public float computeDistance(float x1, float x2)
		* \brief	Computes distance from one point to another
		* \param	x1		x position of first point 
		* \param	x2		x position of second point 
		* \return	float	distance between two points
		*/
		float computeDistance(float x1, float x2);

		/**
		* \fn		public vl::fvec3 *getDirection(vl::fvec3 *pStartPoint, vl::fvec3 *pEndPoint)
		* \brief	Get direction from start point to end point
		* \param	pStartPoint		position of start point 
		* \param	pEndPoint		position of end point 
		* \return	vl::fvec3*		direction from one point to second
		*/
		vl::fvec3 *getDirection(vl::fvec3 *pStartPoint, vl::fvec3 *pEndPoint);

		// comm TODO
		Settings *loadSettings(std::string pFileName);

		// comm TODO
		bool saveSettings(Settings *pSettings);

		// comm TODO
		qlonglong getHairID();

		// comm TODO
		void resetIDCounter();

		/**
		* \fn		std::vector<vl::fvec3> *computeInterpolationPoints(std::vector<vl::fvec3> *pControlPoints, int pNewPointsNumber)
		* \brief	Compute interpolation points from control points given as parameter using Catmull-Rom interpolation method
		* \param	pControlPoints				control points 
		* \param	pNewPointsNumber			number of created interpolation points 
		* \return	std::vector<vl::fvec3>*		interpolated points
		*/
		std::vector<vl::fvec3> computeInterpolationPoints(std::vector<vl::fvec3> *pControlPoints, int pNewPointsNumber);

	protected:
		/**
		* \fn		public std::set<vl::fvec3> getRandomPositions(qlonglong pNumberOfPositions, float pRadius)
		* \brief	Computes random positions on top of sphere
		* \param	pNumberOfPositions		number of positions to be return
		* \param	pRadius					radius of a circle
		* \return	std::list<vl::fvec3>	list of random positions in circle
		*/
		std::set<vl::fvec3> getRandomPositions(qlonglong pNumberOfPositions, float pRadius);

		// TODO comm
		vl::fvec3 getRandomCirclePosition(float pPointAMin, float pPointAMax, float pPointBMin, float pPointBMax, float pRadius);

		/**
		* \fn		public float getRandomNumber(float min, float max)
		* \brief	Computes random number in range
		* \param	min		minimum number range
		* \param	max		maximum number range
		* \return	float	random number
		*/
		float getRandomNumber(float min, float max);

		vl::fvec3 getNewPointPosition(vl::fvec3 pPoint1, vl::fvec3 pPoint2, float pValueX);

		float getMin(float value1, float value2, float value3);

		float getMin(float value1, float value2);

		float getMax(float value1, float value2, float value3);

		float getMax(float value1, float value2);

		// comm TODO
		qlonglong hairID;
};

#endif
