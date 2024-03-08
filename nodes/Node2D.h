#ifndef __CCIMWIDGETS_PREVIEW_H__
#define __CCIMWIDGETS_PREVIEW_H__

#include <string>
#include "NodeVisistor.h"

namespace CCImWidgets
{
    class Node2D: public NodeVisistor
    {
    private:
        void visit() override;
    };

    

}

#endif