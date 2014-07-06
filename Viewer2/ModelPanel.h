#pragma once
#include "afxcmn.h"


namespace graphic  {
	class cBoneNode;
}


// CModelPanel ��ȭ �����Դϴ�.
class CModelPanel : public CDialogEx
								, public common::iObserver
{
public:
	CModelPanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModelPanel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MODEL };

	virtual void Update() override;


protected:
	void UpdateMeshInfo();
	void UpdateMaterialInfo();
	void UpdateBoneInfo();
	void UpdateRawBoneInfo();
	void MakeBoneTree(HTREEITEM hParent,  graphic::cBoneNode *node);
	void ExpandAll(CTreeCtrl &treeCtrl);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.


	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_MeshTree;
	CTreeCtrl m_MaterialTree;
	CTreeCtrl m_RawBoneTree;
	CTreeCtrl m_BoneTree;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
