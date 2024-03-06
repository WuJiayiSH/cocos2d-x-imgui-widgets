#ifndef __CCIMWIDGETS_IMPROXY_H__
#define __CCIMWIDGETS_IMPROXY_H__

#include "cocos2d.h"

#include <vector>
#include <string>

namespace CCImWidgets
{
    class TypeWrapper: public cocos2d::Ref
    {
    public:
        virtual void wrap() = 0;

    private:
        template<typename Getter, typename Setter, typename NodeType, typename... Args>
        NodeProxy& property(const char* label, Getter&& getter, Setter&& setter, NodeType* node, Args&&... args)
        {
			using namespace std;
			using ValueType = std::remove_cv<std::remove_reference<std::result_of<Getter(NodeType*)>::type>::type>::type;

            if (_context == Drawing)
            {
                ValueType val = std::forward<Getter>(getter)(node);
                if (NodeGuiPropertyRenderer<ValueType>::draw(label, val, std::forward<Args>(args)...))
                {
                    std::forward<Setter>(setter)(node, val);
                }
            }
        }

        const std::string& getName() const {return _name;}
        const std::string& getDisplayName() const {return _displayName;}
     
    private:
        std::string _name;
        std::string _displayName;
    };
}

#endif
        

