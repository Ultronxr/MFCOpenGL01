/*
Ctrl+M+O 折叠所有方法
Ctrl+M+M 折叠或者展开当前方法
Ctrl+M+L 展开所有方法
*/

// MFCOpenGL01View.h : CMFCOpenGL01View 类的接口
//

#pragma once
#include "MFCOpenGL01Doc.h"

class CMFCOpenGL01View : public CView
{
protected: // 仅从序列化创建
	CMFCOpenGL01View();
    DECLARE_DYNCREATE(CMFCOpenGL01View)

// 特性
public:
	CMFCOpenGL01Doc* GetDocument() const;

// 操作
public:

// 重写
public:
    virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCOpenGL01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()




///成员变量

protected:
    HGLRC m_hRC;

    CMFCOpenGL01Doc* m_pDoc = NULL;

    CRectTracker m_RectTracker; //选择框


    //保存位图
    bool saveTag = false;
    CString saveFilePath = _T("D:\\");

    //打开位图
    CString BmpName;                               //保存图像文件文件名
    CString EntName;                               //保存图像文件扩展名
    CBitmap m_bitmap;                              //创建位图对象






///MFC窗口和按钮相关
public:
    afx_msg void OnDrawRuler();
    afx_msg void OnDrawOrtho();

    afx_msg void OnFileSave();
    afx_msg void OnFileOpen();
    void ShowBitmap(CDC *pDC, CString BmpName);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    
    
};

#ifndef _DEBUG  // MFCOpenGL01View.cpp 中的调试版本
inline CMFCOpenGL01Doc* CMFCOpenGL01View::GetDocument() const
   { return reinterpret_cast<CMFCOpenGL01Doc*>(m_pDocument); }
#endif

