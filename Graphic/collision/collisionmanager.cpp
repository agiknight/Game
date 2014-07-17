
#include "stdafx.h"
#include "collisionmanager.h"
#include "collision.h"
#include <list>


using namespace graphic;


cCollisionManager::cCollisionManager()
{
	m_group1 = new sCollisionNode( 0 );
	m_group2 = new sCollisionNode( 0 );
}

cCollisionManager::~cCollisionManager()
{
	SAFE_DELETE(m_group1);
	SAFE_DELETE(m_group2);
}


//-----------------------------------------------------------------------------//
// nGroup: 0, 1 �� �����Ѵ�.
// �浹�׽�Ʈ�� �ٸ� �׷쳢���� �����ϴ�.
// pObj : �浹�׽�Ʈ�� ������Ʈ
// nTestNum : �浹�׽�Ʈ ��ȣ�̸�, �ٸ� �׷쿡�� ���� �浹�׽�Ʈ��ȣ ���� �浹�׽�Ʈ�Ѵ�.
//-----------------------------------------------------------------------------//
void cCollisionManager::InsertObject( int group, ICollisionable *obj, int nTestNum )
{
	sCollisionNode *node;
	if (0 == group) 
		node = m_group1;
	else if (1 == group) 
		node = m_group2;
	else 
		return;

	InsertObject( node, obj, nTestNum );
}


//-----------------------------------------------------------------------------//
// �浹�׽�Ʈ�� ������Ʈ �߰�
// pParent : �θ� �浹 ������Ʈ
// pParent ������Ʈ�� �浹���� �ڽ����� pObj ������Ʈ�� �浹�׽�Ʈ �˻�ȴ�.
//-----------------------------------------------------------------------------//
void cCollisionManager::InsertObject( ICollisionable *parent, ICollisionable *obj, int testNum )
{
	RET(!parent);

	// �α׷쿡�� �θ� ��带 ã�´�.
	sCollisionNode *node;
	node = (sCollisionNode*)m_group1->FindNode( parent->GetId() );
	if (!node) 
		node = (sCollisionNode*)m_group2->FindNode( parent->GetId() );

	InsertObject( node, obj, testNum );
}


//-----------------------------------------------------------------------------//
// �浹�׽�Ʈ�� ������Ʈ �߰�
// nTestNum �� 3�� ������Ʈ�� �̵��Ҷ� �浹�� üũ�ϴ� ��ȣ�̴�.
//-----------------------------------------------------------------------------//
void cCollisionManager::InsertObject( sCollisionNode *parent, ICollisionable *obj, int testNum )
{
	sCollisionNode *pnew = new sCollisionNode( obj->GetId() );
	pnew->testnum = testNum;
	pnew->pobj = obj;
	pnew->box = obj->GetCollisionBox();
	//pnew->psphere = pObj->GetSphere();

	parent->InsertChild(pnew);
}


//-----------------------------------------------------------------------------//
// ����Ʈ���� ������Ʈ �߰�
//-----------------------------------------------------------------------------//
void cCollisionManager::RemoveObject( ICollisionable *obj )
{
	m_group1->RemoveNode( obj->GetId() );
	m_group2->RemoveNode( obj->GetId() );
}


//-----------------------------------------------------------------------------//
// �浹�׽�Ʈ�ϱ� ���� CollisionBox ��ǥ�� ������Ʈ�Ѵ�.
// ���� �̵��Ǿ��ٸ� CollisionTest() �Լ� ȣ�� ���� �� �Լ��� ���� ȣ���ؾ� �Ѵ�.
//-----------------------------------------------------------------------------//
void cCollisionManager::UpdateCollisionBox()
{
	UpdateCollisionBoxRec(m_group1);
	UpdateCollisionBoxRec(m_group2);
}

void cCollisionManager::UpdateCollisionBoxRec( sCollisionNode *obj )
{
	RET(!obj);

	obj->pobj->UpdateCollisionBox();
	BOOST_FOREACH (auto &node, obj->GetChildren())
		UpdateCollisionBoxRec((sCollisionNode*)node);
}


//-----------------------------------------------------------------------------//
// nTestNum ������ ������ CollisionBox�鸸 �浹�׽�Ʈ�Ѵ�.
// �����׷쳢���� �浹�׽�Ʈ ���� �ʴ´�.
// �浹�� ������Ʈ ������ �����Ѵ�.
//-----------------------------------------------------------------------------//
int cCollisionManager::CollisionTest( int nTestNum )
{
	int cnt = 0;
	BOOST_FOREACH (cNode *p1, m_group1->GetChildren())
	{
		sCollisionNode *node1 = (sCollisionNode*)p1;
		if (!node1->pobj->IsTest(nTestNum))
			continue;

		BOOST_FOREACH (cNode *p2, m_group2->GetChildren())
		{
			sCollisionNode *node2 = (sCollisionNode*)p2;
			if (!node2->pobj->IsTest(nTestNum))
				continue;

			// �浹 �׽�Ʈ
			if (CheckNodeCollision(node1, node2, nTestNum))
			{
				// �ڽ��� ���ٸ� �浹�׽�Ʈ ��
				// nTestNum�� 3�̶�� ��Ʈ�� �浹�׽�Ʈ �Ѵ�.
//				if( 3 == nTestNum || (!node1->m_pChild && !node2->m_pChild) )
				//{
				//	m_ChkTable[ cnt][ 0] = node1->pobj;
				//	m_ChkTable[ cnt][ 1] = node2->pobj;
				//	++cnt;
				//}
				//else
				{
					//// �ڽ��� �ִٸ� �ڽı��� �浹�׽�Ʈ �����ؾ� ���������� �浹�� ���°� �ȴ�.
					//SObjTree *p1 = (SObjTree*)((node1->m_pChild)? node1->m_pChild : node1);
					//SObjTree *p2 = (SObjTree*)((node2->m_pChild)? node2->m_pChild : node2);
					//if (CollisionTest_SrcRec(p1, p2, nTestNum))
					//{
					//	m_ChkTable[ cnt][ 0] = node1->pobj;
					//	m_ChkTable[ cnt][ 1] = node2->pobj;
					//	++cnt;
					//}
				}
			}

		}

	}

	return 0;
}


bool cCollisionManager::CheckNodeCollision(sCollisionNode *node1, sCollisionNode *node2, int testNum )
{
	RETV(!node1 || !node2, false);

	// Src TestNum���� 0�϶��� Target�� TestNum������� �浹�׽�Ʈ�� �Ѵ�.
	// Src TestNum���� �����Ǿ� �������� ���ڷ� �Ѿ�� nTestNum���� Target�� TestNum�� �������� �浹�׽�Ʈ�Ѵ�.
	if ( ((0 != node1->testnum) && (testNum != node1->testnum)) 
		|| (((0 != node1->testnum) && (0 != node2->testnum)) && (node1->testnum != node2->testnum)) )
		return false;

	// Sphere vs Sphere �浹�׽�Ʈ

	// Box vs Box �浹�׽�Ʈ
	if (node1->box && node2->box)
	{
		if (node1->box->Collision(*node2->box))
		{
			//// �ڽ��� �ִٸ� �ڽı��� �浹�׽�Ʈ �����ؾ� ���������� �浹�� ���°� �ȴ�.
			sCollisionNode *p1 = (sCollisionNode*)((node1->GetChildren().empty())? node1->m_pChild : node1);
			sCollisionNode *p2 = (sCollisionNode*)((node2->m_pChild)? node2->m_pChild : node2);

			CollisionTestRec(node1, node2, testNum);
		}
	}

	return false;
}


int cCollisionManager::CollisionTestRec( sCollisionNode *srcNode, sCollisionNode *targetNode, int testNum )
{
	RETV(!srcNode || !targetNode, 0);

	if (srcNode->GetChildren().empty() && targetNode->GetChildren().empty())
		return 1;

	int cnt = 0;
	BOOST_FOREACH (cNode *p1, srcNode->GetChildren())
	{
		sCollisionNode *node1 = (sCollisionNode*)p1;
		if (!node1->pobj->IsTest(nTestNum))
			continue;

		BOOST_FOREACH (cNode *p2, targetNode->GetChildren())
		{
			sCollisionNode *node2 = (sCollisionNode*)p2;
			if (!node2->pobj->IsTest(nTestNum))
				continue;

			// �浹 �׽�Ʈ
			if (CheckNodeCollision(node1, node2, nTestNum))
			{
				// �ڽ��� ���ٸ� �浹�׽�Ʈ ��
				// nTestNum�� 3�̶�� ��Ʈ�� �浹�׽�Ʈ �Ѵ�.
				//				if( 3 == nTestNum || (!node1->m_pChild && !node2->m_pChild) )
				//{
				//	m_ChkTable[ cnt][ 0] = node1->pobj;
				//	m_ChkTable[ cnt][ 1] = node2->pobj;
				//	++cnt;
				//}
				//else
				{
					//// �ڽ��� �ִٸ� �ڽı��� �浹�׽�Ʈ �����ؾ� ���������� �浹�� ���°� �ȴ�.
					//SObjTree *p1 = (SObjTree*)((node1->m_pChild)? node1->m_pChild : node1);
					//SObjTree *p2 = (SObjTree*)((node2->m_pChild)? node2->m_pChild : node2);
					//if (CollisionTest_SrcRec(p1, p2, nTestNum))
					//{
					//	m_ChkTable[ cnt][ 0] = node1->pobj;
					//	m_ChkTable[ cnt][ 1] = node2->pobj;
					//	++cnt;
					//}
				}
			}
		}
	}

	return cnt;
}
