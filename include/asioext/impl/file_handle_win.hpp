/// @copyright Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
/// Distributed under the Boost Software License, Version 1.0.
/// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ASIOEXT_IMPL_FILEHANDLE_WIN_HPP
#define ASIOEXT_IMPL_FILEHANDLE_WIN_HPP

#include "asioext/file_handle.hpp"

#include "asioext/detail/win_file_ops.hpp"
#include "asioext/detail/buffer.hpp"

ASIOEXT_NS_BEGIN

// Note: Currently always only the first buffer is used.
// This is possible since we can get away with returning less than requested
// and is unfortunately the only way this can be implemented reasonably.
//
// Windows has vectored I/O functions (ReadFileScatter, WriteFileGather),
// but they impose very strict alignment and size requirements and are thus
// unusable here.

template <typename MutableBufferSequence>
std::size_t file_handle::read_some(const MutableBufferSequence& buffers,
                                   error_code& ec) ASIOEXT_NOEXCEPT
{
  const asio::mutable_buffer buf = asioext::first_mutable_buffer(buffers);
  return detail::win_file_ops::read(
      handle_, buf.data(), static_cast<uint32_t>(buf.size()), ec);
}

template <typename ConstBufferSequence>
std::size_t file_handle::write_some(const ConstBufferSequence& buffers,
                                    error_code& ec) ASIOEXT_NOEXCEPT
{
  const asio::const_buffer buf = asioext::first_const_buffer(buffers);
  return detail::win_file_ops::write(
      handle_, buf.data(), static_cast<uint32_t>(buf.size()), ec);
}

template <typename MutableBufferSequence>
std::size_t file_handle::read_some_at(uint64_t offset,
                                      const MutableBufferSequence& buffers,
                                      error_code& ec) ASIOEXT_NOEXCEPT
{
  const asio::mutable_buffer buf = asioext::first_mutable_buffer(buffers);
  return detail::win_file_ops::pread(
      handle_, buf.data(), static_cast<uint32_t>(buf.size()), offset, ec);
}

template <typename ConstBufferSequence>
std::size_t file_handle::write_some_at(uint64_t offset,
                                       const ConstBufferSequence& buffers,
                                       error_code& ec) ASIOEXT_NOEXCEPT
{
  const asio::const_buffer buf = asioext::first_const_buffer(buffers);
  return detail::win_file_ops::pwrite(
      handle_, buf.data(), static_cast<uint32_t>(buf.size()), offset, ec);
}

ASIOEXT_NS_END

#endif
