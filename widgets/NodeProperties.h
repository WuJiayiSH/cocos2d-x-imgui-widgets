#ifndef __CCIMWIDGETS_NODEPROPERTIES_H__
#define __CCIMWIDGETS_NODEPROPERTIES_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class NodeProperties: public Widget
    {
    private:
        void draw() override;
    };
}

#endif