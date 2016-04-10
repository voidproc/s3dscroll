#pragma once

class ScrollBar
{
public:
    // size      : スクロールされる対象のサイズ
    // view_size : 描画領域のサイズ
    // rect      : スクロールバーを描画する領域
    ScrollBar(const int size, const int view_size, const Rect& rect);

    // 現在のスクロール位置を設定
    void scroll(const int scroll);

    // マウスが押された座標によりスクロール位置を設定（利用する場合は毎フレーム呼ぶ．）
    virtual void scrollIfMouseDown();

    // 現在のスクロール位置を取得
    const int value() const { return scroll_; }

    // 描画
    virtual void draw(const Color& c) const = 0;

private:
    virtual void scrollByMousePosImpl() = 0;

    int scroll_;
    int scroll_max_;
    bool dragging_;

protected:
    int size_;
    int view_size_;
    Rect rect_;
};

class VScrollBar : public ScrollBar
{
public:
    VScrollBar(const int size, const int view_size, const Rect& rect);

    virtual void draw(const Color& c) const;

private:
    virtual void scrollByMousePosImpl() override;
};

class HScrollBar : public ScrollBar
{
public:
    HScrollBar(const int size, const int view_size, const Rect& rect);

    virtual void draw(const Color& c) const;

private:
    virtual void scrollByMousePosImpl() override;
};
