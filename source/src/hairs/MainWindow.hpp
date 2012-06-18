/*!
* MainWindow.hpp
* Project Hair simulation and visualization using GPU
*/
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <vlGraphics/Applet.hpp>
#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlGraphics/SceneManagerActorTree.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlGraphics/FontManager.hpp>
#include <vlGraphics/GLSL.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/Text.hpp>
#include <vlCore/Time.hpp>
#include <vlCore/Array.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vlCore/ResourceDatabase.hpp>
#include <vlQt4/Qt4Widget.hpp>
#include <vlGraphics/OpenGL.hpp>
#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QWidget>
#include <QLayout>
#include <QtGui>
#include <QMenuBar>
#include <QApplication>
#include <QMenu>
#include <map>
#include <vector>
#include <list>
#include "GlutStuff.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"
#include "GLDebugDrawer.h"
#include <boost/thread.hpp>

#include "Hair.hpp"
#include "SettingsWindow.hpp"
#include "CoreFunctions.hpp"
#include "Physics.hpp"
#include "HairEffect.hpp"

/**
* \class	MainWindow
* \brief	Main window class
* \author	Tomas Hurban
* \date		30.06.2011
*/
class MainWindow: public vl::Applet
{
	public: 
		/**
		* \fn		public constructor MainWindow(Settings* pSettings, int pArgc, char** pArgv)
		* \brief	Constructor
		* \param	pSettings		input settings for model
		* \param	pArgc			number of program input parameters
		* \param	pArgv			program input parameters
		*/
		MainWindow(Settings* pSettings, int pArgc, char** pArgv);

		/**
		* \fn		public destructor ~MainWindow()
		* \brief	Destructor
		*/
		~MainWindow();

		/** 
		*  Called once after the OpenGL window has been opened
		*/
		void initEvent();

		/** 
		*  Called every frame
		*/
		virtual void updateScene();

		/** 
		*  Function called when any key is pressed
		*/
		virtual void keyPressEvent(unsigned short, vl::EKey key);

		/**
		* \fn		public void setText(vl::String pText)
		* \brief	Set text
		* \param	pText		text
		*/
		inline void setText(vl::String pText);

		/**
		* \fn		public bool environmentInitialization()
		* \brief	Scene initialization
		* \return	bool		true, if error occured, else false
		*/
		bool environmentInitialization();

		/**
		* \fn		public bool hairInitialization()
		* \brief	Hair model initialization
		* \return	bool		true, if error occured, else false
		*/
		bool hairInitialization();

	protected:
		/**
		* \fn		protected int getRefreshSpeed(unsigned int pSpeed)
		* \brief	Return synchronization speed value
		* \param	pSpeed		speed value
		* \return	bool		true, if error occured, else false
		*/
		int getRefreshSpeed(unsigned int pSpeed);

		/**
		* vl::ref<vl::Effect> effectText
		* \brief	Text effect
		*/
		vl::ref<vl::Effect> effectText;

		/**
		* vl::ref<vl::ResourceDatabase> resDB
		* \brief	Resource databasel
		*/
		vl::ref<vl::ResourceDatabase> resDB;

		/**
		* vl::ref<vl::SceneManagerActorTree> scene_manager
		* \brief	Scene manager
		*/
		vl::ref<vl::SceneManagerActorTree> scene_manager;

		/**
		* vl::ref<vl::Transform> transformModel
		* \brief	Model transform
		*/
		vl::ref<vl::Transform> transformModel;

		/**
		* vl::Text* text
		* \brief	Text
		*/
		vl::Text* text;

		/**
		* vl::Time mFPSTimer
		* \brief	FPS timer
		*/
		vl::Time mFPSTimer;	

		/**
		* vl::Actor* actor
		* \brief	Head model
		*/
		vl::Actor* actor;

		/**
		* SettingsWindow* settingsWindow
		* \brief	SettingsWindow class instance
		*/
		SettingsWindow* settingsWindow;

		/**
		* CoreFunctions* core
		* \brief	CoreFunctions class instance
		*/
		CoreFunctions* core;

		/**
		* HairEffect* hairEffect
		* \brief	HairEffect class instance
		*/
		HairEffect* hairEffect;

		/**
		* bool error
		* \brief	true if error occured
		*/
		bool error;

		/**
		* boost::thread simulationThread
		* \brief	Simulation thread
		*/
		boost::thread simulationThread;

		/**
		* bool simulationStarted
		* \brief	true if simulation already started
		*/
		bool simulationStarted;

		/**
		* int refreshSpeed
		* \brief	Speed of scene repaint
		*/
		int refreshSpeed;

		/**
		* int refreshTimer
		* \brief	Timer of scene repaint
		*/
		int refreshTimer;

		/**
		* bool settingsChanged
		* \brief	true if any model parameter is changed 
		*/
		bool settingsChanged;
};

#endif
