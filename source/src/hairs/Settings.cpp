#include "Settings.hpp"

using namespace vl;

Settings::Settings()
{

}

Settings::~Settings()
{

}

void Settings::setSettings(std::map<std::string, std::string> pSettings)
{
	settings = &pSettings;
	configFileName = getSettingValue("config_file_name").c_str();

	// window size and position
	windowXPosition = atoi(getSettingValue("window_start_x_position").c_str());
	windowYPosition = atoi(getSettingValue("window_start_y_position").c_str());
	windowWidth = atoi(getSettingValue("window_width").c_str());
	windowHeight = atoi(getSettingValue("window_height").c_str());
	simulationWindowXPosition = atoi(getSettingValue("simulation_window_start_x_position").c_str());
	simulationWindowYPosition = atoi(getSettingValue("simulation_window_start_y_position").c_str());
	simulationWindowWidth = atoi(getSettingValue("simulation_window_width").c_str());
	simulationWindowHeight = atoi(getSettingValue("simulation_window_height").c_str());

	if (atoi(getSettingValue("simulation_window_show").c_str()) == 1)
		simulationWindowShow = true;
	else
		simulationWindowShow = false;

	windowBgColorR = atof(getSettingValue("window_bg_color_r").c_str());
	windowBgColorG = atof(getSettingValue("window_bg_color_g").c_str());
	windowBgColorB = atof(getSettingValue("window_bg_color_b").c_str());
	windowBgColorA = atof(getSettingValue("window_bg_color_a").c_str());

	// format settings
	if (atoi(getSettingValue("format_double_buffer").c_str()) == 1)
		formatDoubleBufferEnabled = true;
	else
		formatDoubleBufferEnabled = false;

	formatRBit = atoi(getSettingValue("format_r_bit").c_str());
	formatGBit = atoi(getSettingValue("format_g_bit").c_str());
	formatBBit = atoi(getSettingValue("format_b_bit").c_str());
	formatABit = atoi(getSettingValue("format_a_bit").c_str());
	formatDepthBufferBits = atoi(getSettingValue("format_depth_buffer_bits").c_str());
	formatStencilBufferBits = atoi(getSettingValue("format_stencil_buffer_bits").c_str());

	if (atoi(getSettingValue("format_fullscreen").c_str()) == 1)
		formatIsFullscreen = true;
	else
		formatIsFullscreen = false;

	formatMultisamplingValue = atoi(getSettingValue("format_multisampling_value").c_str());

	if (atoi(getSettingValue("format_multisampling_enabled").c_str()) == 1)
		formatMultisamplingEnabled = true;
	else
		formatMultisamplingEnabled = false;

	// hair settings
	hairsNumber = atoi(getSettingValue("hairs_number").c_str());
	hairsLength = atof(getSettingValue("hairs_length").c_str());
	hairsWidth = atof(getSettingValue("hairs_width").c_str());
	hairParticlesNumber = atoi(getSettingValue("hair_particles_number").c_str());
	hairInterpolationPointsNumber = atoi(getSettingValue("hair_interpol_number").c_str());
	hairColorR = atof(getSettingValue("hair_color_r").c_str());
	hairColorG = atof(getSettingValue("hair_color_g").c_str());
	hairColorB = atof(getSettingValue("hair_color_b").c_str());
	hairColorA = atof(getSettingValue("hair_color_a").c_str());
	hairStartPointsInputFile = getSettingValue("hair_start_positions_input_file").c_str();
	hairStartPositionsType = atoi(getSettingValue("hair_start_positions_type").c_str());
	hairSphereCenterPositionX = atof(getSettingValue("hair_sphere_center_position_x").c_str());
	hairSphereCenterPositionY = atof(getSettingValue("hair_sphere_center_position_y").c_str());
	hairSphereCenterPositionZ = atof(getSettingValue("hair_sphere_center_position_z").c_str());
	hairSphereRadius = atof(getSettingValue("hair_sphere_radius").c_str());
	hairSpherePlanePointX = atof(getSettingValue("hair_sphere_plane_point_x").c_str());
	hairSpherePlanePointY = atof(getSettingValue("hair_sphere_plane_point_y").c_str());
	hairSpherePlanePointZ = atof(getSettingValue("hair_sphere_plane_point_z").c_str());
	hairDirectionStartPointX = atof(getSettingValue("hair_direction_start_point_x").c_str());
	hairDirectionStartPointY = atof(getSettingValue("hair_direction_start_point_y").c_str());
	hairDirectionStartPointZ = atof(getSettingValue("hair_direction_start_point_z").c_str());
	hairControlPointsDistributionType = atoi(getSettingValue("hair_control_points_dist_type").c_str());
	hairControlPointsDistributionType3Multiplier = atof(getSettingValue("hair_control_points_dist_type_3_multiplier").c_str());
	hairType = atoi(getSettingValue("hair_type").c_str());

	// environment settings
	model = getSettingValue("model").c_str();

	if (atoi(getSettingValue("model_enabled").c_str()) == 1)
		modelEnabled = true;
	else
		modelEnabled = false;

	modelSizeCoef = atof(getSettingValue("model_size_coef").c_str());

	textFont = getSettingValue("text_font").c_str();
	textSize = atoi(getSettingValue("text_size").c_str());

	if (atoi(getSettingValue("text_enabled").c_str()) == 1)
		textEnabled = true;
	else
		textEnabled = false;

	if (atoi(getSettingValue("text_bg_enabled").c_str()) == 1)
		textBgEnabled = true;
	else
		textBgEnabled = false;

	textColorR = atof(getSettingValue("text_color_r").c_str());
	textColorG = atof(getSettingValue("text_color_g").c_str());
	textColorB = atof(getSettingValue("text_color_b").c_str());
	textColorA = atof(getSettingValue("text_color_a").c_str());

	textBgColorR = atof(getSettingValue("text_bg_color_r").c_str());
	textBgColorG = atof(getSettingValue("text_bg_color_g").c_str());
	textBgColorB = atof(getSettingValue("text_bg_color_b").c_str());
	textBgColorA = atof(getSettingValue("text_bg_color_a").c_str());

	// simulation settings
	if (atoi(getSettingValue("simulation_run").c_str()) == 1)
		simulationRunning = true;
	else
		simulationRunning = false;

	simulationSpeed = atof(getSettingValue("simulation_speed").c_str());

	if (atoi(getSettingValue("simulation_speed_auto_enabled").c_str()) == 1)
		simulationSpeedAutoEnabled = true;
	else
		simulationSpeedAutoEnabled = false;

	simulationSynchSpeed = atoi(getSettingValue("simulation_synch_speed").c_str());

	if (atoi(getSettingValue("simulation_texturing_enabled").c_str()) == 1)
		simulationTexturingEnabled = true;
	else
		simulationTexturingEnabled = false;

	if (atoi(getSettingValue("simulation_shadows_enabled").c_str()) == 1)
		simulationShadowsEnabled = true;
	else
		simulationShadowsEnabled = false;

	simulationGravityX = atoi(getSettingValue("simulation_gravity_x").c_str());
	simulationGravityY = atoi(getSettingValue("simulation_gravity_y").c_str());
	simulationGravityZ = atoi(getSettingValue("simulation_gravity_z").c_str());
	simulationSizeCoef = atof(getSettingValue("simulation_size_coef").c_str());
	simulationControlPointRadius = atof(getSettingValue("simulation_control_point_radius").c_str());
	simulationControlPointMass = atof(getSettingValue("simulation_control_point_mass").c_str());
	simulationHairMass = atof(getSettingValue("simulation_hair_mass").c_str());

	// format creation
	createFormat();
}

std::string Settings::getSettingValue(std::string pSettingName)
{
	std::map<std::string, std::string>::iterator it;

	it = settings->find(pSettingName);

	if (it != settings->end())
	{
		return it->second;
	}
	else
	{
		vl::Log::error(Say("Configuration file corrupted.\nCannot find \"%s\" parameter.\n") << pSettingName);
		exit(1);
	}
}

void Settings::createFormat()
{
	format.setDoubleBuffer(formatDoubleBufferEnabled);
	format.setRGBABits(formatRBit, formatGBit, formatBBit, formatABit);
	format.setDepthBufferBits(formatDepthBufferBits);
	format.setStencilBufferBits(formatStencilBufferBits);
	format.setFullscreen(formatIsFullscreen);
	format.setMultisampleSamples(formatMultisamplingValue);
	format.setMultisample(formatMultisamplingEnabled);
}