// DialogPolygon.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogPolygon.h"
#include "afxdialogex.h"

#include "MFCOpenGL01View.h"

extern int view_flag_global;
extern int polygon_size_global;
extern COLORREF polygon_color_global;

// DialogPolygon 对话框

IMPLEMENT_DYNAMIC(DialogPolygon, CDialogEx)

DialogPolygon::DialogPolygon(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_POLYGON, pParent)
{

}

DialogPolygon::~DialogPolygon()
{
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
    polygon_size_global = GetDlgItemInt(IDC_EDIT1);
    view_flag_global = 5;

    EndDialog(0);
}


void DialogPolygon::OnBnClickedMfccolorbutton1()
{
    polygon_color_global = polygon_color.GetColor();
}
