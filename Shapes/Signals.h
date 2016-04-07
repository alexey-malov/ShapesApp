#pragma once

#pragma warning(push, 3)
#include <boost/signals2.hpp>
#pragma warning(pop)
#pragma warning(disable:4503)

namespace ui
{

template <typename Handler>
using Signal = boost::signals2::signal<Handler>;

using Connection = boost::signals2::connection;

}
