#pragma once
#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

// DialogCircleOval 对话框

class DialogCircleOval : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCircleOval)

public:
	DialogCircleOval(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogCircleOval();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CIRCLE_OVAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;

public:
    CMFCColorButton circle_oval_color;
    afx_msg void OnBnClickedButtonCircleOvalBresenham();
    afx_msg void OnBnClickedMfccolorbutton1();
    afx_msg void OnBnClickedButtonCircleOvalMidpoint();
    afx_msg void OnBnClickedButtonCircleOvalXxx();
};
