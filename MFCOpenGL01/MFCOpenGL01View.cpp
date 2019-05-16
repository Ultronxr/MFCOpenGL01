
// MFCOpenGL01View.cpp : CMFCOpenGL01View 类的实现
//


#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCOpenGL01.h"

#endif

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
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_SETCURSOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FILE_SAVE, &CMFCOpenGL01View::OnFileSave)
    ON_COMMAND(ID_FILE_OPEN, &CMFCOpenGL01View::OnFileOpen)
END_MESSAGE_MAP()

// CMFCOpenGL01View 构造/析构

CMFCOpenGL01View::CMFCOpenGL01View()
{   
    m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
    m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;


    //调试输出信息用的控制台
    /*::AllocConsole();
    FILE *fp;
    freopen_s(&fp, "CONOUT$", "w+t", stdout);*/
}

CMFCOpenGL01View::~CMFCOpenGL01View()
{
    m_pDoc = NULL;

    //释放调试控制台
    //FreeConsole();
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

void CMFCOpenGL01View::OnDraw(CDC* pDC){
    
    CMFCOpenGL01Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc) return;

    if (!m_pDoc) m_pDoc = GetDocument();

    // TODO: 在此处为本机数据添加绘制代码

    //作业
    COLORREF red = RGB(255, 0, 0), green = RGB(0, 255, 0), blue = RGB(0 ,0 ,255),  black = RGB(0, 0, 0);
    
    m_pDoc->flush_all_drawing(pDC);
    


    if (EntName.Compare(_T("bmp")) == 0){
        ShowBitmap(pDC, BmpName);               //显示图片
        EntName = "";
    }
    
}




///MFC窗口和按钮相关 开始


//菜单栏的菜单项

void CMFCOpenGL01View::OnDrawRuler()
{
    // TODO: 在此添加命令处理程序代码

    //简单刻度（每50像素一刻度）
    CDC* dc1 = GetDC();
    for (int i = 0; i <= 1920; i += 50) m_pDoc->line_dda(dc1, RGB(0, 0, 0), i, 0, i, 10);
    for (int i = 0; i <= 1920; i += 50) m_pDoc->line_dda(dc1, RGB(0, 0, 0), 0, i, 10, i);
    ReleaseDC(dc1);
}

void CMFCOpenGL01View::OnDrawOrtho()
{
    // TODO: 在此添加命令处理程序代码

    //模拟笛卡尔坐标系（坐标原点在(900,400)，每隔50像素为单位1）
    int xx = 900, yy = 400;
    CDC* dc1 = GetDC();
    m_pDoc->line_dda(dc1, RGB(0, 0, 0), xx, 0, xx, 1080); for (int j = 0; j <= 1080; j += 50)  m_pDoc->line_dda(dc1, RGB(0, 0, 0), xx, j, xx + 10, j);
    m_pDoc->line_dda(dc1, RGB(0, 0, 0), 0, yy, 1960, yy); for (int j = 0; j <= 1920; j += 50)  m_pDoc->line_dda(dc1, RGB(0, 0, 0), j, yy - 10, j, yy);
    ReleaseDC(dc1);
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
    /*
    IDC_APPSTARTING 标准的箭头和小沙漏
    IDC_ARROW 标准的箭头
    IDC_CROSS 十字光标
    IDC_HAND Windows 98/Me, Windows 2000/XP: Hand
    IDC_HELP 标准的箭头和问号
    IDC_IBEAM 工字光标
    IDC_ICON Obsolete for applications marked version 4.0 or later.
    IDC_NO 禁止圈
    IDC_SIZE Obsolete for applications marked version 4.0 or later. Use IDC_SIZEALL.
    IDC_SIZEALL 四向箭头指向东、西、南、北
    IDC_SIZENESW 双箭头指向东北和西南
    IDC_SIZENS 双箭头指向南北
    IDC_SIZENWSE 双箭头指向西北和东南
    IDC_SIZEWE 双箭头指向东西
    IDC_UPARROW 垂直箭头
    IDC_WAIT 沙漏，Windows7系统下会显示为选择的圆圈表示等待
    */
    if (pWnd == this && m_pDoc->m_operation == 100) {
        HCURSOR hCur = LoadCursor(NULL, IDC_SIZEALL);
        ::SetCursor(hCur);
        return TRUE;
    }
    else if (pWnd == this && m_pDoc->m_operation == 101) {
        HCURSOR hCur = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(CURSOR_TRANSFORM_ROTATE));
        ::SetCursor(hCur);
        return TRUE;
    }
    else if (pWnd == this && m_pDoc->m_operation == 102) {
        HCURSOR hCur = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(CURSOR_TRANSFORM_SCALE));
        ::SetCursor(hCur);
        return TRUE;
    }
    else if (pWnd == this && m_pDoc->m_operation != 0) {
        HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);
        ::SetCursor(hCur);
        return TRUE;
    }
    return CView::OnSetCursor(pWnd, nHitTest, message);
}

CPoint parentPoint, oldPoint, newPoint;
//备份目标区域的内容，选择框再次移到别的地方去需要填回去
CRect rect_parent, rect_old, rect_new;
int clk_inside = 0;

std::vector<CPoint> temp_ps;
double oldRadius = 0.0;
CPoint tp1(0, 0), tp2(0, 0);
int ta = 0, tb = 0;

CMFCOpenGL01Doc::d_polygon tpolygon(temp_ps, 1, RGB(0,0,0));

void CMFCOpenGL01View::OnLButtonDown(UINT nFlags, CPoint point)
{
    CDC *dc1 = GetDC();
    
    if (m_pDoc->m_operation == 0) {
        m_pDoc->select_all(dc1, point);
    }

    else if (m_pDoc->m_operation == 2) {
        oldPoint = point;
        newPoint = point;
    }
    else if (m_pDoc->m_operation == 3) {
        oldPoint = point;
        newPoint = point;
    }
    else if (m_pDoc->m_operation == 4) {
        oldPoint = point;
        newPoint = point;
    }
    else if (m_pDoc->m_operation == 5) {
        if (!m_pDoc->is_drawing_polygon) {
            parentPoint = point;
            oldPoint = point;
            newPoint = point;
            m_pDoc->is_drawing_polygon = TRUE;
            temp_ps.clear();
            temp_ps.push_back(parentPoint);
        }
        else {
            newPoint = point;
            temp_ps.push_back(newPoint);
        }
    }
    else if (m_pDoc->m_operation == 20) {
        
        m_RectTracker.TrackRubberBand(this, point, TRUE);
        m_RectTracker.m_rect.NormalizeRect();
        m_RectTracker.Draw(GetDC());

        rect_parent = m_RectTracker.m_rect;
        rect_old = m_RectTracker.m_rect;

        m_pDoc->m_operation = 21;
    }
    else if (m_pDoc->m_operation == 21) {
        
        int judge = m_RectTracker.HitTest(point);
        if (judge < 0) { //光标位置在选框外部，重置选择框
            m_RectTracker.m_rect.SetRect(0, 0, 0, 0);
            m_RectTracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

            if (clk_inside > 0) {
                rect_parent.top--; rect_parent.bottom++; rect_parent.left--; rect_parent.right++;
                dc1->FillSolidRect(rect_parent, RGB(255, 255, 255));
            }
            
            clk_inside = 0;
            m_pDoc->m_operation = 0;
        }
        else { //把选择框内的像素全部复制到目标区域
            clk_inside++;

            rect_old = m_RectTracker.m_rect;
            

            m_RectTracker.Track(this, point, TRUE);
            //Invalidate(TRUE);
            m_RectTracker.Draw(dc1);

            //BitBlt(GetDC()->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, rect_old.Width(), rect_old.Height(), dc_backup.m_hDC, 0, 0, SRCCOPY);

            rect_new = m_RectTracker.m_rect;
            int x = m_RectTracker.m_rect.TopLeft().x, y = m_RectTracker.m_rect.TopLeft().y;
            int width = m_RectTracker.m_rect.Width(), height = m_RectTracker.m_rect.Height();

            //备份目标覆盖区域的图像
            //BitBlt(dc_backup.m_hDC, 0, 0, width, height, GetDC()->m_hDC, x, y, SRCCOPY);

            
            //绘制图像
            BitBlt(GetDC()->m_hDC, x, y, width, height, dc1->m_hDC, rect_old.TopLeft().x, rect_old.TopLeft().y, SRCCOPY);

            rect_old.top--; rect_old.bottom++; rect_old.left--; rect_old.right++;
            dc1->FillSolidRect(rect_old, RGB(255, 255, 255));
        }
    }
    else if (m_pDoc->m_operation == 101) {
        oldPoint = point;
    }
    else if (m_pDoc->m_operation == 102) {
        oldPoint = point;
    }
    ReleaseDC(dc1);
    CView::OnLButtonDown(nFlags, point);
}


void CMFCOpenGL01View::OnLButtonUp(UINT nFlags, CPoint point)
{
    CDC* dc1 = GetDC(), *dc2 = GetDC();
    int index = -1;
    dc1->SetROP2(R2_NOT);

    if (m_pDoc->m_operation == 1) {
        if (m_pDoc->point_type == 0) m_pDoc->point_circle(dc2, m_pDoc->m_color, point.x, point.y, m_pDoc->m_size);
        else if (m_pDoc->point_type == 1) m_pDoc->point_cross(dc2, m_pDoc->m_color, point.x, point.y, m_pDoc->m_size);
        else if (m_pDoc->point_type == 2) m_pDoc->point_rhombus(dc2, m_pDoc->m_color, point.x, point.y, m_pDoc->m_size);
        m_pDoc->v_point.push_back(CMFCOpenGL01Doc::d_point(point, m_pDoc->point_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 2) {
        //抹去最后一次的作图提示线
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        m_pDoc->line_cpen(dc2, m_pDoc->m_color, oldPoint, point, m_pDoc->m_size);
        m_pDoc->v_line.push_back(CMFCOpenGL01Doc::d_line(oldPoint, newPoint, m_pDoc->line_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        
        //抹去最后一次的作图提示线
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        
        m_pDoc->circle_perfect_cpen(dc2, m_pDoc->m_color, oldPoint, radius, m_pDoc->m_size);
        m_pDoc->v_perf_circle.push_back(CMFCOpenGL01Doc::d_perf_circle(oldPoint, radius, m_pDoc->circle_perfect_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 4) {
        //抹去最后一次的作图提示线
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));

        int x0 = (oldPoint.x + newPoint.x) / 2, y0 = (oldPoint.y + newPoint.y) / 2;
        int a = std::abs(x0 - oldPoint.x), b = std::abs(y0 - oldPoint.y);
        m_pDoc->circle_oval_angle_cpen(dc2, m_pDoc->m_color, x0, y0, a, b, 0, m_pDoc->m_size);
        m_pDoc->v_oval_circle.push_back(CMFCOpenGL01Doc::d_oval_circle(CPoint(x0, y0), a, b, 0, m_pDoc->circle_oval_type, m_pDoc->m_size, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 5) {
        //抹去最后一次的作图提示线
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);

        m_pDoc->point_circle(dc2, m_pDoc->m_color, newPoint.x, newPoint.y, m_pDoc->m_size);
        m_pDoc->line_cpen(dc2, m_pDoc->m_color, oldPoint, newPoint, m_pDoc->m_size);
        oldPoint = newPoint;
    }
    else if (m_pDoc->m_operation == 10) {
        m_pDoc->flood_fill_cbrush(dc2, m_pDoc->m_color, GetDC()->GetPixel(point.x, point.y), point);
        m_pDoc->v_fill.push_back(CMFCOpenGL01Doc::d_fill(point, m_pDoc->m_color));
    }
    else if (m_pDoc->m_operation == 100) { //平移
        if ((index = m_pDoc->selected_point) != -1) {
            m_pDoc->transform_translate_point(m_pDoc->v_point, index, point);
            m_pDoc->selected_point = -1;
        }
        else if ((index = m_pDoc->selected_line) != -1) {
            m_pDoc->transform_translate_line(m_pDoc->v_line, index, point);
            m_pDoc->selected_line = -1;
        }
        else if ((index = m_pDoc->selected_perfect_circle) != -1) {
            m_pDoc->transform_translate_perfect_circle(m_pDoc->v_perf_circle, index, point);
            m_pDoc->selected_perfect_circle = -1;
        }
        else if ((index = m_pDoc->selected_oval_circle) != -1) {
            m_pDoc->transform_translate_oval_circle(m_pDoc->v_oval_circle, index, point);
            m_pDoc->selected_oval_circle = -1;
        }
        else if ((index = m_pDoc->selected_polygon) != -1) {
            m_pDoc->transform_translate_polygon(m_pDoc->v_polygon, index, point);
            m_pDoc->selected_polygon = -1;
        }
        m_pDoc->m_operation = 0;
        Invalidate(TRUE);
    }
    else if (m_pDoc->m_operation == 101) { //旋转
        if ((index = m_pDoc->selected_line) != -1) {
            m_pDoc->transform_rotate_line(m_pDoc->v_line, index, oldPoint, point);
            m_pDoc->selected_line = -1;
            tp1.x = tp1.y = tp2.x = tp2.y = 0;
        }
        else if ((index = m_pDoc->selected_oval_circle) != -1) {
            m_pDoc->transform_rotate_oval_circle(m_pDoc->v_oval_circle, index, oldPoint, point);
            m_pDoc->selected_oval_circle = -1;
        }
        else if ((index = m_pDoc->selected_polygon) != -1) {
            m_pDoc->transform_rotate_polygon(m_pDoc->v_polygon, index, oldPoint, point);
            m_pDoc->selected_polygon = -1;
            tpolygon.ps.clear();
            tpolygon.size = 1;
            tpolygon.color = RGB(0, 0, 0);
        }
        m_pDoc->m_operation = 0;
        Invalidate(TRUE);
    }
    else if (m_pDoc->m_operation == 102) { //缩放
        int index = -1;
        if ((index = m_pDoc->selected_line) != -1) {
            m_pDoc->transform_scale_line(m_pDoc->v_line, index, oldPoint, point);
            m_pDoc->selected_line = -1;
            tp1.x = tp1.y = tp2.x = tp2.y = 0;
        }
        else if ((index = m_pDoc->selected_perfect_circle) != -1) {
            m_pDoc->transform_scale_perfect_circle(m_pDoc->v_perf_circle, index, oldPoint, point);
            m_pDoc->selected_perfect_circle = -1;
            oldRadius = 0.0;
        }
        else if ((index = m_pDoc->selected_oval_circle) != -1) {
            m_pDoc->transform_scale_oval_circle(m_pDoc->v_oval_circle, index, oldPoint, point);
            m_pDoc->selected_oval_circle = -1;
            ta = tb = 0;
        }
        else if ((index = m_pDoc->selected_polygon) != -1) {
            m_pDoc->transform_scale_polygon(m_pDoc->v_polygon, index, oldPoint, point);
            m_pDoc->selected_polygon = -1;
            tpolygon.ps.clear();
            tpolygon.size = 1;
            tpolygon.color = RGB(0, 0, 0);
        }
        m_pDoc->m_operation = 0;
        Invalidate(TRUE);
    }
    ReleaseDC(dc2);
    ReleaseDC(dc1);
    CView::OnLButtonUp(nFlags, point);
}


void CMFCOpenGL01View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CDC *dc1 = GetDC();
    if (m_pDoc->m_operation == 5) {
        m_pDoc->line_cpen(dc1, m_pDoc->m_color, newPoint, parentPoint, m_pDoc->m_size);
        m_pDoc->is_drawing_polygon = FALSE;

        m_pDoc->v_polygon.push_back(CMFCOpenGL01Doc::d_polygon(temp_ps, m_pDoc->m_size, m_pDoc->m_color));
    }

    ReleaseDC(dc1);
    CView::OnLButtonDblClk(nFlags, point);
}


void CMFCOpenGL01View::OnMouseMove(UINT nFlags, CPoint point)
{
    CDC *dc1 = GetDC(), *dc2 = GetDC();
    int index = -1;
    dc1->SetROP2(R2_NOT);

    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 2) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 3) {
        int radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
        newPoint = point;
        radius = std::sqrt((newPoint.x - oldPoint.x)*(newPoint.x - oldPoint.x) + ((newPoint.y - oldPoint.y)*(newPoint.y - oldPoint.y)));
        dc1->Arc(CRect(oldPoint.x - radius, oldPoint.y - radius, oldPoint.x + radius, oldPoint.y + radius), CPoint(0, 0), CPoint(0, 0));
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 4) {
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));
        newPoint = point;
        dc1->Arc(CRect(oldPoint.x, oldPoint.y, newPoint.x, newPoint.y), CPoint(0, 0), CPoint(0, 0));
    }
    if (m_pDoc->m_operation == 5 && m_pDoc->is_drawing_polygon) {
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
        newPoint = point;
        dc1->MoveTo(oldPoint);
        dc1->LineTo(newPoint);
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 100) { //平移
        //COLORREF co = RGB(255, 0, 128);
        if (m_pDoc->selected_line != -1) {
            index = m_pDoc->selected_line;
            m_pDoc->line_cpen(dc1, m_pDoc->v_line[index].color, m_pDoc->v_line[index].p1, m_pDoc->v_line[index].p2, m_pDoc->v_line[index].size);
            m_pDoc->transform_translate_line(m_pDoc->v_line, index, point);
            m_pDoc->line_cpen(dc1, m_pDoc->v_line[index].color, m_pDoc->v_line[index].p1, m_pDoc->v_line[index].p2, m_pDoc->v_line[index].size);
        }
        else if (m_pDoc->selected_perfect_circle != -1) {
            index = m_pDoc->selected_perfect_circle;
            m_pDoc->circle_perfect_cpen(dc1, m_pDoc->v_perf_circle[index].color, m_pDoc->v_perf_circle[index].p0, m_pDoc->v_perf_circle[index].radius, m_pDoc->v_perf_circle[index].size);
            m_pDoc->transform_translate_perfect_circle(m_pDoc->v_perf_circle, index, point);
            m_pDoc->circle_perfect_cpen(dc1, m_pDoc->v_perf_circle[index].color, m_pDoc->v_perf_circle[index].p0, m_pDoc->v_perf_circle[index].radius, m_pDoc->v_perf_circle[index].size);
        }
        else if (m_pDoc->selected_oval_circle != -1) {
            index = m_pDoc->selected_oval_circle;
            m_pDoc->circle_oval_angle_cpen(dc1, m_pDoc->v_oval_circle[index].color, m_pDoc->v_oval_circle[index].p0.x, m_pDoc->v_oval_circle[index].p0.y, m_pDoc->v_oval_circle[index].a, m_pDoc->v_oval_circle[index].b, m_pDoc->v_oval_circle[index].angle, m_pDoc->v_oval_circle[index].size);
            m_pDoc->transform_translate_oval_circle(m_pDoc->v_oval_circle, index, point);
            m_pDoc->circle_oval_angle_cpen(dc1, m_pDoc->v_oval_circle[index].color, m_pDoc->v_oval_circle[index].p0.x, m_pDoc->v_oval_circle[index].p0.y, m_pDoc->v_oval_circle[index].a, m_pDoc->v_oval_circle[index].b, m_pDoc->v_oval_circle[index].angle, m_pDoc->v_oval_circle[index].size);
        }
        else if (m_pDoc->selected_polygon != -1) {
            index = m_pDoc->selected_polygon;
            m_pDoc->draw_polygon_cpen(dc1, m_pDoc->v_polygon[index], m_pDoc->v_polygon[index].color, m_pDoc->v_polygon[index].size);
            m_pDoc->transform_translate_polygon(m_pDoc->v_polygon, index, point);
            m_pDoc->draw_polygon_cpen(dc1, m_pDoc->v_polygon[index], m_pDoc->v_polygon[index].color, m_pDoc->v_polygon[index].size);
        }
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 101) { //旋转
        if (m_pDoc->selected_line != -1) {
            index = m_pDoc->selected_line;
            m_pDoc->line_cpen(dc1, m_pDoc->v_line[index].color, tp1, tp2, m_pDoc->v_line[index].size);

            //此处单独计算是为了不把数据写入存储对象，保持旋转过程不产生误差
            int xm = (m_pDoc->v_line[index].p1.x + m_pDoc->v_line[index].p2.x) / 2,
                ym = (m_pDoc->v_line[index].p1.y + m_pDoc->v_line[index].p2.y) / 2;
            double a = sqrt((xm - point.x)*(xm - point.x) + (ym - point.y)*(ym - point.y)),
                b = sqrt((oldPoint.x - point.x)*(oldPoint.x - point.x) + (oldPoint.y - point.y)*(oldPoint.y - point.y)),
                c = sqrt((xm - oldPoint.x)*(xm - oldPoint.x) + (ym - oldPoint.y)*(ym - oldPoint.y));
            double angle = (acos((a*a + c*c - b*b) / (2 * a*c)) / m_pDoc->pi * 180.0);
            double angle_judge = (oldPoint.x - xm)*(point.y - ym) - (point.x - xm)*(oldPoint.y - ym); //>0顺时针，<0逆时针
            angle = (angle_judge >= 0.0 ? angle : -angle);
            tp1 = m_pDoc->get_rotated_point(m_pDoc->v_line[index].p1, CPoint(xm, ym), angle);
            tp2 = m_pDoc->get_rotated_point(m_pDoc->v_line[index].p2, CPoint(xm, ym), angle);

            m_pDoc->line_cpen(dc1, m_pDoc->v_line[index].color, tp1, tp2, m_pDoc->v_line[index].size);
        }
        else if (m_pDoc->selected_oval_circle != -1) {
            index = m_pDoc->selected_oval_circle;
            m_pDoc->circle_oval_angle_cpen(dc1, m_pDoc->v_oval_circle[index].color, m_pDoc->v_oval_circle[index].p0.x, m_pDoc->v_oval_circle[index].p0.y, m_pDoc->v_oval_circle[index].a, m_pDoc->v_oval_circle[index].b, m_pDoc->v_oval_circle[index].angle, m_pDoc->v_oval_circle[index].size);
            m_pDoc->transform_rotate_oval_circle(m_pDoc->v_oval_circle, index, oldPoint, point);
            oldPoint = point;
            m_pDoc->circle_oval_angle_cpen(dc1, m_pDoc->v_oval_circle[index].color, m_pDoc->v_oval_circle[index].p0.x, m_pDoc->v_oval_circle[index].p0.y, m_pDoc->v_oval_circle[index].a, m_pDoc->v_oval_circle[index].b, m_pDoc->v_oval_circle[index].angle, m_pDoc->v_oval_circle[index].size);
        }
        else if (m_pDoc->selected_polygon != -1) {
            index = m_pDoc->selected_polygon;
            m_pDoc->draw_polygon_cpen(dc1, tpolygon, m_pDoc->v_polygon[index].color, m_pDoc->v_polygon[index].size);

            //此处单独计算是为了不把数据写入存储对象，保持旋转过程不产生误差
            int mid_x = 0, mid_y = 0;
            for (int i = 0; i < m_pDoc->v_polygon[index].ps.size(); i++) {
                mid_x += m_pDoc->v_polygon[index].ps[i].x;
                mid_y += m_pDoc->v_polygon[index].ps[i].y;
            }
            mid_x /= m_pDoc->v_polygon[index].ps.size();
            mid_y /= m_pDoc->v_polygon[index].ps.size();

            double a = sqrt((mid_x - point.x)*(mid_x - point.x) + (mid_y - point.y)*(mid_y - point.y)),
                b = sqrt((oldPoint.x - point.x)*(oldPoint.x - point.x) + (oldPoint.y - point.y)*(oldPoint.y - point.y)),
                c = sqrt((mid_x - oldPoint.x)*(mid_x - oldPoint.x) + (mid_y - oldPoint.y)*(mid_y - oldPoint.y));
            double angle = (acos((a*a + c*c - b*b) / (2 * a*c)) / m_pDoc->pi * 180.0);
            double angle_judge = (oldPoint.x - mid_x)*(point.y - mid_y) - (point.x - mid_x)*(oldPoint.y - mid_y); //>0顺时针，<0逆时针
            angle = (angle_judge >= 0.0 ? angle : -angle);
            tpolygon = m_pDoc->v_polygon[index];
            for (int i = 0; i < tpolygon.ps.size(); i++)
                tpolygon.ps[i] = m_pDoc->get_rotated_point(tpolygon.ps[i], CPoint(mid_x, mid_y), angle);

            m_pDoc->draw_polygon_cpen(dc1, tpolygon, m_pDoc->v_polygon[index].color, m_pDoc->v_polygon[index].size);
        }
    }
    if (nFlags == MK_LBUTTON && m_pDoc->m_operation == 102) { //缩放
        if (m_pDoc->selected_line != -1) {
            index = m_pDoc->selected_line;
            m_pDoc->line_cpen(dc1, m_pDoc->v_line[index].color, tp1, tp2, m_pDoc->v_line[index].size);
            
            //此处单独计算是为了不把数据写入存储对象，保持缩放速率不变
            int x1 = m_pDoc->v_line[index].p1.x, y1 = m_pDoc->v_line[index].p1.y,
                x2 = m_pDoc->v_line[index].p2.x, y2 = m_pDoc->v_line[index].p2.y;
            int xm = (x1 + x2) / 2, ym = (y1 + y2) / 2;
            double dis1 = sqrt((oldPoint.x - xm)*(oldPoint.x - xm) + (oldPoint.y - ym)*(oldPoint.y - ym)),
                dis2 = sqrt((point.x - xm)*(point.x - xm) + (point.y - ym)*(point.y - ym));
            double rate = dis2 / dis1;
            tp1 = CPoint((x1 - xm)*rate + xm, (y1 - ym)*rate + ym), tp2 = CPoint((x2 - xm)*rate + xm, (y2 - ym)*rate + ym);

            m_pDoc->line_cpen(dc1, m_pDoc->v_line[index].color, tp1, tp2, m_pDoc->v_line[index].size);
        }
        else if (m_pDoc->selected_perfect_circle != -1) {
            index = m_pDoc->selected_perfect_circle;
            m_pDoc->circle_perfect_cpen(dc1, m_pDoc->v_perf_circle[index].color, m_pDoc->v_perf_circle[index].p0, oldRadius, m_pDoc->v_perf_circle[index].size);
            
            //此处单独计算是为了不把数据写入存储对象，保持缩放速率不变
            int xm = m_pDoc->v_perf_circle[index].p0.x, ym = m_pDoc->v_perf_circle[index].p0.y;
            double dis1 = sqrt((oldPoint.x - xm)*(oldPoint.x - xm) + (oldPoint.y - ym)*(oldPoint.y - ym)),
                dis2 = sqrt((point.x - xm)*(point.x - xm) + (point.y - ym)*(point.y - ym));
            double rate = dis2 / dis1;
            oldRadius = (m_pDoc->v_perf_circle[index].radius)*rate;
            
            m_pDoc->circle_perfect_cpen(dc1, m_pDoc->v_perf_circle[index].color, m_pDoc->v_perf_circle[index].p0, oldRadius, m_pDoc->v_perf_circle[index].size);
        }
        else if (m_pDoc->selected_oval_circle != -1) {
            index = m_pDoc->selected_oval_circle;
            m_pDoc->circle_oval_angle_cpen(dc1, m_pDoc->v_oval_circle[index].color, m_pDoc->v_oval_circle[index].p0.x, m_pDoc->v_oval_circle[index].p0.y, ta, tb, m_pDoc->v_oval_circle[index].angle, m_pDoc->v_oval_circle[index].size);
            
            //此处单独计算是为了不把数据写入存储对象，保持缩放速率不变
            int xm = m_pDoc->v_oval_circle[index].p0.x,
                ym = m_pDoc->v_oval_circle[index].p0.y;
            double dis1 = sqrt((oldPoint.x - xm)*(oldPoint.x - xm) + (oldPoint.y - ym)*(oldPoint.y - ym)),
                dis2 = sqrt((point.x - xm)*(point.x - xm) + (point.y - ym)*(point.y - ym));
            double rate = dis2 / dis1;
            ta = m_pDoc->v_oval_circle[index].a * rate;
            tb = m_pDoc->v_oval_circle[index].b * rate;
            
            m_pDoc->circle_oval_angle_cpen(dc1, m_pDoc->v_oval_circle[index].color, m_pDoc->v_oval_circle[index].p0.x, m_pDoc->v_oval_circle[index].p0.y, ta, tb, m_pDoc->v_oval_circle[index].angle, m_pDoc->v_oval_circle[index].size);
        }
        else if (m_pDoc->selected_polygon != -1) {
            index = m_pDoc->selected_polygon;
            m_pDoc->draw_polygon_cpen(dc1, tpolygon, m_pDoc->v_polygon[index].color, m_pDoc->v_polygon[index].size);
            
            //此处单独计算是为了不把数据写入存储对象，保持缩放速率不变
            int mid_x = 0, mid_y = 0;
            for (int i = 0; i < m_pDoc->v_polygon[index].ps.size(); i++) {
                mid_x += m_pDoc->v_polygon[index].ps[i].x;
                mid_y += m_pDoc->v_polygon[index].ps[i].y;
            }
            mid_x /= m_pDoc->v_polygon[index].ps.size();
            mid_y /= m_pDoc->v_polygon[index].ps.size();
            double dis1 = sqrt((oldPoint.x - mid_x)*(oldPoint.x - mid_x) + (oldPoint.y - mid_y)*(oldPoint.y - mid_y)),
                dis2 = sqrt((point.x - mid_x)*(point.x - mid_x) + (point.y - mid_y)*(point.y - mid_y));
            double rate = dis2 / dis1;
            tpolygon = m_pDoc->v_polygon[index];
            for (int i = 0; i < tpolygon.ps.size(); i++) {
                tpolygon.ps[i].x = (tpolygon.ps[i].x - mid_x)*rate + mid_x;
                tpolygon.ps[i].y = (tpolygon.ps[i].y - mid_y)*rate + mid_y;
            }
            
            m_pDoc->draw_polygon_cpen(dc1, tpolygon, m_pDoc->v_polygon[index].color, m_pDoc->v_polygon[index].size);
        }
    }

    ReleaseDC(dc2);
    ReleaseDC(dc1);
    CView::OnMouseMove(nFlags, point);
}




