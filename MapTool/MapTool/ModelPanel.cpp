// ModelPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
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
	DDX_Control(pDX, IDC_MFCEDITBROWSE_MODEL, m_modelBrowser);
	DDX_Control(pDX, IDC_LIST_MODEL, m_modelList);
}


BEGIN_MESSAGE_MAP(CModelPanel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModelPanel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CModelPanel::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE_MODEL, &CModelPanel::OnChangeMfceditbrowseModel)
	ON_LBN_SELCHANGE(IDC_LIST_MODEL, &CModelPanel::OnSelchangeListModel)
END_MESSAGE_MAP()


// CModelPanel �޽��� ó�����Դϴ�.


void CModelPanel::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}


void CModelPanel::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


BOOL CModelPanel::OnInitDialog()
{
	__super::OnInitDialog();

	m_modelBrowser.EnableFolderBrowseButton();
	m_modelBrowser.SetWindowText( L"../../media/" );
	UpdateModelList("../../media/" );

	return TRUE;
}


void CModelPanel::Update(int type)
{

}


void CModelPanel::UpdateModelList(const string &directoryPath)
{
	// ����Ʈ �ڽ� �ʱ�ȭ.
	while (0 < m_modelList.GetCount())
		m_modelList.DeleteString(0);

	// ���� ã��.
	list<string> extList;
	extList.push_back("dat");
	list<string> textureFiles;
	common::CollectFiles(extList, directoryPath, textureFiles);

	BOOST_FOREACH(auto &fileName, textureFiles)
	{
		const wstring wstr = str2wstr(fileName);
		m_modelList.InsertString(m_modelList.GetCount(), wstr.c_str());
	}	
}


void CModelPanel::OnChangeMfceditbrowseModel()
{
	CString wfilePath;
	m_modelBrowser.GetWindowText(wfilePath);
	string filePath = common::wstr2str((wstring)wfilePath);
	filePath += "\\";
	UpdateModelList(filePath);
}


void CModelPanel::OnSelchangeListModel()
{


	
}

