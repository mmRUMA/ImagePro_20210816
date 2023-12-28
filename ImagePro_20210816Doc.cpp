
// ImagePro_20210816Doc.cpp: CImagePro20210816Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_20210816.h"
#endif

#include "ImagePro_20210816Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImagePro20210816Doc

IMPLEMENT_DYNCREATE(CImagePro20210816Doc, CDocument)

BEGIN_MESSAGE_MAP(CImagePro20210816Doc, CDocument)
END_MESSAGE_MAP()


// CImagePro20210816Doc 생성/소멸

CImagePro20210816Doc::CImagePro20210816Doc() noexcept
{
	inputImg = NULL;
	inputImg2 = NULL;
	resultImg = NULL;
	gResultImg = NULL;
}

CImagePro20210816Doc::~CImagePro20210816Doc()
{
	if (inputImg != NULL)
	{
		for (int i = 0; i < imageHeight; i++)
		{
			free(inputImg[i]);
			free(resultImg[i]);
		}
		free(inputImg);
		free(resultImg);
	}

	if (inputImg2 != NULL)
	{
		for (int i = 0; i < imageHeight; i++)
			free(inputImg2[i]);
		free(inputImg2);
	}

	if (gResultImg != NULL) {
		for (int i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}
}

BOOL CImagePro20210816Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImagePro20210816Doc serialization

void CImagePro20210816Doc::Serialize(CArchive& ar)
{
	if (!ar.IsStoring()) LoadImageFile(ar);
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImagePro20210816Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImagePro20210816Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImagePro20210816Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImagePro20210816Doc 진단

#ifdef _DEBUG
void CImagePro20210816Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImagePro20210816Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImagePro20210816Doc 명령


void CImagePro20210816Doc::LoadImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isBMP = false;

	// 헤더 읽기
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);

		do ar.ReadString(buf, 255);
		while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imageWidth, &imageHeight);

		do ar.ReadString(buf, 255);
		while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		
		imageWidth = 256;
		imageHeight = 256;
		depth = 1;
	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0)
	{
		// bitmap file header 읽기
		BITMAPFILEHEADER bfh;
		ar.Read((LPSTR)&bfh, sizeof(bfh));
		if (bfh.bfType != (WORD)('B' | ('M' << 8))) return;

		// bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imageWidth = bih.biWidth;
		imageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;
		
		if (depth == 1) // palette 존재
		{
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isBMP = true;
	}

	// 메모리 할당
	inputImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));
	resultImg = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (int i = 0; i < imageHeight; i++)
	{
		inputImg[i] = (unsigned char*)malloc(imageWidth * depth);
		resultImg[i] = (unsigned char*)malloc(imageWidth * depth);
	}

	// 영상 데이터 읽기
	if (!isBMP)
		for (int i = 0; i < imageHeight; i++)
			ar.Read(inputImg[i], imageWidth * depth);
	else
	{
		// 파일 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (imageWidth * 8 + 31) / 32 * 4;

		for (int j = 0; j < imageHeight; j++)
		{
			if (depth == 1)
				ar.Read(inputImg[imageHeight - 1 - j], imageWidth * depth);
			else
			{
				for (int i = 0; i < imageWidth; i++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1); 	ar.Read(&g, 1); 	ar.Read(&r, 1);

					inputImg[imageHeight - 1 - j][3 * i] = r;
					inputImg[imageHeight - 1 - j][3 * i + 1] = g;
					inputImg[imageHeight - 1 - j][3 * i + 2] = b;
				}
			}

			if ((widthfile - imageWidth) != 0)
				ar.Read(nu, (widthfile - imageWidth * depth));
		}
	}
}


void CImagePro20210816Doc::LoadSecondImageFile(CArchive& ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isBMP = false;

	int imgw, imgh, imgd;

	// 메모리 반환
	if (inputImg2 != NULL)
	{
		for (int i = 0; i < imageHeight; i++)
			free(inputImg2[i]);
		free(inputImg2);
	}

	// 헤더 읽기
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);

		do ar.ReadString(buf, 255);
		while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imgw, &imgh);

		do ar.ReadString(buf, 255);
		while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) imgd = 1;
		else imgd = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}

		imgw = 256;
		imgh = 256;
		imgd = 1;
	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0)
	{
		// bitmap file header 읽기
		BITMAPFILEHEADER bfh;
		ar.Read((LPSTR)&bfh, sizeof(bfh));
		if (bfh.bfType != (WORD)('B' | ('M' << 8))) return;

		// bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imgw = bih.biWidth;
		imgh = bih.biHeight;
		imgd = bih.biBitCount / 8;

		if (imgd == 1) // palette 존재
		{
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isBMP = true;
	}

	if (imgw != imageWidth || imgh != imageHeight || imgd != depth)
	{
		AfxMessageBox("동일한 크기의 파일만 사용가능합니다.");
		return;
	}

	// 메모리 할당
	inputImg2 = (unsigned char**)malloc(imageHeight * sizeof(unsigned char*));

	for (int i = 0; i < imageHeight; i++)
		inputImg2[i] = (unsigned char*)malloc(imageWidth * depth);

	// 영상 데이터 읽기
	if (!isBMP)
		for (int i = 0; i < imageHeight; i++)
			ar.Read(inputImg2[i], imageWidth * depth);
	else
	{
		// 파일 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (imageWidth * 8 + 31) / 32 * 4;

		for (int j = 0; j < imageHeight; j++)
		{
			if (depth == 1)
				ar.Read(inputImg2[imageHeight - 1 - j], imageWidth * depth);
			else
			{
				for (int i = 0; i < imageWidth; i++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1); 	ar.Read(&g, 1); 	ar.Read(&r, 1);

					inputImg2[imageHeight - 1 - j][3 * i] = r;
					inputImg2[imageHeight - 1 - j][3 * i + 1] = g;
					inputImg2[imageHeight - 1 - j][3 * i + 2] = b;
				}
			}

			if ((widthfile - imageWidth) != 0)
				ar.Read(nu, (widthfile - imageWidth * depth));
		}
	}
}
