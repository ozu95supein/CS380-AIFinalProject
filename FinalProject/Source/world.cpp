/* Copyright Steve Rabin, 2012. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright Steve Rabin, 2012"
 */

#include <Stdafx.h>

//#define UNIT_TESTING


World::World(void)
: m_initialized(false)
{

}

World::~World(void)
{
}

void World::InitializeSingletons( void )
{
	//Create Singletons
	m_clock = &g_clock;
	m_database = &g_database;
	m_msgroute = &g_msgroute;
	m_debuglog = &g_debuglog;
	m_debugdrawing = &g_debugdrawing;
	m_terrain = &g_terrain;
}
void World::CreateSquadMember(AI_Squad_Controller * controller, CMultiAnim *pMA, std::vector< CTiny* > *pv_pChars, CSoundManager *pSM, double dTimeCurrent)
{
	//oscars code AI controller
	GameObject* SquadMember = new GameObject(g_database.GetNewObjectID(), OBJECT_Character, "SquadMember");
	D3DXVECTOR3 pos1(0.0f, 0.0f, 0.0f);
	SquadMember->CreateBody(100, pos1);
	SquadMember->CreateMovement();
	SquadMember->CreateTiny(pMA, pv_pChars, pSM, dTimeCurrent);
	g_database.Store(*SquadMember);
	SquadMember->CreateStateMachineManager();
	SquadMember->GetStateMachineManager()->PushStateMachine(*new AI_Squad_Member(*SquadMember, controller), STATE_MACHINE_QUEUE_0, true);

}
void World::Initialize( CMultiAnim *pMA, std::vector< CTiny* > *pv_pChars, CSoundManager *pSM, double dTimeCurrent )
{
	if(!m_initialized)
	{
		m_initialized = true;
	
		g_terrain.Create();


#ifdef UNIT_TESTING

		//Create unit test game objects
		GameObject* unittest1 = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest1" );
		GameObject* unittest2 = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest2" );
		GameObject* unittest3a = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest3a" );
		GameObject* unittest3b = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest3b" );
		GameObject* unittest4 = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest4" );
		GameObject* unittest5 = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest5" );
		GameObject* unittest6 = new GameObject( g_database.GetNewObjectID(), OBJECT_Ignore_Type, "UnitTest6" );
		
		D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
		unittest1->CreateBody( 100, pos );
		unittest2->CreateBody( 100, pos );
		unittest3a->CreateBody( 100, pos );
		unittest3b->CreateBody( 100, pos );
		unittest4->CreateBody( 100, pos );
		unittest5->CreateBody( 100, pos );
		unittest6->CreateBody( 100, pos );

		unittest1->CreateStateMachineManager();
		unittest2->CreateStateMachineManager();
		unittest3a->CreateStateMachineManager();
		unittest3b->CreateStateMachineManager();
		unittest4->CreateStateMachineManager();
		unittest5->CreateStateMachineManager();
		unittest6->CreateStateMachineManager();
		
		g_database.Store( *unittest1 );
		g_database.Store( *unittest2 );
		g_database.Store( *unittest3a );
		g_database.Store( *unittest3b );
		g_database.Store( *unittest4 );
		g_database.Store( *unittest5 );
		g_database.Store( *unittest6 );

		//Give the unit test game objects a state machine
		unittest1->GetStateMachineManager()->PushStateMachine( *new UnitTest1( *unittest1 ), STATE_MACHINE_QUEUE_0, TRUE );
		unittest2->GetStateMachineManager()->PushStateMachine( *new UnitTest2a( *unittest2 ), STATE_MACHINE_QUEUE_0, TRUE );
		unittest3a->GetStateMachineManager()->PushStateMachine( *new UnitTest3a( *unittest3a ), STATE_MACHINE_QUEUE_0, TRUE );
		unittest3b->GetStateMachineManager()->PushStateMachine( *new UnitTest3b( *unittest3b ), STATE_MACHINE_QUEUE_0, TRUE );
		unittest4->GetStateMachineManager()->PushStateMachine( *new UnitTest4( *unittest4 ), STATE_MACHINE_QUEUE_0, TRUE );
		unittest5->GetStateMachineManager()->PushStateMachine( *new UnitTest5( *unittest5 ), STATE_MACHINE_QUEUE_0, TRUE );
		unittest6->GetStateMachineManager()->PushStateMachine( *new UnitTest6( *unittest6 ), STATE_MACHINE_QUEUE_0, TRUE );

#else

	{	//Agent

			FLOAT r, g, b, a;

		GameObject* agent = new GameObject( g_database.GetNewObjectID(), OBJECT_Player, "Player" );
		D3DXVECTOR3 pos(0.1125f, 0.0f, 0.1375f);
		agent->CreateBody( 100, pos );
		agent->CreateMovement();
		agent->CreateTiny( pMA, pv_pChars, pSM, dTimeCurrent );
		g_database.Store( *agent );
		agent->CreateStateMachineManager();
		agent->GetStateMachineManager()->PushStateMachine( *new Agent( *agent ), STATE_MACHINE_QUEUE_0, true );
		//m_pAI->SetDiffuse(&D3DXVECTOR4(r, g, b, 1.0f));
		r = 1.0;
		g = 0.0;
		b = 0.0;
		a = 0.0;
		//agent->GetTiny().SetDiffuse(&D3DXVECTOR4(r, g, b, a));
		
		//oscars code AI controller
		GameObject* AI_Controller = new GameObject(g_database.GetNewObjectID(), OBJECT_Character, "AI_Controller");
		D3DXVECTOR3 pos1(0.5f, 0.0f, 0.5f);
		AI_Controller->CreateBody(100, pos1);
		AI_Controller->CreateMovement();
		AI_Controller->CreateTiny(pMA, pv_pChars, pSM, dTimeCurrent);
		g_database.Store(*AI_Controller);
		AI_Controller->CreateStateMachineManager();
		//saving the AI_Controller so the squad members can use it
		AI_Squad_Controller * tempcontroller = new AI_Squad_Controller(*AI_Controller);
		AI_Controller->GetStateMachineManager()->PushStateMachine(*tempcontroller, STATE_MACHINE_QUEUE_0, true);
		//AI_Controller->GetTiny().SetDiffuse(&D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));

		//AI_Squad_Member(GameObject & object, AI_Squad_Controller * cont) : StateMachine(object), m_moving(true)
		//Member 1
		GameObject* Member1 = new GameObject(g_database.GetNewObjectID(), OBJECT_Player, "Member1");
		D3DXVECTOR3 pos2(0.0f, 0.0f, 0.0f);
		Member1->CreateBody(100, pos2);
		Member1->CreateMovement();
		Member1->CreateTiny(pMA, pv_pChars, pSM, dTimeCurrent);
		g_database.Store(*Member1);
		Member1->CreateStateMachineManager();
		//keep track of the squadmember state machines
		AI_Squad_Member * tempMember1 = new AI_Squad_Member(*(Member1), tempcontroller);
		Member1->GetStateMachineManager()->PushStateMachine(*tempMember1, STATE_MACHINE_QUEUE_0, true);
		//Member1->GetTiny().SetDiffuse(&D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));

		//Member 2
		GameObject* Member2 = new GameObject(g_database.GetNewObjectID(), OBJECT_Player, "Member2");
		D3DXVECTOR3 pos3(0.0f, 0.0f, 1.0f);
		Member2->CreateBody(100, pos3);
		Member2->CreateMovement();
		Member2->CreateTiny(pMA, pv_pChars, pSM, dTimeCurrent);
		g_database.Store(*Member2);
		Member2->CreateStateMachineManager();
		//keep track of the squadmember state machines
		AI_Squad_Member * tempMember2 = new AI_Squad_Member(*(Member2), tempcontroller);
		Member2->GetStateMachineManager()->PushStateMachine(*tempMember2, STATE_MACHINE_QUEUE_0, true);
		//Member2->GetTiny().SetDiffuse(&D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));


		//create and initialize the bb
		tempcontroller->CreateAndSetBB();
		//add squadmembers to the BB
		tempcontroller->AddSquadMember(Member1, tempMember1);
		tempcontroller->AddSquadMember(Member2, tempMember2);
		//set the squadcontroller in the members
		tempMember1->SetSquadController(tempcontroller);
		tempMember2->SetSquadController(tempcontroller);

	}

#if defined (PROJECT_THREE)
	{	// Enemy
		GameObject* enemy = new GameObject(g_database.GetNewObjectID(), OBJECT_Enemy, "Enemy");
		D3DXVECTOR3 pos(0.5f, 0.0f, 0.5f);
		enemy->CreateBody(100, pos);
		enemy->CreateMovement();
		enemy->GetMovement().SetSingleStep(false);
		enemy->GetMovement().SetDebugDraw(false);
		enemy->CreateTiny(pMA, pv_pChars, pSM, dTimeCurrent);
		enemy->GetTiny().SetDiffuse(0.0f, 0.0f, 1.0f);
		g_database.Store(*enemy);
		enemy->CreateStateMachineManager();
		enemy->GetStateMachineManager()->PushStateMachine(*new Enemy(*enemy), STATE_MACHINE_QUEUE_0, true);
	}
#endif


#endif

	}
}


void World::PostInitialize()
{
	g_database.Initialize();
}


void World::Update()
{
	g_clock.MarkTimeThisTick();
	g_database.Update();
}

void World::Animate( double dTimeDelta )
{
	g_database.Animate( dTimeDelta );
}

void World::AdvanceTimeAndDraw( IDirect3DDevice9* pd3dDevice, D3DXMATRIX* pViewProj, double dTimeDelta, D3DXVECTOR3 *pvEye )
{
	g_database.AdvanceTimeAndDraw( pd3dDevice, pViewProj, dTimeDelta, pvEye );
	g_terrain.DrawDebugVisualization( pd3dDevice );
}

void World::RestoreDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice )
{
	return( g_database.RestoreDeviceObjects( pd3dDevice ) );
}

void World::InvalidateDeviceObjects( void )
{
	g_database.InvalidateDeviceObjects();
}
