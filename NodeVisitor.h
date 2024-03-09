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

        virtual void visit() {};
    protected:
        // template<typename Getter, typename Setter, typename NodeType, typename... Args>
        // NodeProxy& property(const char* label, Getter&& getter, Setter&& setter, NodeType* node, Args&&... args)
        // {
		// 	using namespace std;
		// 	using ValueType = std::remove_cv<std::remove_reference<std::result_of<Getter(NodeType*)>::type>::type>::type;

        //     if (_context == Drawing)
        //     {
        //         ValueType val = std::forward<Getter>(getter)(node);
        //         if (NodeGuiPropertyRenderer<ValueType>::draw(label, val, std::forward<Args>(args)...))
        //         {
        //             std::forward<Setter>(setter)(node, val);
        //         }
        //     }
        // }
    private:
        Context _context;
    };
}

#endif