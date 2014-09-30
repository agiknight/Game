// TabPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "TabPanel.h"
#include "afxdialogex.h"
#include "HeightMapPanel.h"
#include "TerrainPanel.h"
#include "BrushPanel.h"
#include "ModelPanel.h"


// CTabPanel 대화 상자입니다.
CTabPanel::CTabPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabPanel::IDD, pParent)
,	m_modelPanel(NULL)
{

}

CTabPanel::~CTabPanel()
{
	SAFE_DELETE(m_heightMapPanel);
	SAFE_DELETE(m_terrainPanel);
	SAFE_DELETE(m_brushPanel);
	SAFE_DELETE(m_modelPanel);
}

void CTabPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CTabPanel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTabPanel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTabPanel::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabPanel::OnSelchangeTab1)
END_MESSAGE_MAP()


// CTabPanel 메시지 처리기입니다.


void CTabPanel::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void CTabPanel::OnBnClickedCancel()
{
	//CDialogEx::OnCancel();
}


BOOL CTabPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Tab.InsertItem(0,  L"Terrain");
	m_Tab.InsertItem(1, L"HeightMap");
	m_Tab.InsertItem(2,  L"Brush");
	m_Tab.InsertItem(3, L"Model");

	CRect cr;
	GetClientRect(cr);

	m_terrainPanel = new CTerrainPanel(this);
	m_terrainPanel->Create(CTerrainPanel::IDD, this);
	m_terrainPanel->MoveWindow(CRect(0, 25, cr.Width(), cr.Height()));
	m_panels.push_back(m_terrainPanel);

	m_heightMapPanel = new CHeightMapPanel(this);
	m_heightMapPanel->Create(CHeightMapPanel::IDD, this);
	m_heightMapPanel->MoveWindow(CRect(0, 25, cr.Width(), cr.Height()));
	m_panels.push_back(m_heightMapPanel);

	m_brushPanel = new CBrushPanel(this);
	m_brushPanel->Create(CBrushPanel::IDD, this);
	m_brushPanel->MoveWindow(CRect(0, 25, cr.Width(), cr.Height()));
	m_panels.push_back(m_brushPanel);

	m_modelPanel = new CModelPanel(this);
	m_modelPanel->Create(CModelPanel::IDD, this);
	m_modelPanel->MoveWindow(CRect(0, 25, cr.Width(), cr.Height()));
	m_panels.push_back(m_modelPanel);

	BOOST_FOREACH (auto &panel, m_panels)
	{
		if (iObserver2 *observer = dynamic_cast<iObserver2*>(panel))
			cMapController::Get()->AddObserver(observer);
	}

	ShowPanel(0);

	return TRUE;
}


void CTabPanel::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShowPanel(m_Tab.GetCurSel());
	*pResult = 0;
}


void CTabPanel::ShowPanel(int idx)
{
	BOOST_FOREACH (auto &panel, m_panels)
		panel->ShowWindow(SW_HIDE);

	if ((int)m_panels.size() > idx)
	{
		m_panels[ idx]->ShowWindow(SW_SHOW);	
		cMapController::Get()->ChangeEditMode((EDIT_MODE::TYPE)idx);
	}
}
