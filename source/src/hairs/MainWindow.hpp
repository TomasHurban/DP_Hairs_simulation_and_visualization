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

class MainWindow: public vl::Applet
{
	public: 
		/** 
		*  Constructor
		*/
		MainWindow(Settings *pSettings, int pArgc, char **pArgv);

		/** 
		*  Destructor
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

		//vl::Actor* showHair(const std::vector<vl::fvec3>& ctrl_points);

		inline void setText(vl::String pText);
		bool environmentInitialization();
		bool hairInitialization();

	protected:
		int getRefreshSpeed(unsigned int pSpeed);

		vl::ref<vl::Effect> effectModel;
		vl::ref<vl::Effect> effectText;
		vl::ref<vl::Geometry> model;
		vl::ref<vl::ResourceDatabase> resDB;
		vl::ref<vl::SceneManagerActorTree> scene_manager;
		vl::ref<vl::Transform> transformModel;
		vl::Text *text;
		vl::Time mFPSTimer;	

		SettingsWindow *settingsWindow;
		CoreFunctions *core;

		bool error;
		boost::thread simulationThread;
		bool simulationStarted;
		int refreshSpeed;
		int refreshTimer;
		bool settingsChanged;
};

#endif
