#ifndef __CCIMWIDGETS_PREVIEW_H__
#define __CCIMWIDGETS_PREVIEW_H__

#include <string>
#include "Widget.h"
#include "CCIMGUI.h"
namespace CCImWidgets
{
    class Preview: public Widget
    {
    private:
        void draw() override;
		void update(float dt);
        bool init(const std::string& name, const std::string& displayName, size_t count) override;

        void updateFrameBufferObject(unsigned int width, unsigned int height);

        cocos2d::RefPtr<cocos2d::Camera> _camera;
		ImVec2 _windowSize;
    };
}

#endif