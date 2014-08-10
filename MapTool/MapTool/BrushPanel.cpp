// BrushPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "BrushPanel.h"
#include "afxdialogex.h"


// CBrushPanel ��ȭ �����Դϴ�.

CBrushPanel::CBrushPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBrushPanel::IDD, pParent)
,	m_texture(NULL)
{

}

CBrushPanel::~CBrushPanel()
{
}

void CBrushPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TEXTURE_FILES, m_TextureFiles);
}


BEGIN_MESSAGE_MAP(CBrushPanel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBrushPanel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBrushPanel::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST_TEXTURE_FILES, &CBrushPanel::OnSelchangeListTextureFiles)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBrushPanel �޽��� ó�����Դϴ�.
BOOL CBrushPanel::OnInitDialog()
{
	__super::OnInitDialog();

	UpdateTextureFiles();

	return TRUE;
}


void CBrushPanel::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CBrushPanel::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}


void CBrushPanel::Update()
{

}


void CBrushPanel::UpdateTextureFiles()
{
	// ����Ʈ �ڽ� �ʱ�ȭ.
	while (0 < m_TextureFiles.GetCount())
		m_TextureFiles.DeleteString(0);

	// ���� ã��.
	list<string> extList;
	extList.push_back("jpg");
	extList.push_back("png");
	extList.push_back("bmp");
	list<string> textureFiles;
	common::CollectFiles(extList, "../../media/terrain/", textureFiles);

	BOOST_FOREACH(auto &fileName, textureFiles)
	{
		const wstring wstr = str2wstr(fileName);
		m_TextureFiles.InsertString(m_TextureFiles.GetCount(), wstr.c_str());
	}
}


void CBrushPanel::OnSelchangeListTextureFiles()
{
	CString fileName;
	m_TextureFiles.GetText(m_TextureFiles.GetCurSel(), fileName);
	SAFE_DELETE(m_texture);
	m_texture = Image::FromFile(fileName);
	InvalidateRect(NULL, FALSE);
}


void CBrushPanel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Graphics *graph = Graphics::FromHDC(dc.GetSafeHdc());

	if (m_texture)
	{
		// �ؽ��� ���.
		if (CWnd *pictureCtlr = GetDlgItem(IDC_STATIC_TEXTURE))
		{
			CRect cr;
			pictureCtlr->GetWindowRect(cr);
			ScreenToClient(cr);

			const Rect dest(cr.left, cr.top, cr.Width(), cr.Height());
			graph->DrawImage(m_texture, dest );
		}
	}
}
