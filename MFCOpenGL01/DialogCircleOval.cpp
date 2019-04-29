// DialogCircleOval.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogCircleOval.h"
#include "afxdialogex.h"

// DialogCircleOval 对话框

IMPLEMENT_DYNAMIC(DialogCircleOval, CDialogEx)

DialogCircleOval::DialogCircleOval(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_DIALOG_CIRCLE_OVAL, pParent)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogCircleOval::~DialogCircleOval()
{
    m_pDoc = NULL;
}

void DialogCircleOval::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, circle_oval_color);
}


BEGIN_MESSAGE_MAP(DialogCircleOval, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CIRCLE_OVAL_BRESENHAM, &DialogCircleOval::OnBnClickedButtonCircleOvalBresenham)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogCircleOval::OnBnClickedMfccolorbutton1)
    ON_BN_CLICKED(IDC_BUTTON_CIRCLE_OVAL_MIDPOINT, &DialogCircleOval::OnBnClickedButtonCircleOvalMidpoint)
    ON_BN_CLICKED(IDC_BUTTON_CIRCLE_OVAL_XXX, &DialogCircleOval::OnBnClickedButtonCircleOvalXxx)
END_MESSAGE_MAP()


// DialogCircleOval 消息处理程序


void DialogCircleOval::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = circle_oval_color.GetColor();
}

void DialogCircleOval::OnBnClickedButtonCircleOvalBresenham()
{
    m_pDoc->m_operation = 4;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT5);
    if (m_pDoc->m_size <= 0) m_pDoc->m_size = 1;
    m_pDoc->circle_oval_type = 0;

    EndDialog(0);
}

void DialogCircleOval::OnBnClickedButtonCircleOvalMidpoint()
{
    m_pDoc->m_operation = 4;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT5);
    if (m_pDoc->m_size <= 0) m_pDoc->m_size = 1;
    m_pDoc->circle_oval_type = 1;

    EndDialog(0);
}


void DialogCircleOval::OnBnClickedButtonCircleOvalXxx()
{
    m_pDoc->m_operation = 4;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT5);
    if (m_pDoc->m_size <= 0) m_pDoc->m_size = 1;
    m_pDoc->circle_oval_type = 2;

    EndDialog(0);
}
