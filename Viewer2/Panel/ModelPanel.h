#pragma once
#include "afxcmn.h"


// CModelPanel ��ȭ �����Դϴ�.

class CModelPanel : public CDialogEx
{
public:
	CModelPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModelPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MODEL };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_MeshTree;
};
