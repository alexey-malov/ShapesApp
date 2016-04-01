// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <boost/algorithm/string/replace.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/remove.hpp>

// TODO: reference additional headers your program requires here
#define BOOST_TEST_INCLUDED
#pragma warning (disable: 4702)
#pragma warning (push, 3)
#include <boost/test/unit_test.hpp>
#pragma warning (pop)

#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>
