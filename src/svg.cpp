#include "svg.h"
#include <algorithm>

// blah

namespace experimental
{

/*
Restored from history for alternate purpose.

Will form the basis of the C++ DOM model (and in time the js api)
*/

namespace dom
{

error::error(ErrorCode code)
 : std::runtime_error("dom error."), code(code)
{
}

std::string node_t::textContent() const
{

}
void node_t::textContent(const std::string& context)
{

}
node node_t::appendChild(node newChild) // throw(DOMException);
{
    auto it = std::find(begin(children), end(children), newChild);
    if(it != end(children))
        children.erase(it);

    newChild->parent = shared_from_this();
    children.push_back(newChild);
    return newChild;
}
node node_t::insertBefore(node newChild, node refChild) // throw(DOMException);
{

}
node node_t::removeChild(node oldChild) // throw(DOMException);
{

}

node_t::~node_t()
{
}

}


}

