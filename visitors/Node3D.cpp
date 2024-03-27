#include "Node3D.h"
#include "NodeFactory.h"
#include "cocos2d.h"

namespace CCImWidgets
{
    namespace
    {
        static NodeFactory::AutoRegister<Node3D> s_register(
            "CCImWidgets.Node3D",
            "3D/Node3D",
			&cocos2d::Node::create,
            static_cast<uint32_t>(NodeVisitorFlag::CAN_HAVE_CHILDREN) | static_cast<uint32_t>(NodeVisitorFlag::CAN_BE_ROOT)
        );
    }
}
