//=================================================================================================================================
// 2023-02-21. PWH
//
// Outline() : 높이 1인 글자의 외곽선을 뽑아내는 함수
//

#pragma once

#include <vector>
#include <deque>

#include <Windows.h>

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
using xLine = std::vector<xPoint>;	// 여러 점으로 구성된 하나의 연결된 라인
using xLines = std::deque<xLine>;	// 여러 라인으로 구성된 글자들

/// @brief 높이 1인 글자의 외곽선을 뽑아내는 함수. 문자열을 획으로 변환. (획은 여러개의 선분으로 구성됨)
/// @param text : 문자열
/// @param lf : Font
/// @param bOutline : 외곽선 출력
/// @param bHorzHatching : 수평 Hatching 출력
/// @param nHorzHatchingStep : Hatching Step 라인의 Y 방향 간격
/// @return : 선분
xLines Outline(CString const& text, LOGFONT const& lf, bool bOutline, bool bHorzHatching, int nHorzHatchingStep);
