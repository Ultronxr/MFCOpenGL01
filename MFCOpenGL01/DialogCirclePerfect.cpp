// DialogCirclePerfect.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogCirclePerfect.h"
#include "afxdialogex.h"

// DialogCirclePerfect 对话框

IMPLEMENT_DYNAMIC(DialogCirclePerfect, CDialogEx)

DialogCirclePerfect::DialogCirclePerfect(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CIRCLE_PERFECT, pParent)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogCirclePerfect::~DialogCirclePerfect()
{
    m_pDoc = NULL;
}

void DialogCirclePerfect::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, circle_perfect_color);
}


BEGIN_MESSAGE_MAP(DialogCirclePerfect, CDialogEx)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogCirclePerfect::OnBnClickedMfccolorbutton1)
    ON_BN_CLICKED(IDC_CIRCLE_PERFECT_BRESENHAM, &DialogCirclePerfect::OnBnClickedCirclePerfectBresenham)
    ON_BN_CLICKED(IDC_CIRCLE_PERFECT_MIDPOINT, &DialogCirclePerfect::OnBnClickedCirclePerfectMidpoint)
    ON_BN_CLICKED(IDC_BUTTON_CIRCLE_PERFECT_XXX, &DialogCirclePerfect::OnBnClickedButtonCirclePerfectXxx)
END_MESSAGE_MAP()


// DialogCirclePerfect 消息处理程序

void DialogCirclePerfect::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = circle_perfect_color.GetColor();
}


void DialogCirclePerfect::OnBnClickedCirclePerfectBresenham()
{
    m_pDoc->m_operation = 3;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT4);
    m_pDoc->circle_perfect_type = 0;

    EndDialog(0);
}


void DialogCirclePerfect::OnBnClickedCirclePerfectMidpoint()
{
    m_pDoc->m_operation = 3;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT4);
    m_pDoc->circle_perfect_type = 1;

    EndDialog(0);
}


void DialogCirclePerfect::OnBnClickedButtonCirclePerfectXxx()
{
    m_pDoc->m_operation = 3;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT4);
    m_pDoc->circle_perfect_type = 2;

    EndDialog(0);
}
