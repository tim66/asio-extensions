/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ASIOEXT_IMPL_OPENFLAGS_CPP
#define ASIOEXT_IMPL_OPENFLAGS_CPP

#include "asioext/open_flags.hpp"

#include "asioext/detail/push_options.hpp"

ASIOEXT_NS_BEGIN

namespace open_flags {

bool is_valid(uint32_t flags)
{
  int creation_modes = !!(flags & create_new) +
                       !!(flags & create_always) +
                       !!(flags & open_existing) +
                       !!(flags & open_always) +
                       !!(flags & truncate_existing);

  if (creation_modes > 1)
    return false;

  return true;
}

}

ASIOEXT_NS_END

#include "asioext/detail/pop_options.hpp"

#endif
