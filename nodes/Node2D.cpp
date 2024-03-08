#ifndef __CCIMWIDGETS_PREVIEW_H__
#define __CCIMWIDGETS_PREVIEW_H__

#include <string>
#include "NodeVisistor.h"

namespace CCImWidgets
{

    void Node2D::visit()
    {
    }

    namespace
    {
        bool create(Node** node)
        {
            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                Node* tmp = Node::create();
                node = &tmp;
                return true;
            }

            return false
        }
        static NodeFactory::AutoRegister<NodeProperties> s_register(
            "CCImWidgets.Node2D",
            "2D/Node2D");
    }
}

#endif