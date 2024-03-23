#ifndef __CCIMWIDGETS_IMGUIDEMO_H__
#define __CCIMWIDGETS_IMGUIDEMO_H__

#include "Widget.h"

namespace CCImWidgets
{
    class ImGuiDemo: public Widget
    {
    private:
        void draw(bool* open) override;
    };
}

#endif