#pragma once

#include <string>
#include <etk/widgets/widget.h>

#include <etk/renderer/generic/text.h>

namespace etk {
/// <summary>
/// A Text Input Field 
/// </summary>
class TextField : public Widget {
public:
	TextField();
	TextField(const TextField&) = delete;;
	TextField& operator=(const TextField&) = delete;
	virtual ~TextField() {}

	void Draw() override;

	/// <summary>
	/// Data bound to this field.
	/// Should contain the text field it is holding + current cursor position
	/// </summary>
	class Data {
	public:
		std::wstring GetText() const {
			return mText;
		}

		void SetText(std::wstring text) {
			mText = text;
		}
	private:
		std::wstring mText;
		int mCursorPos{ -1 };
	};

	/// <summary>
	/// Objects which are considered "cached" and can be invalidated,
	/// All drawable objects + widget position can be considered cached.
	/// Cached objects may not be outright deleted, but they are "unstable"
	/// and can be affected by outside forces
	/// </summary>
	class Cached {
	public:
	private:
		glm::vec2 mPos{ 0.0f, 0.0f };
	};
private:

	std::shared_ptr<Data> mData;

};
}