#ifndef __CCIMWIDGETS_NODEVISITOR_H__
#define __CCIMWIDGETS_NODEVISITOR_H__

#include "cocos2d.h"

namespace CCImWidgets
{
    enum class NodeVisitorFlag : uint32_t
	{
		CAN_HAVE_CHILDREN = 1,
        CAN_BE_ROOT = 1 << 1
	};

    class NodeVisitor : public cocos2d::Component
    {
    };
}

#endif