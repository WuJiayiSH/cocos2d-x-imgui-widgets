#ifndef __CCIMWIDGETS_PREVIEW_H__
#define __CCIMWIDGETS_PREVIEW_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class Preview: public Widget
    {
    private:
        void draw() override;
    };
}

#endif