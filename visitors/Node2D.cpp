#include "Node2D.h"
#include "NodeFactory.h"
#include "cocos2d.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    void Node2D::draw() 
    {
        property("Position", 
            [](cocos2d::Node* node) -> cocos2d::Vec3 {return node->getPosition3D(); },
            [](cocos2d::Node* node, const cocos2d::Vec3& pos) -> void {node->setPosition3D(pos); },
            getOwner());
    }
    
    namespace
    {
        bool create(cocos2d::Node** node)
        {
            *node = cocos2d::Node::create();
            Node2D* visitor = new Node2D();
			visitor->init();
            visitor->autorelease();
            visitor->setName("CCImWidgets.NodeVisitor");
			(*node)->addComponent(visitor);
			(*node)->setName("Node2D");
			return true;
        }

        static NodeFactory::AutoRegister<Node2D> s_register(
            "CCImWidgets.Node2D",
            "2D/Node2D",
            create);
    }
}
