#ifndef __CCIMWIDGETS_PREVIEW_H__
#define __CCIMWIDGETS_PREVIEW_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class Preview: public Widget
    {
    private:
        void draw() override {};

        bool init(const std::string& name, const std::string& displayName, size_t count) override;

        cocos2d::RefPtr<cocos2d::Camera> _camera;
    };
}

#endif