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

		/**
		* \fn		public std::list<vl::fvec3> getStartingPositions(std::string pFileName)
		* \brief	Get hair starting points positions from file
		* \param	pFileName				file name
		* \return	std::list<vl::fvec3>	list of hairs starting positions
		*/
		std::list<vl::fvec3> getStartingPositions(std::string pFileName);

		/**
		* \fn		public std::list<vl::fvec3> getStartingPositions(std::map<std::list<vl::fvec3>, unsigned int> pArea, bool pStartingPositionsInCorners)
		* \brief	Computes random hair starting points positions on defined area
		* \param	pArea						area defined by triangles with number of start positions on each area
		* \param	pStartingPositionsInCorners	if true, start positions will be generated at corner points too
		* \return	std::list<vl::fvec3>		list of hairs starting positions
		*/
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

		/**
		* \fn		public Settings* loadSettings(std::string pFileName)
		* \brief	Load settings for hair model from file
		* \param	pFileName		settings file name 
		* \return	Settings*		settings loaded from file
		*/
		Settings* loadSettings(std::string pFileName);

		/**
		* \fn		public bool saveSettings(Settings *pSettings)
		* \brief	! NOT IMPLEMENTED YET! Save settings for hair model to file
		* \param	pSettings		settings to be saved 
		* \return	bool			true if error occured, else false
		*/
		bool saveSettings(Settings* pSettings);

		/**
		* \fn		public qlonglong getHairID()
		* \brief	Return next hair ID
		* \return	qlonglong		hair ID
		*/
		qlonglong getHairID();

		/**
		* \fn		public void resetIDCounter()
		* \brief	Function reset hair ID counter
		*/
		void resetIDCounter();

		/**
		* \fn		std::vector<vl::fvec3> *computeInterpolationPoints(std::vector<vl::fvec3> *pControlPoints, int pNewPointsNumber)
		* \brief	Compute interpolation points from control points given as parameter using Catmull-Rom interpolation method
		* \param	pControlPoints				control points 
		* \param	pNewPointsNumber			number of created interpolation points 
		* \return	std::vector<vl::fvec3>*		interpolated points
		*/
		std::vector<vl::fvec3> computeInterpolationPoints(std::vector<vl::fvec3> *pControlPoints, int pNewPointsNumber);
	
		/**
		* \fn		std::vector<vl::fvec3> computeFinalPoints(std::vector<vl::fvec3> *pInterpolationPoints, float pWidth)
		* \brief	Compute final hair points from interpolation points
		* \param	pInterpolationPoints		interpolation points 
		* \param	pWidth						hair width 
		* \return	std::vector<vl::fvec3>		final hair points
		*/
		std::vector<vl::fvec3> computeFinalPoints(std::vector<vl::fvec3> *pInterpolationPoints, float pWidth);

	protected:
		/**
		* \fn		protected std::set<vl::fvec3> getRandomPositions(qlonglong pNumberOfPositions, float pRadius)
		* \brief	Computes random positions on top of sphere
		* \param	pNumberOfPositions		number of positions to be return
		* \param	pRadius					radius of a circle
		* \return	std::list<vl::fvec3>	list of random positions in circle
		*/
		std::set<vl::fvec3> getRandomPositions(qlonglong pNumberOfPositions, float pRadius);

		/**
		* \fn		protected vl::fvec3 getRandomCirclePosition(float pPointAMin, float pPointAMax, float pPointBMin, float pPointBMax, float pRadius)
		* \brief	Computes random position on defined circle area
		* \param	pPointAMin		point 1 minimum value 
		* \param	pPointAMax		point 1 maximum value
		* \param	pPointBMin		point 2 minimum value
		* \param	pPointBMax		point 2 maximum value
		* \param	pRadius			radius of a circle
		* \return	std::list<vl::fvec3>	list of random positions in circle
		*/
		vl::fvec3 getRandomCirclePosition(float pPointAMin, float pPointAMax, float pPointBMin, float pPointBMax, float pRadius);

		/**
		* \fn		protected float getRandomNumber(float min, float max)
		* \brief	Computes random number in range
		* \param	min		minimum number range
		* \param	max		maximum number range
		* \return	float	random number
		*/
		float getRandomNumber(float min, float max);

		/**
		* \fn		protected vl::fvec3 getNewPointPosition(vl::fvec3 pPoint1, vl::fvec3 pPoint2, float pValueX)
		* \brief	Computes new position
		* \param	pPoint1		first poitn position
		* \param	pPoint2		second point position
		* \param	pValueX		position on the x axis 
		* \return	vl::fvec3	position of new point
		*/
		vl::fvec3 getNewPointPosition(vl::fvec3 pPoint1, vl::fvec3 pPoint2, float pValueX);

		/**
		* \fn		protected float getMin(float value1, float value2, float value3)
		* \brief	Return minimum value
		* \param	value1		value 1
		* \param	value2		value 2
		* \param	value3		value 3
		* \return	float		minimum value
		*/
		float getMin(float value1, float value2, float value3);

		/**
		* \fn		protected float getMin(float value1, float value2)
		* \brief	Return minimum value
		* \param	value1		value 1
		* \param	value2		value 2
		* \return	float		minimum value
		*/
		float getMin(float value1, float value2);

		/**
		* \fn		protected float getMax(float value1, float value2, float value3)
		* \brief	Return maximum value
		* \param	value1		value 1
		* \param	value2		value 2
		* \param	value3		value 3
		* \return	float		maximum value
		*/
		float getMax(float value1, float value2, float value3);

		/**
		* \fn		protected float getMax(float value1, float value2)
		* \brief	Return maximum value
		* \param	value1		value 1
		* \param	value2		value 2
		* \return	float		maximum value
		*/
		float getMax(float value1, float value2);

		/**
		* \fn		protected qlonglong hairID
		* \brief	Hair ID counter
		*/
		qlonglong hairID;
};

#endif
