#pragma once
#include "afxcmn.h"


// CMainPanelTab 대화 상자입니다.
class CModelPanel;

class CMainPanelTab : public CDialogEx
{
public:
	CMainPanelTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMainPanelTab();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MAINPANEL };


protected:
	CModelPanel *m_pModelPanel;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CTabCtrl m_Tab;
};
