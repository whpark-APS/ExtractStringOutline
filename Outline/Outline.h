#pragma once

//=================================================================================================================================
// 2023-02-21. PWH


#include <vector>

struct xPoint {
	double x, y;

	auto operator <=> (const xPoint& p) const = default;

	xPoint& operator *= (double scale) {
		x *= scale;
		y *= scale;
		return *this;
	}
	friend xPoint operator * (xPoint p, double scale) {
		return p *= scale;
	}
	friend xPoint operator * (double scale, xPoint p) {
		return p *= scale;
	}
};

using xLine = std::vector<xPoint>;
using xLines = std::deque<xLine>;

// 높이 1인 글자의 외곽선을 뽑아내는 함수
xLines Outline(CString const& text, LOGFONT const& lf, bool bOutline, bool bHorzHatching, int nHorzHatchingStep);
