#include "pch.h"
#include "Outline.h"

#include "opencv2/opencv.hpp"

xLines Outline(CString const& text, LOGFONT const& lf, bool bOutline, bool bHorzHatching, int nHorzHatchingStep) {
	xLines lines;

	// First, Calc Rectangle (필요한 Canvas 크기 구하기)
	CRect rect;
	{
		CDC dc;
		dc.CreateCompatibleDC(nullptr);
		CFont font;
		font.CreateFontIndirect(&lf);
		dc.SelectObject(&font);
		dc.DrawText(text, &rect, DT_CALCRECT | DT_SINGLELINE | DT_TOP | DT_LEFT);
	}
	if (rect.IsRectEmpty())	// if failed
		return lines;

	// Text 를 rendering할 Canvas 만들기
	CImage canvas;
	rect.right = ((rect.right + 3) / 4 * 4);	// 32 bit align
	canvas.Create(rect.Width(), rect.Height(), 24);
	// Draw Text (antialiased... )
	{
		CDC dc;
		HDC hDC = canvas.GetDC();
		dc.Attach(hDC);
		dc.SelectStockObject(NULL_PEN);
		dc.SelectStockObject(WHITE_BRUSH);
		dc.Rectangle(rect);
		CFont font;
		font.CreateFontIndirect(&lf);
		//LOGFONT logfont{};
		//logfont.lfQuality = NONANTIALIASED_QUALITY;	// 안티얼라이어징 끄려면 이거 쓰면 됨
		dc.SelectObject(&font);
		dc.SetTextColor(RGB(0, 0, 0));
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(text, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT);
		dc.Detach();
		canvas.ReleaseDC();
	}
#ifdef _DEBUG
	canvas.Save(L"text.png");
#endif

	// canvas to cv::Mat
	cv::Mat mat(rect.Height() - 1, rect.Width() - 1, CV_8UC3);
	auto pitch = canvas.GetPitch();
	auto* src = (uchar*)canvas.GetBits();
	for (int y = 0; y < mat.rows; ++y, src += pitch) {
		auto* dst = mat.ptr(y);
		memcpy(dst, src, mat.step);
	}
	// BGR to Gray
	cv::cvtColor(mat, mat, cv::COLOR_RGB2GRAY);

	// 가로 Hatching Line
	if (bHorzHatching) {
		if (nHorzHatchingStep < 1)
			nHorzHatchingStep = 1;
		uchar threshold = 127;
		for (int y{}; y < mat.rows; y += nHorzHatchingStep) {
			auto* ptr = mat.ptr<uchar>(y);

			for (int x{}; x < mat.cols; x++) {
				if (ptr[x] > threshold)
					continue;
				xPoint pt0{x, y};
				bool bAdded{};
				for (x++; x < mat.cols; x++) {
					if (ptr[x] > threshold)
						break;
				}
				xPoint pt1{x-1, y};
				lines.push_back({ pt0, pt1 });
			}
		}
	}

	// Outline 뽑아내기
	if (bOutline) {
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(mat, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

	#ifdef _DEBUG
		// 그려보기.
		cv::Mat img(mat.size(), CV_8UC1);
		for (int idx{}; idx < contours.size(); idx++) {
			cv::drawContours(img, contours, idx, cv::Scalar(0));
		}
	#endif

		// to line, and calc boundary
		//lines.reserve(contours.size());
		for (auto const& contour : contours) {
			lines.push_back({});
			auto& line = lines.back();
			line.reserve(contour.size());
			for (auto const& pt2i : contour) {
				xPoint pt{ pt2i.x, pt2i.y };
				line.push_back(pt);
			}
		}
	}

	// 크기 계산 -> 높이 1로 Normalize. (Y뒤집기 포함)
	if (mat.rows > 1) {
		auto scale = 1./mat.rows;
		for (auto& line : lines) {
			for (auto& pt : line) {
				pt *= scale;
				// Flip Y. 실세계 좌표계에서는 윗쪽으로 + 이므로 Y 좌표를 뒤집어 줌
				pt.y = 1 - pt.y;
			}
		}
	}

	return lines;
}
