
// MFCOpenGL01View.cpp : CMFCOpenGL01View 类的实现
//


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCOpenGL01.h"

#include "DialogPoint.h"
#include "DialogLine.h"
#include "DialogCirclePerfect.h"
#include "DialogCircleOval.h"
#include "DialogPolygon.h"
#include "DialogFill.h"

#endif

//#include "MFCOpenGL01Doc.h"
#include "MFCOpenGL01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCOpenGL01View

IMPLEMENT_DYNCREATE(CMFCOpenGL01View, CView)

BEGIN_MESSAGE_MAP(CMFCOpenGL01View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCOpenGL01View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_PAINT()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(ID_DRAW_RULER, &CMFCOpenGL01View::OnDrawRuler)
    ON_COMMAND(ID_DRAW_ORTHO, &CMFCOpenGL01View::OnDrawOrtho)
    ON_COMMAND(ID_32784, &CMFCOpenGL01View::OnDrawLine)
    ON_COMMAND(ID_32783, &CMFCOpenGL01View::OnDrawPoint)
    ON_COMMAND(ID_32785, &CMFCOpenGL01View::OnDrawCirclePerfect)
    ON_COMMAND(ID_32786, &CMFCOpenGL01View::OnDrawCircleOval)
    ON_COMMAND(ID_32788, &CMFCOpenGL01View::OnDrawPolygon)
    ON_COMMAND(ID_32789, &CMFCOpenGL01View::OnDrawFill)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_COMMAND(ID_32792, &CMFCOpenGL01View::OnDrawSelect)
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_32793, &CMFCOpenGL01View::OnDrawErase)
    ON_COMMAND(ID_32794, &CMFCOpenGL01View::OnDrawClear)
    ON_COMMAND(ID_FILE_SAVE, &CMFCOpenGL01View::OnFileSave)
    ON_COMMAND(ID_FILE_OPEN, &CMFCOpenGL01View::OnFileOpen)
END_MESSAGE_MAP()

// CMFCOpenGL01View 构造/析构


CMFCOpenGL01View::CMFCOpenGL01View()
{
	// TODO: 在此处添加构造代码
    //AfxInitRichEdit(); //初始化RichEdit2.0!!!!!!!!
    
    m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
    m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;
}

CMFCOpenGL01View::~CMFCOpenGL01View()
{
}

BOOL CMFCOpenGL01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
    
	return CView::PreCreateWindow(cs);
}


// CMFCOpenGL01View 打印


void CMFCOpenGL01View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCOpenGL01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCOpenGL01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: 添加额外的打印前进行的初始化过程
}

void CMFCOpenGL01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCOpenGL01View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCOpenGL01View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCOpenGL01View 诊断

#ifdef _DEBUG
void CMFCOpenGL01View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOpenGL01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOpenGL01Doc* CMFCOpenGL01View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOpenGL01Doc)));
	return (CMFCOpenGL01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCOpenGL01View 消息处理程序

/****************************************OpenGL相关核心代码 开始************************************/

//int CMFCOpenGL01View::OnCreate(LPCREATESTRUCT lpCreateStruct){
//    if (CView::OnCreate(lpCreateStruct) == -1)
//        return -1;
//
//    // TODO:  在此添加您专用的创建代码
//
//    CClientDC dc(this);
//    PIXELFORMATDESCRIPTOR pfd;
//    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
//    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
//    pfd.nVersion = 1;
//    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.cColorBits = 24;
//    pfd.cDepthBits = 32;
//    int pixelFormat = ChoosePixelFormat(dc.m_hDC, &pfd);
//    SetPixelFormat(dc.m_hDC, pixelFormat, &pfd);
//    m_hRC = wglCreateContext(dc.m_hDC);
//    return 0;
//}

//void CMFCOpenGL01View::OnSize(UINT nType, int cx, int cy){
//    CView::OnSize(nType, cx, cy);
//
//    // TODO: 在此处添加消息处理程序代码
//    CClientDC dc(this);
//    wglMakeCurrent(dc.m_hDC, m_hRC);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    double deepth = 100;
//    double n = 1;
//
//    //glOrtho(-cx / n, -cx / n, -cy / n, -cy / n, -deepth, deepth);
//    glOrtho(0, 1920, 0, 1080, -100, 100); //设置坐标系
//
//    glMatrixMode(GL_MODELVIEW);
//    glViewport(0, 0, cx, cy);
//    //int viewport_arg = cx > cy ? cx : cy;
//    //glViewport(0, 0, viewport_arg, viewport_arg);
//    wglMakeCurrent(NULL, NULL);
//    //ReSizeGLScene(cx, cy);
//}

//void CMFCOpenGL01View::ReSizeGLScene(int width, int height) {
//    if (height == 0) height = 1;
//
//    glViewport(0, 0, width, height);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}

void CMFCOpenGL01View::OnDraw(CDC* pDC){
    CMFCOpenGL01Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: 在此处为本机数据添加绘制代码

    //作业
    COLORREF red = RGB(255, 0, 0), green = RGB(0, 255, 0), blue = RGB(0 ,0 ,255),  black = RGB(0, 0, 0);
    
    if (EntName.Compare(_T("bmp")) == 0){
        ShowBitmap(pDC, BmpName);               //显示图片
        EntName = "";
    }
    /*
    FillPath
    FillRect 填矩形 √
    FillRgn
    PolyPolygon 填多边形，带黑色边框 √
    FloodFill 填最小的封闭区域 （默认为FLOODFILLBORDER）√
    ExtFloodFill 带模式填封闭区域（FLOODFILLBORDER 指定边界颜色，FLOODFILLSURFACE 指定需要覆盖的颜色）√
    */
    
    //CPen cpen;
    //cpen.CreatePen(PS_SOLID, 10, red);
    //CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    //
    //pDC->MoveTo(100, 100);
    //pDC->LineTo(500, 500);

    //pDC->SetROP2(R2_NOTXORPEN);
    //pDC->MoveTo(100, 100);
    //pDC->LineTo(500, 500);

    ///*pDC->MoveTo(100, 100);
    //pDC->LineTo(500, 500);*/

    //pDC->SelectObject(pOldPen);
    //cpen.DeleteObject();

    /*wglMakeCurrent(pDC->m_hDC, m_hRC);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3d(255,0,0);

    ....

    SwapBuffers(pDC->m_hDC);
    wglMakeCurrent(NULL, NULL);*/
}


//BOOL CMFCOpenGL01View::OnEraseBkgnd(CDC* pDC){
//    //return CView::OnEraseBkgnd(pDC);
//    return TRUE;
//}

//void CMFCOpenGL01View::OnDestroy(){
//    CView::OnDestroy();
//
//    // TODO: 在此处添加消息处理程序代码
//    wglMakeCurrent(NULL, NULL);
//    wglDeleteContext(m_hRC);
//    m_hRC = NULL;
//}


/****************************************OpenGL相关核心代码 结束************************************/





/**********************************************MFC窗口和按钮相关 开始****************************************/

//对话框中的变量

//定义哪种操作，1点，2线，3圆，4椭圆，5多边形
int view_flag_global = 0;

//画点
int point_size_global, point_type_global;
COLORREF point_color_global;

//画线
int line_size_global, line_type_global;
COLORREF line_color_global;

//画正圆
int circle_perfect_size_global, circle_perfect_type_global;
COLORREF circle_perfect_color_global;

//画椭圆
int circle_oval_size_global, circle_oval_type_global;
COLORREF circle_oval_color_global;

//画多边形
CMFCOpenGL01View::polygon polygon_global;
COLORREF polygon_color_global;
int polygon_size_global;
BOOL is_drawing_polygon_gloabl = FALSE;

//填充
COLORREF fill_color_global;




//菜单栏的菜单项

void CMFCOpenGL01View::OnDrawRuler()
{
    // TODO: 在此添加命令处理程序代码

    //简单刻度（每50像素一刻度）
    CDC *pDC = GetDC();
    for (int i = 0; i <= 1920; i += 50) line_dda(pDC, RGB(0, 0, 0), i, 0, i, 10);
    for (int i = 0; i <= 1920; i += 50) line_dda(pDC, RGB(0, 0, 0), 0, i, 10, i);
}

void CMFCOpenGL01View::OnDrawOrtho()
{
    // TODO: 在此添加命令处理程序代码

    //模拟笛卡尔坐标系（坐标原点在(900,400)，每隔50像素为单位1）
    CDC *pDC = GetDC();
    int xx = 900, yy = 400;
    line_dda(pDC, RGB(0, 0, 0), xx, 0, xx, 1080); for (int j = 0; j <= 1080; j += 50) line_dda(pDC, RGB(0, 0, 0), xx, j, xx + 10, j);
    line_dda(pDC, RGB(0, 0, 0), 0, yy, 1960, yy); for (int j = 0; j <= 1920; j += 50) line_dda(pDC, RGB(0, 0, 0), j, yy - 10, j, yy);
}

void CMFCOpenGL01View::OnDrawPoint()
{
    //view_flag_global = 1;
    point_color_global = RGB(0, 0, 0);
    DialogPoint dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawLine()
{
    //view_flag_global = 2;
    line_color_global = RGB(0, 0, 0);
    DialogLine dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawCirclePerfect()
{
    //view_flag_global = 3;
    circle_perfect_color_global = RGB(0, 0, 0);
    DialogCirclePerfect dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawCircleOval()
{
    //view_flag_global = 4;
    circle_oval_color_global = RGB(0, 0, 0);
    DialogCircleOval dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawPolygon()
{
    //view_flag_global = 5;
    polygon_color_global = RGB(0, 0, 0);
    DialogPolygon dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawFill()
{
    //view_flag_global = 10;
    fill_color_global = RGB(0, 0, 0);
    DialogFill dlg;
    dlg.DoModal();
}

void CMFCOpenGL01View::OnDrawSelect()
{
    view_flag_global = 20;
}

void CMFCOpenGL01View::OnDrawErase()
{
    view_flag_global = 30;
}

void CMFCOpenGL01View::OnDrawClear()
{
    /*CRect rc;
    GetClientRect(&rc);
    GetDC()->FillSolidRect(&rc, RGB(255, 255, 255));*/
    Invalidate(TRUE);
}



void CMFCOpenGL01View::OnFileSave()
{
    Invalidate(FALSE); 
    CClientDC dc(this);
    CRect rect;
    BOOL  showMsgTag;                  //是否要弹出”图像保存成功对话框" 
    GetClientRect(&rect);                  //获取画布大小
    HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
    //创建兼容位图
    HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
    HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
    //将位图选入DC，并保存返回值 
    BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
    //将屏幕DC的图像复制到内存DC中
    CImage image;
    image.Attach(hbitmap);                //将位图转化为一般图像
    if (!saveTag)                          //如果图像是第一次被写入,则打开对话框
    {
        saveTag = TRUE;
        showMsgTag = TRUE;
        CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件|*.gif|PNG图像文件|*.png|其他格式(*.*)|*.*||");
        CFileDialog dlg(FALSE, _T("bmp"), _T("iPaint1.bmp"), NULL, strFilter);
        if (dlg.DoModal() != IDOK)
            return;

        CString strFileName;          //如果用户没有指定文件扩展名，则为其添加一个
        CString strExtension;
        strFileName = dlg.m_ofn.lpstrFile;
        if (dlg.m_ofn.nFileExtension = 0)               //扩展名项目为0
        {
            switch (dlg.m_ofn.nFilterIndex) {
            case 1:
                strExtension = "bmp"; break;
            case 2:
                strExtension = "jpg"; break;
            case 3:
                strExtension = "gif"; break;
            case 4:
                strExtension = "png"; break;
            default:
                break;
            }
            strFileName = strFileName + "." + strExtension;
        }
        saveFilePath = strFileName;     //saveFilePath为视类中的全局变量,类型为CString
    }
    else {
        showMsgTag = FALSE;
    }
    //AfxMessageBox(saveFilePath);               //显示图像保存的全路径(包含文件名)
    HRESULT hResult = image.Save(saveFilePath);     //保存图像
    if (FAILED(hResult)) {
        MessageBox(_T("保存图像文件失败！"));
    }
    else {
        if (showMsgTag)
            MessageBox(_T("文件保存成功！"));
    }
    image.Detach();
    SelectObject(hdc, hOldMap);
}

void CMFCOpenGL01View::OnFileOpen()
{
    CString filter;
    filter = "位图文件(*.bmp)|*.bmp|其他格式(*.*)|*.*||";
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);
    //按下确定按钮 dlg.DoModal() 函数显示对话框
    if (dlg.DoModal() == IDOK)
    {
        BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
        EntName = dlg.GetFileExt();      //获取文件扩展名
        EntName.MakeLower();             //将文件扩展名转换为一个小写字符
        Invalidate();                    //调用该函数就会调用OnDraw重绘画图
    }

    
}

void CMFCOpenGL01View::ShowBitmap(CDC *pDC, CString BmpName)
{
    //定义bitmap指针 调用函数LoadImage装载位图
    HBITMAP m_hBitmap;
    m_hBitmap = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

    if (m_bitmap.m_hObject)
    {
        m_bitmap.Detach();           //切断CWnd和窗口联系
    }
    m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联

                                     //边界
    CRect rect;
    GetClientRect(&rect);

    //图片显示(x,y)起始坐标
    int m_showX = 0;
    int m_showY = 0;
    int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度
    int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度

                                                   //定义并创建一个内存设备环境DC
    CDC dcBmp;
    if (!dcBmp.CreateCompatibleDC(pDC))   //创建兼容性的DC
        return;

    BITMAP m_bmp;                          //临时bmp图片变量
    m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中

    CBitmap *pbmpOld = NULL;
    dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

                                           //图片显示调用函数stretchBlt
    pDC->StretchBlt(0, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);

    dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图
    DeleteObject(&m_bitmap);               //删除内存中的位图
    dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC
}


BOOL CMFCOpenGL01View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{

    if (pWnd == this && m_RectTracker.SetCursor(this, nHitTest)) {
        return TRUE;
    }
    if (pWnd == this && view_flag_global != 0) {
        HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);
        ::SetCursor(hCur);
        return TRUE;
    }
    return CView::OnSetCursor(pWnd, nHitTest, message);
}

CPoint oldPoint, newPoint;
//备份目标区域的内容，选择框再次移到别的地方去需要填回去
CRect rect_parent, rect_old, rect_new;
CDC dc_backup;
int clk_inside = 0;

void CMFCOpenGL01View::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (view_flag_global == 2) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 3) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 3) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 4) {
        oldPoint = point;
        newPoint = point;
    }
    else if (view_flag_global == 5) {
        if (!is_drawing_polygon_gloabl) {
            oldPoint = point;
            newPoint = point;
            is_drawing_polygon_gloabl = TRUE;
        }
        else {
            newPoint = point;
        }
    }
    else if (view_flag_global == 20) {
        
        m_RectTracker.TrackRubberBand(this, point, TRUE);
        m_RectTracker.m_rect.NormalizeRect();
        m_RectTracker.Draw(GetDC());

        rect_parent = m_RectTracker.m_rect;
        rect_old = m_RectTracker.m_rect;

        view_flag_global = 21;
    }
    else if (view_flag_global == 21) {
        
        int judge = m_RectTracker.HitTest(point);
        if (judge < 0) { //光标位置在选框外部，重置选择框
            m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
            m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

            if (clk_inside > 0) {
                rect_parent.top--; rect_parent.bottom++; rect_parent.left--; rect_parent.right++;
                GetDC()->FillSolidRect(rect_parent, RGB(255, 255, 255));
            }
            
            clk_inside = 0;
            view_flag_global = 0;
        }
        else { //把选择框内的像素全部复制到目标区域
            clk_inside++;

            rect_old = m_RectTracker.m_rect;
            

            m_RectTracker.Track(this, point, TRUE);
            //Invalidate(TRUE);
            m_RectTracker.Draw(GetDC());

            BitBlt(GetDC()->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, rect_old.Width(), rect_old.Height(), dc_backup.m_hDC, 0, 0, SRCCOPY);

            rect_new = m_RectTracker.m_rect;
            int x = m_RectTracker.m_rect.TopLeft().x, y = m_RectTracker.m_rect.TopLeft().y;
            int width = m_RectTracker.m_rect.Width(), height = m_RectTracker.m_rect.Height();

            //备份目标覆盖区域的图像
            //BitBlt(dc_backup.m_hDC, 0, 0, width, height, GetDC()->m_hDC, x, y, SRCCOPY);

            
            //绘制图像
            BitBlt(GetDC()->m_hDC, x, y, width, height, GetDC()->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, SRCCOPY);

            rect_old.top--; rect_old.bottom++; rect_old.left--; rect_old.right++;
            GetDC()->FillSolidRect(rect_old, RGB(255, 255, 255));
        }
    }

    CView::OnLButtonDown(nFlags, point);
}

CDC *dc2;

void CMFCOpenGL01View::OnLButtonUp(UINT nFlags, CPoint point)
{
    dc2 = GetDC();
    dc2->SetROP2(R2_NOT);

    if (view_flag_global == 1) {
        if (point_type_global == 0)
            point_circle(GetDC(), point_color_global, point.x, point.y, point_size_global);

        if (point_type_global == 1)
            point_cross(GetDC(), point_color_global, point.x, point.y, point_size_global);

        if (point_type_global == 2)
            point_rhombus(GetDC(), point_color_global, point.x, point.y, point_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 2) {
        //抹去最后一次的作图提示线
        dc2->MoveTo(oldPoint);
        dc2->LineTo(newPoint);

        if (line_type_global == 0) line_dda_cpen(GetDC(), line_color_global, oldPoint.x, oldPoint.y, point.x, point.y, line_size_global);
        else if (line_type_global == 1) line_midpoint_cpen(GetDC(), line_color_global, oldPoint.x, oldPoint.y, point.x, point.y, line_size_global);
        else if (line_type_global == 2) line_bresenham_cpen(GetDC(), line_color_global, oldPoint.x, oldPoint.y, point.x, point.y, line_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        
        //抹去最后一次的作图提示线
        dc2->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        if (circle_perfect_type_global == 0) circle_perfect_bresenham_cpen(GetDC(), circle_perfect_color_global, oldPoint.x, oldPoint.y, radius, circle_perfect_size_global);
        else if (circle_perfect_type_global == 1) circle_perfect_midpoint_cpen(GetDC(), circle_perfect_color_global, oldPoint.x, oldPoint.y, radius, circle_perfect_size_global);
        else if (circle_perfect_type_global == 2) circle_perfect_midpoint_cpen(GetDC(), circle_perfect_color_global, oldPoint.x, oldPoint.y, radius, circle_perfect_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 4) {
        //抹去最后一次的作图提示线
        dc2->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        int x0 = (oldPoint.x + newPoint.x) / 2, y0 = (oldPoint.y + newPoint.y) / 2;
        int a = std::abs(x0 - oldPoint.x), b = std::abs(y0 - oldPoint.y);
        if (circle_oval_type_global == 0) circle_oval_bresenham_cpen(GetDC(), circle_oval_color_global, x0, y0, a, b, circle_oval_size_global);
        else if (circle_oval_type_global == 1) circle_oval_midpoint_cpen(GetDC(), circle_oval_color_global, x0, y0, a, b, circle_oval_size_global);
        else if (circle_oval_type_global == 2) circle_oval_midpoint_cpen(GetDC(), circle_oval_color_global, x0, y0, a, b, circle_oval_size_global);

        view_flag_global = 0;
    }
    else if (view_flag_global == 5) {
        //抹去最后一次的作图提示线
        dc2->MoveTo(oldPoint);
        dc2->LineTo(newPoint);

        polygon_global.vertexes.push_back(vertex(point.x, point.y));
        polygon_global.vertex_num++;

        oldPoint.x = polygon_global.vertexes[(polygon_global.vertex_num) - 1].x;
        oldPoint.y = polygon_global.vertexes[(polygon_global.vertex_num) - 1].y;

        if (polygon_global.vertex_num == 1) {
            point_circle(GetDC(), polygon_color_global, point.x, point.y, polygon_size_global);
        }
        else {
            line_midpoint_cpen(GetDC(), polygon_color_global, polygon_global.vertexes[(polygon_global.vertex_num) - 1].x, polygon_global.vertexes[(polygon_global.vertex_num) - 1].y, polygon_global.vertexes[(polygon_global.vertex_num) - 2].x, polygon_global.vertexes[(polygon_global.vertex_num) - 2].y, polygon_size_global);
        }
    }
    else if (view_flag_global == 10) {
        flood_fill_cbrush(GetDC(), fill_color_global, GetDC()->GetPixel(point.x, point.y), point);

        view_flag_global = 0;
    }
    
    CView::OnLButtonUp(nFlags, point);
}


void CMFCOpenGL01View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    if (view_flag_global == 5) {
        polygon_global.vertexes.push_back(vertex(point.x, point.y));
        polygon_global.vertex_num++;
        if (polygon_global.vertex_num == 1) {
            point_circle(GetDC(), polygon_color_global, point.x, point.y, polygon_size_global);
        }
        else {
            line_midpoint_cpen(GetDC(), polygon_color_global, polygon_global.vertexes[(polygon_global.vertex_num) - 1].x, polygon_global.vertexes[(polygon_global.vertex_num) - 1].y, polygon_global.vertexes[(polygon_global.vertex_num) - 2].x, polygon_global.vertexes[(polygon_global.vertex_num) - 2].y, polygon_size_global);
            line_midpoint_cpen(GetDC(), polygon_color_global, polygon_global.vertexes[(polygon_global.vertex_num) - 1].x, polygon_global.vertexes[(polygon_global.vertex_num) - 1].y, polygon_global.vertexes[0].x, polygon_global.vertexes[0].y, polygon_size_global);
        }
        polygon_global.vertexes.clear();
        polygon_global.vertex_num = 0;
        view_flag_global = 0;
        is_drawing_polygon_gloabl = FALSE;
    }
    else if (view_flag_global == 20) {
        view_flag_global = 0;
    }
    CView::OnLButtonDblClk(nFlags, point);
}


CRect rect_eraser;
CDC *dc1;

void CMFCOpenGL01View::OnMouseMove(UINT nFlags, CPoint point)
{
    dc1 = GetDC();
    dc1->SetROP2(R2_NOT);

    if (nFlags == MK_LBUTTON && view_flag_global == 2) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && view_flag_global == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        newPoint = point;
        radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
    }
    if (nFlags == MK_LBUTTON && view_flag_global == 4) {
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        newPoint = point;
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));
    }
    if (view_flag_global == 5 && is_drawing_polygon_gloabl) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && view_flag_global == 30) {
        rect_eraser.SetRect(CPoint(point.x - 25, point.y - 25), CPoint(point.x + 25, point.y + 25));
        //GetDC()->FillSolidRect(&rect_eraser, RGB(255, 255, 255));
        InvalidateRect(rect_eraser);

    }

    CView::OnMouseMove(nFlags, point);
}



/**********************************************MFC窗口和按钮相关 结束****************************************/




/**********************************************画点 开始****************************************/

//绘制圆形的点
void CMFCOpenGL01View::point_circle(CDC *pDC, COLORREF color, int x, int y, int size) {
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
    pDC->MoveTo(x, y);
    pDC->LineTo(x, y);
    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}

//绘制十字的点
void CMFCOpenGL01View::point_cross(CDC *pDC, COLORREF color, int x, int y, int size) {

    if (size == 1) {
        line_midpoint(pDC, color, x - 4, y, x + 3, y);
        line_midpoint(pDC, color, x, y - 4, x, y + 3);
        return;
    }

    int t = size / 2 + 3 * size;
    CRect rec1(x - t, y - size / 2, x + t, y + size / 2);
    CRect rec2(x - size / 2, y - t, x + size / 2, y + t);

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->FillRect(rec1, &cbrush);
    pDC->FillRect(rec2, &cbrush);

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}

//绘制菱形的点
void CMFCOpenGL01View::point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size) {

    int t = size + size / 5;
    line_midpoint(pDC, color, x - size, y, x, y - t);
    line_midpoint(pDC, color, x, y - t, x + size, y);
    line_midpoint(pDC, color, x + size, y, x, y + t);
    line_midpoint(pDC, color, x, y + t, x - size, y);

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->FloodFill(x, y, color); //从起点开始，用brush的颜色填充“最小”的那块封闭区域，相当于油漆桶
    //COLORREF color_banned = pDC->GetPixel(CPoint(x, y));
    //pDC->ExtFloodFill(x, y, color_banned, FLOODFILLSURFACE); //从起点开始，用brush的颜色向外填充，直到遇到某种颜色为止

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}




/**********************************************画点 开始****************************************/






/**********************************************画线算法 开始****************************************/

//DDA数值微分法法画线，斜率任意；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标
void CMFCOpenGL01View::line_dda(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

    double delta_x = 0.0, delta_y = 0.0, x = 0.0, y = 0.0;
    int dx = 0, dy = 0, steps = 0;
    dx = x1 - x0;
    dy = y1 - y0;
    if (abs(dx)>abs(dy)) steps = abs(dx);
    else steps = abs(dy);
    delta_x = (double)dx / (double)steps;
    delta_y = (double)dy / (double)steps;
    x = x0, y = y0;
    pDC->SetPixel(x, y, color);
    for (int i = 1; i <= steps; i++){
        x += delta_x;
        y += delta_y;
        pDC->SetPixel(x, y, color);
    }

    return;
}

//中点法画线，斜率任意；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标
void CMFCOpenGL01View::line_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // 斜率绝对值 <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            pDC->SetPixel(x, y, color);
        }
    }
    else { // 斜率绝对值 > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            pDC->SetPixel(x, y, color);
        }
    }
    return;
}

//中点法画线，斜率绝对值[0,1]，指定线宽，垂直线刷子；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标，线宽
void CMFCOpenGL01View::line_midpoint_vertical_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // 斜率绝对值 <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            for(int i = -width/2; i <= width/2; i++)
                pDC->SetPixel(x, y+i, color);
        }
    }
    else { // 斜率绝对值 > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            for (int i = -width / 2; i <= width / 2; i++)
                pDC->SetPixel(x, y+i, color);
        }
    }
    return;
}

//中点法画线，斜率绝对值(1,+oo)，指定线宽，水平线刷子；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标，线宽
void CMFCOpenGL01View::line_midpoint_horizontal_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // 斜率绝对值 <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            for (int i = -width / 2; i <= width / 2; i++)
                pDC->SetPixel(x+i, y, color);
        }
    }
    else { // 斜率绝对值 > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            for (int i = -width / 2; i <= width / 2; i++)
                pDC->SetPixel(x+i, y, color);
        }
    }
    return;
}

//中点法画线，斜率任意，指定线宽，方形线刷子；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标，线宽
void CMFCOpenGL01View::line_midpoint_square_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width) {

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // 斜率绝对值 <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            for (int i = -width / 2; i <= width / 2; i++) {
                for (int j = -width / 2; j <= width / 2; j++) {
                    pDC->SetPixel(x + i, y + j, color);
                }
            }
        }
    }
    else { // 斜率绝对值 > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            for (int i = -width / 2; i <= width / 2; i++) {
                for (int j = -width / 2; j <= width / 2; j++) {
                    pDC->SetPixel(x + i, y + j, color);
                }
            }
        }
    }
    return;
}

//bresenham法画线，斜率任意；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标
void CMFCOpenGL01View::line_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1) {

    int dx = x1 - x0;
    int dy = y1 - y0;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = x0, y = y0, eps;

    eps = 0; dx = abs(dx); dy = abs(dy);
    if (dx > dy) {
        for (x = x0; x != x1; x += ux) {
            pDC->SetPixel(x, y, color);
            eps += dy;
            if ((eps << 1) >= dx) {
                y += uy; eps -= dx;
            }
        }
    }
    else {
        for (y = y0; y != y1; y += uy) {
            pDC->SetPixel(x, y, color);
            eps += dx;
            if ((eps << 1) >= dy) {
                x += ux; eps -= dy;
            }
        }
    }

    return;
}


//Cpen函数

void CMFCOpenGL01View::line_dda_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
    
    double delta_x = 0.0, delta_y = 0.0, x = 0.0, y = 0.0;
    int dx = 0, dy = 0, steps = 0;
    dx = x1 - x0;
    dy = y1 - y0;
    if (abs(dx)>abs(dy)) steps = abs(dx);
    else steps = abs(dy);
    delta_x = (double)dx / (double)steps;
    delta_y = (double)dy / (double)steps;
    x = x0, y = y0;
    pDC->MoveTo(x, y);
    pDC->LineTo(x, y);
    for (int i = 1; i <= steps; i++) {
        x += delta_x;
        y += delta_y;
        pDC->MoveTo(x, y);
        pDC->LineTo(x, y);
    }

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}

void CMFCOpenGL01View::line_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    int x = x0, y = y0;
    int a = y0 - y1;
    int b = x1 - x0;
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int d, d1, d2;
    if (-a <= b) { // 斜率绝对值 <= 1
        d = a + a + b;
        d1 = a + a;
        d2 = a + a + b + b;
        while (x != x1) {
            if (d < 0) {
                y += cy;
                d += d2;
            }
            else {
                d += d1;
            }
            x += cx;
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
        }
    }
    else { // 斜率绝对值 > 1
        d = a + b + b;
        d1 = b + b;
        d2 = a + a + b + b;
        while (y != y1) {
            if (d < 0) {
                d += d1;
            }
            else {
                x += cx;
                d += d2;
            }
            y += cy;
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
        }
    }
    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}

void CMFCOpenGL01View::line_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    int dx = x1 - x0;
    int dy = y1 - y0;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = x0, y = y0, eps;

    eps = 0; dx = abs(dx); dy = abs(dy);
    if (dx > dy) {
        for (x = x0; x != x1; x += ux) {
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
            eps += dy;
            if ((eps << 1) >= dx) {
                y += uy; eps -= dx;
            }
        }
    }
    else {
        for (y = y0; y != y1; y += uy) {
            pDC->MoveTo(x, y);
            pDC->LineTo(x, y);
            eps += dx;
            if ((eps << 1) >= dy) {
                x += ux; eps -= dy;
            }
        }
    }

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}


/**********************************************画线算法 结束****************************************/



/**********************************************画圆算法 开始****************************************/

//bresenham法画正圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，半径
void CMFCOpenGL01View::circle_perfect_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int radius) {

    double x = 0.0, y = 0.0, d = 0.0;
    d = 1.25 - radius;
    x = 0; y = radius;
    for (x = 0; x <= y; x++) {
        set_points_on_circle(pDC, color, x0, y0, x, y);
        if (d < 0) d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
    }

    return;
}

//bresenham法画正圆-gl版；    参数：整型颜色R，整型颜色G，整型颜色B，圆心x坐标，圆心y坐标，半径
void CMFCOpenGL01View::circle_perfect_bresenham_gl(int colord1, int colord2, int colord3, int x0, int y0, int radius) {

    glBegin(GL_POINTS);
    double x = 0.0, y = 0.0, d = 0.0;
    d = 1.25 - radius;
    x = 0; y = radius;
    for (x = 0; x < y; x++) {
        glVertex2d((x0 + x), (y0 + y));
        glVertex2d((x0 - x), (y0 + y));
        glVertex2d((x0 + x), (y0 - y));
        glVertex2d((x0 - x), (y0 - y));

        glVertex2d((x0 + y), (y0 + x));
        glVertex2d((x0 - y), (y0 + x));
        glVertex2d((x0 + y), (y0 - x));
        glVertex2d((x0 - y), (y0 - x));
        if (d < 0) d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
    }
    glEnd();
    return;
}

//中点法画正圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，半径
void CMFCOpenGL01View::circle_perfect_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int radius) {

    int x = 0, y = 0, h = 0;
    x = 0, y = radius;
    h = 1 - radius;
    set_points_on_circle(pDC, color, x0, y0, x, y);
    while (x < y) {
        if (h < 0) h += 2 * x + 2;
        else {
            h += 2 * (x - y) + 5;
            y--;
        }
        x++;
        set_points_on_circle(pDC, color, x0, y0, x, y);
    }

    return;
}

//对称地画圆上的点；    参数：pDC，颜色，圆心x坐标，圆心y坐标，目标点的x坐标，目标点的y坐标
void CMFCOpenGL01View::set_points_on_circle(CDC *pDC, COLORREF color, int x0, int y0, int x, int y) {

    pDC->SetPixel((x0 + x), (y0 + y), color);
    pDC->SetPixel((x0 - x), (y0 + y), color);
    pDC->SetPixel((x0 + x), (y0 - y), color);
    pDC->SetPixel((x0 - x), (y0 - y), color);

    pDC->SetPixel((x0 + y), (y0 + x), color);
    pDC->SetPixel((x0 - y), (y0 + x), color);
    pDC->SetPixel((x0 + y), (y0 - x), color);
    pDC->SetPixel((x0 - y), (y0 - x), color);

    return;
}


//bresenham法画椭圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，长轴的长度，短轴的长度
void CMFCOpenGL01View::circle_oval_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int a, int b) {

    int sqa = a * a, sqb = b * b;
    int x = 0, y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    set_points_on_oval(pDC, color, x0, y0, x, y);
    int P_x = round((double)sqa / sqrt((double)(sqa + sqb)));
    while (x <= P_x){
        if (d < 0)
            d += 2 * sqb * (2 * x + 3);
        else{
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }

    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0){
        set_points_on_oval(pDC, color, x0, y0, x, y);
        y--;
        if (d < 0){
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else
            d = d - 2 * sqa * y - sqa;
    }

    return;
}

//中点法画椭圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，长轴的长度，短轴的长度
void CMFCOpenGL01View::circle_oval_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int a, int b) {

    double sqa = a * a;
    double sqb = b * b;
    double d = sqb + sqa * (-b + 0.25);
    int x = 0;
    int y = b;
    set_points_on_oval(pDC, color, x0, y0, x, y);
    while (sqb * (x + 1) < sqa * (y - 0.5)){
        if (d < 0) d += sqb * (2 * x + 3);
        else{
            d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
            y--;
        }
        x++;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0){
        if (d < 0){
            d += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
            x++;
        }
        else d += sqa * (-2 * y + 3);
        y--;
        set_points_on_oval(pDC, color, x0, y0, x, y);
    }

    return;
}

//对称地画椭圆上的点；    参数：pDC，颜色，圆心x坐标，圆心y坐标，目标点的x坐标，目标点的y坐标
void CMFCOpenGL01View::set_points_on_oval(CDC *pDC, COLORREF color, int x0, int y0, int x, int y) {

    pDC->SetPixel((x0 + x), (y0 + y), color);
    pDC->SetPixel((x0 - x), (y0 + y), color);
    pDC->SetPixel((x0 + x), (y0 - y), color);
    pDC->SetPixel((x0 - x), (y0 - y), color);

    return;
}



//CPen函数

void CMFCOpenGL01View::circle_perfect_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size) {
    double x = 0.0, y = 0.0, d = 0.0;
    d = 1.25 - radius;
    x = 0; y = radius;
    for (x = 0; x <= y; x++) {
        set_points_on_circle_cpen(pDC, color, x0, y0, x, y, size);
        if (d < 0) d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
    }
    return;
}

void CMFCOpenGL01View::circle_perfect_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size) {
    int x = 0, y = 0, h = 0;
    x = 0, y = radius;
    h = 1 - radius;
    set_points_on_circle_cpen(pDC, color, x0, y0, x, y, size);
    while (x < y) {
        if (h < 0) h += 2 * x + 2;
        else {
            h += 2 * (x - y) + 5;
            y--;
        }
        x++;
        set_points_on_circle_cpen(pDC, color, x0, y0, x, y, size);
    }
    return;
}

void CMFCOpenGL01View::set_points_on_circle_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size) {
    size++;
    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
    pDC->MoveTo((x0 + x), (y0 + y));
    pDC->LineTo((x0 + x), (y0 + y));
    pDC->MoveTo((x0 - x), (y0 + y));
    pDC->LineTo((x0 - x), (y0 + y));
    pDC->MoveTo((x0 + x), (y0 - y));
    pDC->LineTo((x0 + x), (y0 - y));
    pDC->MoveTo((x0 - x), (y0 - y));
    pDC->LineTo((x0 - x), (y0 - y));

    pDC->MoveTo((x0 + y), (y0 + x));
    pDC->LineTo((x0 + y), (y0 + x));
    pDC->MoveTo((x0 - y), (y0 + x));
    pDC->LineTo((x0 - y), (y0 + x));
    pDC->MoveTo((x0 + y), (y0 - x));
    pDC->LineTo((x0 + y), (y0 - x));
    pDC->MoveTo((x0 - y), (y0 - x));
    pDC->LineTo((x0 - y), (y0 - x));

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}


void CMFCOpenGL01View::circle_oval_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size) {

    size++;
    int sqa = a * a, sqb = b * b;
    int x = 0, y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    int P_x = round((double)sqa / sqrt((double)(sqa + sqb)));
    while (x <= P_x) {
        if (d < 0)
            d += 2 * sqb * (2 * x + 3);
        else {
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
            y--;
        }
        x++;
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    }

    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while (y >= 0) {
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
        y--;
        if (d < 0) {
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else
            d = d - 2 * sqa * y - sqa;
    }

    return;
}

void CMFCOpenGL01View::circle_oval_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size) {

    size++;

    double sqa = a * a;
    double sqb = b * b;
    double d = sqb + sqa * (-b + 0.25);
    int x = 0;
    int y = b;
    set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    while (sqb * (x + 1) < sqa * (y - 0.5)) {
        if (d < 0) d += sqb * (2 * x + 3);
        else {
            d += (sqb * (2 * x + 3) + sqa * (-2 * y + 2));
            y--;
        }
        x++;
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0) {
        if (d < 0) {
            d += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
            x++;
        }
        else d += sqa * (-2 * y + 3);
        y--;
        set_points_on_oval_cpen(pDC, color, x0, y0, x, y, size);
    }

    return;
}

void CMFCOpenGL01View::set_points_on_oval_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size) {

    CPen cpen;
    cpen.CreatePen(PS_SOLID, size, color);
    CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

    pDC->MoveTo((x0 + x), (y0 + y));
    pDC->LineTo((x0 + x), (y0 + y));
    pDC->MoveTo((x0 - x), (y0 + y));
    pDC->LineTo((x0 - x), (y0 + y));
    pDC->MoveTo((x0 + x), (y0 - y));
    pDC->LineTo((x0 + x), (y0 - y));
    pDC->MoveTo((x0 - x), (y0 - y));
    pDC->LineTo((x0 - x), (y0 - y));

    pDC->SelectObject(pOldPen);
    cpen.DeleteObject();
    return;
}


/**********************************************画圆算法 结束****************************************/



/**********************************************区域填充算法 开始****************************************/

void CMFCOpenGL01View::set_PolygonVertex(int num, int array_vertex[][2]) {

    PolygonVertex = new vertex[num];
    for (int i = 0; i < num; i++) {
        PolygonVertex[i].x = array_vertex[i][0];
        PolygonVertex[i].y = array_vertex[i][1];
    }

    return;
}

void CMFCOpenGL01View::init_EdgeTable(int num, vertex* PolygonVertex) {

    int y_max = -99999;
    for (int i = 0; i < num; i++) if (PolygonVertex[i].y > y_max) y_max = PolygonVertex[i].y;
    EdgeTable = new edge[y_max+1];

    //把顶点构造成边
    for (int i = 0; i < num-1; i++) {
        vertex vertex_left, vertex_right;
        if (PolygonVertex[i].x < PolygonVertex[i + 1].x) {
            vertex_left = PolygonVertex[i];
            vertex_right = PolygonVertex[i + 1];
        }
        else {
            vertex_left = PolygonVertex[i + 1];
            vertex_right = PolygonVertex[i];
        }
        
        if (vertex_left.y == vertex_right.y) continue; //忽略水平边
        edge* one_edge = new edge;
        one_edge->y_high = max(vertex_left.y, vertex_right.y);
        one_edge->delta_x = (double)(vertex_right.x - vertex_left.x) / (double)(vertex_right.y - vertex_left.y); //斜率分之一，1/k
        //one_edge->x_intersection = 
    }
}


void CMFCOpenGL01View::insert_edge(edge* AELorET, int y, edge* one_edge) {

    edge* tail_edge = AELorET[y].next_edge;
    while (tail_edge != NULL) {
        tail_edge = tail_edge->next_edge;
    }
    tail_edge->next_edge = one_edge;
    one_edge->next_edge = NULL;

    return;
}

void CMFCOpenGL01View::del_edge(edge* AELorET, edge* one_edge) {



}


void CMFCOpenGL01View::flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt) {

    CBrush cbrush;
    cbrush.CreateSolidBrush(color);
    CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

    pDC->ExtFloodFill(pt.x, pt.y, color_banned, FLOODFILLSURFACE);

    pDC->SelectObject(pOldBrush);
    cbrush.DeleteObject();

    return;
}



/**********************************************区域填充算法 结束****************************************/




/**********************************************二维图形裁剪算法 开始****************************************/


//Cohen-Sutherland+中点分割（区域编码+中点分割）法线段裁剪    参数：pDC，颜色，裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，几条线，待裁剪的直线
void CMFCOpenGL01View::line_cut_Sutherland_midpoint(CDC *pDC, COLORREF color, vertex window_vertex_left_top, vertex window_vertex_right_bottom, int num, line lines[]){

    for (int i = 0; i < num; i++) {
        set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &lines[i].vertex_coded_begin);
        set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &lines[i].vertex_coded_end);
    }

    for (int i = 0; i < num; i++) {
        vertex_coded vb = lines[i].vertex_coded_begin;
        vertex_coded ve = lines[i].vertex_coded_end;
        if (vb.code == 0 && ve.code == 0) { //全部在裁剪范围内，直接整条画出来
            line_midpoint(pDC, color, vb.x, vb.y, ve.x, ve.y);
            continue;
        }
        if ((vb.code & ve.code) != 0) { //全部不在裁剪范围内，直接删除
            //line_midpoint(pDC, RGB(0,255,0), vb.x, vb.y, ve.x, ve.y);
            continue;
        }
        if((vb.code & ve.code) == 0) {
            if ((vb.code == 0) || (ve.code == 0)) { //有一点在外，另一点在内
                vertex_coded vd = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, lines[i]);
                if(vb.code == 0)
                    line_midpoint(pDC, color, vb.x, vb.y, vd.x, vd.y);
                else
                    line_midpoint(pDC, color, ve.x, ve.y, vd.x, vd.y);
            }
            else { //两点全在外面（线段贯穿裁剪框），需要把线段分割成两部分分别处理
                vertex_coded vmid;
                //左上->右下的对角线与待裁剪线段存在交点，用此交点进行分割成两部分
                if (judge_line_pos(window_vertex_left_top, window_vertex_right_bottom, lines[i].vertex_coded_begin, lines[i].vertex_coded_end)) {
                    vmid = get_mid_point(window_vertex_left_top, window_vertex_right_bottom, vb, ve);
                    set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &vmid);
                }
                else { //右上->左下的对角线与待裁剪线段存在交点，用此交点进行分割成两部分
                    vmid = get_mid_point(vertex(window_vertex_right_bottom.x, window_vertex_left_top.y), vertex(window_vertex_left_top.x, window_vertex_right_bottom.y), vb, ve);
                    set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &vmid);
                }
                vertex_coded vd1 = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, line(vb, vmid));
                vertex_coded vd2 = line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, line(vmid, ve));
                line_midpoint(pDC, color, vmid.x, vmid.y, vd1.x, vd1.y);
                line_midpoint(pDC, color, vmid.x, vmid.y, vd2.x, vd2.y);
            }
            
        }
    }

    return;
}

//中点分割法递归二分确定线段与裁剪边框相交于哪一点    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，待裁剪的直线
CMFCOpenGL01View::vertex_coded CMFCOpenGL01View::line_cut_midpoint(vertex window_vertex_left_top, vertex window_vertex_right_bottom, line single_line) {

    vertex_coded vin = single_line.vertex_coded_begin.code == 0 ? single_line.vertex_coded_begin : single_line.vertex_coded_end;
    vertex_coded vout = single_line.vertex_coded_begin.code != 0 ? single_line.vertex_coded_begin : single_line.vertex_coded_end;
    vertex_coded vmid = vertex_coded((vin.x + vout.x) / 2, (vin.y + vout.y) / 2);
    set_vertex_code(window_vertex_left_top, window_vertex_right_bottom, &vmid);

    if (abs(vmid.x - vin.x) <= 1 || abs(vmid.y - vin.y) <= 1) return vmid;     //取极限

    if (vmid.code == 0) vin = vmid; //中点在裁剪框内，把内部的端点移向中点
    else vout = vmid; //中点在裁剪框外，把外部的点移向中点
        
    return line_cut_midpoint(window_vertex_left_top, window_vertex_right_bottom, line(vin, vout));
}

//确定线段的端点落在那个区域，获取其对应的编码    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，端点指针
void CMFCOpenGL01View::set_vertex_code(vertex window_vertex_left_top, vertex window_vertex_right_bottom, vertex_coded *v) {

    if (v->y >= window_vertex_left_top.y) v->code |= 8;    //1000 上
    if (v->y <= window_vertex_right_bottom.y) v->code |= 4; //0100 下
    if (v->x >= window_vertex_right_bottom.x) v->code |= 2;  //0010 右
    if (v->x <= window_vertex_left_top.x) v->code |= 1;   //0001 左

    return;
}

//判断裁剪框对角线和待裁剪线段的位置关系    参数：裁剪线框的对角线的起点，裁剪线框对角线的终点，待裁剪线段的起点，待裁剪线段的终点
bool CMFCOpenGL01View::judge_line_pos(vertex window_vertex_a, vertex window_vertex_b, vertex_coded va, vertex_coded vb) {
    long long int d1, d2, d3, d4;
    d1 = (window_vertex_b.x - window_vertex_a.x)*(va.y - window_vertex_a.y) - (window_vertex_b.y - window_vertex_a.y)*(va.x - window_vertex_a.x);
    d2 = (window_vertex_b.x - window_vertex_a.x)*(vb.y - window_vertex_a.y) - (window_vertex_b.y - window_vertex_a.y)*(vb.x - window_vertex_a.x);
    d3 = (vb.x - va.x)*(window_vertex_a.y - va.y) - (vb.y - va.y)*(window_vertex_a.x - va.x);
    d4 = (vb.x - va.x)*(window_vertex_b.y - va.y) - (vb.y - va.y)*(window_vertex_b.x - va.x);
    if (d1*d2 <= 0 && d3*d4 <= 0)
        return true; //相交及重合
    else
        return false; //不相交
}

//得到线段与对角线的交点    参数：裁剪框对角线的起点，裁剪框对角线的终点，待裁剪线的起点，待裁剪线的终点
CMFCOpenGL01View::vertex_coded CMFCOpenGL01View::get_mid_point(vertex diagonal_vertex_a, vertex diagonal_vertex_b, vertex_coded va, vertex_coded vb) {
    int a = vb.x - va.x;
    int b = diagonal_vertex_a.x - diagonal_vertex_b.x;
    int c = vb.y - va.y;
    int d = diagonal_vertex_a.y - diagonal_vertex_b.y;
    int g = diagonal_vertex_a.x - va.x;
    int h = diagonal_vertex_a.y - va.y;
    int f = a*d - b*c;
    double t = double((d*g - b*h)) / double(f);
    vertex_coded m;
    m.x = va.x + t*(vb.x - va.x);
    m.y = va.y + t*(vb.y - va.y);
    return m;
}





//Sutherland-Hodgman（逐边裁剪）法多边形裁剪（返回裁剪完成的新多边形）    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，待裁剪的多边形
CMFCOpenGL01View::polygon CMFCOpenGL01View::polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon) {

    polygon p1, p2, p3, p4;
    vertex vs, vp; //s->p
    //左边框裁剪
    for (int i = 0; i < src_polygon.vertex_num; i++) {
        vs = src_polygon.vertexes[i];
        if (i == src_polygon.vertex_num - 1) vp = src_polygon.vertexes[0];
        else vp = src_polygon.vertexes[i + 1];

        if (vs.x >= window_vertex_left_top.x && vp.x >= window_vertex_left_top.x) { //情况一：s、p都在内侧，输出p
            p1.vertexes.push_back(vp);
            p1.vertex_num++;
        }
        if (vs.x < window_vertex_left_top.x && vp.x < window_vertex_left_top.x) { //情况二：s、p都在外侧，无输出
            continue;
        }
        if (vs.x >= window_vertex_left_top.x && vp.x < window_vertex_left_top.x) { //情况三：s在内侧，p在外侧，输出交点i
            vertex vi(window_vertex_left_top.x, get_intersection_point(vs, vp, window_vertex_left_top.x, true));
            p1.vertexes.push_back(vi);
            p1.vertex_num++;
        }
        if (vs.x < window_vertex_left_top.x && vp.x >= window_vertex_left_top.x) { //情况四：s在外侧，p在内侧，输出i和p
            vertex vi(window_vertex_left_top.x, get_intersection_point(vs, vp, window_vertex_left_top.x, true));
            p1.vertexes.push_back(vi);
            p1.vertexes.push_back(vp);
            p1.vertex_num += 2;
        }
    }

    //上边框裁剪
    for (int i = 0; i < p1.vertex_num; i++) {
        vs = p1.vertexes[i];
        if (i == p1.vertex_num - 1) vp = p1.vertexes[0];
        else vp = p1.vertexes[i + 1];

        if (vs.y <= window_vertex_left_top.y && vp.y <= window_vertex_left_top.y) { //情况一：s、p都在内侧，输出p
            p2.vertexes.push_back(vp);
            p2.vertex_num++;
        }
        if (vs.y > window_vertex_left_top.y && vp.y > window_vertex_left_top.y) { //情况二：s、p都在外侧，无输出
            continue;
        }
        if (vs.y <= window_vertex_left_top.y && vp.y > window_vertex_left_top.y) { //情况三：s在内侧，p在外侧，输出交点i
            vertex vi(get_intersection_point(vs, vp, window_vertex_left_top.y, false), window_vertex_left_top.y);
            p2.vertexes.push_back(vi);
            p2.vertex_num++;
        }
        if (vs.y > window_vertex_left_top.y && vp.y <= window_vertex_left_top.y) { //情况四：s在外侧，p在内侧，输出i和p
            vertex vi(get_intersection_point(vs, vp, window_vertex_left_top.y, false), window_vertex_left_top.y);
            p2.vertexes.push_back(vi);
            p2.vertexes.push_back(vp);
            p2.vertex_num += 2;
        }
    }

    //右边框裁剪
    for (int i = 0; i < p2.vertex_num; i++) {
        vs = p2.vertexes[i];
        if (i == p2.vertex_num - 1) vp = p2.vertexes[0];
        else vp = p2.vertexes[i + 1];

        if (vs.x <= window_vertex_right_bottom.x && vp.x <= window_vertex_right_bottom.x) { //情况一：s、p都在内侧，输出p
            p3.vertexes.push_back(vp);
            p3.vertex_num++;
        }
        if (vs.x > window_vertex_right_bottom.x && vp.x > window_vertex_right_bottom.x) { //情况二：s、p都在外侧，无输出
            continue;
        }
        if (vs.x <= window_vertex_right_bottom.x && vp.x > window_vertex_right_bottom.x) { //情况三：s在内侧，p在外侧，输出交点i
            vertex vi(window_vertex_right_bottom.x, get_intersection_point(vs, vp, window_vertex_right_bottom.x, true));
            p3.vertexes.push_back(vi);
            p3.vertex_num++;
        }
        if (vs.x > window_vertex_right_bottom.x && vp.x <= window_vertex_right_bottom.x) { //情况四：s在外侧，p在内侧，输出i和p
            vertex vi(window_vertex_right_bottom.x, get_intersection_point(vs, vp, window_vertex_right_bottom.x, true));
            p3.vertexes.push_back(vi);
            p3.vertexes.push_back(vp);
            p3.vertex_num += 2;
        }
    }

    //下边框裁剪
    for (int i = 0; i < p3.vertex_num; i++) {
        vs = p3.vertexes[i];
        if (i == p3.vertex_num - 1) vp = p3.vertexes[0];
        else vp = p3.vertexes[i + 1];

        if (vs.y >= window_vertex_right_bottom.y && vp.y >= window_vertex_right_bottom.y) { //情况一：s、p都在内侧，输出p
            p4.vertexes.push_back(vp);
            p4.vertex_num++;
        }
        if (vs.y < window_vertex_right_bottom.y && vp.y < window_vertex_right_bottom.y) { //情况二：s、p都在外侧，无输出
            continue;
        }
        if (vs.y >= window_vertex_right_bottom.y && vp.y < window_vertex_right_bottom.y) { //情况三：s在内侧，p在外侧，输出交点i
            vertex vi(get_intersection_point(vs, vp, window_vertex_right_bottom.y, false), window_vertex_right_bottom.y);
            p4.vertexes.push_back(vi);
            p4.vertex_num++;
        }
        if (vs.y < window_vertex_right_bottom.y && vp.y >= window_vertex_right_bottom.y) { //情况四：s在外侧，p在内侧，输出i和p
            vertex vi(get_intersection_point(vs, vp, window_vertex_right_bottom.y, false), window_vertex_right_bottom.y);
            p4.vertexes.push_back(vi);
            p4.vertexes.push_back(vp);
            p4.vertex_num += 2;
        }
    }

    return p4;
}

//求出直线和裁剪框的交点（返回交点处的数值）    参数：待裁剪的线的起始点，待裁剪的线的结束点，裁剪线框的某一条线x=value或y=value的value值，是x=还是y=（true为x，false为y）
int CMFCOpenGL01View::get_intersection_point(vertex vb, vertex ve, int value, bool flag) {

    int result = 0;

    if (flag) { //与直线x=value相交，返回y
        if (vb.y == ve.y) { //k=0
            result = vb.y;
        }
        else {
            double k = 1.0*(ve.y - vb.y) / (ve.x - vb.x);
            double b = ve.y - (k * ve.x);
            result = k*value + b;
        }
    }
    else { //与直线y=value相交，返回x
        if (vb.x == ve.x) { //k不存在
            result = vb.x;
        }
        else {
            double k = 1.0*(ve.y - vb.y) / (ve.x - vb.x);
            double b = ve.y - (k * ve.x);
            result = (value - b) / k;
        }
    }

    return result;
}

//绘制多边形    参数：PDC，颜色，顶点个数，多边形
void CMFCOpenGL01View::draw_polygon(CDC *pDC, COLORREF color, polygon p) {
    for (int i = 0; i < p.vertex_num-1; i++)
        line_midpoint(pDC, color, p.vertexes[i].x, p.vertexes[i].y, p.vertexes[i + 1].x, p.vertexes[i + 1].y);

    line_midpoint(pDC, color, p.vertexes[p.vertex_num-1].x, p.vertexes[p.vertex_num-1].y, p.vertexes[0].x, p.vertexes[0].y);

    return;
}


/**********************************************二维图形裁剪算法 结束****************************************/








/**********************************************二维图形变换算法 开始****************************************/

//多边形旋转变换    参数：PDC，颜色，原始多边形，旋转中心点，旋转角度（角度制，有正负）
void CMFCOpenGL01View::transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle) {

    double pi = 3.1415926;
    double arc = pi / 180.0*angle; //转弧度制

    polygon res_polygon = src_polygon;
    for (int i = 0; i < res_polygon.vertex_num; i++) {
        vertex t = res_polygon.vertexes[i];
        res_polygon.vertexes[i].x = center.x + (t.x - center.x)*std::cos(arc) - (t.y - center.y)*std::sin(arc);
        res_polygon.vertexes[i].y = center.y + (t.x - center.x)*std::sin(arc) + (t.y - center.y)*std::cos(arc);
    }

    draw_polygon(pDC, color, res_polygon);

    return;
}







/**********************************************二维图形变换算法 结束****************************************/


