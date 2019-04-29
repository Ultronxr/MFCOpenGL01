#pragma once
#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

// DialogPolygon 对话框

class DialogPolygon : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPolygon)

public:
	DialogPolygon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogPolygon();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POLYGON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;

public:
    afx_msg void OnBnClickedOk();
    CMFCColorButton polygon_color;
    afx_msg void OnBnClickedMfccolorbutton1();
};
