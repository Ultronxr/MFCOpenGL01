#pragma once
#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

// DialogPoint 对话框

class DialogPoint : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPoint)

public:
	DialogPoint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogPoint();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;
    

public:
    afx_msg void OnBnClickedOk();
    CMFCColorButton point_color;
    afx_msg void OnBnClickedMfccolorbutton1();
    int point_radio_group;
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
};
