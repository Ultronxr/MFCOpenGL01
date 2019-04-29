// DialogLine.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogLine.h"
#include "afxdialogex.h"

// DialogLine 对话框

IMPLEMENT_DYNAMIC(DialogLine, CDialogEx)

DialogLine::DialogLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LINE, pParent)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogLine::~DialogLine()
{
    m_pDoc = NULL;
}

void DialogLine::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, line_color);
}


BEGIN_MESSAGE_MAP(DialogLine, CDialogEx)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogLine::OnBnClickedMfccolorbutton1)
    ON_BN_CLICKED(IDC_LINE_DDA, &DialogLine::OnBnClickedLineDda)
    ON_BN_CLICKED(IDC_LINE_MIDPOINT, &DialogLine::OnBnClickedLineMidpoint)
    ON_BN_CLICKED(IDC_LINE_BRESENHAM, &DialogLine::OnBnClickedLineBresenham)
END_MESSAGE_MAP()


// DialogLine 消息处理程序


void DialogLine::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = line_color.GetColor();
}

void DialogLine::OnBnClickedLineDda()
{
    m_pDoc->m_operation = 2;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT5);
    m_pDoc->line_type = 0;

    EndDialog(0);
}


void DialogLine::OnBnClickedLineMidpoint()
{
    m_pDoc->m_operation = 2;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT5);
    m_pDoc->line_type = 1;

    EndDialog(0);
}


void DialogLine::OnBnClickedLineBresenham()
{
    m_pDoc->m_operation = 2;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT5);
    m_pDoc->line_type = 2;

    EndDialog(0);
}
