#pragma once

#include <cliext/vector>

using namespace System;

namespace ExtractStringOutline {
	public ref class xPoint {
	public:
		double x{}, y{};
		xPoint() {};
	};

	public ref class xLine {
	public:
		xPoint p0, p1;
		xLine() {}
	};

	public ref class xExtractStringOutline
	{
	public:
		static cliext::vector<xLine> ExtractStringOutline(String^ str);
		// Make DC and print some text

	};
}
