
// cgWGFillPolyView.h : CcgWGFillPolyView 类的接口
//

#pragma once
#define N 1000

class CcgWGFillPolyView : public CView
{
protected: // 仅从序列化创建
	CcgWGFillPolyView();
	DECLARE_DYNCREATE(CcgWGFillPolyView)

// 特性
public:
	CcgWGFillPolyDoc* GetDocument() const;/// 获取Doc指针函数
	int pNumbers;/// 多边形顶点的个数                      
	CPoint MPolygon[N];/// 多边形存储
	CPoint mousePoint;/// 鼠标位置
	int edgeNumbers;/// 多边形边的条数
	double yMax[N], yMin[N], Xa[N], Dx[N];/// 有序边表发数据结构
	int edgeEnd, edgeBegin;/// 有序边表法边起开始和边结束
	int yScan;/// 有序边表法y扫描线
	int dx[4];/// 种子法的四连通x坐标表示
	int dy[4];/// 种子法的四连通y坐标biaoshi
	COLORREF judgeRgb;/// 种子法初始位置的像素值
	COLORREF targetRgb;/// 种子法需要填充的像素值

// 操作
public:
	void Define_OriginalPoint(CDC *pDC);/// 重新定义坐标系函数
	void SortedEdgeTableFillPolygon(int pNumbers, CPoint MPolygon[], CDC* pDC);/// 有序边表法
	void LoadPolygon(int pNumbers, CPoint MPolygon[]);/// 载入多边形的边
	void InsertPolygon(double x1, double y1, double x2, double y2);/// 插入多边形的边
	void Include();/// 求交函数
	void UpdataXvalue();/// 更新操作变集合函数
	void SortX(int edgeBedin, int i);/// 排序函数
	void FillScan(CDC* pDC);/// 填充函数
	void PointwiseFillPolygon(int pNumbers, CPoint MPolygon[], CDC* pDC);/// 逐点法
	bool JudgeIn(int x, int y, double tempx[], double tempy[], int pNumbers);/// 判断一个点是否在多边形内
	void SeedFillPolygon(int pNumbers, CPoint MPolygon[], CDC* pDC);/// 种子填充法
	void SeedRecursion(int x, int y, CDC* pDC);/// 终止填充法递归函数
	bool PT(int pNumbers, CPoint MPolygon[], CDC* pDC);/// 多边形的三角剖分函数

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CcgWGFillPolyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // cgWGFillPolyView.cpp 中的调试版本
inline CcgWGFillPolyDoc* CcgWGFillPolyView::GetDocument() const
   { return reinterpret_cast<CcgWGFillPolyDoc*>(m_pDocument); }
#endif

