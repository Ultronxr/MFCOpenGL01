// DialogLine.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogLine.h"
#include "afxdialogex.h"
#include "MFCOpenGL01View.h"

extern int view_flag_global;
extern int line_size_global, line_type_global;
extern COLORREF line_color_global;

// DialogLine 对话框

IMPLEMENT_DYNAMIC(DialogLine, CDialogEx)

DialogLine::DialogLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LINE, pParent)
{

}

DialogLine::~DialogLine()
{
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
    line_color_global = line_color.GetColor();
}

void DialogLine::OnBnClickedLineDda()
{
    view_flag_global = 2;
    line_size_global = GetDlgItemInt(IDC_EDIT5);
    line_type_global = 0;

    EndDialog(0);
}


void DialogLine::OnBnClickedLineMidpoint()
{
    view_flag_global = 2;
    line_size_global = GetDlgItemInt(IDC_EDIT5);
    line_type_global = 1;

    EndDialog(0);
}


void DialogLine::OnBnClickedLineBresenham()
{
    view_flag_global = 2;
    line_size_global = GetDlgItemInt(IDC_EDIT5);
    line_type_global = 2;

    EndDialog(0);
}
