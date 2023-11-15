
// ImagePro_20210816View.cpp: CImagePro20210816View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_20210816.h"
#endif

#include "ImagePro_20210816Doc.h"
#include "ImagePro_20210816View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImagePro20210816View

IMPLEMENT_DYNCREATE(CImagePro20210816View, CScrollView)

BEGIN_MESSAGE_MAP(CImagePro20210816View, CScrollView)
	ON_COMMAND(ID_PIXEL_ADD, &CImagePro20210816View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImagePro20210816View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImagePro20210816View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImagePro20210816View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImagePro20210816View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STR, &CImagePro20210816View::OnPixelContrastStr)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImagePro20210816View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImagePro20210816View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImagePro20210816View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SMOODING, &CImagePro20210816View::OnRegionSmooding)
	ON_COMMAND(ID_REGION_SHARPENING, &CImagePro20210816View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImagePro20210816View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImagePro20210816View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CImagePro20210816View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CImagePro20210816View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTER, &CImagePro20210816View::OnRegionAverageFilter)
	ON_COMMAND(ID_REGION_MEDIAM_FILTER, &CImagePro20210816View::OnRegionMediamFilter)
	ON_COMMAND(ID_MORPHOLOGY_COLOR_GRAY, &CImagePro20210816View::OnMorphologyColorGray)
	ON_COMMAND(ID_MORPHOLOGY_BINARIZATION, &CImagePro20210816View::OnMorphologyBinarization)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CImagePro20210816View::OnMorphologyErosion)
	ON_COMMAND(ID_MORPHOLOGY_DILATION, &CImagePro20210816View::OnMorphologyDilation)
	ON_COMMAND(ID_MORPHOLOGY_OPENING, &CImagePro20210816View::OnMorphologyOpening)
	ON_COMMAND(ID_MORPHOLOGY_CLOSING, &CImagePro20210816View::OnMorphologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImagePro20210816View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CImagePro20210816View::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImagePro20210816View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImagePro20210816View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG_FILTER, &CImagePro20210816View::OnGeometryZoomoutAvgFilter)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImagePro20210816View::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CImagePro20210816View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CImagePro20210816View::OnGeometryFlip)
END_MESSAGE_MAP()

// CImagePro20210816View 생성/소멸

CImagePro20210816View::CImagePro20210816View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImagePro20210816View::~CImagePro20210816View()
{
}

BOOL CImagePro20210816View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImagePro20210816View 그리기

void CImagePro20210816View::OnDraw(CDC* pDC)
{
	CImagePro20210816Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	int x, y;

	if (pDoc->inputImg != NULL) // 입력 영상1 출력
	{
		if (pDoc->depth == 1) // 흑백 영상 출력
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
		}
		else // 컬러 영상 출력
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3 * x], pDoc->inputImg[y][3 * x + 1], pDoc->inputImg[y][3 * x + 2]));
		}
	}

	if (pDoc->resultImg != NULL) // 결과 영상 출력
	{
		if (pDoc->depth == 1) // 흑백 영상 출력
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(pDoc->imageWidth + 20 + x, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
		}
		else // 컬러 영상 출력
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(pDoc->imageWidth + 20 + x, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x + 1], pDoc->resultImg[y][3 * x + 2]));
		}
	}
	
	if (pDoc->inputImg2 != NULL) // 입력 영상2 출력
	{
		if (pDoc->depth == 1) // 흑백 영상 출력
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(2 * (pDoc->imageWidth + 20) + x, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x]));
		}
		else // 컬러 영상 출력
		{
			for (y = 0; y < pDoc->imageHeight; y++)
				for (x = 0; x < pDoc->imageWidth; x++)
					pDC->SetPixel(2 * (pDoc->imageWidth + 20) + x, y, RGB(pDoc->inputImg2[y][3 * x], pDoc->inputImg2[y][3 * x + 1], pDoc->inputImg2[y][3 * x + 2]));
		}
	}

	if (pDoc->gResultImg != NULL) // 크기가 변한 결과 영상 출력
	{
		if (pDoc->depth == 1) // 흑백 영상 출력
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
		}
		else // 컬러 영상 출력
		{
			for (y = 0; y < pDoc->gImageHeight; y++)
				for (x = 0; x < pDoc->gImageWidth; x++)
					pDC->SetPixel(x, pDoc->imageHeight + 20 + y, RGB(pDoc->gResultImg[y][3 * x], pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
		}
	}
}

void CImagePro20210816View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx, sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImagePro20210816View 진단

#ifdef _DEBUG
void CImagePro20210816View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImagePro20210816View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImagePro20210816Doc* CImagePro20210816View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagePro20210816Doc)));
	return (CImagePro20210816Doc*)m_pDocument;
}
#endif //_DEBUG


// CImagePro20210816View 메시지 처리기


void CImagePro20210816View::OnPixelAdd()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	int x, y, value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			value = pDoc->inputImg[y][x] + 50;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();
}


void CImagePro20210816View::OnPixelSub()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	int x, y, value;

	for (y=0; y < pDoc->imageHeight; y++)
		for (x=0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			value = pDoc->inputImg[y][x] - 50;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();
}


void CImagePro20210816View::OnPixelMul()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	int x, y, value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			value = pDoc->inputImg[y][x] * 1.5;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();
}


void CImagePro20210816View::OnPixelDiv()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	int x, y, value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			value = int(pDoc->inputImg[y][x] / 1.5);
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();
}


void CImagePro20210816View::OnPixelHistoEq()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;
	if (pDoc->depth == 3) {
		AfxMessageBox("흑백 영상만 적용가능합니다.");
		return;
	}

	int x, y, i, k;
	int acc_hist = 0; // 히스토그램 누적 합
	int N = pDoc->imageWidth * pDoc->imageHeight; // 영상의 전체 픽셀수
	int hist[256], sum[256];

	for (i = 0; i < 256; i++) hist[i] = 0;

	// 히스토그램 구하기
	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			k = pDoc->inputImg[y][x];
			hist[k]++;
		}

	// 누적 분포 구하기
	for (i = 0; i < 256; i++)
	{
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	// 평활화 화소값 저장
	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			k = pDoc->inputImg[y][x];
			pDoc->resultImg[y][x] = (float) sum[k] / N * 255;
		}

	Invalidate();
}


void CImagePro20210816View::OnPixelContrastStr()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;
	if (pDoc->depth == 3) {
		AfxMessageBox("흑백 영상만 적용가능합니다.");
		return;
	}

	int x, y, value;
	int max = 0;
	int min = 255;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			value = pDoc->inputImg[y][x];
			if (value < min) min = value; // 최대값 갱신
			if (value > max) max = value; // 최소값 갱신
		}

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
			pDoc->resultImg[y][x] = (pDoc->inputImg[y][x] - min) * 255 / (max - min);

	Invalidate();
}


void CImagePro20210816View::OnPixelBinarization()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	int x, y;
	int threshold = 128;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->inputImg[y][x] > threshold) pDoc->resultImg[y][x] = 255;
				else pDoc->resultImg[y][x] = 0;
			}
			else
			{
				if ((pDoc->inputImg[y][3 * x] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2]) / 3 > threshold)
				{
					pDoc->resultImg[y][3 * x] = 255;
					pDoc->resultImg[y][3 * x + 1] = 255;
					pDoc->resultImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->resultImg[y][3 * x] = 0;
					pDoc->resultImg[y][3 * x + 1] = 0;
					pDoc->resultImg[y][3 * x + 2] = 0;
				}
			}
		}

	Invalidate();
}


void CImagePro20210816View::LoadTwoImage()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	CFileDialog dlg(true);

	if (dlg.DoModal() != IDOK) return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->LoadSecondImageFile(ar);
	file.Close();
}


void CImagePro20210816View::OnPixelTwoImageAdd()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	LoadTwoImage();

	int x, y, value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			value = 0.7 * pDoc->inputImg[y][x] + 0.3 * pDoc->inputImg2[y][x];
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();
}


void CImagePro20210816View::OnPixelTwoImageSub()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	if (pDoc->inputImg == NULL) return;

	LoadTwoImage();

	int x, y, value;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
		{
			value = abs(pDoc->inputImg[y][x] - pDoc->inputImg2[y][x]);
			if (value > 64) value = 255;
			else value = 0;
			//if (value > 255) value = 255;
			//else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();
}


void CImagePro20210816View::Convolve(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float mask[][3], int bias, int dep)
{
	int x, y, i, j;
	float sum, rsum, gsum, bsum;

	for (y = 1; y < rows-1; y++)
		for (x = 1; x < cols-1; x++)
		{
			if (dep == 1) // 흑백 영상
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
						sum += inImg[y + j - 1][x + i - 1] * mask[j][i];
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;

				outImg[y][x] = sum;
			}
			else // 컬러 영상
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += inImg[y + j - 1][3*(x + i - 1)] * mask[j][i];
						gsum += inImg[y + j - 1][3*(x + i - 1) + 1] * mask[j][i];
						bsum += inImg[y + j - 1][3*(x + i - 1) + 2] * mask[j][i];
					}
				rsum += bias;
				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;

				gsum += bias;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;

				bsum += bias;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				outImg[y][3*x] = rsum;
				outImg[y][3*x+1] = gsum;
				outImg[y][3*x+2] = bsum;
			}
		}
}


void CImagePro20210816View::OnRegionSmooding()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	float kernel[][3] = {{1 / 9., 1 / 9., 1 / 9.},
								 {1 / 9., 1 / 9., 1 / 9.},
								 {1 / 9., 1 / 9., 1 / 9.}};

	Convolve(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImagePro20210816View::OnRegionSharpening()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	float kernel[][3] = {{ 0, -1,  0},
								 {-1,  5, -1},
								 { 0, -1,  0}};

	Convolve(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImagePro20210816View::OnRegionEmbossing()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	float kernel[][3] = {{-1, 0, 0},
								 { 0, 0, 0},
								 { 0, 0, 1}};

	Convolve(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, kernel, 128, pDoc->depth);

	Invalidate();
}


void CImagePro20210816View::DetectEdge(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float hmask[][3], float wmask[][3], int dep)
{
	int i, x, y, value;
	unsigned char** Er, ** Ec;

	// 메모리 할당
	Er = (unsigned char**)malloc(rows * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(rows * sizeof(unsigned char*));

	for (i = 0; i < rows; i++)
	{
		Er[i] = (unsigned char*)malloc(cols * dep);
		Ec[i] = (unsigned char*)malloc(cols * dep);
	}

	Convolve(inImg, Er, cols, rows, hmask, 0, dep);
	Convolve(inImg, Ec, cols, rows, wmask, 0, dep);

	for (y = 0; y < rows; y++)
		for (x = 0; x < cols; x++)
		{
			if (dep == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				outImg[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3 * x] * Er[y][3 * x] + Ec[y][3 * x] * Ec[y][3 * x]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				outImg[y][3 * x] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				outImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				outImg[y][3 * x + 2] = value;

				value = sqrt(outImg[y][3 * x] * outImg[y][3 * x] + outImg[y][3 * x + 1] * outImg[y][3 * x + 1] + outImg[y][3 * x + 2] * outImg[y][3 * x + 2]);
				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				outImg[y][3 * x] = value;
				outImg[y][3 * x + 1] = value;
				outImg[y][3 * x + 2] = value;
			}
		}

	// 메모리 반환
	for (int i = 0; i < rows; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);
}


void CImagePro20210816View::OnRegionPrewitt()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	float hmask[][3] = {{-1, -1, -1},
									{ 0,  0,  0},
									{ 1,  1,  1}};
	float wmask[][3] = {{1, 0, -1},
									{1, 0, -1},
									{1, 0, -1}};

	DetectEdge(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, hmask, wmask, pDoc->depth);

	Invalidate();
}


void CImagePro20210816View::OnRegionRoberts()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	float hmask[][3] = {{-1, 0, 0},
									{ 0, 1, 0},
									{ 0, 0, 0}};
	float wmask[][3] = {{0, 0, -1},
									{0, 1,  0},
									{0, 0,  0}};

	DetectEdge(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, hmask, wmask, pDoc->depth);

	Invalidate();
}


void CImagePro20210816View::OnRegionSobel()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	float hmask[][3] = {{-1,-2,-1},
									{ 0, 0, 0},
									{ 1, 2, 1}};
	float wmask[][3] = {{1, 0 -1},
									{2, 0,-2},
									{1, 0,-1}};

	DetectEdge(pDoc->inputImg, pDoc->resultImg, pDoc->imageWidth, pDoc->imageHeight, hmask, wmask, pDoc->depth);

	Invalidate();
}


void CImagePro20210816View::OnRegionAverageFilter()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y, i, j;
	int xcor, ycor;
	int sum, rsum, gsum, bsum, count;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1) {
				sum = 0;
				count = 0;

				for (j = -2; j <= 2; j++)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;

						if (ycor >= 0 && ycor <= pDoc->imageHeight - 1 && xcor >= 0 && xcor <= pDoc->imageWidth - 1)
						{
							sum += pDoc->inputImg[ycor][xcor];
							count++;
						}
					}
				pDoc->resultImg[y][x] = sum / count;
			}
			else {
				rsum = 0; gsum = 0; bsum = 0;
				count = 0;

				for (j = -2; j <= 2; j++)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;

						if (ycor >= 0 && ycor <= pDoc->imageHeight - 1 && xcor >= 0 && xcor <= pDoc->imageWidth - 1)
						{
							rsum += pDoc->inputImg[ycor][3 * xcor];
							gsum += pDoc->inputImg[ycor][3 * xcor + 1];
							bsum += pDoc->inputImg[ycor][3 * xcor + 2];
							count++;
						}
					}
				pDoc->resultImg[y][3 * x] = rsum / count;
				pDoc->resultImg[y][3 * x + 1] = gsum / count;
				pDoc->resultImg[y][3 * x + 2] = bsum / count;
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnRegionMediamFilter()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y, i, j, temp;
	int n[9];

	for (y = 1; y < pDoc->imageHeight - 1; y++)
		for (x = 1; x < pDoc->imageWidth - 1; x++)
		{
			if (pDoc->depth == 1) // 흑백 영상
			{
				n[0] = pDoc->inputImg[y - 1][x - 1];
				n[1] = pDoc->inputImg[y - 1][x];
				n[2] = pDoc->inputImg[y - 1][x + 1];
				n[3] = pDoc->inputImg[y][x - 1];
				n[4] = pDoc->inputImg[y][x];
				n[5] = pDoc->inputImg[y][x + 1];
				n[6] = pDoc->inputImg[y + 1][x - 1];
				n[7] = pDoc->inputImg[y + 1][x];
				n[8] = pDoc->inputImg[y + 1][x + 1];

				// 정렬
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][x] = n[4];
			}
			else // 컬러 영상
			{
				n[0] = pDoc->inputImg[y - 1][3 * (x - 1)];
				n[1] = pDoc->inputImg[y - 1][3 * x];
				n[2] = pDoc->inputImg[y - 1][3 * (x + 1)];
				n[3] = pDoc->inputImg[y][3 * (x - 1)];
				n[4] = pDoc->inputImg[y][3 * x];
				n[5] = pDoc->inputImg[y][3 * (x + 1)];
				n[6] = pDoc->inputImg[y + 1][3 * (x - 1)];
				n[7] = pDoc->inputImg[y + 1][3 * x];
				n[8] = pDoc->inputImg[y + 1][3 * (x + 1)];

				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][3 * x] = n[4];

				n[0] = pDoc->inputImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->inputImg[y - 1][3 * x + 1];
				n[2] = pDoc->inputImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->inputImg[y][3 * (x - 1) + 1];
				n[4] = pDoc->inputImg[y][3 * x + 1];
				n[5] = pDoc->inputImg[y][3 * (x + 1) + 1];
				n[6] = pDoc->inputImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->inputImg[y + 1][3 * x + 1];
				n[8] = pDoc->inputImg[y + 1][3 * (x + 1) + 1];

				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][3 * x + 1] = n[4];

				n[0] = pDoc->inputImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->inputImg[y - 1][3 * x + 2];
				n[2] = pDoc->inputImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->inputImg[y][3 * (x - 1) + 2];
				n[4] = pDoc->inputImg[y][3 * x + 2];
				n[5] = pDoc->inputImg[y][3 * (x + 1) + 2];
				n[6] = pDoc->inputImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->inputImg[y + 1][3 * x + 2];
				n[8] = pDoc->inputImg[y + 1][3 * (x + 1) + 2];

				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][3 * x + 2] = n[4];
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnMorphologyColorGray()
{
	CImagePro20210816Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			gray = (pDoc->inputImg[y][3 * x] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2]) / 3;

			pDoc->inputImg[y][3 * x] = gray;
			pDoc->inputImg[y][3 * x + 1] = gray;
			pDoc->inputImg[y][3 * x + 2] = gray;
		}

	Invalidate();
}


void CImagePro20210816View::OnMorphologyBinarization()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;
	int threshold = 128;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->inputImg[y][x] > threshold) pDoc->inputImg[y][x] = 255;
				else pDoc->inputImg[y][x] = 0;
			}
			else
			{
				if ((pDoc->inputImg[y][3 * x] + pDoc->inputImg[y][3 * x + 1] + pDoc->inputImg[y][3 * x + 2]) / 3 > threshold)
				{
					pDoc->inputImg[y][3 * x] = 255;
					pDoc->inputImg[y][3 * x + 1] = 255;
					pDoc->inputImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->inputImg[y][3 * x] = 0;
					pDoc->inputImg[y][3 * x + 1] = 0;
					pDoc->inputImg[y][3 * x + 2] = 0;
				}
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnMorphologyErosion()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min, rmin, gmin, bmin;

	for (y = 1; y < pDoc->imageHeight - 1; y++)
		for (x = 1; x < pDoc->imageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				min = 255;

				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
						if (pDoc->inputImg[y + j][x + i] < min)
							min = pDoc->inputImg[y + j][x + i];
				pDoc->resultImg[y][x] = min;
			}
			else
			{
				rmin = 255; gmin = 255; bmin = 255;

				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->inputImg[y + j][3 * (x + i)] < rmin)
							rmin = pDoc->inputImg[y + j][3 * (x + i)];
						if (pDoc->inputImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->inputImg[y + j][3 * (x + i) + 1];
						if (pDoc->inputImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->inputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->resultImg[y][3 * x] = rmin;
				pDoc->resultImg[y][3 * x + 1] = gmin;
				pDoc->resultImg[y][3 * x + 2] = bmin;
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnMorphologyDilation()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max, rmax, gmax, bmax;

	for (y = 1; y < pDoc->imageHeight - 1; y++)
		for (x = 1; x < pDoc->imageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;

				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
						if (pDoc->inputImg[y + j][x + i] > max)
							max = pDoc->inputImg[y + j][x + i];
				pDoc->resultImg[y][x] = max;
			}
			else
			{
				rmax = 0; gmax = 0; bmax = 0;

				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->inputImg[y + j][3 * (x + i)] > rmax)
							rmax = pDoc->inputImg[y + j][3 * (x + i)];
						if (pDoc->inputImg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->inputImg[y + j][3 * (x + i) + 1];
						if (pDoc->inputImg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->inputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->resultImg[y][3 * x] = rmax;
				pDoc->resultImg[y][3 * x + 1] = gmax;
				pDoc->resultImg[y][3 * x + 2] = bmax;
			}
		}

	Invalidate();
}


void CImagePro20210816View::CopyResultToInput()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth * pDoc->depth; x++)
			pDoc->inputImg[y][x] = pDoc->resultImg[y][x];
}


void CImagePro20210816View::OnMorphologyOpening()
{
	for (int i = 0; i < 3; i++)
	{
		OnMorphologyErosion();
		CopyResultToInput();
	}

	for (int i = 0; i < 3; i++)
	{
		OnMorphologyDilation();
		CopyResultToInput();
	}

	Invalidate();
}


void CImagePro20210816View::OnMorphologyClosing()
{
	for (int i = 0; i < 3; i++)
	{
		OnMorphologyDilation();
		CopyResultToInput();
	}

	for (int i = 0; i < 3; i++)
	{
		OnMorphologyErosion();
		CopyResultToInput();
	}

	Invalidate();
}


void CImagePro20210816View::OnGeometryZoominPixelCopy()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;

	int xscale = 3;
	int yscale = 2;

	// 메모리 반환
	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth * xscale;
	pDoc->gImageHeight = pDoc->imageHeight * yscale;

	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->gImageHeight; i++)
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);

	for (y=0; y<pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->inputImg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultImg[y][3 * x] = pDoc->inputImg[y / yscale][3 * (x / xscale)];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->inputImg[y / yscale][3 * (x / xscale) + 2];
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnGeometryZoominInterpolation()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;

	float xscale = 2.3;
	float yscale = 1.5;

	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	// 메모리 반환
	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->imageHeight * yscale + 0.5;

	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->gImageHeight; i++)
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);

	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			// 원시 영상의 픽셀 좌표
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int) src_x;
			beta = src_y - (int) src_y;

			// 보간에 사용될 픽셀 좌표
			Ax = (int) src_x;
			Ay = (int) src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->imageWidth - 1) Bx = pDoc->imageWidth - 1;
			if (Cy > pDoc->imageHeight - 1) Cy = pDoc->imageHeight - 1;
			if (Dx > pDoc->imageWidth - 1) Dx = pDoc->imageWidth - 1;
			if (Dy > pDoc->imageHeight - 1) Dy = pDoc->imageHeight - 1;

			if (pDoc->depth == 1)
			{
				// x 방향으로 보간
				E = (1 - alpha) * pDoc->inputImg[Ay][Ax] + alpha * pDoc->inputImg[By][Bx];
				F = (1 - alpha) * pDoc->inputImg[Cy][Cx] + alpha * pDoc->inputImg[Dy][Dx];

				// y 방향으로 보간
				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax] + alpha * pDoc->inputImg[By][3 * Bx];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx] + alpha * pDoc->inputImg[Dy][3 * Dx];
				pDoc->gResultImg[y][3 * x] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 1] + alpha * pDoc->inputImg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 1] + alpha * pDoc->inputImg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->inputImg[Ay][3 * Ax + 2] + alpha * pDoc->inputImg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->inputImg[Cy][3 * Cx + 2] + alpha * pDoc->inputImg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnGeometryZoomoutSubsampling()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;

	int xscale = 3; // 3분의 1
	int yscale = 2; // 2분의 1

	// 메모리 반환
	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth / xscale;
	pDoc->gImageHeight = pDoc->imageHeight / yscale;

	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->gImageHeight; i++)
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);

	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->inputImg[y * yscale][x * xscale];
			else
			{
				pDoc->gResultImg[y][3 * x] = pDoc->inputImg[y * yscale][3 * (x * xscale)];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->inputImg[y * yscale][3 * (x * xscale) + 2];
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmooding();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}


void CImagePro20210816View::OnGeometryZoomoutAvgFilter()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y, i, j;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	int xscale = 3; // 3분의 1
	int yscale = 2; // 2분의 1

	// 메모리 반환
	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageWidth / xscale + 1;
	pDoc->gImageHeight = pDoc->imageHeight / yscale + 1;

	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++)
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);

	// 전방향 사상
	for (y = 0; y < pDoc->imageHeight; y += yscale)
		for (x = 0; x < pDoc->imageWidth; x += xscale)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->inputImg[src_y][src_x];
					}
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else
			{
				rsum = 0; gsum = 0; bsum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->inputImg[src_y][3 * src_x];
						gsum += pDoc->inputImg[src_y][3 * src_x + 1];
						bsum += pDoc->inputImg[src_y][3 * src_x + 2];
					}
				pDoc->gResultImg[y / yscale][3 * (x / xscale)] = rsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		}

	Invalidate();
}


#define PI 3.1416926521
#include "CAngleDialog.h"
void CImagePro20210816View::OnGeometryRotate()
{
	CImagePro20210816Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int x, y, i;

	int angle = -45; // degree
	float radian;
	int Hy;
	int Cx, Cy;
	int xdiff, ydiff;
	int src_x, src_y;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL) return;
	angle = dlg.m_iAngle;

	radian = PI / 180 * angle;

	// 마지막 좌표의 y
	Hy = pDoc->imageHeight - 1;

	// 중심점
	Cx = pDoc->imageWidth / 2;
	Cy = pDoc->imageHeight / 2;

	// 메모리 반환
	if (pDoc->gResultImg != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->imageHeight * fabs(cos(PI / 2 - radian)) + pDoc->imageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->imageHeight * fabs(cos(radian)) + pDoc->gImageWidth * fabs(cos(PI / 2 - radian));

	// 메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->gImageHeight; i++)
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);

	xdiff = (pDoc->gImageWidth - pDoc->imageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->imageHeight) / 2;

	for (y = -ydiff; y < pDoc->gImageHeight - ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			if (pDoc->depth == 1)
			{
				src_x = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
				src_y = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

				if (src_x < 0 || src_x > pDoc->imageWidth - 1 || src_y < 0 || src_y > pDoc->imageHeight - 1)
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->inputImg[src_y][src_x];
			}
			else
			{
				src_x = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
				src_y = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

				if (src_x < 0 || src_x > pDoc->imageWidth - 1 || src_y < 0 || src_y > pDoc->imageHeight - 1)
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff)] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff)] = pDoc->inputImg[src_y][3 * src_x];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->inputImg[src_y][3 * src_x + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->inputImg[src_y][3 * src_x + 2];
				}
			}
		}
}


void CImagePro20210816View::OnGeometryMirror()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->resultImg[y][x] = pDoc->inputImg[y][pDoc->imageWidth - 1 - x];
			else
			{
				pDoc->resultImg[y][3 * x] = pDoc->inputImg[y][3 * (pDoc->imageWidth - 1 - x)];
				pDoc->resultImg[y][3 * x + 1] = pDoc->inputImg[y][3 * (pDoc->imageWidth - 1 - x) + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->inputImg[y][3 * (pDoc->imageWidth - 1 - x) + 2];
			}
		}

	Invalidate();
}


void CImagePro20210816View::OnGeometryFlip()
{
	CImagePro20210816Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->imageHeight; y++)
		for (x = 0; x < pDoc->imageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->resultImg[pDoc->imageHeight  -1 - y][x] = pDoc->inputImg[y][x];
			else
			{
				pDoc->resultImg[pDoc->imageHeight - 1 - y][3 * x] = pDoc->inputImg[y][3 * x];
				pDoc->resultImg[pDoc->imageHeight - 1 - y][3 * x + 1] = pDoc->inputImg[y][3 * x + 1];
				pDoc->resultImg[pDoc->imageHeight - 1 - y][3 * x + 2] = pDoc->inputImg[y][3 * x + 2];
			}
		}

	Invalidate();
}
