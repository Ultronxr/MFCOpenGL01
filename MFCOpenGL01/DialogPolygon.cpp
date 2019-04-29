// DialogPolygon.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogPolygon.h"
#include "afxdialogex.h"

// DialogPolygon 对话框

IMPLEMENT_DYNAMIC(DialogPolygon, CDialogEx)

DialogPolygon::DialogPolygon(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_POLYGON, pParent)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogPolygon::~DialogPolygon()
{
    m_pDoc = NULL;
}

void DialogPolygon::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, polygon_color);
}


BEGIN_MESSAGE_MAP(DialogPolygon, CDialogEx)
    ON_BN_CLICKED(IDOK, &DialogPolygon::OnBnClickedOk)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogPolygon::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// DialogPolygon 消息处理程序


void DialogPolygon::OnBnClickedOk()
{
    m_pDoc->m_operation = 5;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT1);
    if (m_pDoc->m_size <= 0) m_pDoc->m_size = 1;

    EndDialog(0);
}


void DialogPolygon::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = polygon_color.GetColor();
}
