#ifndef __CCIMNODETREE_H__
#define __CCIMNODETREE_H__

#include <string>
#include "CCImWidget.h"

namespace CCImWidgets
{
    class CCImNodeTree: public CCImWidget
    {
    private:
        void draw() override;
    };
}

#endif