// ModelPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../Viewer2.h"
#include "ModelPanel.h"
#include "afxdialogex.h"


// CModelPanel ��ȭ �����Դϴ�.

CModelPanel::CModelPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelPanel::IDD, pParent)
{

}

CModelPanel::~CModelPanel()
{
}

void CModelPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_MESH, m_MeshTree);
}


BEGIN_MESSAGE_MAP(CModelPanel, CDialogEx)
END_MESSAGE_MAP()


// CModelPanel �޽��� ó�����Դϴ�.
