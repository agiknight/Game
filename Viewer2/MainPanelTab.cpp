// MainPanelTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Viewer2.h"
#include "MainPanelTab.h"
#include "afxdialogex.h"
#include "ModelPanel.h"


// CMainPanelTab ��ȭ �����Դϴ�.

CMainPanelTab::CMainPanelTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainPanelTab::IDD, pParent)
,	m_pModelPanel(NULL)
{

}

CMainPanelTab::~CMainPanelTab()
{
}

void CMainPanelTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CMainPanelTab, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMainPanelTab::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMainPanelTab::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainPanelTab::OnSelchangeTab)
END_MESSAGE_MAP()


// CMainPanelTab �޽��� ó�����Դϴ�.


void CMainPanelTab::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void CMainPanelTab::OnBnClickedCancel()
{
	//CDialogEx::OnCancel();
}


BOOL CMainPanelTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Tab.InsertItem(0, L"Model");
	m_Tab.InsertItem(1, L"Animation");

	CRect cr;
	GetClientRect(cr);

	m_pModelPanel = new CModelPanel(this);
	m_pModelPanel->Create(CModelPanel::IDD, this);
	m_pModelPanel->MoveWindow(CRect(0, 25, cr.Width(), cr.Height()));
	m_pModelPanel->ShowWindow(SW_SHOW);

	cController::Get()->AddObserver(m_pModelPanel);

	return TRUE;
}


void CMainPanelTab::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch (m_Tab.GetCurSel())
	{
	case 0:
		m_pModelPanel->ShowWindow(SW_SHOW);
		break;

	case 1:
		m_pModelPanel->ShowWindow(SW_HIDE);
		break;
	}

	*pResult = 0;
}
