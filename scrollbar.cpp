#include "scrollbar.h"

ScrollBar::ScrollBar(const int size, const int view_size, const Rect& rect)
    : size_(size), scroll_(0), scroll_max_(size - view_size), dragging_(false), view_size_(view_size), rect_(rect)
{
}

void ScrollBar::scroll(const int scroll)
{
    scroll_ = Clamp(scroll, 0, scroll_max_);
}

void ScrollBar::scrollIfMouseDown()
{
    if (rect_.mouseOver && Input::MouseL.clicked) {
        dragging_ = true;
    }

    if (!Input::MouseL.pressed) {
        dragging_ = false;
    }

    if (dragging_) {
        scrollByMousePosImpl();
    }
}


// Vertical

VScrollBar::VScrollBar(const int size, const int view_size, const Rect& rect)
    : ScrollBar(size, view_size, rect)
{
}

void VScrollBar::scrollByMousePosImpl()
{
    scroll(Mouse::Pos().y / (double)rect_.h * size_ - view_size_ / 2.0);
}

void VScrollBar::draw(const Color& c) const
{
    // frame
    rect_.draw(Color(0, 0, 0, c.a/2));

    // position
    const int y = rect_.h * value() / size_;
    const int h = rect_.h * view_size_ / size_;
    const int pad = 2;
    Rect(rect_.x + pad, rect_.y + y + pad, rect_.w - pad * 2, h - pad * 2).draw(c);
}


// Horizontal

HScrollBar::HScrollBar(const int size, const int view_size, const Rect& rect)
    : ScrollBar(size, view_size, rect)
{
}

void HScrollBar::scrollByMousePosImpl()
{
    scroll(Mouse::Pos().x / (double)rect_.w * size_ - view_size_ / 2.0);
}

void HScrollBar::draw(const Color& c) const
{
    // frame
    rect_.draw(Color(0, 0, 0, c.a /2));

    // position
    const int x = rect_.w * value() / size_;
    const int w = rect_.w * view_size_ / size_;
    const int pad = 2;
    Rect(rect_.x + x + pad, rect_.y + pad, w - pad * 2, rect_.h - pad * 2).draw(c);
}

