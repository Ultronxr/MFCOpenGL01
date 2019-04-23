// DialogCirclePerfect.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogCirclePerfect.h"
#include "afxdialogex.h"

#include "MFCOpenGL01View.h"

extern int view_flag_global;
extern int circle_perfect_size_global, circle_perfect_type_global;
extern COLORREF circle_perfect_color_global;

// DialogCirclePerfect 对话框

IMPLEMENT_DYNAMIC(DialogCirclePerfect, CDialogEx)

DialogCirclePerfect::DialogCirclePerfect(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CIRCLE_PERFECT, pParent)
{

}

DialogCirclePerfect::~DialogCirclePerfect()
{
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
    circle_perfect_color_global = circle_perfect_color.GetColor();
}


void DialogCirclePerfect::OnBnClickedCirclePerfectBresenham()
{
    view_flag_global = 3;
    circle_perfect_size_global = GetDlgItemInt(IDC_EDIT4);
    circle_perfect_type_global = 0;

    EndDialog(0);
}


void DialogCirclePerfect::OnBnClickedCirclePerfectMidpoint()
{
    view_flag_global = 3;
    circle_perfect_size_global = GetDlgItemInt(IDC_EDIT4);
    circle_perfect_type_global = 1;

    EndDialog(0);
}


void DialogCirclePerfect::OnBnClickedButtonCirclePerfectXxx()
{
    view_flag_global = 3;
    circle_perfect_size_global = GetDlgItemInt(IDC_EDIT4);
    circle_perfect_type_global = 2;

    EndDialog(0);
}
