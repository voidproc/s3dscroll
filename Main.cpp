#include "scrollbar.h"


void Main()
{
    Window::SetStyle(WindowStyle::Sizeable);
    Window::Resize(Size(640, 480));

    TextureAsset::Register(L"earth", L"Assets/Earth.jpg");

    // スクロールバー作成
    Size wnd_size, wnd_size_prev;
    const int bar_width = 16;

    VScrollBar vscrollbar;
    HScrollBar hscrollbar;

	while (System::Update())
	{
        wnd_size = Window::Size();
        if (wnd_size != wnd_size_prev) {
            const Rect vbar_rect(wnd_size.x - bar_width, 0, bar_width, wnd_size.y - bar_width);
            const Rect hbar_rect(0, wnd_size.y - bar_width, wnd_size.x - bar_width, bar_width);
            vscrollbar = VScrollBar(TextureAsset(L"earth").height, wnd_size.y, vbar_rect);
            hscrollbar = HScrollBar(TextureAsset(L"earth").width, wnd_size.x, hbar_rect);
        }

        Rect(0, 0, wnd_size.x, wnd_size.y)(TextureAsset(L"earth")(hscrollbar.value(), vscrollbar.value(), wnd_size.x, wnd_size.y)).draw();

        vscrollbar.scrollIfMouseDown();
        hscrollbar.scrollIfMouseDown();

        const int a_max = 200;
        vscrollbar.draw(Color(96, 168, 255, Clamp(a_max - (wnd_size.x - bar_width - Mouse::Pos().x), 0, a_max)));
        hscrollbar.draw(Color(96, 168, 255, Clamp(a_max - (wnd_size.y - bar_width - Mouse::Pos().y), 0, a_max)));

        wnd_size_prev = wnd_size;
    }
}
