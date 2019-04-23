#pragma once
#include "afxcolorbutton.h"


// DialogFill 对话框

class DialogFill : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFill)

public:
	DialogFill(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DialogFill();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CMFCColorButton fill_color;
    afx_msg void OnBnClickedMfccolorbutton1();
    afx_msg void OnBnClickedOk();
};
