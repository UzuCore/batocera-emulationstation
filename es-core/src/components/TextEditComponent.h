#pragma once
#ifndef ES_CORE_COMPONENTS_TEXT_EDIT_COMPONENT_H
#define ES_CORE_COMPONENTS_TEXT_EDIT_COMPONENT_H

#include "components/NinePatchComponent.h"
#include "GuiComponent.h"
#include <algorithm>

class Font;
class TextCache;

// Used to enter text.
class TextEditComponent : public GuiComponent
{
public:
	TextEditComponent(Window* window);
	
	void textInput(const char* text) override;
	bool input(InputConfig* config, Input input) override;
	void update(int deltaTime) override;
	void render(const Transform4x4f& parentTrans) override;

	void onFocusGained() override;
	void onFocusLost() override;

	void onSizeChanged() override;

	void setValue(const std::string& val) override;
	std::string getValue() const override;

	inline bool isEditing() const { return mEditing; };
	inline const std::shared_ptr<Font>& getFont() const { return mFont; }

	void setCursor(size_t pos);

	virtual std::vector<HelpPrompt> getHelpPrompts() override;

	void startEditing(); 
	void stopEditing(); 

private:
	bool hasAnyKeyPressed();

	void onTextChanged();
	void onCursorChanged();

	void updateCursorRepeat(int deltaTime);
	void moveCursor(int amt);

	bool isMultiline();
	Vector2f getTextAreaPos() const;
	Vector2f getTextAreaSize() const;

	std::string mText;
	bool mFocused;
	bool mEditing;
	unsigned int mCursor; // cursor position in characters

	int mCursorRepeatTimer;
	int mCursorRepeatDir;

	Vector2f mScrollOffset;

	NinePatchComponent mBox;

	std::shared_ptr<Font> mFont;
	std::unique_ptr<TextCache> mTextCache;

	int mBlinkTime;
	bool mDeferTextInputStart;

	// for korean text input
	const std::vector<const char*> KOREAN_CHOSUNG_LIST = { "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ" };
	const std::vector<const char*> KOREAN_JOONGSUNG_LIST = { "ㅏ", "ㅐ", "ㅑ", "ㅒ", "ㅓ", "ㅔ", "ㅕ", "ㅖ", "ㅗ", "ㅘ", "ㅙ", "ㅚ", "ㅛ", "ㅜ", "ㅝ", "ㅞ", "ㅟ", "ㅠ", "ㅡ", "ㅢ", "ㅣ" };
	const std::vector<const char*> KOREAN_JONGSUNG_LIST = { " ", "ㄱ", "ㄲ", "ㄳ", "ㄴ", "ㄵ", "ㄶ", "ㄷ", "ㄹ", "ㄺ", "ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅁ", "ㅂ", "ㅄ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ" };
	const std::vector<const char*> KOREAN_GYEOP_BATCHIM_LIST = { "ㄳ", "ㄵ", "ㄶ", "ㄺ", "ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅄ" };
	const std::vector<const char*> KOREAN_GYEOP_BATCHIM_COMBINATIONS = { "ㄱㅅ", "ㄴㅈ", "ㄴㅎ", "ㄹㄱ", "ㄹㅁ", "ㄹㅂ", "ㄹㅅ", "ㄹㅌ", "ㄹㅍ", "ㄹㅎ", "ㅂㅅ" };
	const std::vector<const char*> KOREAN_IJUNG_MOEUM_LIST = { "ㅘ", "ㅙ", "ㅚ", "ㅝ", "ㅞ", "ㅟ", "ㅢ" };
	const std::vector<const char*> KOREAN_IJUNG_MOEUM_COMBINATIONS = { "ㅗㅏ", "ㅗㅐ", "ㅗㅣ", "ㅜㅓ", "ㅜㅔ", "ㅜㅣ", "ㅡㅣ" };

	template <typename T> inline int findIndexInVector(const std::vector<T>& vec, const T& key) {
		auto it = std::find_if(vec.begin(), vec.end(), [&](const T& item) { 
			return std::strcmp(item, key) == 0; 
		});

		if (it != vec.end())
			return std::distance(vec.begin(), it);

		return -1;
	}

	void koreanTextInput(const char* text);
};

#endif // ES_CORE_COMPONENTS_TEXT_EDIT_COMPONENT_H
