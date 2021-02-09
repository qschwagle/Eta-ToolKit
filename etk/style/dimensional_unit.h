#pragma once

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
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class EMUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class CHUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
	}
};

class VHUnit : public DimensionalUnit {
public:
	float GetPixels(const float parentPixels, const float vPortWidth, const float vPortHeight, const float ftSize) const override {
		return GetValue();
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