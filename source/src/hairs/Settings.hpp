#ifndef SETTINGS_H
#define SETTINGS_H

#include <vlCore/Log.hpp>
#include <vlGraphics/Applet.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlQt4/Qt4Widget.hpp>
#include <map>

class Settings
{
	public:
		Settings();

		~Settings();

		void setSettings(std::map<std::string, std::string> pSettings);

		inline bool isError() { return errorLoadingSettings; }
		inline void setError(bool pErrorLoadingSettings) { errorLoadingSettings = pErrorLoadingSettings; }

		inline std::string getConfigFileName() { return configFileName; }
		inline void setConfigFileName(std::string pConfigFileName) { configFileName = pConfigFileName; }

		// windows size and positions
		inline int getArgc() { return argc; }
		inline void setArgc(int pArgc) { argc = pArgc; }
		inline char **getArgv() { return argv; }
		inline void setArgv(char **pArgv) { argv = pArgv; }

		inline int getWindowXPosition() { return windowXPosition; }
		inline void setWindowXPosition(int pWindowXPosition) { windowXPosition = pWindowXPosition; }
		inline int getWindowYPosition() { return windowYPosition; }
		inline void setWindowYPosition(int pWindowYPosition) { windowYPosition = pWindowYPosition; }
		inline int getWindowWidth() { return windowWidth; }
		inline void setWindowWidth(int pWindowWidth) { windowWidth = pWindowWidth; }
		inline int getWindowHeight() { return windowHeight; }
		inline void setWindowHeight(int pWindowHeight) { windowHeight = pWindowHeight; }

		inline int getSimulationWindowXPosition() { return simulationWindowXPosition; }
		inline void setSimulationWindowXPosition(int pSimulationWindowXPosition) { simulationWindowXPosition = pSimulationWindowXPosition; }
		inline int getSimulationWindowYPosition() { return simulationWindowYPosition; }
		inline void setSimulationWindowYPosition(int pSimulationWindowYPosition) { simulationWindowYPosition = pSimulationWindowYPosition; }
		inline int getSimulationWindowWidth() { return simulationWindowWidth; }
		inline void setSimulationWindowWidth(int pSimulationWindowWidth) { simulationWindowWidth = pSimulationWindowWidth; }
		inline int getSimulationWindowHeight() { return simulationWindowHeight; }
		inline void setSimulationWindowHeight(int pSimulationWindowHeight) { simulationWindowHeight = pSimulationWindowHeight; }

		inline bool getSimulationWindowShow() { return simulationWindowShow; }
		inline void setSimulationWindowShow(bool pSimulationWindowShow) { simulationWindowShow = pSimulationWindowShow; }

		inline float getWindowBgColorR() { return windowBgColorR; }
		inline void setWindowBgColorR(float pWindowBgColorR) { windowBgColorR = pWindowBgColorR; }
		inline float getWindowBgColorG() { return windowBgColorG; }
		inline void setWindowBgColorG(float pWindowBgColorG) { windowBgColorG = pWindowBgColorG; }
		inline float getWindowBgColorB() { return windowBgColorB; }
		inline void setWindowBgColorB(float pWindowBgColorB) { windowBgColorB = pWindowBgColorB; }
		inline float getWindowBgColorA() { return windowBgColorA; }
		inline void setWindowBgColorA(float pWindowBgColorA) { windowBgColorA = pWindowBgColorA; }

		// format settings
		inline vl::OpenGLContextFormat getFormat() { return format; }
		inline void setFormat(vl::OpenGLContextFormat pFormat) { format = pFormat; }

		inline bool getFormatDoubleBufferEnabled() { return formatDoubleBufferEnabled; }
		inline void setFormatDoubleBufferEnabled(bool pFormatDoubleBufferEnabled) { formatDoubleBufferEnabled = pFormatDoubleBufferEnabled; }

		inline int getFormatRBit() { return formatRBit; }
		inline void setFormatRBit(int pFormatRBit) { formatRBit = pFormatRBit; }
		inline int getFormatGBit() { return formatGBit; }
		inline void setFormatGBit(int pFormatGBit) { formatGBit = pFormatGBit; }
		inline int getFormatBBit() { return formatBBit; }
		inline void setFormatBBit(int pFormatBBit) { formatBBit = pFormatBBit; }
		inline int getFormatABit() { return formatABit; }
		inline void setFormatABit(int pFormatABit) { formatABit = pFormatABit; }

		inline int getFormatDepthBufferBits() { return formatDepthBufferBits; }
		inline void setFormatDepthBufferBits(int pFormatDepthBufferBits) { formatDepthBufferBits = pFormatDepthBufferBits; }

		inline int getFormatStencilBufferBits() { return formatStencilBufferBits; }
		inline void setFormatStencilBufferBits(int pFormatStencilBufferBits) { formatStencilBufferBits = pFormatStencilBufferBits; }

		inline bool getFormatIsFullscreen() { return formatIsFullscreen; }
		inline void setFormatIsFullscreen(bool pFormatIsFullscreen) { formatIsFullscreen = pFormatIsFullscreen; }

		inline int getFormatMultisamplingValue() { return formatMultisamplingValue; }
		inline void setFormatMultisamplingValue(int pFormatMultisamplingValue) { formatMultisamplingValue = pFormatMultisamplingValue; }

		inline bool getFormatMultisamplingEnabled() { return formatMultisamplingEnabled; }
		inline void setFormatMultisamplingEnabled(bool pFormatMultisamplingEnabled) { formatMultisamplingEnabled = pFormatMultisamplingEnabled; }

		// hair settings
		inline unsigned int getHairsNumber() { return hairsNumber; }
		inline void setHairsNumber(unsigned int pHairsNumber) { hairsNumber = pHairsNumber; }

		inline float getHairsLength() { return hairsLength; }
		inline void setHairsLength(float pHairsLength) { hairsLength = pHairsLength; }

		inline float getHairsWidth() { return hairsWidth; }
		inline void setHairsWidth(float pHairsWidth) { hairsWidth = pHairsWidth; }

		inline unsigned int getHairParticlesNumber() { return hairParticlesNumber; }
		inline void setHairParticlesNumber(unsigned int pHairParticlesNumber) { hairParticlesNumber = pHairParticlesNumber; }
		inline unsigned int getHairInterpolationPointsNumber() { return hairInterpolationPointsNumber; }
		inline void setHairInterpolationPointsNumber(unsigned int pHairInterpolationPointsNumber) { hairInterpolationPointsNumber = pHairInterpolationPointsNumber; }

		inline float getHairColorR() { return hairColorR; }
		inline void setHairColorR(float pHairColorR) { hairColorR = pHairColorR; }
		inline float getHairColorG() { return hairColorG; }
		inline void setHairColorG(float pHairColorG) { hairColorG = pHairColorG; }
		inline float getHairColorB() { return hairColorB; }
		inline void setHairColorB(float pHairColorB) { hairColorB = pHairColorB; }
		inline float getHairColorA() { return hairColorA; }
		inline void setHairColorA(float pHairColorA) { hairColorA = pHairColorA; }

		inline int getHairStartPositionsType() { return hairStartPositionsType; }
		inline void setHairStartPositionsType(int pHairStartPositionsType) { hairStartPositionsType = pHairStartPositionsType; }
		inline std::string getHairStartPointsInputFile() { return hairStartPointsInputFile; }
		inline void setHairStartPointsInputFile(float pHairStartPointsInputFile) { hairStartPointsInputFile = pHairStartPointsInputFile; }

		inline float getHairSphereCenterPositionX() { return hairSphereCenterPositionX; }
		inline void setHairSphereCenterPositionX(float pHairSphereCenterPositionX) { hairSphereCenterPositionX = pHairSphereCenterPositionX; }
		inline float getHairSphereCenterPositionY() { return hairSphereCenterPositionY; }
		inline void setHairSphereCenterPositionY(float pHairSphereCenterPositionY) { hairSphereCenterPositionY = pHairSphereCenterPositionY; }
		inline float getHairSphereCenterPositionZ() { return hairSphereCenterPositionZ; }
		inline void setHairSphereCenterPositionZ(float pHairSphereCenterPositionZ) { hairSphereCenterPositionZ = pHairSphereCenterPositionZ; }

		inline float getHairSphereRadius() { return hairSphereRadius; }
		inline void setHairSphereRadius(float pHairSphereRadius) { hairSphereRadius = pHairSphereRadius; }

		inline float getHairSpherePlanePointX() { return hairSpherePlanePointX; }
		inline void setHairSpherePlanePointX(float pHairSpherePlanePointX) { hairSpherePlanePointX = pHairSpherePlanePointX; }
		inline float getHairSpherePlanePointY() { return hairSpherePlanePointY; }
		inline void setHairSpherePlanePointY(float pHairSpherePlanePointY) { hairSpherePlanePointY = pHairSpherePlanePointY; }
		inline float getHairSpherePlanePointZ() { return hairSpherePlanePointZ; }
		inline void setHairSpherePlanePointZ(float pHairSpherePlanePointZ) { hairSpherePlanePointZ = pHairSpherePlanePointZ; }

		inline float getHairDirectionStartPointX() { return hairDirectionStartPointX; }
		inline void setHairDirectionStartPointX(float pHairDirectionStartPointX) { hairDirectionStartPointX = pHairDirectionStartPointX; }
		inline float getHairDirectionStartPointY() { return hairDirectionStartPointY; }
		inline void setHairDirectionStartPointY(float pHairDirectionStartPointY) { hairDirectionStartPointY = pHairDirectionStartPointY; }
		inline float getHairDirectionStartPointZ() { return hairDirectionStartPointZ; }
		inline void setHairDirectionStartPointZ(float pHairDirectionStartPointZ) { hairDirectionStartPointZ = pHairDirectionStartPointZ; }

		inline int getHairControlPointsDistributionType() { return hairControlPointsDistributionType; }
		inline void setHairControlPointsDistributionType(int pHairControlPointsDistributionType) { hairControlPointsDistributionType = pHairControlPointsDistributionType; }
		inline float getHairControlPointsDistributionType3Multiplier() { return hairControlPointsDistributionType3Multiplier; }
		inline void setHairControlPointsDistributionType3Multiplier(float pHairControlPointsDistributionType3Multiplier) { hairControlPointsDistributionType3Multiplier = pHairControlPointsDistributionType3Multiplier; }

		inline int getHairType() { return hairType; }
		inline void setHairType(int pHairType) { hairType = pHairType; }

		inline std::list<vl::fvec3> getStartPositions() { return startPositions; }
		inline void setStartPositions(std::list<vl::fvec3> pStartPositions) { startPositions = pStartPositions; }

		// environment settings
		inline vl::String getModel() { return model; }
		inline void setModel(vl::String pModel) { model = pModel; }
		inline bool getModelEnabled() { return modelEnabled; }
		inline void setModelEnabled(bool pModelEnabled) { modelEnabled = pModelEnabled; }
		inline float getModelSizeCoef() { return modelSizeCoef; }
		inline void setModelSizeCoef(float pModelSizeCoef) { modelSizeCoef = pModelSizeCoef; }

		inline vl::String getTextFont() { return textFont; }
		inline void setTextFont(vl::String pTextFont) { textFont = pTextFont; }

		inline unsigned int getTextSize() { return textSize; }
		inline void setTextSize(unsigned int pTextSize) { textSize = pTextSize; }

		inline bool getTextEnabled() { return textEnabled; }
		inline void setTextEnabled(bool pTextEnabled) { textEnabled = pTextEnabled; }

		inline bool getTextBgEnabled() { return textBgEnabled; }
		inline void setTextBgEnabled(bool pTextBgEnabled) { textBgEnabled = pTextBgEnabled; }

		inline float getTextColorR() { return textColorR; }
		inline void setTextColorR(float pTextColorR) { textColorR = pTextColorR; }
		inline float getTextColorG() { return textColorG; }
		inline void setTextColorG(float pTextColorG) { textColorG = pTextColorG; }
		inline float getTextColorB() { return textColorB; }
		inline void setTextColorB(float pTextColorB) { textColorB = pTextColorB; }
		inline float getTextColorA() { return textColorA; }
		inline void setTextColorA(float pTextColorA) { textColorA = pTextColorA; }

		inline float getTextBgColorR() { return textBgColorR; }
		inline void setTextBgColorR(float pTextBgColorR) { textBgColorR = pTextBgColorR; }
		inline float getTextBgColorG() { return textBgColorG; }
		inline void setTextBgColorG(float pTextBgColorG) { textBgColorG = pTextBgColorG; }
		inline float getTextBgColorB() { return textBgColorB; }
		inline void setTextBgColorB(float pTextBgColorB) { textBgColorB = pTextBgColorB; }
		inline float getTextBgColorA() { return textBgColorA; }
		inline void setTextBgColorA(float pTextBgColorA) { textBgColorA = pTextBgColorA; }

		// simulation settings
		inline bool isSimulationRunning() { return simulationRunning; }
		inline void setSimulationRunning(bool pSimulationRunning) { simulationRunning = pSimulationRunning; }

		inline float getSimulationSpeed() { return simulationSpeed; }
		inline void setSimulationSpeed(float pSimulationSpeed) { simulationSpeed = pSimulationSpeed; }
		inline bool getSimulationSpeedAutoEnabled() { return simulationSpeedAutoEnabled; }
		inline void setSimulationSpeedAutoEnabled(bool pSimulationSpeedAutoEnabled) { simulationSpeedAutoEnabled = pSimulationSpeedAutoEnabled; }
		inline unsigned int getSimulationSynchSpeed() { return simulationSynchSpeed; }
		inline void setSimulationSynchSpeed(unsigned int pSimulationSynchSpeed) { simulationSynchSpeed = pSimulationSynchSpeed; }
		inline void simulationSpeedIncrease() { simulationSynchSpeed++; }
		inline void simulationSpeedDecrease() { simulationSynchSpeed--; }

		inline bool isSimulationTexturingEnabled() { return simulationTexturingEnabled; }
		inline void setSimulationTexturingEnabled(bool pSimulationTexturingEnabled) { simulationTexturingEnabled = pSimulationTexturingEnabled; }

		inline bool isSimulationShadowsEnabled() { return simulationShadowsEnabled; }
		inline void setSimulationShadowsEnabled(bool pSimulationShadowsEnabled) { simulationShadowsEnabled = pSimulationShadowsEnabled; }

		inline int getSimulationGravityX() { return simulationGravityX; }
		inline void setSimulationGravityX(int pSimulationGravityX) { simulationGravityX = pSimulationGravityX; }
		inline int getSimulationGravityY() { return simulationGravityY; }
		inline void setSimulationGravityY(int pSimulationGravityY) { simulationGravityY = pSimulationGravityY; }
		inline int getSimulationGravityZ() { return simulationGravityZ; }
		inline void setSimulationGravityZ(int pSimulationGravityZ) { simulationGravityZ = pSimulationGravityZ; }

		inline float getSimulationSizeCoef() { return simulationSizeCoef; }
		inline void setSimulationSizeCoef(float pSimulationSizeCoef) { simulationSizeCoef = pSimulationSizeCoef; }

		inline float getSimulationControlPointRadius() { return simulationControlPointRadius; }
		inline void setSimulationControlPointRadius(float pSimulationControlPointRadius) { simulationControlPointRadius = pSimulationControlPointRadius; }

		inline float getSimulationControlPointMass() { return simulationControlPointMass; }
		inline void setSimulationControlPointMass(float pSimulationControlPointMass) { simulationControlPointMass = pSimulationControlPointMass; }
		inline float getSimulationHairMass() { return simulationHairMass; }
		inline void setSimulationHairMass(float pSimulationHairMass) { simulationHairMass = pSimulationHairMass; }

	protected:

		std::string getSettingValue(std::string pSettingName);
		void createFormat();
		std::map<std::string, std::string> *settings;
		bool errorLoadingSettings;

		std::string configFileName;

		// windows size and positions
		int argc;
		char **argv;
		int windowXPosition;
		int windowYPosition;
		int windowWidth;
		int windowHeight;
		int simulationWindowXPosition;
		int simulationWindowYPosition;
		int simulationWindowWidth;
		int simulationWindowHeight;
		bool simulationWindowShow;
		float windowBgColorR;
		float windowBgColorG;
		float windowBgColorB;
		float windowBgColorA;

		// format settings
		vl::OpenGLContextFormat format;
		bool formatDoubleBufferEnabled;
		int formatRBit;
		int formatGBit;
		int formatBBit;
		int formatABit;
		int formatDepthBufferBits;
		int formatStencilBufferBits;
		bool formatIsFullscreen;
		int formatMultisamplingValue;
		bool formatMultisamplingEnabled;

		// hair settings
		unsigned int hairsNumber;
		float hairsLength;
		float hairsWidth;
		unsigned int hairParticlesNumber;
		unsigned int hairInterpolationPointsNumber;
		float hairColorR;
		float hairColorG;
		float hairColorB;
		float hairColorA;
		int hairStartPositionsType;
		std::string hairStartPointsInputFile;
		float hairSphereCenterPositionX;
		float hairSphereCenterPositionY;
		float hairSphereCenterPositionZ;
		float hairSphereRadius;
		float hairSpherePlanePointX;
		float hairSpherePlanePointY;
		float hairSpherePlanePointZ;
		float hairDirectionStartPointX;
		float hairDirectionStartPointY;
		float hairDirectionStartPointZ;
		int hairControlPointsDistributionType;
		float hairControlPointsDistributionType3Multiplier;
		int hairType;
		std::list<vl::fvec3> startPositions;

		// environment settings
		vl::String model;
		bool modelEnabled;
		float modelSizeCoef;
		vl::String textFont;
		unsigned int textSize;
		bool textEnabled;
		bool textBgEnabled;
		float textColorR;
		float textColorG;
		float textColorB;
		float textColorA;
		float textBgColorR;
		float textBgColorG;
		float textBgColorB;
		float textBgColorA;

		// simulation settings
		bool simulationRunning;
		float simulationSpeed;
		bool simulationSpeedAutoEnabled;
		unsigned int simulationSynchSpeed;
		bool simulationTexturingEnabled;
		bool simulationShadowsEnabled;
		int simulationGravityX;
		int simulationGravityY;
		int simulationGravityZ;
		float simulationSizeCoef;
		float simulationControlPointRadius;
		float simulationControlPointMass;
		float simulationHairMass;
};

#endif
