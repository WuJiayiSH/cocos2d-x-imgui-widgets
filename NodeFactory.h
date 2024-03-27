#ifndef __CCIMWIDGETS_NODEFACTORY_H__
#define __CCIMWIDGETS_NODEFACTORY_H__

#include "cocos2d.h"

#include <string>
#include <unordered_map>

namespace CCImWidgets
{
    class NodeFactory : public cocos2d::Ref
    {
	public:
        struct Creator
        {
            friend class NodeFactory;
            
            Creator(const std::string& name, const std::string& displayName, uint32_t mask, const std::function<cocos2d::Node*()>& constructor)
            : _name(name)
            , _displayName(displayName)
            , _mask(mask)
            , _constructor(constructor)
            {
            }

            const std::string& getName() const { return _name; };

            const std::string& getDisplayName() const { return _displayName; };

            uint32_t getMask() const { return _mask; };

            cocos2d::Node* create() const { return _constructor(); };

        private:
            std::string _name;
            std::string _displayName;
            uint32_t _mask;
            std::function<cocos2d::Node*()> _constructor;
		};
    
        template <typename T>
        struct AutoRegister
        {
            AutoRegister(const char* name, const char* displayName, const std::function<cocos2d::Node*()>& constructor, uint32_t mask = 0)
            {
                std::function<cocos2d::Node*()> wrapper = [constructor]() -> cocos2d::Node* {
                    cocos2d::Node* node = constructor();
                    if (!node)
                        return nullptr;

					T* visitor = new (std::nothrow)T();
                    if (!visitor)
                        return nullptr;

					if (!visitor->init())
					{
						delete visitor;
						return nullptr;
					}

                    visitor->setName("CCImWidgets.NodeVisitor");
                    node->addComponent(visitor);
                    return node;
                };
                NodeFactory::getInstance()->_creators.emplace(name, Creator(name, displayName, mask, wrapper));
            }
        };

        const std::unordered_map<std::string, Creator>& getCreators() { return _creators; };

		cocos2d::Node* createNode(const std::string& name);
        
        static NodeFactory* getInstance();

    private:
        std::unordered_map<std::string, Creator> _creators;
    };
}

#endif