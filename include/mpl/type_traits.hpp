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

namespace lunacy
{

namespace mpl
{

template<typename T, T v>
struct IntegralConstant 
{
  static constexpr T value = v;
  constexpr operator T() const { return value; }
  constexpr T operator()() const { return value; }
};

template<typename T, T v>
constexpr T IntegralConstant<T, v>::value;

using TrueType  = IntegralConstant<bool, true>;
using FalseType = IntegralConstant<bool, false>;

template<bool b, typename IfTrue, typename IfFalse>
struct __ConditionalImpl
{
    using Type = IfTrue;
};

template<typename IfTrue, typename IfFalse>
struct __ConditionalImpl<false, IfTrue, IfFalse>
{
    using Type = IfFalse;
};

template<bool b, typename IfTrue, typename IfFalse>
using Conditional = __ConditionalImpl<b, IfTrue, IfFalse>;



} // namespace lunacy

} // namespace mpl