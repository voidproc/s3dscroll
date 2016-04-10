#include "scrollbar.h"

void Main()
{
    Window::Resize(Size(640, 480));

    TextureAsset::Register(L"earth", L"Assets/Earth.jpg");

    const int bar_width = 16;

    const Rect vbar_rect(640 - bar_width, 0, bar_width, 480 - bar_width);
    VScrollBar vscrollbar(TextureAsset(L"earth").height, 480, vbar_rect);

    const Rect hbar_rect(0, 480 - bar_width, 640 - bar_width, bar_width);
    HScrollBar hscrollbar(TextureAsset(L"earth").width, 640, hbar_rect);

	while (System::Update())
	{
        Rect(0, 0, 640, 480)(TextureAsset(L"earth")(hscrollbar.value(), vscrollbar.value(), 640, 480)).draw();

        vscrollbar.scrollIfMouseDown();
        hscrollbar.scrollIfMouseDown();

        const int a_max = 200;
        vscrollbar.draw(Clamp(a_max - (640 - bar_width - Mouse::Pos().x), 0, a_max));
        hscrollbar.draw(Clamp(a_max - (480 - bar_width - Mouse::Pos().y), 0, a_max));
    }
}
