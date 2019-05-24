// DialogBezier.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogBezier.h"
#include "afxdialogex.h"


// DialogBezier 对话框

IMPLEMENT_DYNAMIC(DialogBezier, CDialogEx)

DialogBezier::DialogBezier(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_BEZIER, pParent)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogBezier::~DialogBezier()
{
    m_pDoc = NULL;
}

void DialogBezier::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, bezier_color);
}


BEGIN_MESSAGE_MAP(DialogBezier, CDialogEx)
    ON_BN_CLICKED(IDOK, &DialogBezier::OnBnClickedOk)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogBezier::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// DialogBezier 消息处理程序


void DialogBezier::OnBnClickedOk()
{
    m_pDoc->m_operation = 6;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT1);
    if (m_pDoc->m_size <= 0) m_pDoc->m_size = 1;

    EndDialog(0);
}


void DialogBezier::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = bezier_color.GetColor();
}
