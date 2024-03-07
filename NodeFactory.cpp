#include "NodeFactory.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    
    NodeFactory* NodeFactory::getInstance()
    {
        static NodeFactory* instance = new NodeFactory();
        return instance;
    }

    Node* NodeFactory::createNode(const std::string& name)
    {
        std::unordered_map<std::string, NodeCreator>::iterator it = _nodeCreators.find(name);
        if (it != _nodeCreators.end())
        {
            NodeCreator& creator = it->second;
            Node* node = creator._ctor();
            std::string name = creator._name;
            std::string displayName = creator._displayName;
            if (creator._count > 0)
            {
                name = name + "/" + creator._count;
            }
            if (node && node->init(std::move(name), std::move(displayName)))
            {
                creator._count ++;
                return node;
            }
            
            delete node;
        }
        
        return nullptr;
    }
}
