#ifndef __CCIMGUINODEPROPERTIES_H__
#define __CCIMGUINODEPROPERTIES_H__

#include <string>
#include "CCImGuiWidget.h"

namespace CCImGuiWidgets
{
    class ImGuiNodeProperties: public ImGuiWidget
    {
    private:
        void draw() override;
    };
}

#endif