/*!
* MainWindow.cpp
* Project Hair simulation and visualization using GPU
*/
#include "MainWindow.hpp"

static GLDebugDrawer sDebugDraw;

using namespace std;
using namespace vl;
using namespace vlQt4;
using namespace boost; 

Settings *settings;
Physics *physics;
std::list<Hair> hairs;

MainWindow::MainWindow(Settings *pSettings, int pArgc, char **pArgv)
{
	settings = pSettings;
	settings->setArgc(pArgc);
	settings->setArgv(pArgv);

	mFPSTimer.start();
	simulationStarted = false;
	refreshTimer = 1;
	settingsChanged = false;

	core = new CoreFunctions();

	settingsWindow = new SettingsWindow(&settings, &settingsChanged);
	physics = new Physics();

	refreshSpeed = getRefreshSpeed(pSettings->getSimulationSynchSpeed());
}

MainWindow::~MainWindow()
{
	std::list<Hair>::iterator it;

	for (it = hairs.begin(); it != hairs.end(); it++)
		delete &(*it);

	delete settingsWindow;
	delete core;
}

void MainWindow::initEvent()
{
	if (!(GLEW_ARB_shading_language_100 || GLEW_VERSION_3_0))
	{
		vl::Log::error("OpenGL Shading Language not supported.\n");
		vl::Time::sleep(3000);
		exit(1);
	}

	error = environmentInitialization();

	if (!error)
	{
		text->setText( Say("Environment ready") );
		error = hairInitialization();
	}

	if (!error)
	{
		text->setText( Say("Ready") );
	}
}

void MainWindow::updateScene()
{
	// synchronization Visualisation library with Bullet Physics library
	if (refreshTimer == refreshSpeed && settings->isSimulationRunning())
	{
		std::map<unsigned int, std::vector<vl::fvec3>> newPositions;
		std::map<unsigned int, std::vector<vl::fvec3>>::iterator itNewPositions;
		std::list<Hair>::iterator itHairs;

		newPositions = physics->getControlPointsPositions();
	
		if (!newPositions.empty())
		{
			for (itHairs=hairs.begin(); itHairs!=hairs.end(); itHairs++)
			{
				itNewPositions = newPositions.find(itHairs->getId());

				if (itNewPositions != newPositions.end())
				{
					std::vector<vl::fvec3> *controlPoints = &itNewPositions->second;

					// set new control points
					itHairs->setControlPoints(controlPoints);

					// compute interpolated points from control points
					itHairs->setInterpolationPoints(&(core->computeInterpolationPoints(controlPoints, settings->getHairInterpolationPointsNumber())));

					// compute interpolated points from control points
					itHairs->computeFinalPoints();

					// repaint hair
					itHairs->repaintHair();
				}
				else
				{
					// std::cout << "Error: MainWindow::updateScene()\n";
				}
			}
		}
	}

	// refresh time setup
	if (refreshTimer < refreshSpeed)
	{
		refreshTimer++;
	}
	else if (refreshSpeed != 1)
	{
		refreshTimer = 1;
	}

	// FPS timer
	if (mFPSTimer.elapsed() > 2)
	{
		mFPSTimer.start();
		openglContext()->setWindowTitle( vl::Say("[%.1n] %s") << fps() << "Hairs simulation and visualization" );
		vl::Log::print( vl::Say("FPS=%.1n\n") << fps() );
	}

	// check if settings changed
	if (settingsChanged == true)
	{
		settingsChanged = false;

		if (simulationStarted == true)
		{
			// TODO stop simulation if running
			//simulationStarted = false;
			//simulationThread.join();
		}
	}
}

int MainWindow::getRefreshSpeed(unsigned int pSpeed)
{
	switch (pSpeed)
	{
		case 1:	return 10000;
		case 2:	return 5000;
		case 3:	return 1000;
		case 4:	return 750;
		case 5:	return 500;
		case 6:	return 250;
		case 7:	return 100;
		case 8:	return 50;
		case 9:	return 10;
		case 10: return 1;
		default: return 1;
	}
}

void simulationStart()
{
	physics->setSettings(settings);
	physics->setHairs(&hairs);
	physics->initPhysics();
	physics->getDynamicsWorld()->setDebugDrawer(&sDebugDraw);

	#ifdef CHECK_MEMORY_LEAKS
		physics.exitPhysics();
	#else
		int val = glutmain(settings->getArgc(), settings->getArgv(), settings->getSimulationWindowWidth(), settings->getSimulationWindowHeight(), "Hair Simulation", physics, settings->getSimulationWindowXPosition(), settings->getSimulationWindowYPosition(), settings->getSimulationWindowShow());
	#endif
}

void MainWindow::keyPressEvent(unsigned short, vl::EKey key)
{
	// Simulation (gravity, collision detection) start / stop
	if (key == vl::Key_Space)
	{
		if (settings->isSimulationRunning())
		{
			settings->setSimulationRunning(false);
			text->setText( Say("Simulation stopped") );
		}
		else
		{
			settings->setSimulationRunning(true);
			text->setText( Say("Simulation running") );

			if (simulationStarted == false)
			{
				simulationThread = thread(simulationStart);
				simulationStarted = true;
				simulationThread.interrupt();
			}
		}
	}

	// Simulation synchronization speed increased
	if (key == vl::Key_Up)
	{
		if (settings->getSimulationSynchSpeed() < 10)
		{
			settings->simulationSpeedIncrease();
			refreshSpeed = getRefreshSpeed(settings->getSimulationSynchSpeed());
			refreshTimer = 1;
		}

		text->setText( Say("Simulation synchronization speed: 1/%n") << refreshSpeed);
	}

	// Simulation synchronization speed decreased
	if (key == vl::Key_Down)
	{
		if (settings->getSimulationSynchSpeed() > 1)
		{
			settings->simulationSpeedDecrease();
			refreshSpeed = getRefreshSpeed(settings->getSimulationSynchSpeed());
			refreshTimer = 1;
		}

		text->setText( Say("Simulation synchronization speed: 1/%n") << refreshSpeed);
	}

	// Menu
	if (key == vl::Key_M)
	{
		if (settingsWindow->isHidden()) 
		{
			settingsWindow->show();
			vl::Log::print( Say("Menu displayed\n") );
		}
	}

	// Show / hide simulation window
	if (key == vl::Key_H)
	{
		if (simulationStarted)
		{
			showSimulationWindow(settings->getSimulationWindowShow());
			settings->setSimulationWindowShow(!settings->getSimulationWindowShow());
		}
	}
}

inline void MainWindow::setText(vl::String pText) 
{ 
	text->setText( Say(pText) ); 
}

bool MainWindow::environmentInitialization()
{
	bool error = false;
	scene_manager = new vl::SceneManagerActorTree;
	rendering()->as<vl::Rendering>()->sceneManagers()->push_back(scene_manager.get());

	if (settings->getModelEnabled())
	{
		resDB = vl::loadResource(settings->getModel());
		
		// check if model file exist and is loaded
		if (resDB == NULL)
		{
			vl::Log::error( Say("Error while loading model \"%s\". Check if file exist.\n") << settings->getModel());
		}
		else
		{
			transformModel = new vl::Transform;
			rendering()->as<vl::Rendering>()->transform()->addChild( transformModel.get() );

			transformModel.get()->scale(settings->getModelSizeCoef(), settings->getModelSizeCoef(), settings->getModelSizeCoef());
			transformModel.get()->computeWorldMatrix();

			int k = 0;
			actor = resDB->next<vl::Actor>(k);
			actor->setTransform(transformModel.get());

			sceneManager()->tree()->addActor(actor);
		}
	}	
	else
	{
		// draw nothing
	}

	if (settings->getTextEnabled())
	{
		text = new Text;
		text->setFont( defFontManager()->acquireFont(settings->getTextFont(), settings->getTextSize()) );
		text->setAlignment( AlignLeft | AlignBottom);
		text->setViewportAlignment( AlignLeft | AlignBottom );
		text->translate(5,5,0);
		text->setBackgroundEnabled(settings->getTextBgEnabled());
		text->setColor( fvec4(settings->getTextColorR(), settings->getTextColorG(), settings->getTextColorB(), settings->getTextColorA()) );
		text->setBackgroundColor( fvec4(settings->getTextBgColorR(), settings->getTextBgColorG(), settings->getTextBgColorB(), settings->getTextBgColorA()) );

		effectText = new Effect;
		effectText->shader()->enable(EN_BLEND);

		sceneManager()->tree()->addActor( text, effectText.get() );
	}

	return error;
}

bool MainWindow::hairInitialization()
{
	bool error = false;

	// default hair effect
	hairEffect = new HairEffect(settings->getHairColorR(), settings->getHairColorG(), settings->getHairColorB(), settings->getHairColorA());
	std::list<vl::fvec3> startPositions;
	std::list<vl::fvec3>::iterator it;
	fvec3 *sphereCenterPosition;
	fvec3 *planePoint;
	vl::fvec4 *hairColor;
	vl::fvec3 *directionStartPoint;
	vl::fvec3 *direction;
	vl::fvec3 *hairStartPosition;
	hairs.clear();

	sphereCenterPosition = new fvec3(settings->getHairSphereCenterPositionX(), settings->getHairSphereCenterPositionY(), settings->getHairSphereCenterPositionZ());
	planePoint = new fvec3(settings->getHairSpherePlanePointX(), settings->getHairSpherePlanePointY(), settings->getHairSpherePlanePointZ());
	hairColor = new vl::fvec4(settings->getHairColorR(), settings->getHairColorG(), settings->getHairColorB(), settings->getHairColorA());
	directionStartPoint = new vl::fvec3(settings->getHairDirectionStartPointX(), settings->getHairDirectionStartPointY(), settings->getHairDirectionStartPointZ());

	// check if we want to load hair starting positions from file
	if (settings->getHairStartPositionsType() == 2)
	{
		// load hair starting positions from file 
		startPositions = core->getStartingPositions(settings->getHairStartPointsInputFile());

		// check if loaded correctly
		if (startPositions.empty())
		{
			vl::Log::error( Say("Cannot open hair starting points input file!\n") );
			// cannot load positions from file, so generate hair starting position randomly 
			startPositions = core->getStartingPositions(settings->getHairsNumber(), sphereCenterPosition, settings->getHairSphereRadius(), planePoint);
		}
	}
	else if (settings->getHairStartPositionsType() == 3)
	{
		/*** example  ***/
		bool inCorners = false;
		std::map<std::list<vl::fvec3>, unsigned int> area;
		unsigned int number;

		for (int i=1; i<4; i++)
		{
			number = 30;
			float pos = (float) i;
			std::list<vl::fvec3> cornerPoints;
			cornerPoints.push_back(vl::fvec3(pos/10, 0, 0));
			cornerPoints.push_back(vl::fvec3(-pos/10, 0, 0));
			cornerPoints.push_back(vl::fvec3(0, 0, -pos/10));

			area.insert(pair<std::list<vl::fvec3>, unsigned int>(cornerPoints, number));
		}
		/***         ***/

		// get starting points from defined area
		startPositions = core->getStartingPositions(area, inCorners);
	}
	else // type 1
	{
		// generate hair starting position randomly on sphere surface
		startPositions = core->getStartingPositions(settings->getHairsNumber(), sphereCenterPosition, settings->getHairSphereRadius(), planePoint);
	}

	settings->setStartPositions(startPositions);

	// create hairs
	for (it=startPositions.begin(); it!=startPositions.end(); it++)
	{
		hairStartPosition = &(*it);

		direction = core->getDirection(directionStartPoint, hairStartPosition);
		if (direction->x() == 0 && direction->y() == 0 && direction->z() == 0)
		{
			vl::Log::print( Say("Wrong hair start point choosen. (direction start position == hair start position)\n") );
		}

		Hair *newHair = new Hair(core->getHairID(), settings->getHairsLength(), settings->getHairsWidth(), settings->getHairParticlesNumber(), hairColor, hairStartPosition, direction, settings->getHairType(), settings->getHairControlPointsDistributionType(), settings->getHairControlPointsDistributionType3Multiplier());
		newHair->createHair(rendering(), settings->getHairInterpolationPointsNumber(), hairEffect->get());

		sceneManager()->tree()->addActor(newHair->getHair()->get());
		hairs.push_back(*newHair);
	}

	return error;
}