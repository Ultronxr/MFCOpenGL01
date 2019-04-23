// DialogFill.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogFill.h"
#include "afxdialogex.h"

#include "MFCOpenGL01View.h"

extern int view_flag_global;
extern COLORREF fill_color_global;

// DialogFill 对话框

IMPLEMENT_DYNAMIC(DialogFill, CDialogEx)

DialogFill::DialogFill(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILL, pParent)
{

}

DialogFill::~DialogFill()
{
}

void DialogFill::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, fill_color);
}


BEGIN_MESSAGE_MAP(DialogFill, CDialogEx)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogFill::OnBnClickedMfccolorbutton1)
    ON_BN_CLICKED(IDOK, &DialogFill::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogFill 消息处理程序


void DialogFill::OnBnClickedMfccolorbutton1()
{
    fill_color_global = fill_color.GetColor();
}


void DialogFill::OnBnClickedOk()
{
    view_flag_global = 10;

    EndDialog(0);
}
