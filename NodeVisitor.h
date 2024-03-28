#ifndef __CCIMWIDGETS_NODEVISITOR_H__
#define __CCIMWIDGETS_NODEVISITOR_H__

#include "cocos2d.h"
#include "invoke.hpp/invoke.hpp"
#include "PropertyRenderer.h"

namespace CCImWidgets
{
    enum class NodeVisitorFlag : uint32_t
	{
		CAN_HAVE_CHILDREN = 1,
        CAN_BE_ROOT = 1 << 1
	};

    class NodeVisitor : public cocos2d::Component
    {
    public:
        virtual void visit() {};
    protected:
        template <class Getter, class Setter, class Object, class... Args>
        void draw(const char *label, Getter &&getter, Setter &&setter, Object&& object, Args &&...args)
        {
            auto v = invoke_hpp::invoke(std::forward<Getter>(getter), std::forward<Object>(object));
            if (PropertyRenderer<decltype(v)>::draw(label, v, std::forward<Args>(args)...))
            {
                invoke_hpp::invoke(std::forward<Setter>(setter), std::forward<Object>(object), v);
            }
        }
    };
}

#endif