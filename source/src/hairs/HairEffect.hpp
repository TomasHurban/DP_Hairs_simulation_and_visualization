/*!
* HairEffect.hpp
* Project Hair simulation and visualization using GPU
*/
#ifndef HAIR_EFFECT_H
#define HAIR_EFFECT_H

#include <vlGraphics/GeometryPrimitives.hpp>
#include <vlGraphics/Rendering.hpp>
#include <vlGraphics/Actor.hpp>
#include <vlGraphics/Effect.hpp>
#include <vlGraphics/GLSL.hpp>
#include <vlGraphics/Light.hpp>
#include <vlGraphics/Text.hpp>
#include <vlCore/VisualizationLibrary.hpp>
#include <vector>
#include <QtGlobal>
#include <iostream>
#include <vlGraphics/Geometry.hpp>
#include <vlGraphics/GLSL.hpp>

#include "CoreFunctions.hpp"

/**
* \class	HairEffect
* \brief	Default hair effect
* \author	Tomas Hurban
* \date		30.03.2012
*/
class HairEffect
{
	public:
		HairEffect();

		~HairEffect();

		vl::ref<vl::Effect>* get() { return &effect; }

	protected:
		void createMaterial();
		
		void createLight();
	
		void createEffect();

		/**
		* vl::ref<vl::Effect> effect
		* \brief	Hair effect
		*/
		vl::ref<vl::Effect> effect;

		/**
		* vl::ref<vl::Light> light
		* \brief	Hair light
		*/
		vl::ref<vl::Light> light;

		/**
		* vl::ref<vl::Material> materialHair
		* \brief	Hair material
		*/
		vl::ref<vl::Material> material;
};

#endif
