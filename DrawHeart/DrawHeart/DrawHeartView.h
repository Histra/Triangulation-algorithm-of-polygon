
// DrawHeartView.h : CDrawHeartView 类的接口
//

#pragma once


class CDrawHeartView : public CView
{
protected: // 仅从序列化创建
	CDrawHeartView();
	DECLARE_DYNCREATE(CDrawHeartView)

// 特性
public:
	CDrawHeartDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void Define_OriginalPoint(CDC *pDC);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawHeartView();
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
};

#ifndef _DEBUG  // DrawHeartView.cpp 中的调试版本
inline CDrawHeartDoc* CDrawHeartView::GetDocument() const
   { return reinterpret_cast<CDrawHeartDoc*>(m_pDocument); }
#endif

