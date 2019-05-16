
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MFCOpenGL01.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
    ON_COMMAND(TOOLBAR_DRAW_POINT, &CMainFrame::OnToolBarDrawPoint)
    ON_COMMAND(TOOLBAR_DRAW_LINE, &CMainFrame::OnToolBarDrawLine)
    ON_COMMAND(TOOLBAR_DRAW_CIRCLE_PERFECT, &CMainFrame::OnToolBarDrawCirclePerfect)
    ON_COMMAND(TOOLBAR_DRAW_CIRCLE_OVAL, &CMainFrame::OnToolBarDrawCircleOval)
    ON_COMMAND(TOOLBAR_DRAW_POLYGON, &CMainFrame::OnToolBarDrawPolygon)
    ON_COMMAND(TOOLBAR_TOOLS_MOUSE, &CMainFrame::OnToolBarToolsMouse)
    //ON_COMMAND(TOOLBAR_TOOLS_SELECT, &CMainFrame::OnToolBarToolsSelect)
    ON_COMMAND(TOOLBAR_TOOLS_FILL, &CMainFrame::OnToolBarToolsFill)
    //ON_COMMAND(TOOLBAR_TOOLS_ERASE, &CMainFrame::OnToolBarToolsErase)
    ON_COMMAND(TOOLBAR_TOOLS_CLEAR, &CMainFrame::OnToolBarToolsClear)
    //ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, &CMainFrame::OnToolbarDropDown)
    ON_COMMAND(TOOLBAR_TRANSFORM_TRANSLATE, &CMainFrame::OnToolBarTransformTranslate)
    ON_COMMAND(TOOLBAR_TRANSFORM_ROTATE, &CMainFrame::OnToolBarTransformRotate)
    ON_COMMAND(TOOLBAR_TRANSFORM_SCALE, &CMainFrame::OnToolBarTransformScale)
    ON_COMMAND(TOOLBAR_TRANSFORM_SYMMETRY_LR, &CMainFrame::OnToolBarTransformSymmetryLR)
    ON_COMMAND(TOOLBAR_TRANSFORM_SYMMETRY_TB, &CMainFrame::OnToolBarTransformSymmetryTB)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);

}

CMainFrame::~CMainFrame()
{
    m_pDoc = NULL;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this)){
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
    

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_MAINFRAME_256) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME_256)){
        TRACE0("未能创建标准工具栏\n"); return -1; }

    if (!m_drawToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_TOOLBAR_DRAW) ||
        !m_drawToolBar.LoadToolBar(IDR_TOOLBAR_DRAW)){
        TRACE0("未能创建绘图工具栏\n"); return -1; }
    
    if (!m_toolsToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_TOOLBAR_TOOLS) ||
        !m_toolsToolBar.LoadToolBar(IDR_TOOLBAR_TOOLS)) {
        TRACE0("未能创建工具工具栏\n"); return -1; }

    /*if (!m_linesizeToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_TOOLBAR_LINESIZE) ||
        !m_linesizeToolBar.LoadToolBar(IDR_TOOLBAR_LINESIZE)) {
        TRACE0("未能创建线宽工具栏\n"); return -1;
    }*/

    if (!m_transformToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), IDR_TOOLBAR_TOOLS) ||
        !m_transformToolBar.LoadToolBar(IDR_TOOLBAR_TRANSFORM)) {
        TRACE0("未能创建图形变换工具栏\n"); return -1;
    }

    EnableDocking(CBRS_ALIGN_TOP);
    m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
    m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
    m_drawToolBar.EnableDocking(CBRS_ALIGN_TOP);
    m_toolsToolBar.EnableDocking(CBRS_ALIGN_TOP);
    //m_linesizeToolBar.EnableDocking(CBRS_ALIGN_TOP);
    m_transformToolBar.EnableDocking(CBRS_ALIGN_TOP);
    
    DockPane(&m_wndMenuBar);
    //DockPane(&m_linesizeToolBar);
    DockPane(&m_transformToolBar);
    DockPaneLeftOf(&m_toolsToolBar, &m_transformToolBar);
    DockPaneLeftOf(&m_drawToolBar, &m_toolsToolBar);
    DockPaneLeftOf(&m_wndToolBar, &m_drawToolBar);
    





    




    //！！！！关闭把界面布局自动保存在注册表中，每次启动都是代码的初始界面
    this->GetDockingManager()->DisableRestoreDockState(TRUE);

	return 0;
}

void CMainFrame::OnToolbarDropDown() {

}


void CMainFrame::OnToolBarDrawPoint() {
    //if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();
    
    m_pDoc->m_color = RGB(0, 0, 0);
    DialogPoint dlg;
    dlg.DoModal();
}

void CMainFrame::OnToolBarDrawLine() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_color = RGB(0, 0, 0);
    DialogLine dlg;
    dlg.DoModal();
}

void CMainFrame::OnToolBarDrawCirclePerfect() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_color = RGB(0, 0, 0);
    DialogCirclePerfect dlg;
    dlg.DoModal();
}

void CMainFrame::OnToolBarDrawCircleOval() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_color = RGB(0, 0, 0);
    DialogCircleOval dlg;
    dlg.DoModal();
}

void CMainFrame::OnToolBarDrawPolygon() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_color = RGB(0, 0, 0);
    DialogPolygon dlg;
    dlg.DoModal();
}

void CMainFrame::OnToolBarToolsMouse() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_operation = 0;
    m_pDoc->m_color = RGB(0, 0, 0);
    m_pDoc->is_drawing_polygon = FALSE;
}

void CMainFrame::OnToolBarToolsSelect() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_operation = 20;
}

void CMainFrame::OnToolBarToolsFill() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_color = RGB(0, 0, 0);
    DialogFill dlg;
    dlg.DoModal();
}

void CMainFrame::OnToolBarToolsClear() {
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->v_point.clear();
    m_pDoc->v_line.clear();
    m_pDoc->v_perf_circle.clear();
    m_pDoc->v_oval_circle.clear();
    m_pDoc->v_polygon.clear();
    ((CMFCOpenGL01View*)GetActiveView())->Invalidate(TRUE);
    m_pDoc->selected_point = -1;
    m_pDoc->selected_line = -1;
    m_pDoc->selected_perfect_circle = -1;
    m_pDoc->selected_oval_circle = -1;
    m_pDoc->selected_polygon = -1;
}

void CMainFrame::OnToolBarTransformTranslate(){
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_operation = 100;
}

void CMainFrame::OnToolBarTransformRotate(){
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_operation = 101;
}

void CMainFrame::OnToolBarTransformScale(){
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    m_pDoc->m_operation = 102;
}

void CMainFrame::OnToolBarTransformSymmetryLR(){
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    int index = -1;
    if ((index = m_pDoc->selected_line) != -1) {
        m_pDoc->transform_symmetry_line(m_pDoc->v_line, index, 1);
        m_pDoc->selected_line = -1;
    }
    else if ((index = m_pDoc->selected_oval_circle) != -1) {
        m_pDoc->transform_symmetry_oval_circle(m_pDoc->v_oval_circle, index, 1);
        m_pDoc->selected_oval_circle = -1;
    }
    else if ((index = m_pDoc->selected_polygon) != -1) {
        m_pDoc->transform_symmetry_polygon(m_pDoc->v_polygon, index, 1);
        m_pDoc->selected_polygon = -1;
    }
    Invalidate(TRUE);
}

void CMainFrame::OnToolBarTransformSymmetryTB(){
    if (!m_pDoc) m_pDoc = (CMFCOpenGL01Doc*)((CMFCOpenGL01View*)GetActiveView())->GetDocument();

    int index = -1;
    if ((index = m_pDoc->selected_line) != -1) {
        m_pDoc->transform_symmetry_line(m_pDoc->v_line, index, 0);
        m_pDoc->selected_line = -1;
    }
    else if ((index = m_pDoc->selected_oval_circle) != -1) {
        m_pDoc->transform_symmetry_oval_circle(m_pDoc->v_oval_circle, index, 0);
        m_pDoc->selected_oval_circle = -1;
    }
    else if ((index = m_pDoc->selected_polygon) != -1) {
        m_pDoc->transform_symmetry_polygon(m_pDoc->v_polygon, index, 0);
        m_pDoc->selected_polygon = -1;
    }
    Invalidate(TRUE);
}







BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
}
