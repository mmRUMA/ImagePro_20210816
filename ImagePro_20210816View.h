
// ImagePro_20210816View.h: CImagePro20210816View 클래스의 인터페이스
//

#pragma once


class CImagePro20210816View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImagePro20210816View() noexcept;
	DECLARE_DYNCREATE(CImagePro20210816View)

// 특성입니다.
public:
	CImagePro20210816Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CImagePro20210816View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStr();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSharpening();
	void Convolve(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float mask[][3], int bias, int dep);
	afx_msg void OnRegionSmooding();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	void DetectEdge(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float hmask[][3], float wmask[][3], int dep);
	afx_msg void OnRegionAverageFilter();
	afx_msg void OnRegionMediamFilter();
	afx_msg void OnMorphologyColorGray();
	afx_msg void OnMorphologyBinarization();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnMorphologyDilation();
	afx_msg void OnMorphologyOpening();
	afx_msg void OnMorphologyClosing();
	void CopyResultToInput();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryZoomoutAvgFilter();
	afx_msg void OnGeometryRotate();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
};

#ifndef _DEBUG  // ImagePro_20210816View.cpp의 디버그 버전
inline CImagePro20210816Doc* CImagePro20210816View::GetDocument() const
   { return reinterpret_cast<CImagePro20210816Doc*>(m_pDocument); }
#endif

