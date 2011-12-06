#ifndef PHYSICS_H
#define PHYSICS_H

#include "Settings.hpp"
#include "Hair.hpp"

#ifdef _WINDOWS
#include "Win32DemoApplication.h"
#define PlatformApplication Win32DemoApplication
#else
#include "GlutDemoApplication.h"
#define PlatformApplication GlutDemoApplication
#endif

#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h"
#include "BulletCollision/NarrowPhaseCollision/btGjkEpa2.h"
#include "LinearMath/btQuickprof.h"
#include "LinearMath/btIDebugDraw.h"
#include "LinearMath/btConvexHull.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"
#include "GL_ShapeDrawer.h"
#include "GLDebugFont.h"
#include "GlutStuff.h"
#include <stdio.h>
#include "LinearMath/btAlignedObjectArray.h"
#include "BulletSoftBody/btSoftBody.h"
#include <vlCore/VisualizationLibrary.hpp>
#include <list>
#include <map>

class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;
class btSoftSoftCollisionAlgorithm;
class btSoftRididCollisionAlgorithm;
class btSoftRigidDynamicsWorld;

class Physics : public PlatformApplication
{
	public:

		btAlignedObjectArray<btSoftSoftCollisionAlgorithm*> m_SoftSoftCollisionAlgorithms;
		btAlignedObjectArray<btSoftRididCollisionAlgorithm*> m_SoftRigidCollisionAlgorithms;
		btSoftBodyWorldInfo	m_softBodyWorldInfo;

		int m_lastmousepos[2];
		btSoftBody::Node *m_node;
		btVector3 m_goal;
		bool m_drag;

		//keep the collision shapes, for deletion/cleanup
		btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
		btBroadphaseInterface* m_broadphase;
		btCollisionDispatcher* m_dispatcher;
		btConstraintSolver* m_solver;
		btCollisionAlgorithmCreateFunc* m_boxBoxCF;
		btDefaultCollisionConfiguration* m_collisionConfiguration;

	public:

		void setSettings(Settings *pSettings);
		void setHairs(std::list<Hair> *pHairs);
		void createHairs();

		std::map<unsigned int, std::vector<vl::fvec3>> getControlPointsPositions();

		void initPhysics();
		void exitPhysics();

		Physics() : m_drag(false) {	controlPoints.clear(); }

		virtual ~Physics()
		{
			exitPhysics();
		}

		virtual void clientMoveAndDisplay();
		virtual void displayCallback();

		static DemoApplication* Create()
		{
			Physics* app = new Physics;
			app->myinit();
			app->initPhysics();
			return app;
		}

		virtual	void setDrawClusters(bool drawClusters);
		virtual const btSoftRigidDynamicsWorld*	getSoftDynamicsWorld() const
		{
			return (btSoftRigidDynamicsWorld*) m_dynamicsWorld;
		}
		virtual btSoftRigidDynamicsWorld*	getSoftDynamicsWorld()
		{
			return (btSoftRigidDynamicsWorld*) m_dynamicsWorld;
		}
		void clientResetScene();
		void renderme();
		void keyboardCallback(unsigned char key, int x, int y);

	protected:
		Settings *settings;
		std::list<Hair> *hairs;
		float sizeCoef;
		btScalar controlPointRadius;
		float controlPointMass;
		float hairMass;
		float simulationSpeed;
		bool isSimulationRunning;

		std::map<unsigned int, std::vector<vl::fvec3>> controlPointsPositions;
		std::map<unsigned int, std::list<btRigidBody*>> controlPoints;
		std::map<unsigned int, vl::fvec3> startPoints;
};

#endif
