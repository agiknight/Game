#pragma once
#include "afxwin.h"


// CBrushPanel ��ȭ �����Դϴ�.

class CBrushPanel : public CDialogEx
								, public common::iObserver
{
public:
	CBrushPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBrushPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BRUSH };


public:
	virtual void Update() override;


protected:
	void UpdateTextureFiles();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	Image *m_texture;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListBox m_TextureFiles;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListTextureFiles();
	afx_msg void OnPaint();
};
