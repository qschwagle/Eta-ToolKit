#pragma once

#include <etk/renderer/generic/screen_box.h>

namespace etk {
/// <summary>
/// A dimensional unit for screen space. 
/// 
///  Since some units are relative to either font-size, viewport, or parent element, extra data must be provided
///  when retrieving the pixels
/// </summary>
class DimensionalUnit {
public:

	DimensionalUnit() = default;
	DimensionalUnit(float val) { mValue = val; }
	virtual void SetValue(const float val) {
		mValue = val;
	}
	virtual float GetValue(void) const {
		return mValue;
	}

	/// <summary>
	/// Retrieves the pixels equivalent for the dm unit
	/// </summary>
	/// <param name="parentPixels">the parent dimension in pixels</param>
	/// <param name="vPortWidth">the view port width</param>
	/// <param name="vPortHeight">the view port height</param>
	/// <param name="ftSize">the current font size</param>
	virtual float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const {
		return GetValue();
	}
	virtual float GetPt(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const {
		return GetValue();
	}
private:
	float mValue{ 0.0f };
};

class InchUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class MillimeterUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class CentimeterUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class PixelUnit : public DimensionalUnit {
public:
	PixelUnit(float val) : DimensionalUnit(val) {}

	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class PointUnit : public DimensionalUnit {
public:

	PointUnit(float val) : DimensionalUnit(val) {}
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class EMUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
	/// <summary>
	/// EM are multiples of the base ptSize
	/// </summary>
	/// <param name="parentPixels"></param>
	/// <param name="vPortWidth"></param>
	/// <param name="vPortHeight"></param>
	/// <param name="ftSize"></param>
	/// <returns></returns>
	float GetPt(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return ftSize * GetValue();
	}
};

class CHUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};


class VWUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return 0.01 * vPortWidth;
	}
};

class VHUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return 0.01 * vPortHeight;
	}
};

class VMinUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class VMaxUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class PercentageUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};
}