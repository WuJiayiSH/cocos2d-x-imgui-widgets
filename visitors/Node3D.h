#ifndef __CCIMWIDGETS_NODE3D_H__
#define __CCIMWIDGETS_NODE3D_H__

#include "NodeVisitor.h"

namespace CCImWidgets
{
    class Node3D: public NodeVisitor
    {
    public:
        void visit() override;
    };
}

#endif