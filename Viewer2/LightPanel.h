#pragma once


// CLightPanel ��ȭ �����Դϴ�.

class CLightPanel : public CDialogEx
{
public:
	CLightPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLightPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
