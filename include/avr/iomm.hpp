/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Christian Menard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <stddef.h>
#include <avr/avrconstants.hpp>
#include <inline.hpp>

namespace Lunacy
{
    template<typename, size_t> class IOMMPtr;
}

/**
 * A static pointer that provides read and write access to the I/O Memory Space.
 * 
 * @tparam T    type that is used for read and write access
 * @tparam addr the address this pointer points to (absolute memory address)
 * 
 * TODO for types larger than 1 byte interrupts need to be disabled on each 
 *      write and read access.
 */
template<typename T, size_t addr>
class Lunacy::IOMMPtr
{
private:
  using PtrType = volatile T*;
  static constexpr PtrType ptr = (PtrType) addr;
public:
  static INLINE T           read()     { return *ptr; }
  static INLINE volatile T& deref()    { return *ptr; }
  static INLINE void        write(T v) { *ptr = v; }

  // sanity check
  static_assert(addr >= AvrConstants::iommBase && 
                addr + sizeof(T) < AvrConstants::iommTop,
                "IOMMPtr points to region outside of I/O memory!");
};
