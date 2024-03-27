#include "NodeFactory.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    NodeFactory* NodeFactory::getInstance()
    {
        static NodeFactory* instance = new NodeFactory();
        return instance;
    }

    cocos2d::Node* NodeFactory::createNode(const std::string& name)
    {
        std::unordered_map<std::string, Creator>::iterator it = _creators.find(name);
        if (it != _creators.end())
        {
			Creator& creator = it->second;
			return creator.create();
        }
        
        return nullptr;
    }
}
