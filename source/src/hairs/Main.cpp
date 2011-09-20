#include "MainWindow.hpp"

using namespace vl;
using namespace vlQt4;

int main(int argc, char *argv[])
{
	std::string settingsFileName = "config.txt";
	int val = 0;

	QApplication app(argc, argv);
	VisualizationLibrary::init();

	CoreFunctions *core = new CoreFunctions();
	Settings *settings = core->loadSettings(settingsFileName);

	//QRect screenResolution = QApplication::desktop()->screenGeometry();
	//int screenWidth = screenResolution.width();
	//int screenHeight = screenResolution.height();

	if (settings->isError())
	{
		vl::Log::error( Say("Error while loading \"config.txt\". Check if file exist.\n") );
	}
	else
	{
		ref<vlQt4::Qt4Widget> qt4_window = new vlQt4::Qt4Widget;
		ref<Applet> applet = new MainWindow(settings, argc, argv);
		applet->initialize(); 
		qt4_window->addEventListener(applet.get());
		applet->rendering()->as<Rendering>()->renderer()->setRenderTarget( qt4_window->renderTarget() );
		applet->rendering()->as<Rendering>()->camera()->viewport()->setClearColor(settings->getWindowBgColorR(), settings->getWindowBgColorG(), settings->getWindowBgColorB(), settings->getWindowBgColorA());
		vec3 eye    = vec3(0,0,4);	// camera position
		vec3 center = vec3(0,0,0);  // point the camera is looking at
		vec3 up     = vec3(0,1,0);  // up direction
		mat4 view_mat = mat4::getLookAt(eye, center, up).getInverse();
		applet->rendering()->as<Rendering>()->camera()->setViewMatrix( view_mat );

		qt4_window->initQt4Widget( "Hairs simulation and visualization", settings->getFormat(), NULL, settings->getWindowXPosition(), settings->getWindowYPosition(), settings->getWindowWidth(), settings->getWindowHeight() );
		qt4_window->show();
		
		val = app.exec();
		qt4_window = NULL;
	}

	VisualizationLibrary::shutdown();

	delete core;

	return val;
}