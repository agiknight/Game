// LightPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Viewer2.h"
#include "LightPanel.h"
#include "afxdialogex.h"


// CLightPanel ��ȭ �����Դϴ�.
CLightPanel::CLightPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLightPanel::IDD, pParent)
{

}

CLightPanel::~CLightPanel()
{
}

void CLightPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLightPanel, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CLightPanel::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CLightPanel::OnBnClickedOk)
END_MESSAGE_MAP()


// CLightPanel �޽��� ó�����Դϴ�.


void CLightPanel::OnBnClickedCancel()
{
	//CDialogEx::OnCancel();
}


void CLightPanel::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}
