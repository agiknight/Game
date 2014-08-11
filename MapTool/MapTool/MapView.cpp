// MapView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "MapView.h"
#include "TerrainCursor.h"


using namespace graphic;


// CMapView
CMapView::CMapView() :
	m_dxInit(false)
,	m_RButtonDown(false)
,	m_cursor(NULL)
{

}

CMapView::~CMapView()
{
	SAFE_DELETE(m_cursor);
}

BEGIN_MESSAGE_MAP(CMapView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMapView �׸����Դϴ�.

void CMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CMapView �����Դϴ�.

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMapView �޽��� ó�����Դϴ�.

bool CMapView::Init()
{
	m_camera.SetCamera(Vector3(100,100,-500), Vector3(0,0,0), Vector3(0,1,0));
	m_camera.SetProjection( D3DX_PI / 4.f, (float)WINDOW_WIDTH / (float) WINDOW_HEIGHT, 1.f, 10000.0f);

	graphic::GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	graphic::GetDevice()->LightEnable (
		0, // Ȱ��ȭ/ ��Ȱ��ȭ �Ϸ��� ���� ����Ʈ ���� ���
		true); // true = Ȱ��ȭ �� false = ��Ȱ��ȭ


	m_grid.Create(64,64,50.f);
	m_cube.SetCube(Vector3(-10,-10,-10), Vector3(10,10,10));
	m_cube.SetColor( 0xFF0000FF );
	m_dxInit = true;

	m_terrainShader.Create( "../../media/shader/hlsl_terrain.fx", "TShader" );

	m_cursor = new cTerrainCursor();

	return true;
}


void CMapView::Render()
{
	if (!m_dxInit)
		return;

	//ȭ�� û��
	if (SUCCEEDED(graphic::GetDevice()->Clear( 
		0,			//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
		NULL,		//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
		D3DCOLOR_XRGB(150, 150, 150),			//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
		1.0f,				//���̹��۸� û���Ұ� ( 0 ~ 1 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
		0					//���ٽ� ���۸� ä�ﰪ
		)))
	{
		//ȭ�� û�Ұ� ���������� �̷�� ���ٸ�... ������ ����
		graphic::GetDevice()->BeginScene();
		graphic::GetRenderer()->RenderFPS();
		//graphic::GetRenderer()->RenderGrid();

		const Matrix44 matIdentity;

		m_terrainShader.SetMatrix( "mVP", m_camera.GetViewProjectionMatrix());
		m_terrainShader.SetVector( "vLightDir", Vector3(0,-1,0) );
		m_terrainShader.SetVector( "vEyePos", m_camera.GetEyePos());
		m_terrainShader.SetMatrix( "mWIT", matIdentity);
		m_terrainShader.SetMatrix( "mWorld", matIdentity);
		//m_terrainShader.SetTexture("ShadowMap", m_pShadowTex);

		m_terrainShader.SetRenderPass(1);
		//cMapController::Get()->GetTerrain().Render();
		cMapController::Get()->GetTerrain().RenderShader(m_terrainShader);


		if (cMapController::Get()->GetEditMode() == EDIT_MODE::MODE_BRUSH)
		{
			// Render Brush Line
			const Vector3 p0 = m_ray.orig + Vector3(10,10,0);
			const Vector3 p1 = m_ray.orig + m_ray.dir * 200.f;
			m_line.SetLine( p0, p1, 0.5f );
			//m_line.Render();
			m_cursor->Render();
		}

		graphic::GetRenderer()->RenderAxis();

		//������ ��
		graphic::GetDevice()->EndScene();
		//�������� �������� �������� ���� ȭ������ ����
		graphic::GetDevice()->Present( NULL, NULL, NULL, NULL );
	}

}


void CMapView::Update(float elapseT)
{
	graphic::GetRenderer()->Update(elapseT);

	if (m_cursor)
	{
		m_ray.Create(m_curPos.x, m_curPos.y, WINDOW_WIDTH, WINDOW_HEIGHT, 
			m_camera.GetProjectionMatrix(), m_camera.GetViewMatrix() );

		Vector3 pickPos;
		cMapController::Get()->GetTerrain().Pick( m_curPos.x, m_curPos.y, m_ray.orig, m_ray.dir, pickPos);
		m_cursor->UpdateCursor( cMapController::Get()->GetTerrain(), pickPos );
	}
}


void CMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);
}


void CMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonUp(nFlags, point);
}


void CMapView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	SetCapture();
	m_RButtonDown = true;
	m_curPos = point;
	CView::OnRButtonDown(nFlags, point);
}


void CMapView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_RButtonDown = false;	
	CView::OnRButtonUp(nFlags, point);
}


void CMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_RButtonDown)
	{
		CPoint pos = point - m_curPos;
		m_curPos = point;
		m_camera.Pitch2(pos.y * 0.005f); 
		m_camera.Yaw2(pos.x * 0.005f); 
	}
	else
	{
		m_curPos = point;
	}

	CView::OnMouseMove(nFlags, point);
}


void CMapView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMButtonDown(nFlags, point);
}


void CMapView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMButtonUp(nFlags, point);
}


BOOL CMapView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	const float len = m_camera.GetDistance();
	float zoomLen = (len > 100)? 50 : (len/4.f);
	if (nFlags & 0x4)
		zoomLen = zoomLen/10.f;

	m_camera.Zoom( (zDelta<0)? -zoomLen : zoomLen );	

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CMapView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_TAB:
		{
			static bool flag = false;
			graphic::GetDevice()->SetRenderState(D3DRS_CULLMODE, flag? D3DCULL_CCW : D3DCULL_NONE);
			graphic::GetDevice()->SetRenderState(D3DRS_FILLMODE, flag? D3DFILL_SOLID : D3DFILL_WIREFRAME);
			flag = !flag;
		}
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
