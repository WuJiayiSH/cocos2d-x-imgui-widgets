#ifndef __CCIMGUINODEPREVIEW_H__
#define __CCIMGUINODEPREVIEW_H__

#include <string>
#include "CCImGuiWidget.h"

namespace CCImGuiWidgets
{
    class ImGuiNodePreview: public ImGuiWidget
    {
    private:
        void draw() override;
    };
}

#endif