
// MFCOpenGL01Doc.h : CMFCOpenGL01Doc 类的接口
//


#pragma once

class CMFCOpenGL01Doc : public CDocument
{
protected: // 仅从序列化创建
	CMFCOpenGL01Doc();
	DECLARE_DYNCREATE(CMFCOpenGL01Doc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCOpenGL01Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // 生成的消息映射函数
protected:
    DECLARE_MESSAGE_MAP()



///自定数据结构
public:

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

    //自定义多边形数据结构
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




    ///所有直接用于绘图的数据结构

    typedef struct draw_point {
        CPoint p;
        int type; //指 点的类型
        int size;
        COLORREF color;

        draw_point(CPoint p, int type, int size, COLORREF color) {
            this->p = p;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_point;

    typedef struct draw_line {
        CPoint p1, p2;
        int type; //指 线的算法
        int size;
        COLORREF color;

        draw_line(CPoint p1, CPoint p2, int type, int size, COLORREF color) {
            this->p1 = p1;
            this->p2 = p2;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_line;

    typedef struct draw_perfect_circle {
        CPoint p0;
        int radius;
        int type;
        int size;
        COLORREF color;

        draw_perfect_circle(CPoint p0, int radius, int type, int size, COLORREF color) {
            this->p0 = p0;
            this->radius = radius;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_perf_circle;

    typedef struct draw_oval_circle {
        CPoint p0;
        int a, b;
        int angle; //顺时针旋转角度
        int type;
        int size;
        COLORREF color;

        draw_oval_circle(CPoint p0, int a, int b, int angle, int type, int size, COLORREF color) {
            this->p0 = p0;
            this->a = a;
            this->b = b;
            this->angle = angle;
            this->type = type;
            this->size = size;
            this->color = color;
        }
    }d_oval_circle;

    typedef struct draw_polygon {
        std::vector<CPoint> ps;
        int size;
        COLORREF color;

        draw_polygon(std::vector<CPoint> ps, int size, COLORREF color) {
            this->ps = ps;
            this->size = size;
            this->color = color;
        }
    }d_polygon;

    typedef struct draw_fill {
        CPoint p;
        COLORREF color;

        draw_fill(CPoint p, COLORREF color) {
            this->p = p;
            this->color = color;
        }
    }d_fill;




///绘图数据存储
public:

    //存储所有绘图内容
    std::vector<d_point> v_point;
    std::vector<d_line> v_line;
    std::vector<d_perf_circle> v_perf_circle;
    std::vector<d_oval_circle> v_oval_circle;
    std::vector<d_polygon> v_polygon;
    std::vector<d_fill> v_fill;


    double pi = acos(-1.0);

    //当前操作、当前颜色、当前线宽
    int m_operation; //0无，1点，2线，3正圆，4椭圆，5多边形，10填充，20/21裁剪，30橡皮擦
    COLORREF m_color;
    int m_size;


    //对话框中的变量
    //点的类型、线的类型、正圆的类型、椭圆的类型（类型指不同的算法）
    int point_type, line_type, circle_perfect_type, circle_oval_type;

    //多边形
    polygon m_polygon;
    BOOL is_drawing_polygon = FALSE;




    //上次被选中的图形
    int selected_point = -1, selected_line = -1, selected_perfect_circle = -1, selected_oval_circle = -1, selected_polygon = -1;


    ///寻找鼠标是否选中图形

    void select_all(CDC *pDC, CPoint point);

    //选中点
    int select_point(CPoint pos);

    //选中线
    int select_line(CPoint pos);

    //选中正圆
    int select_perfect_circle(CPoint pos);

    //选中椭圆
    int select_oval_circle(CPoint pos);

    //选中多边形
    int select_polygon(CPoint pos);
    



    //刷新所有绘制的图像
    void flush_all_drawing(CDC *pDC);

    //绘制多边形
    void draw_polygon_cpen(CDC *pDC, d_polygon p);

    



    ///画点 开始

    //绘制圆形的点
    void point_circle(CDC *pDC, COLORREF color, int x, int y, int size);

    //绘制十字的点
    void point_cross(CDC *pDC, COLORREF color, int x, int y, int size);

    //绘制菱形的点
    void point_rhombus(CDC *pDC, COLORREF color, int x, int y, int size);







    ///画线算法 开始

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





    ///画圆算法 开始

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

    //带有旋转角度的椭圆，顺时针旋转  参数：pDC，颜色，圆心x，圆心y，长轴a，短轴b，旋转角度（角度制），线宽
    void circle_oval_angle_cpen(CDC *pDC, COLORREF color, float x0, float y0, float a, float b, double angle, int size);




    ///区域填充算法 开始

    //CPen

    void flood_fill_cbrush(CDC *pDC, COLORREF color, COLORREF color_banned, CPoint pt);







    ///二维图形裁剪算法 开始


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



    //Sutherland-Hodgman（逐边裁剪）法多边形裁剪（返回裁剪完成的新多边形）    参数：裁剪窗口范围的左上方点坐标，裁剪窗口范围的右下方点坐标，待裁剪的多边形
    polygon polygon_cut_Sutherland_Hodgman(vertex window_vertex_left_top, vertex window_vertex_right_bottom, polygon src_polygon);

    //求出直线和裁剪框的交点（返回交点处的数值）    参数：待裁剪的线的起始点，待裁剪的线的结束点，裁剪线框的某一条线x=value或y=value的value值，是x=还是y=（true为x，false为y）
    int get_intersection_point(vertex vb, vertex ve, int value, bool flag);

    //绘制多边形    参数：PDC，颜色，顶点个数，多边形
    void draw_polygon(CDC *pDC, COLORREF color, polygon p);


    //CPen









    ///二维图形变换算法 开始

    //平移
    void transform_translate();

    //多边形旋转变换    参数：PDC，颜色，原始多边形，旋转中心点，旋转角度（角度制，有正负）
    void transform_rotate_polygon(CDC *pDC, COLORREF color, polygon src_polygon, vertex center, int angle);

    //旋转
    void transform_rotate();

    //缩放
    void transform_scale();

    //对称
    void transform_symmetry();

    //错切
    void transform_shear();

    //仿射
    void transform_affline();

    //复合
    void transform_compound();


#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
