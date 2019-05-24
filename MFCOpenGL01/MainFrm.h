
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"
#include "DialogPoint.h"
#include "DialogLine.h"
#include "DialogCirclePerfect.h"
#include "DialogCircleOval.h"
#include "DialogPolygon.h"
#include "DialogBezier.h"
#include "DialogFill.h"


class CMainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CMFCOpenGL01Doc* m_pDoc = NULL;

	CMFCMenuBar m_wndMenuBar;
	CMFCToolBar m_wndToolBar;
    CMFCToolBar m_drawToolBar;
    CMFCToolBar m_toolsToolBar;
    //CMFCToolBar m_linesizeToolBar;
    //CMFCToolBar m_colorrefToolBar;
    CMFCToolBar m_transformToolBar;
    

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

    afx_msg void OnToolbarDropDown();

    afx_msg void OnToolBarDrawPoint();
    afx_msg void OnToolBarDrawLine();
    afx_msg void OnToolBarDrawCirclePerfect();
    afx_msg void OnToolBarDrawCircleOval();
    afx_msg void OnToolBarDrawPolygon();
    afx_msg void OnToolBarDrawBezier();
    afx_msg void OnToolBarToolsMouse();
    afx_msg void OnToolBarToolsSelect();
    afx_msg void OnToolBarToolsFill();
    afx_msg void OnToolBarToolsClear();
    
    afx_msg void OnToolBarTransformTranslate();
    afx_msg void OnToolBarTransformRotate();
    afx_msg void OnToolBarTransformScale();
    afx_msg void OnToolBarTransformSymmetryLR();
    afx_msg void OnToolBarTransformSymmetryTB();
};


