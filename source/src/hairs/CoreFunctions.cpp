#include "CoreFunctions.hpp"

using namespace vl;
using namespace std;

CoreFunctions::CoreFunctions()
{
	hairID = 0;
}

CoreFunctions::~CoreFunctions()
{

}

std::list<vl::fvec3> CoreFunctions::getStartingPositions(qlonglong pNumberOfPositions, vl::fvec3 *pSphereCenterPosition, float pRadius, vl::fvec3 *pPlanePoint)
{
	std::list<vl::fvec3> positions;
	float surfaceAreaSize; // Size of area where hairs can be placed
	float baseDiameter; // Length of diameter of sphere part base
	float baseRadius; // Length of radius of sphere part base
	float baseAreaSize; // Size of base area
	const float pi = 3.14f; // PI value
	float distance; // Distance from Sphere center position to Plane point
	float difference; // Difference between length of sphere radius and length of distance variable 
	std::set<vl::fvec3> randPositions; // Random positions in a circle
	std::set<vl::fvec3>::iterator itRandPositions;

	distance = computeDistance(pSphereCenterPosition, pPlanePoint);
	if (distance > pRadius)
	{
		// planePoint is out of sphere !
		return positions;
	}

	difference = pRadius - distance;
	baseRadius = (pRadius * pRadius) - (distance * distance);
	baseRadius = sqrt(baseRadius);
	baseDiameter = 2 * baseRadius;

	baseAreaSize = pi * baseRadius * baseRadius;
	surfaceAreaSize = 2 * pi * pRadius * difference;

	// random positions in circle
	randPositions = getRandomPositions(pNumberOfPositions, baseRadius);

	// now we move them to the top of sphere layout
	for (itRandPositions = randPositions.begin(); itRandPositions != randPositions.end(); itRandPositions++)
	{
		float lengthXZ = computeDistance(0, 0, itRandPositions->x(), itRandPositions->z());
		float lengthY = (pRadius * pRadius) - (lengthXZ * lengthXZ);
		lengthY = sqrt(lengthY);

		// move them acording to the position of sphere center position
		float finalX = pSphereCenterPosition->x() + itRandPositions->x();
		float finalY = pSphereCenterPosition->y() + lengthY;
		float finalZ = pSphereCenterPosition->z() + itRandPositions->z();

		positions.push_back(vl::fvec3(finalX, finalY, finalZ));
	}

	// TODO: posunut body podla otocenia roviny

	return positions;
}

std::list<vl::fvec3> CoreFunctions::getStartingPositions(std::string pFileName)
{
	std::list<vl::fvec3> positions;
	std::string line;
	ifstream file;
	bool error = false;
	float x;
	float y;
	float z;
	std::string position;

	file.open(pFileName.c_str(), ios::in);

	// check if file is open
	if (file.is_open())
	{
		while (file.good())
		{
			int index;

			getline(file, line);
			index = line.find(" ");
			position = line.substr(0, index);
			x = atof(position.c_str());

			line = line.substr(index + 1);
			index = line.find(" ");
			position = line.substr(0, index);
			y = atof(position.c_str());

			position = line.substr(index + 1);
			z = atof(position.c_str());

			positions.push_back(vl::fvec3(x, y, z));
		}
 
		file.close();
	}
	else
	{
		error = true;
		positions.clear();
	}

	return positions;
}

std::list<vl::fvec3> CoreFunctions::getStartingPositions(std::map<std::list<vl::fvec3>, unsigned int> pArea, bool pStartingPositionsInCorners)
{
	std::list<vl::fvec3> positions;
	std::set<vl::fvec3> cornerPositions;
	std::set<vl::fvec3>::iterator itCornerPositions;
	std::map<std::list<vl::fvec3>, unsigned int>::iterator itMap;
	std::list<vl::fvec3> points;
	std::list<vl::fvec3>::iterator itPoints;
	unsigned int number;
	vl::fvec3 point1;
	vl::fvec3 point2;
	vl::fvec3 point3;
	vl::fvec3 newPoint1;
	vl::fvec3 newPoint2;
	float valueX;
	float valueY;
	float valueZ;
	bool error = false;
	
	for (itMap=pArea.begin(); itMap!=pArea.end(); itMap++)
	{
		points = (*itMap).first;
		number = (*itMap).second;

		itPoints=points.begin();
		if (itPoints != points.end())
		{
			point1 = *itPoints;
			itPoints++;
		}
		if (itPoints != points.end())
		{
			point2 = *itPoints;
			itPoints++;
		}
		if (itPoints != points.end())
		{
			point3 = *itPoints;
		}
		else 
		{
			error = true;
			break;
		}

		// check if points are in plane 
		if ((point1 == point2) || (point1 == point3) || (point2 == point3))
		{
			error = true;
			break;
		}

		// we use corners points as starting points too
		if (pStartingPositionsInCorners)
		{
			cornerPositions.insert(point1);
			cornerPositions.insert(point2);
			cornerPositions.insert(point3);
		}

		for (int i=0; i<number; i++)
		{
			float minX = getMin(point1.x(), point2.x(), point3.x());
			float maxX = getMax(point1.x(), point2.x(), point3.x());

			do {
				valueX = getRandomNumber(minX, maxX);
			}
			while ((valueX == point1.x()) || (valueX == point2.x()) || (valueX == point3.x()));

			if ((valueX < point1.x() && valueX < point2.x()) || (valueX > point1.x() && valueX > point2.x()))
			{
				// x is between points 1-3 and 2-3
				newPoint1 = getNewPointPosition(point1, point3, valueX);
				newPoint2 = getNewPointPosition(point2, point3, valueX);
			}
			else if ((valueX < point1.x() && valueX < point3.x()) || (valueX > point1.x() && valueX > point3.x()))
			{
				// x is between points 1-2 and 2-3
				newPoint1 = getNewPointPosition(point1, point2, valueX);
				newPoint2 = getNewPointPosition(point2, point3, valueX);
			}
			else if ((valueX < point2.x() && valueX < point3.x()) || (valueX > point2.x() && valueX > point3.x()))
			{
				// x is between points 1-2 and 1-3
				newPoint1 = getNewPointPosition(point1, point3, valueX);
				newPoint2 = getNewPointPosition(point2, point3, valueX);
			}
			else
			{
				error = true;
				break;
			}

			if (newPoint1.y() > newPoint2.y())
			{
				vl::fvec3 tmpPoint = newPoint1;
				newPoint1 = newPoint2;
				newPoint2 = tmpPoint;
			}

			valueY = getRandomNumber(newPoint1.y(), newPoint2.y());

			float maxDistanceY = computeDistance(newPoint1.y(), newPoint2.y());
			float partDistanceY = computeDistance(newPoint1.y(), valueY);
			float multiplier = partDistanceY / maxDistanceY;

			float maxDistanceZ = computeDistance(newPoint1.z(), newPoint2.z());
			float partDistanceZ = maxDistanceZ * multiplier;

			if (newPoint1.z() < newPoint2.z())
			{
				valueZ = newPoint1.z() + partDistanceZ;
			}
			else 
			{
				valueZ = newPoint1.z() - partDistanceZ;
			}

			positions.push_back(vl::fvec3(valueX, valueY, valueZ));
		}
	}

	for (itCornerPositions=cornerPositions.begin(); itCornerPositions!=cornerPositions.end(); itCornerPositions++)
	{
		positions.push_back(vl::fvec3((*itCornerPositions).x(), (*itCornerPositions).y(), (*itCornerPositions).z()));
	}

	if (error)
	{
		positions.clear();
	}

	return positions;
}

vl::fvec3 CoreFunctions::getNewPointPosition(vl::fvec3 pPoint1, vl::fvec3 pPoint2, float pValueX)
{
	float maxDistance;
	float partDistance;
	float multiplier;
	float valueY;
	float valueZ;
	
	if (pPoint1.x() > pPoint2.x())
	{
		vl::fvec3 tmpPoint = pPoint1;
		pPoint1 = pPoint2;
		pPoint2 = tmpPoint;
	}

	maxDistance = computeDistance(pPoint1.x(), pPoint2.x());
	partDistance = computeDistance(pPoint1.x(), pValueX);
	multiplier = partDistance / maxDistance;

	maxDistance = computeDistance(pPoint1.y(), pPoint2.y());
	partDistance = maxDistance * multiplier;
	if (pPoint1.y() < pPoint2.y())
	{
		valueY = pPoint1.y() + partDistance;
	}
	else 
	{
		valueY = pPoint1.y() - partDistance;
	}

	maxDistance = computeDistance(pPoint1.z(), pPoint2.z());
	partDistance = maxDistance * multiplier;
	if (pPoint1.z() < pPoint2.z())
	{
		valueZ = pPoint1.z() + partDistance;
	}
	else 
	{
		valueZ = pPoint1.z() - partDistance;
	}

	return vl::fvec3(pValueX, valueY, valueZ);
}

float CoreFunctions::getMin(float value1, float value2, float value3)
{
	float min;

	min = value1;

	if (value2 < min)
	{
		min = value2;
	}

	if (value3 < min)
	{
		min = value3;
	}

	return min;
}

float CoreFunctions::getMin(float value1, float value2)
{
	if (value1 < value2)
	{
		return value1;
	}
	else
	{
		return value2;
	}
}

float CoreFunctions::getMax(float value1, float value2, float value3)
{
	float max;

	max = value1;

	if (value2 > max)
	{
		max = value2;
	}

	if (value3 > max)
	{
		max = value3;
	}

	return max;
}

float CoreFunctions::getMax(float value1, float value2)
{
	if (value1 < value2)
	{
		return value2;
	}
	else
	{
		return value1;
	}
}

float CoreFunctions::computeDistance(vl::fvec3 *pStartPosition, vl::fvec3 *pEndPosition)
{
	float distance; // Absolute value of distance between start and end position
	float diffX; // Absolute value of distance between positions x values
	float diffY; // Absolute value of distance between positions y values
	float diffZ; // Absolute value of distance between positions z values
	float distanceXY; // Absolute distance between x and y points of positions

	diffX = pStartPosition->x() - pEndPosition->x();
	diffX = fabs(diffX); // Absolute value
	diffY = pStartPosition->y() - pEndPosition->y();
	diffY = fabs(diffY); 
	diffZ = pStartPosition->z() - pEndPosition->z();
	diffZ = fabs(diffZ); 

	distanceXY = (diffX * diffX) + (diffY * diffY);
	distanceXY = sqrt(distanceXY);

	distance = (distanceXY * distanceXY) + (diffZ * diffZ);
	distance = sqrt(distance);

	return distance;
}

float CoreFunctions::computeDistance(float x1, float y1, float x2, float y2)
{
	float distance; // Absolute value of distance between start and end position
	float diffX; // Absolute value of distance between positions x values
	float diffY; // Absolute value of distance between positions y values

	diffX = x1 - x2;
	diffX = fabs(diffX);
	diffY = y1 - y2;
	diffY = fabs(diffY);

	distance = (diffX * diffX) + (diffY * diffY);
	distance = sqrt(distance);

	return distance;
}

float CoreFunctions::computeDistance(float x1, float x2)
{
	float distance; // Absolute value of distance between start and end position

	distance = x1 - x2;
	distance = fabs(distance);

	return distance;
}

std::set<vl::fvec3> CoreFunctions::getRandomPositions(qlonglong pNumberOfPositions, float pRadius)
{
	std::set<vl::fvec3> randPositions;
	vl::fvec3 position;

	// for hairs to be better distributed we set 4 quadrants in a circle
	for (qlonglong i=0; i<(pNumberOfPositions/4); i++)
	{
		// 1. quadrant
		position = getRandomCirclePosition((0-pRadius), 0, 0, pRadius, pRadius);
		randPositions.insert(position);

		// 2. quadrant
		position = getRandomCirclePosition(0, pRadius, 0, pRadius, pRadius);
		randPositions.insert(position);

		// 3. quadrant
		position = getRandomCirclePosition(0, pRadius, (0-pRadius), 0, pRadius);
		randPositions.insert(position);

		// 4. quadrant
		position = getRandomCirclePosition((0-pRadius), 0, (0-pRadius), 0, pRadius);
		randPositions.insert(position);
	}

	// if some positions were duplicate or we do not have enough
	while (randPositions.size() < pNumberOfPositions)
	{
		position = getRandomCirclePosition((0-pRadius), pRadius, (0-pRadius), pRadius, pRadius);
		randPositions.insert(position);
	}

	return randPositions;
}

vl::fvec3 CoreFunctions::getRandomCirclePosition(float pPointAMin, float pPointAMax, float pPointBMin, float pPointBMax, float pRadius)
{
	float x, y, z;

	x = getRandomNumber( pPointAMin, pPointAMax);
	y = 0;
	z = getRandomNumber( pPointBMin, pPointBMax);

	while (computeDistance(0, 0, x, z) > pRadius)
	{
		x = x / 2;
		if (computeDistance(0, 0, x, z) < pRadius)
			break;
		z = z / 2;
		if (computeDistance(0, 0, x, z) < pRadius)
			break;
	}

	return vl::fvec3(x, y, z);
}

float CoreFunctions::getRandomNumber(float min, float max)
{
	//srand(time(0));
	return ((max-min)*((float)rand()/RAND_MAX))+min;
}

vl::fvec3 *CoreFunctions::getDirection(vl::fvec3 *pStartPoint, vl::fvec3 *pEndPoint)
{
	vl::fvec3 *direction;
	float distance;
	float multiplier;
	float diffX; 
	float diffY;
	float diffZ;

	distance = computeDistance(pStartPoint, pEndPoint);
	multiplier = 1 / distance;

	diffX = pEndPoint->x() - pStartPoint->x();
	diffY = pEndPoint->y() - pStartPoint->y();
	diffZ = pEndPoint->z() - pStartPoint->z();

	direction = new vl::fvec3( (diffX * multiplier), (diffY * multiplier), (diffZ * multiplier));

	return direction;
}

Settings *CoreFunctions::loadSettings(std::string pFileName)
{
	Settings *settings = new Settings();
	std::map<std::string, std::string> settingsList;
	std::string key;
	std::string value;
	std::string line;
	ifstream file;
	bool error = false;

	settingsList.insert(pair<string, string>("config_file_name", pFileName));

	file.open(pFileName.c_str(), ios::in);

	// check if file is open
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			
			int index = line.find("=");
			key = line.substr(0, index);
			value = line.substr(index + 1);

			settingsList.insert(pair<string, string>(key, value));
		}
 
		file.close();

		settings->setSettings(settingsList);
	}
	else
	{
		error = true;
	}

	settings->setError(error);

	return settings;
}

bool CoreFunctions::saveSettings(Settings *pSettings)
{
	bool error = false;

	// TODO save changed settings to config file - pSettings->configFileName

	return error;
}

qlonglong CoreFunctions::getHairID()
{
	qlonglong newID = hairID;
	hairID++;

	return newID;
}

void CoreFunctions::resetIDCounter()
{
	hairID = 0;
}

std::vector<vl::fvec3> CoreFunctions::computeInterpolatedPoints(std::vector<vl::fvec3> *pControlPoints, int pNewPointsNumber)
{
	std::vector<vl::fvec3> interpolatedPoints;
	vl::CatmullRomInterpolatorFVec3 catmull;

    catmull.interpolator()->setPath(*pControlPoints);
    catmull.interpolator()->setupEndPoints(false);

    for (int i=0; i<pNewPointsNumber; ++i)
    {
		// interpolate from 0.0 to 1.0 included
		float t = (float)i/(pNewPointsNumber-1); 
		interpolatedPoints.push_back(catmull.computePoint(t));
    }

	return interpolatedPoints;
}