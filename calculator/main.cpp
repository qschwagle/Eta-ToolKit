#include <etk/application.h>
#include <etk/window.h>
#include <etk/widgets/scene.h>
#include <etk/widgets/linear_container.h>
#include <etk/widgets/label.h>
#include <etk/widgets/button.h>

int main(int argc, char** argv)
{
	etk::Application app;
	auto window = app.CreateAppWindow("Calculator").lock();
	window->SetColor(etk::colors::WHITE);
	auto scene = std::make_shared<etk::Scene>(L"MAIN_SCENE");
	window->SetScene(scene);
	auto mainLayout = std::make_shared<etk::LinearContainer>();
	auto textView = std::make_shared<etk::Label>();
	textView->SetText(L"Hello World");
	textView->SetFontSize(etk::PointUnit(24));
	auto row1 = std::make_shared<etk::LinearContainer>();
	row1->SetDirection(etk::LinearContainer::Direction::HORIZONTAL);
	auto row2 = std::make_shared<etk::LinearContainer>();
	row2->SetDirection(etk::LinearContainer::Direction::HORIZONTAL);
	auto row3 = std::make_shared<etk::LinearContainer>();
	row3->SetDirection(etk::LinearContainer::Direction::HORIZONTAL);
	auto row4 = std::make_shared<etk::LinearContainer>();
	row4->SetDirection(etk::LinearContainer::Direction::HORIZONTAL);
	auto row5 = std::make_shared<etk::LinearContainer>();
	row5->SetDirection(etk::LinearContainer::Direction::HORIZONTAL);

	scene->SetWidget(L"MAIN_LAYOUT", L"MAIN_SCENE", std::dynamic_pointer_cast<etk::MultiContainer>(mainLayout));
	scene->SetWidget(L"TEXT_VIEW", L"MAIN_LAYOUT", textView);
	scene->SetWidget(L"ROW_1", L"MAIN_LAYOUT", std::dynamic_pointer_cast<etk::MultiContainer>(row1));
	scene->SetWidget(L"ROW_2", L"MAIN_LAYOUT", std::dynamic_pointer_cast<etk::MultiContainer>(row2));
	scene->SetWidget(L"ROW_3", L"MAIN_LAYOUT", std::dynamic_pointer_cast<etk::MultiContainer>(row3));
	scene->SetWidget(L"ROW_4", L"MAIN_LAYOUT", std::dynamic_pointer_cast<etk::MultiContainer>(row4));
	scene->SetWidget(L"ROW_5", L"MAIN_LAYOUT", std::dynamic_pointer_cast<etk::MultiContainer>(row5));


	auto buttonAC = std::make_shared<etk::Button>();
	buttonAC->SetText(L"AC");
	buttonAC->SetFontSize(etk::PointUnit(24));
	buttonAC->SetBackgroundColor(etk::colors::BLUE);
	scene->SetWidget(L"AC", L"ROW_1", buttonAC);
	auto buttonPM = std::make_shared<etk::Button>();
	buttonPM->SetText(L"+/-");
	buttonPM->SetFontSize(etk::PointUnit(24));
	buttonPM->SetBackgroundColor(etk::colors::BLUE);
	scene->SetWidget(L"PM", L"ROW_1", buttonPM);
	auto buttonMod = std::make_shared<etk::Button>();
	buttonMod->SetText(L"%");
	buttonMod->SetFontSize(etk::PointUnit(24));
	buttonMod->SetBackgroundColor(etk::colors::BLUE);
	scene->SetWidget(L"MOD", L"ROW_1", buttonMod);
	auto buttonDiv = std::make_shared<etk::Button>();
	buttonDiv->SetText(L"/");
	buttonDiv->SetFontSize(etk::PointUnit(24));
	buttonDiv->SetBackgroundColor(etk::colors::BLUE);
	scene->SetWidget(L"DIV", L"ROW_1", buttonDiv);

	auto button7 = std::make_shared<etk::Button>();
	button7->SetText(L"7");
	button7->SetFontSize(etk::PointUnit(24));
	button7->SetBackgroundColor(etk::colors::BLUE);
	scene->SetWidget(L"7", L"ROW_2", button7);
	auto button8 = std::make_shared<etk::Button>();
	button8->SetText(L"8");
	button8->SetFontSize(etk::PointUnit(24));
	button8->SetBackgroundColor(etk::colors::BLUE);
	scene->SetWidget(L"8", L"ROW_2", button8);
	auto button9 = std::make_shared<etk::Button>();
	button9->SetText(L"9");
	button9->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"9", L"ROW_2", button9);
	auto buttonMul = std::make_shared<etk::Button>();
	buttonMul->SetText(L"x");
	buttonMul->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"MUL", L"ROW_2", buttonMul);

	auto button4 = std::make_shared<etk::Button>();
	button4->SetText(L"4");
	button4->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"4", L"ROW_3", button4);
	auto button5 = std::make_shared<etk::Button>();
	button5->SetText(L"5");
	button5->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"5", L"ROW_3", button5);
	auto button6 = std::make_shared<etk::Button>();
	button6->SetText(L"6");
	button6->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"6", L"ROW_3", button6);
	auto buttonMin = std::make_shared<etk::Button>();
	buttonMin->SetText(L"-");
	buttonMin->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"MINUS", L"ROW_3", buttonMin);

	auto button1 = std::make_shared<etk::Button>();
	button1->SetText(L"1");
	button1->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"1", L"ROW_4", button1);
	auto button2 = std::make_shared<etk::Button>();
	button2->SetText(L"2");
	button2->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"2", L"ROW_4", button2);
	auto button3 = std::make_shared<etk::Button>();
	button3->SetText(L"3");
	button3->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"3", L"ROW_4", button3);
	auto buttonPlus = std::make_shared<etk::Button>();
	buttonPlus->SetText(L"+");
	buttonPlus->SetFontSize(etk::PointUnit(24));
	scene->SetWidget(L"PLUS", L"ROW_4", buttonPlus);
	app.Init(argc, argv);

	int ret = app.Run();
	return ret;
}