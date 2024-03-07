#ifndef __CCIMWIDGETS_PREVIEW_H__
#define __CCIMWIDGETS_PREVIEW_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class Node2D: public Node
    {
    private:
        void draw() override;
    };

    namespace
    {
        static NodeFactory::AutoRegister<NodeProperties> s_register(
            "CCImWidgets.Node2D",
            "2D/Node2D"
        );
    }
}

#endif