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

#include "Settings.hpp"

/**
* \class	HairEffect
* \brief	Default hair effect
* \author	Tomas Hurban
* \date		30.03.2012
*/
class HairEffect
{
	public:
		/**
		* \fn		public constructor HairEffect(float pColorR, float pColorG, float pColorB, float pColorA
		* \brief	Constructor
		* \param	pColorR		R value of RGBA color model
		* \param	pColorG		G value of RGBA color model
		* \param	pColorB		B value of RGBA color model
		* \param	pColorA		A value of RGBA color model
		*/
		HairEffect(float pColorR, float pColorG, float pColorB, float pColorA);

		/**
		* \fn		public destructor ~HairEffect()
		* \brief	Destructor
		*/
		~HairEffect();

		/**
		* \fn		public vl::ref<vl::Effect>* get()
		* \brief	Return created hair effect
		* \return	vl::ref<vl::Effect>*	hair effect
		*/
		vl::ref<vl::Effect>* get() { return &effect; }

	protected:
		/**
		* \fn		protected void createMaterial()
		* \brief	Create material
		*/
		void createMaterial();
		
		/**
		* \fn		protected void createLight()
		* \brief	Create light
		*/
		void createLight();
	
		/**
		* \fn		protected void createEffect()
		* \brief	Create effect
		*/
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

		/**
		* float colorR
		* \brief	R value of RGBA color model
		*/
		float colorR;

		/**
		* float colorG
		* \brief	G value of RGBA color model
		*/
		float colorG;

		/**
		* float colorB
		* \brief	B value of RGBA color model
		*/
		float colorB;

		/**
		* float colorA
		* \brief	A value of RGBA color model
		*/
		float colorA;

		/**
		* vl::Uniform* uniR
		* \brief	Uniform for R value of RGBA color model
		*/
		vl::Uniform* uniR;

		/**
		* vl::Uniform* uniG
		* \brief	Uniform for G value of RGBA color model
		*/
		vl::Uniform* uniG;

		/**
		* vl::Uniform* uniB
		* \brief	Uniform for B value of RGBA color model
		*/
		vl::Uniform* uniB;

		/**
		* vl::Uniform* uniA
		* \brief	Uniform for A value of RGBA color model
		*/
		vl::Uniform* uniA;
};

#endif
