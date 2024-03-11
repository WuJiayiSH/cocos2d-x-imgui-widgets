#ifndef __CCIMWIDGETS_NODEVISITOR_H__
#define __CCIMWIDGETS_NODEVISITOR_H__

#include "cocos2d.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace CCImWidgets
{
    class NodeVisitor : public cocos2d::Component
    {

    public:
        enum class Context
        {
            DRAW,
            SERIALIZE,
            DESERIALIZE
        };
        
        virtual void draw()
        {
            _context = Context::DRAW;
            visit();
        };

        virtual void serialize()
        {
            _context = Context::SERIALIZE;
            visit();
        };

        virtual void deserialize()
        {
            _context = Context::DESERIALIZE;
            visit();
        };

    protected:
        virtual void visit() {};

        Context _context;
    };
}

#endif