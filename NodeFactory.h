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
            std::function<bool(cocos2d::Node**)> _ctor;
            uint32_t _count;
		};
    public:
        template <typename T>
        struct AutoRegister
        {
            AutoRegister(const char* name, const char* displayName, const std::function<bool(cocos2d::Node**)>& ctor)
            {
                NodeCreator& creator = NodeFactory::getInstance()->_NodeCreators[name];
                creator._name = name;
                creator._displayName = displayName;
				        creator._ctor = ctor;
                creator._count = 0;
            }
        };

        const std::unordered_map<std::string, NodeCreator>& getCreators() { return _NodeCreators; };
		void createNode(const std::string& name);
        
        static NodeFactory* getInstance();

    private:
        std::unordered_map<std::string, NodeCreator> _NodeCreators;
        void draw();
        std::string _currentCreating;
    };
}

#endif