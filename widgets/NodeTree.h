#ifndef __CCIMWIDGETS_NODETREE_H__
#define __CCIMWIDGETS_NODETREE_H__

#include <string>
#include "Widget.h"

namespace CCImWidgets
{
    class NodeTree: public Widget
    {
    private:
        void draw(bool* open) override;
    };
}

#endif