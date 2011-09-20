#include "CoreFunctions.hpp"

using namespace vl;
using namespace std;

CoreFunctions::CoreFunctions()
{
	hairID = 0;
	//settings = new Settings();
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
	//settingsFileName = pFileName;

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

	// TODO save settings to config file - pSettings->configFileName

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