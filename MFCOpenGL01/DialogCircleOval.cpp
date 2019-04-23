// DialogCircleOval.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogCircleOval.h"
#include "afxdialogex.h"

#include "MFCOpenGL01View.h"

extern int view_flag_global;
extern int circle_oval_size_global, circle_oval_type_global;
extern COLORREF circle_oval_color_global;

// DialogCircleOval 对话框

IMPLEMENT_DYNAMIC(DialogCircleOval, CDialogEx)

DialogCircleOval::DialogCircleOval(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CIRCLE_OVAL, pParent)
{

}

DialogCircleOval::~DialogCircleOval()
{
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
    circle_oval_color_global = circle_oval_color.GetColor();
}

void DialogCircleOval::OnBnClickedButtonCircleOvalBresenham()
{
    view_flag_global = 4;
    circle_oval_type_global = 0;
    circle_oval_size_global = GetDlgItemInt(IDC_EDIT5);

    EndDialog(0);
}

void DialogCircleOval::OnBnClickedButtonCircleOvalMidpoint()
{
    view_flag_global = 4;
    circle_oval_type_global = 1;
    circle_oval_size_global = GetDlgItemInt(IDC_EDIT5);

    EndDialog(0);
}


void DialogCircleOval::OnBnClickedButtonCircleOvalXxx()
{
    view_flag_global = 4;
    circle_oval_type_global = 2;
    circle_oval_size_global = GetDlgItemInt(IDC_EDIT5);

    EndDialog(0);
}
