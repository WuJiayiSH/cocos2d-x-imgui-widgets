#ifndef __CCIMGUINODETREE_H__
#define __CCIMGUINODETREE_H__

#include <string>
#include "CCImGuiWidget.h"

namespace CCImGuiWidgets
{
    class ImGuiNodeTree: public ImGuiWidget
    {
    private:
        void draw() override;
    };
}

#endif