#ifndef __CCIMGUIEDITOR_H__
#define __CCIMGUIEDITOR_H__

#include <string>
#include "CCImGuiWidget.h"

namespace CCImGuiWidgets
{
    class ImGuiEditor: public ImGuiWidget
    {
    private:
        void draw() override;
    };
}

#endif