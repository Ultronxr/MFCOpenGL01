// DialogPoint.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCOpenGL01.h"
#include "DialogPoint.h"
#include "afxdialogex.h"

// DialogPoint 对话框

IMPLEMENT_DYNAMIC(DialogPoint, CDialogEx)

DialogPoint::DialogPoint(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_POINT, pParent)
    , point_radio_group(0)
{
    m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogPoint::~DialogPoint()
{
    m_pDoc = NULL;
}

void DialogPoint::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MFCCOLORBUTTON1, point_color);
    DDX_Radio(pDX, IDC_RADIO1, point_radio_group);
}


BEGIN_MESSAGE_MAP(DialogPoint, CDialogEx)
    ON_BN_CLICKED(IDOK, &DialogPoint::OnBnClickedOk)
    ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogPoint::OnBnClickedMfccolorbutton1)
    ON_BN_CLICKED(IDC_RADIO1, &DialogPoint::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &DialogPoint::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &DialogPoint::OnBnClickedRadio3)
END_MESSAGE_MAP()


// DialogPoint 消息处理程序


void DialogPoint::OnBnClickedOk()
{
    m_pDoc->m_operation = 1;
    m_pDoc->m_size = GetDlgItemInt(IDC_EDIT3);
    m_pDoc->point_type = point_radio_group;

    EndDialog(0);
}


void DialogPoint::OnBnClickedMfccolorbutton1()
{
    m_pDoc->m_color = point_color.GetColor();
}


void DialogPoint::OnBnClickedRadio1()
{
    UpdateData(true);
}


void DialogPoint::OnBnClickedRadio2()
{
    UpdateData(true);
}


void DialogPoint::OnBnClickedRadio3()
{
    UpdateData(true);
}
