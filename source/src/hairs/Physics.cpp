#include "Physics.hpp"

extern float eye[3];
const int maxProxies = 32766;
const int maxOverlap = 65535;
static btVector3*	gGroundVertices=0;
static int*	gGroundIndices=0;
static btBvhTriangleMeshShape* trimeshShape =0;

#ifdef _DEBUG
	const int gNumObjects = 1;
#else
	const int gNumObjects = 1;//try this in release mode: 3000. never go above 16384, unless you increate maxNumObjects  value in DemoApplication.cp
#endif

const int maxNumObjects = 32760;
#define CUBE_HALF_EXTENTS 1.5
#define EXTRA_HEIGHT -10.f

void Physics::setSettings(Settings *pSettings)
{
	settings = pSettings;
	sizeCoef = pSettings->getSimulationSizeCoef();
	controlPointRadius = pSettings->getSimulationControlPointRadius();
	controlPointMass = pSettings->getSimulationControlPointMass();
	hairMass = pSettings->getSimulationHairMass();
	isSimulationRunning = true;
}

void Physics::setHairs(std::list<Hair> *pHairs)
{
	hairs = pHairs;
}

std::map<unsigned int, std::vector<vl::fvec3>> Physics::getControlPointsPositions()
{
	controlPointsPositions.clear();
	std::map<unsigned int, std::list<btRigidBody*>>::iterator itHairs;
	std::list<btRigidBody*>::iterator itPoints;

	for (itHairs=controlPoints.begin(); itHairs!=controlPoints.end(); itHairs++)
	{
		std::vector<vl::fvec3> positions;
		std::map<unsigned int, vl::fvec3>::iterator itStartPoints;

		itStartPoints = startPoints.find(itHairs->first);

		if (itStartPoints != startPoints.end())
		{
			positions.push_back(vl::fvec3(itStartPoints->second.x(), itStartPoints->second.y(), itStartPoints->second.z()));

			for (itPoints=itHairs->second.begin(); itPoints!=itHairs->second.end(); itPoints++)
			{
				btRigidBody* body = *itPoints;
				float x = body->getCenterOfMassPosition().getX() / sizeCoef;
				float y = body->getCenterOfMassPosition().getY() / sizeCoef;
				float z = body->getCenterOfMassPosition().getZ() / sizeCoef;

				positions.push_back(vl::fvec3(x, y, z));
			}

			controlPointsPositions.insert( std::pair<unsigned int, std::vector<vl::fvec3>>(itHairs->first, positions) );
		}
		else
		{
			std::cout << "Error: Physics::getControlPointsPositions() -> itStartPoints = startPoints.find(itHairs->first);";
		}
	}

	return controlPointsPositions;
}

void Physics::createStack( btCollisionShape* boxShape, float halfCubeSize, int size, float zPos )
{
	btTransform trans;
	trans.setIdentity();

	for(int i=0; i<size; i++)
	{
		// This constructs a row, from left to right
		int rowSize = size - i;
		for(int j=0; j< rowSize; j++)
		{
			btVector3 pos;
			pos.setValue(
				-rowSize * halfCubeSize + halfCubeSize + j * 2.0f * halfCubeSize,
				halfCubeSize + i * halfCubeSize * 2.0f,
				zPos);

			trans.setOrigin(pos);
			btScalar mass = 1.f;

			btRigidBody* body = 0;
			body = localCreateRigidBody(mass,trans,boxShape);
		}
	}
}

extern int gNumManifold;
extern int gOverlappingPairs;

///for mouse picking
void pickingPreTickCallback (btDynamicsWorld *world, btScalar timeStep)
{
	Physics* softDemo = (Physics*)world->getWorldUserInfo();

	if(softDemo->m_drag)
	{
		const int				x=softDemo->m_lastmousepos[0];
		const int				y=softDemo->m_lastmousepos[1];
		const btVector3			rayFrom=softDemo->getCameraPosition();
		const btVector3			rayTo=softDemo->getRayTo(x,y);
		const btVector3			rayDir=(rayTo-rayFrom).normalized();
		const btVector3			N=(softDemo->getCameraTargetPosition()-softDemo->getCameraPosition()).normalized();
		const btScalar			O=btDot(softDemo->m_impact,N);
		const btScalar			den=btDot(N,rayDir);
		if((den*den)>0)
		{
			const btScalar			num=O-btDot(N,rayFrom);
			const btScalar			hit=num/den;
			if((hit>0)&&(hit<1500))
			{				
				softDemo->m_goal=rayFrom+rayDir*hit;
			}				
		}		
		btVector3				delta=softDemo->m_goal-softDemo->m_node->m_x;
		static const btScalar	maxdrag=10;
		if(delta.length2()>(maxdrag*maxdrag))
		{
			delta=delta.normalized()*maxdrag;
		}
		softDemo->m_node->m_v+=delta/timeStep;
	}
}

void Physics::displayCallback(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	renderme();

	glFlush();
	swapBuffers();
}


void Physics::clientResetScene()
{
	m_azi = 0;
	m_cameraDistance = 30.f;
	m_cameraTargetPosition.setValue(0,0,0);

	DemoApplication::clientResetScene();

	for(int i=m_dynamicsWorld->getNumCollisionObjects()-1;i>=0;i--)
	{
		btCollisionObject*	obj=m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody*		body=btRigidBody::upcast(obj);
		if(body&&body->getMotionState())
		{
			delete body->getMotionState();
		}
		while(m_dynamicsWorld->getNumConstraints())
		{
			btTypedConstraint*	pc=m_dynamicsWorld->getConstraint(0);
			m_dynamicsWorld->removeConstraint(pc);
			delete pc;
		}
		btSoftBody* softBody = btSoftBody::upcast(obj);
		if (softBody)
		{
			getSoftDynamicsWorld()->removeSoftBody(softBody);
		} else
		{
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body)
				m_dynamicsWorld->removeRigidBody(body);
			else
				m_dynamicsWorld->removeCollisionObject(obj);
		}
		delete obj;
	}


	//create ground object
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(btVector3((settings->getHairSphereCenterPositionX() * sizeCoef), (settings->getHairSphereCenterPositionY() * sizeCoef), (settings->getHairSphereCenterPositionZ() * sizeCoef)));

	btCollisionObject* newOb = new btCollisionObject();
	newOb->setWorldTransform(tr);
	newOb->setInterpolationWorldTransform(tr);

	newOb->setCollisionShape(m_collisionShapes[0]);
	m_dynamicsWorld->addCollisionObject(newOb);

	m_softBodyWorldInfo.m_sparsesdf.Reset();

	m_softBodyWorldInfo.air_density		=	(btScalar)1.2;
	m_softBodyWorldInfo.water_density	=	0;
	m_softBodyWorldInfo.water_offset		=	0;
	m_softBodyWorldInfo.water_normal		=	btVector3(0,0,0);
	m_softBodyWorldInfo.m_gravity.setValue(settings->getSimulationGravityX(), settings->getSimulationGravityY(), settings->getSimulationGravityZ());

	m_autocam						=	false;
	m_raycast						=	false;
	m_cutting						=	false;
	m_results.fraction				=	1.f;

	createHairs();
}

void Physics::createHairs()
{
	startPoints.clear();
	std::list<Hair>::iterator itHairs;
	controlPoints.clear();
	int res = 16;

	// 1 - fixed first point, 2 - fixed second point, 3 - fixed both points
	int fixeds = 0; 

	for (itHairs=hairs->begin(); itHairs!=hairs->end(); itHairs++)
	{
		std::vector<vl::fvec3> *points;
		std::vector<vl::fvec3>::iterator itParts;
		float lastPointX, lastPointY, lastPointZ;
		btRigidBody *lastControlPoint;
		std::list<btRigidBody*> rigidBodyList;
	
		points = itHairs->getPoints();
		itParts = points->begin();
		lastPointX = itParts->x();
		lastPointY = itParts->y();
		lastPointZ = itParts->z();

		startPoints.insert( std::pair<unsigned int, vl::fvec3>(itHairs->getId(), vl::fvec3(lastPointX, lastPointY, lastPointZ)) );

		for (itParts++; itParts!=points->end(); itParts++)
		{
			// vytvorime uzol a spojime s predchadzajucim uzlom
			btTransform controlPointTransform;
			controlPointTransform.setIdentity();
			controlPointTransform.setOrigin(btVector3( (itParts->x() * sizeCoef), (itParts->y() * sizeCoef), (itParts->z() * sizeCoef) ));
			
			btRigidBody *controlPoint = localCreateRigidBody(controlPointMass, controlPointTransform, new btSphereShape(controlPointRadius));

			if (itParts == (points->begin() + 1) )
			{
				fixeds = 1;
			}
			else
			{
				fixeds = 0;
			}

			btSoftBody *rope = btSoftBodyHelpers::CreateRope(this->m_softBodyWorldInfo, btVector3( (lastPointX * sizeCoef), (lastPointY * sizeCoef), (lastPointZ * sizeCoef) ), btVector3( (itParts->x() * sizeCoef), (itParts->y() * sizeCoef), (itParts->z() * sizeCoef) ), res, fixeds);

		/*rope->m_cfg.piterations = 4; 
		rope->m_cfg.kDP = 0.005;
		rope->m_cfg.kCHR = 0.1;
		for(int i=0;i<3;++i)
		{
			rope->generateBendingConstraints(2+i);
		}*/
	
			rope->setTotalMass(hairMass);

			this->getSoftDynamicsWorld()->addSoftBody(rope);

			//rope->appendAnchor(rope->m_nodes.size()-1, controlPoint);
			rope->appendAnchor(rope->m_nodes.size()-1, controlPoint);
			if (itParts != (points->begin() + 1) )
			{
				rope->appendAnchor(rope->m_nodes.size()-2, lastControlPoint);
			}

			lastPointX = itParts->x();
			lastPointY = itParts->y();
			lastPointZ = itParts->z();
			lastControlPoint = controlPoint;
			rigidBodyList.push_back(controlPoint);
		}

		controlPoints.insert( std::pair<unsigned int, std::list<btRigidBody*>>(itHairs->getId(), rigidBodyList) );
	}
}

void Physics::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT); 

	if (settings->getSimulationSpeedAutoEnabled() == true)
	{
		float ms = getDeltaTimeMicroseconds();
		simulationSpeed = ms / 1000000.f;	
	}
	else
	{
		simulationSpeed = settings->getSimulationSpeed();
	}

	if (m_dynamicsWorld)
	{
		
		if (isSimulationRunning)
		{
			int numSimSteps = m_dynamicsWorld->stepSimulation(simulationSpeed);
		}

		if(m_drag)
		{
			m_node->m_v*=0;
		}

		m_softBodyWorldInfo.m_sparsesdf.GarbageCollect();
	}

	renderme(); 
	updateCamera();
	glFlush();
	swapBuffers();
}

void Physics::renderme()
{
	btIDebugDraw *idraw = m_dynamicsWorld->getDebugDrawer();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	m_dynamicsWorld->debugDrawWorld();

	btSoftRigidDynamicsWorld* softWorld = (btSoftRigidDynamicsWorld*)m_dynamicsWorld;
	for (  int i=0;i<softWorld->getSoftBodyArray().size();i++)
	{
		btSoftBody*	psb=(btSoftBody*)softWorld->getSoftBodyArray()[i];
		if (softWorld->getDebugDrawer() && !softWorld->getDebugDrawer()->getDebugMode() & (btIDebugDraw::DBG_DrawWireframe))
		{
			btSoftBodyHelpers::DrawFrame(psb,softWorld->getDebugDrawer());
			btSoftBodyHelpers::Draw(psb,softWorld->getDebugDrawer(),softWorld->getDrawFlags());
		}
	}

	/* Bodies		*/ 
	btVector3	ps(0,0,0);
	int			nps=0;

	btSoftBodyArray&	sbs=getSoftDynamicsWorld()->getSoftBodyArray();
	for(int ib=0;ib<sbs.size();++ib)
	{
		btSoftBody*	psb=sbs[ib];
		nps+=psb->m_nodes.size();
		for(int i=0;i<psb->m_nodes.size();++i)
		{
			ps+=psb->m_nodes[i].m_x;
		}		
	}
	ps/=nps;
	if(m_autocam)
		m_cameraTargetPosition+=(ps-m_cameraTargetPosition)*0.05;
	/* Anm			*/ 
	if(!isIdle())
		m_animtime=m_clock.getTimeMilliseconds()/1000.f;
	/* Ray cast		*/ 
	if(m_raycast)
	{		
		/* Prepare rays	*/ 
		const int		res=64;
		const btScalar	fres=res-1;
		const btScalar	size=8;
		const btScalar	dist=10;
		btTransform		trs;
		trs.setOrigin(ps);
		btScalar rayLength = 1000.f;

		const btScalar	angle=m_animtime*0.2;
		trs.setRotation(btQuaternion(angle,SIMD_PI/4,0));
		btVector3	dir=trs.getBasis()*btVector3(0,-1,0);
		trs.setOrigin(ps-dir*dist);
		btAlignedObjectArray<btVector3>	origins;
		btAlignedObjectArray<btScalar>	fractions;
		origins.resize(res*res);
		fractions.resize(res*res,1.f);
		for(int y=0;y<res;++y)
		{
			for(int x=0;x<res;++x)
			{
				const int	idx=y*res+x;
				origins[idx]=trs*btVector3(-size+size*2*x/fres,dist,-size+size*2*y/fres);
			}
		}
		/* Cast rays	*/ 		
		{
			m_clock.reset();
			btVector3*		org=&origins[0];
			btScalar*				fraction=&fractions[0];
			btSoftBody**			psbs=&sbs[0];
			btSoftBody::sRayCast	results;
			for(int i=0,ni=origins.size(),nb=sbs.size();i<ni;++i)
			{
				for(int ib=0;ib<nb;++ib)
				{
					btVector3 rayFrom = *org;
					btVector3 rayTo = rayFrom+dir*rayLength;
					if(psbs[ib]->rayTest(rayFrom,rayTo,results))
					{
						*fraction=results.fraction;
					}
				}
				++org;++fraction;
			}
			long	ms=btMax<long>(m_clock.getTimeMilliseconds(),1);
			long	rayperseconds=(1000*(origins.size()*sbs.size()))/ms;
			printf("%d ms (%d rays/s)\r\n",int(ms),int(rayperseconds));
		}
		/* Draw rays	*/ 
		const btVector3	c[]={	origins[0],
			origins[res-1],
			origins[res*(res-1)],
			origins[res*(res-1)+res-1]};
		idraw->drawLine(c[0],c[1],btVector3(0,0,0));
		idraw->drawLine(c[1],c[3],btVector3(0,0,0));
		idraw->drawLine(c[3],c[2],btVector3(0,0,0));
		idraw->drawLine(c[2],c[0],btVector3(0,0,0));
		for(int i=0,ni=origins.size();i<ni;++i)
		{
			const btScalar		fraction=fractions[i];
			const btVector3&	org=origins[i];
			if(fraction<1.f)
			{
				idraw->drawLine(org,org+dir*rayLength*fraction,btVector3(1,0,0));
			}
			else
			{
				idraw->drawLine(org,org-dir*rayLength*0.1,btVector3(0,0,0));
			}
		}
#undef RES
	}

	DemoApplication::renderme();
}

void Physics::keyboardCallback(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a':	
			m_raycast = !m_raycast;
			break;
	
		case 'b':	
			m_autocam = !m_autocam;
			break;
	
		case 'c':	
			getSoftDynamicsWorld()->setDrawFlags(getSoftDynamicsWorld()->getDrawFlags()^fDrawFlags::Clusters);
			break;
	
		case 'd':
			{
				btSoftBodyArray &sbs = getSoftDynamicsWorld()->getSoftBodyArray();
				for(int ib=0; ib<sbs.size(); ++ib)
				{
					btSoftBody *psb=sbs[ib];
					psb->staticSolve(128);
				}
			}
			break;

		case 's':
			isSimulationRunning = !isSimulationRunning;
			break;

		default:
			DemoApplication::keyboardCallback(key, x, y);
	}
}

void Physics::mouseMotionFunc(int x,int y)
{
	if(m_node&&(m_results.fraction<1.f))
	{
		if(!m_drag)
		{
#define SQ(_x_) (_x_)*(_x_)
			if((SQ(x-m_lastmousepos[0])+SQ(y-m_lastmousepos[1]))>6)
			{
				m_drag=true;
			}
#undef SQ
		}
		if(m_drag)
		{
			m_lastmousepos[0]	=	x;
			m_lastmousepos[1]	=	y;
		}
	}
	else
	{
		DemoApplication::mouseMotionFunc(x,y);
	}
}

void Physics::mouseFunc(int button, int state, int x, int y)
{
	if(button==0)
	{
		switch(state)
		{
		case	0:
			{
				m_results.fraction=1.f;
				DemoApplication::mouseFunc(button,state,x,y);
				if(!m_pickConstraint)
				{
					const btVector3			rayFrom=m_cameraPosition;
					const btVector3			rayTo=getRayTo(x,y);
					const btVector3			rayDir=(rayTo-rayFrom).normalized();
					btSoftBodyArray&		sbs=getSoftDynamicsWorld()->getSoftBodyArray();
					for(int ib=0;ib<sbs.size();++ib)
					{
						btSoftBody*				psb=sbs[ib];
						btSoftBody::sRayCast	res;
						if(psb->rayTest(rayFrom,rayTo,res))
						{
							m_results=res;
						}
					}
					if(m_results.fraction<1.f)
					{				
						m_impact			=	rayFrom+(rayTo-rayFrom)*m_results.fraction;
						m_drag				=	false;
						m_lastmousepos[0]	=	x;
						m_lastmousepos[1]	=	y;
						m_node				=	0;
						switch(m_results.feature)
						{
						case	btSoftBody::eFeature::Face:
							{
								btSoftBody::Face&	f=m_results.body->m_faces[m_results.index];
								m_node=f.m_n[0];
								for(int i=1;i<3;++i)
								{
									if(	(m_node->m_x-m_impact).length2()>
										(f.m_n[i]->m_x-m_impact).length2())
									{
										m_node=f.m_n[i];
									}
								}
							}
							break;
						}
						if(m_node) m_goal=m_node->m_x;
						return;
					}
				}
			}
			break;
		case	1:
			if((!m_drag)&&m_cutting&&(m_results.fraction<1.f))
			{
				//ImplicitSphere	isphere(m_impact,1);
				//printf("Mass before: %f\r\n",m_results.body->getTotalMass());
				//m_results.body->refine(&isphere,0.0001,true);
				//printf("Mass after: %f\r\n",m_results.body->getTotalMass());
			}
			m_results.fraction=1.f;
			m_drag=false;
			DemoApplication::mouseFunc(button,state,x,y);
			break;
		}
	}
	else
	{
		DemoApplication::mouseFunc(button,state,x,y);
	}
}

void Physics::initPhysics()
{
	setTexturing(settings->isSimulationTexturingEnabled());
	setShadows(settings->isSimulationShadowsEnabled());

	m_dispatcher = 0;
	m_collisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_softBodyWorldInfo.m_dispatcher = m_dispatcher;
	btVector3 worldAabbMin(-1000,-1000,-1000);
	btVector3 worldAabbMax(1000,1000,1000);
	m_broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
	m_softBodyWorldInfo.m_broadphase = m_broadphase;
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	m_solver = solver;
	btDiscreteDynamicsWorld* world = new btSoftRigidDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	m_dynamicsWorld = world;
	m_dynamicsWorld->setInternalTickCallback(pickingPreTickCallback,this,true);
	m_dynamicsWorld->getDispatchInfo().m_enableSPU = true;
	m_dynamicsWorld->setGravity(btVector3(settings->getSimulationGravityX(), settings->getSimulationGravityY(), settings->getSimulationGravityZ()));
	m_softBodyWorldInfo.m_gravity.setValue(settings->getSimulationGravityX(), settings->getSimulationGravityY(), settings->getSimulationGravityZ());

	m_azi = 0;//

		m_softBodyWorldInfo.m_sparsesdf.Initialize();


	btCollisionShape *modelShape = new btSphereShape(btScalar(settings->getHairSphereRadius() * sizeCoef));
	m_collisionShapes.push_back(modelShape);

	clientResetScene();
}

void Physics::exitPhysics()
{
	//cleanup in the reverse order of creation/initialization

	int i;
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		m_collisionShapes[j] = 0;
		delete shape;
	}

	delete m_dynamicsWorld;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfiguration;
}

void Physics::setDrawClusters(bool drawClusters)
{
	if (drawClusters)
	{
		getSoftDynamicsWorld()->setDrawFlags(getSoftDynamicsWorld()->getDrawFlags() | fDrawFlags::Clusters);
	} 
	else
	{
		getSoftDynamicsWorld()->setDrawFlags(getSoftDynamicsWorld()->getDrawFlags()& (~fDrawFlags::Clusters));
	}
}