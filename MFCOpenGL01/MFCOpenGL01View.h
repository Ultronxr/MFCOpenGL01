
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
    //virtual void OnDraw(CDC* pDC);
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


/***************************************************************************************************/
/****************************************OpenGL相关核心代码 开始************************************/
/***************************************************************************************************/

protected:
    HGLRC m_hRC;

    CRectTracker m_RectTracker; //选择框


    //保存位图
    bool saveTag = false;
    CString saveFilePath = _T("D:\\");

    //打开位图
    CString BmpName;                               //保存图像文件文件名
    CString EntName;                               //保存图像文件扩展名
    CBitmap m_bitmap;                              //创建位图对象

public:
    //afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); //建立OpenGL环境
    //afx_msg void OnSize(UINT nType, int cx, int cy); //设置OpenGL“画布”大小
    //afx_msg void ReSizeGLScene(int width, int height); //自定义函数，让OpenGL的画布大小随着窗口大小调整
    virtual void OnDraw(CDC* pDC);  //绘制图形的函数，OpenGL作图以glBegin()开始，glEnd()结尾
    //afx_msg BOOL OnEraseBkgnd(CDC* pDC); //强制返回TRUE，防止刷新背景导致窗口闪烁
    //afx_msg void OnDestroy(); //析构，释放内存

/***************************************************************************************************/
/****************************************OpenGL相关核心代码 结束************************************/
/***************************************************************************************************/



/**********************************************MFC窗口和按钮相关 开始****************************************/

    afx_msg void OnDrawRuler();
    afx_msg void OnDrawOrtho();
    afx_msg void OnDrawLine();
    afx_msg void OnDrawPoint();
    afx_msg void OnDrawCirclePerfect();
    afx_msg void OnDrawCircleOval();
    afx_msg void OnDrawPolygon();
    afx_msg void OnDrawFill();
    afx_msg void OnDrawSelect();
    afx_msg void OnDrawErase();
    afx_msg void OnDrawClear();

    afx_msg void OnFileSave();
    afx_msg void OnFileOpen();
    void ShowBitmap(CDC *pDC, CString BmpName);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

/**********************************************MFC窗口和按钮相关 结束****************************************/






/**********************************************画点 开始****************************************/

    //绘制圆形的点
    void point_circle(CDC *pDC, COLORREF color, int x, int y, int size);

    //绘制十字的点
    void point_cross(CDC *pDC, COLORREF color, int x, int y, int size);

    //绘制菱形的点
    void point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size);

/**********************************************画点 开始****************************************/





/**********************************************画线算法 开始****************************************/

    //DDA数值微分法法画线，斜率任意；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标
    void line_dda(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1);

    //中点法画线，斜率任意；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标
    void line_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1);

    //中点法画线，斜率任意，指定线宽，垂直线刷子；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标，线宽
    void line_midpoint_vertical_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width);

    //中点法画线，斜率任意，指定线宽，水平线刷子；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标，线宽
    void line_midpoint_horizontal_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width);

    //中点法画线，斜率任意，指定线宽，方形线刷子；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标，线宽
    void line_midpoint_square_linebrush(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int width);

    //bresenham法画线，斜率任意；    参数：pDC，颜色，起点x坐标，起点y坐标，终点x坐标，终点y坐标
    void line_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1);


    //CPen函数
    void line_dda_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size);
    void line_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size);
    void line_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x1, int y1, int size);

/**********************************************画线算法 结束****************************************/


/**********************************************画圆算法 开始****************************************/

    //bresenham法画正圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，半径
    void circle_perfect_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int radius);

    //bresenham法画正圆-gl版；    参数：整型颜色R，整型颜色G，整型颜色B，圆心x坐标，圆心y坐标，半径
    void circle_perfect_bresenham_gl(int colord1, int colord2, int colord3, int x0, int y0, int radius);

    //中点法画正圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，半径
    void circle_perfect_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int radius);

    //对称地画圆上的点；    参数：pDC，颜色，圆心x坐标，圆心y坐标，目标点的x坐标，目标点的y坐标
    void set_points_on_circle(CDC *pDC, COLORREF color, int x0, int y0, int x, int y);


    //bresenham法画椭圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，长轴的长度，短轴的长度
    void circle_oval_bresenham(CDC *pDC, COLORREF color, int x0, int y0, int a, int b);

    //中点法画椭圆；    参数：pDC，颜色，圆心x坐标，圆心y坐标，长轴的长度，短轴的长度
    void circle_oval_midpoint(CDC *pDC, COLORREF color, int x0, int y0, int a, int b);
    
    //对称地画椭圆上的点；    参数：pDC，颜色，圆心x坐标，圆心y坐标，目标点的x坐标，目标点的y坐标
    void set_points_on_oval(CDC *pDC, COLORREF color, int x0, int y0, int x, int y);



    //CPen函数
    void circle_perfect_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size);
    void circle_perfect_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int radius, int size);
    void set_points_on_circle_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size);

    void circle_oval_bresenham_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size);
    void circle_oval_midpoint_cpen(CDC *pDC, COLORREF color, int x0, int y0, int a, int b, int size);
    void set_points_on_oval_cpen(CDC *pDC, COLORREF color, int x0, int y0, int x, int y, int size);

/**********************************************画圆算法 结束****************************************/


/**********************************************区域填充算法 开始****************************************/

    //多边形顶点的数据结构
    typedef struct one_vertex_info {
        int x;
        int y;

        one_vertex_info() {}
        one_vertex_info(int xx, int yy) {
            this->x = xx;
            this->y = yy;
        }

    }vertex;

    //多边形顶点表
    vertex* PolygonVertex;

    //边的数据结构
    typedef struct one_edge_info {
        double y_high;         //边的上端点的y坐标
        double x_intersection; //扫描线与边的交点的x坐标
        double delta_x;        //边的斜率分之一，1/k
        struct one_edge_info* next_edge; //下一条边的指针
    }edge;

    //分类边表ET 和 活性边表AEL
    edge* EdgeTable;
    edge* ActiveEdgeList;

    //多边形的扫描线填充算法
    void set_PolygonVertex(int num, int array_vertex[][2]);
    void init_EdgeTable(int num, vertex* PolygonVertex);
    void insert_edge(edge* AELorET, int y, edge* one_edge);
    void del_edge(edge* AELorET, edge* one_edge);

    //CPen

    void flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt);

/**********************************************区域填充算法 结束****************************************/


/**********************************************二维图形裁剪算法 开始****************************************/

    //带有编码的端点数据结构
    typedef struct one_coded_vertex_info {
        int x;
        int y;
        int code;

        one_coded_vertex_info() {
            this->code = 0;
        }
        one_coded_vertex_info(int xx, int yy) {
            this->x = xx;
            this->y = yy;
            this->code = 0;
        }

    }vertex_coded;

    //带有编码的直线段的数据结构
    typedef struct one_line_info {
        vertex_coded vertex_coded_begin;
        vertex_coded vertex_coded_end;

        one_line_info() {}
        one_line_info(one_coded_vertex_info vb, one_coded_vertex_info ve) {
            this->vertex_coded_begin = vb;
            this->vertex_coded_end = ve;
        }

    }line;

    //Cohen-Sutherland+中点分割（区域编码+中点分割）法线段裁剪    参数：pDC，颜色，裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，几条线，待裁剪的直线
    void line_cut_Sutherland_midpoint(CDC *pDC, COLORREF color, vertex window_vertex_left_top, vertex window_vertex_right_bottom, int num, line lines[]);
    //中点分割法递归二分确定线段与裁剪边框相交于哪一点    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，待裁剪的直线
    vertex_coded line_cut_midpoint(vertex window_vertex_left_top, vertex window_vertex_right_bottom, line single_line);

    //确定线段的端点落在那个区域，获取其对应的编码    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，端点指针
    void set_vertex_code(vertex window_vertex_left_top, vertex window_vertex_right_bottom, vertex_coded *v);


    //判断裁剪框对角线和待裁剪线段的位置关系    参数：裁剪线框的对角线的起点，裁剪线框对角线的终点，待裁剪线段的起点，待裁剪线段的终点
    bool judge_line_pos(vertex window_vertex_a, vertex window_vertex_b, vertex_coded va, vertex_coded vb);

    //得到线段与对角线的交点    参数：裁剪框对角线的起点，裁剪框对角线的终点，待裁剪线的起点，待裁剪线的终点
    vertex_coded get_mid_point(vertex diagonal_vertex_a, vertex diagonal_vertex_b, vertex_coded va, vertex_coded vb);



    typedef struct one_polygon {
        int vertex_num;
        std::vector<vertex> vertexes;

        one_polygon() {
            this->vertex_num = 0;
            this->vertexes = {};
        }
        one_polygon(int n, std::vector<vertex> v) {
            this->vertex_num = n;
            this->vertexes = v;
        }
    }polygon;

    //Sutherland-Hodgman（逐边裁剪）法多边形裁剪（返回裁剪完成的新多边形）    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，待裁剪的多边形
    polygon polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon);

    //求出直线和裁剪框的交点（返回交点处的数值）    参数：待裁剪的线的起始点，待裁剪的线的结束点，裁剪线框的某一条线x=value或y=value的value值，是x=还是y=（true为x，false为y）
    int get_intersection_point(vertex vb, vertex ve, int value, bool flag);

    //绘制多边形    参数：PDC，颜色，顶点个数，多边形
    void draw_polygon(CDC *pDC, COLORREF color, polygon p);


    //CPen




/**********************************************二维图形裁剪算法 结束****************************************/



    /*
Ctrl+M+O 折叠所有方法
Ctrl+M+M 折叠或者展开当前方法
Ctrl+M+L 展开所有方法
    */


/**********************************************二维图形变换算法 开始****************************************/

    //多边形旋转变换    参数：PDC，颜色，原始多边形，旋转中心点，旋转角度（角度制，有正负）
    void transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle);




/**********************************************二维图形变换算法 结束****************************************/
    

    
    
};

#ifndef _DEBUG  // MFCOpenGL01View.cpp 中的调试版本
inline CMFCOpenGL01Doc* CMFCOpenGL01View::GetDocument() const
   { return reinterpret_cast<CMFCOpenGL01Doc*>(m_pDocument); }
#endif

