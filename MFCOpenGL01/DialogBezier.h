#pragma once

#include "afxcolorbutton.h"
#include "MainFrm.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"
// DialogBezier 对话框

class DialogBezier : public CDialogEx
{
	DECLARE_DYNAMIC(DialogBezier)

public:
	DialogBezier(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogBezier();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BEZIER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;
    CMFCColorButton bezier_color;


public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedMfccolorbutton1();
    
};
