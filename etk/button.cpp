#include "button.h"

#include "color.h"

void etk::Button::Draw()
{
	SetPosition(glm::vec2(0, 0));
	SetPadding(glm::vec4(100,100,100,100));
	SetMargin(glm::vec4(0, 0, 0, 0));
	SetInternalHeight(100);
	SetInternalWidth(100);
	auto factory = GetDrawableFactory().lock();
	auto background = factory->CreateFilledRectangle();
	glm::vec4 padding = GetPadding();
	background->SetPos(padding[3] + GetPosition()[0], padding[0] + GetPosition()[1]);
	background->SetHeight(GetMargin()[0] + GetMargin()[2] + GetInternalHeight());
	background->SetWidth(GetMargin()[1] + GetMargin()[3] + GetInternalWidth());
	background->SetColor(etk::colors::ORANGE);
	background->Draw();
	auto text = factory->CreateText();
}
