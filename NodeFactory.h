#ifndef __CCIMWIDGETS_NODEFACTORY_H__
#define __CCIMWIDGETS_NODEFACTORY_H__

#include "cocos2d.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace CCImWidgets
{
    class NodeFactory : public cocos2d::Ref
    {
    private:
        struct NodeCreator
        {
            std::string _name;
            std::string _displayName;
            std::function<Node*()> _ctor;
            uint32_t _count;
		};
    public:
        template <typename T>
        struct AutoRegister
        {
            AutoRegister(const char* name, const char* displayName)
            {
                NodeCreator& creator = NodeFactory::getInstance()->_NodeCreators[name];
                creator._name = name;
                creator._displayName = displayName;
				        creator._ctor = []() -> Node* {return new (std::nothrow)T(); };
                creator._count = 0;
            }
        };

        Node* createNode(const std::string& name);
        
        static NodeFactory* getInstance();

    private:
        std::unordered_map<std::string, NodeCreator> _NodeCreators;
    };
}

#endif