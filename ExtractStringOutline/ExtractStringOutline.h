#pragma once

#include <cliext/vector>
#include "ManagedObject.h"

using namespace System;

namespace ExtractStringOutline {
	public value class xPoint {
	public:
		double x, y;
		xPoint(double x, double y) : x(x), y(y) {};
	};

	public ref class xLine {
	public:
		xPoint p0, p1;
		xLine(xPoint p0, xPoint p1) : p0(p0), p1(p1) {}
	};

	public ref class xExtractStringOutline {
	public:

		//static cliext::vector<xLine^>^ ExtractStringOutline(String^ str);
		bool ExtractStringOutline(bool b);
		// Make DC and print some text

	};
}
