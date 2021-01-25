#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "../renderer/generic/drawable_factory.h"

namespace etk {
class Widget {
public:
	Widget() : mScroller{ std::make_unique<NoScroller>() } { };
	Widget(const Widget&) = delete;
	Widget& operator=(const Widget&) = delete;
	virtual ~Widget() {}

	bool IsInitialized() const {
		return mInitialized;
	}

	virtual void Init() {
		mInitialized = true;
	}

	const glm::vec2& GetEye() {
		return mEye;
	}

	class Scroller {
	public:
		void SetOwner(Widget *w) {
			mOwner = w;
		}
		virtual float ScrollX(float x) {
			return 0;
		}
		virtual float ScrollY(float y) {
			return  0;
		}
		virtual bool ScrollXEnabled(void) {
			return false;
		}
		virtual bool ScrollYEnabled(void) {
			return false;
		}
	protected:
		Widget* GetOwner() const {
			return mOwner;
		}

	private:
		Widget* mOwner;
	};

	class HorizontalScroller : public Scroller {
	public:
		float ScrollX(float x) override {
			GetOwner()->AdjustEye(glm::vec2(x * 40.0f, 0));
			return 0.0f;
		}
		bool ScrollXEnabled(void) override {
			return true;
		}
	private:
	};

	class VerticalScroller : public Scroller {
	public:
		float ScrollY(float y) override {
			GetOwner()->AdjustEye(glm::vec2(0, y * 40.0f));
			return 0.0f;
		}
		bool ScrollYEnabled(void) override {
			return true;
		}
	};

	class NoScroller : public Scroller {
	};

	class Border {
	public:
		float GetWidth() const {
			return 0;
		}
	private:
	};

	virtual void Draw(const glm::vec2& eye) {}

	virtual void SetPosition(const glm::vec2 pos)
	{
		mPos = pos;
	}

	const glm::vec2& GetPosition(void) const
	{
		return mPos;
	}

	void SetMargin(const glm::vec4 margin) 
	{
		mMargin = margin;
	}

	const glm::vec4& GetMargin() const
	{
		return mMargin;
	}

	void SetPadding(const glm::vec4 padding)
	{
		mPadding = padding;
	}

	const glm::vec4& GetPadding() const 
	{
		return mPadding;
	}

	virtual void Invalidate() {};


	/// <summary>
	/// Internal Width + border + margin + padding
	/// </summary>
	/// <returns></returns>
	float GetExternalWidth() const {
		float width = mPadding[3] + mPadding[1] + mMargin[1] + mMargin[3] + mInternalWidth;
		// branchless version: does not use mBorder->GetWidth() if mBorder is nullptr
		mBorder && (width += mBorder->GetWidth());
		return width;
	}

	/// <summary>
	/// Internal Height + border + margin + padding
	/// </summary>
	/// <returns></returns>
	float GetExternalHeight() const {
		float height = mPadding[0] + mPadding[2] + mMargin[0] + mMargin[2] + mInternalHeight;
		// branchless version: does not use mBorder->GetWidth() if mBorder is nullptr
		mBorder && (height += mBorder->GetWidth());
		return height;
	}

	virtual void SetDrawableFactory(std::weak_ptr<etk::renderer::DrawableFactory> factory) {
		mDrawableFactory = factory;
	}

	virtual bool HitInsideBox(const glm::vec2 point) {
		return GetPosition().x - GetMargin()[3] < point.x && point.x < GetPosition().x + GetInternalWidth() + GetMargin()[1] && GetPosition().y - GetMargin()[0] < point.y && point.y < GetPosition().y + GetInternalHeight() + GetMargin()[2];
	}

	virtual bool OnScroll(const glm::vec2 point, const float x, const float y) {
		if (HitInsideBox(point)) {
			if (x != 0 && mScroller->ScrollXEnabled()) {
				mScroller->ScrollX(x);
				return true;
			}
			if (y != 0 && mScroller->ScrollYEnabled()) {
				mScroller->ScrollY(y);
				return true;
			}
			return false;
		}
		return false;
	}

	void SetScroller(std::unique_ptr<Scroller> s) {
		s->SetOwner(this);
		mScroller = std::move(s);
	}
protected:
	/// <summary>
	/// The internal width of the object
	/// </summary>
	/// <param name="width"></param>
	void SetInternalWidth(float width) {
		mInternalWidth = width;
	}

	/// <summary>
	/// the internal height of the object
	/// </summary>
	/// <param name="height"></param>
	void SetInternalHeight(float height) {
		mInternalHeight = height;
	}

	const float GetInternalHeight() const {
		return mInternalHeight;
	}

	const float GetInternalWidth() const {
		return mInternalWidth;
	}

	std::weak_ptr<etk::renderer::DrawableFactory> GetDrawableFactory() {
		return mDrawableFactory;
	}



protected:
	void SetEye(glm::vec2 eye) {
		mEye = eye;
	}

	void AdjustEye(glm::vec2 eye) {
		mEye += eye;
	}

private:
	float mInternalWidth{ 0.0f };
	float mInternalHeight{ 0.0f };
	/// <summary>
	/// position of the box
	/// </summary>
	glm::vec2 mPos{ 0.0f, 0.0f };

	/// <summary>
	/// margin in the box
	/// </summary>
	glm::vec4 mMargin{ 0.0f, 0.0f, 0.0f, 0.0f };

	/// <summary>
	/// Padding around the box 
	/// </summary>
	glm::vec4 mPadding{ 0.0f, 0.0f, 0.0f, 0.0f };

	/// <summary>
	/// border
	/// </summary>
	std::unique_ptr<Border> mBorder{ nullptr };

	std::weak_ptr<etk::renderer::DrawableFactory> mDrawableFactory;
	

	bool mInitialized{ false };

	std::unique_ptr<Scroller> mScroller;

	glm::vec2 mEye{ 0.0f, 0.0f };
};
}