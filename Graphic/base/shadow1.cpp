
#include "stdafx.h"
#include "shadow1.h"

using namespace graphic;


cShadow1::cShadow1()
{
}

cShadow1::~cShadow1()
{
}


// �׸��� Ŭ���� ����.
bool cShadow1::Create(const int textureWidth, const int textureHeight)
{
	return m_surface.CreateRenderTarget(textureWidth, textureHeight);
}


// �׸��� �ؽ��ĸ� ������Ʈ �Ѵ�.
void cShadow1::UpdateShadow( cNode &node )
{
	RET(!m_surface.IsLoaded());

	Vector3 lightPos(500,1000,0);
	Vector3 pos = node.GetTM().GetPosition();

	m_surface.Begin();

	GetDevice()->Clear(0L, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, 0x00000000, 1.0f, 0L);

	Matrix44 matView;// �� ���
	matView.SetView2( lightPos, pos, Vector3(0,1,0));

	Matrix44 matProj;// ���� ���
	matProj.SetProjection( D3DX_PI/2.5f, 1, 0.1f, 10000);

	node.RenderShadow(matView*matProj, lightPos, Vector3(0,-1,0), Matrix44::Identity);

	m_surface.End();
}


// �׸��� �� ���.
void cShadow1::RenderShadowMap()
{
	m_surface.Render();
}
