#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include "afxcmn.h"


// CModelPanel ��ȭ �����Դϴ�.

class CModelPanel : public CPanelBase
								, public iObserver2
{
public:
	CModelPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModelPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MODEL };


public:
	virtual void Update(int type) override;
	void UpdateModelList(const string &directoryPath);
	void UpdatePlaceModelList();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CListCtrl m_placeModelList;
	afx_msg void OnBnClickedButtonRefresh();
	CFileTreeCtrl m_modelTree;
	afx_msg void OnTvnSelchangedTreeModel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnModelmenuDeletemodel();
	afx_msg void OnLvnItemchangedListPlaceModel(NMHDR *pNMHDR, LRESULT *pResult);
};
