#include "Node2D.h"
#include "NodeFactory.h"
#include "cocos2d.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    namespace
    {
        bool create(cocos2d::Node** node)
        {
            *node = cocos2d::Node::create();
			return true;
        }

        static NodeFactory::AutoRegister<Node2D> s_register(
            "CCImWidgets.Node2D",
            "2D/Node2D",
            create);
    }
}
