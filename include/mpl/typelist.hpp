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

#include <mpl/type_traits.hpp>

namespace lunacy
{
namespace mpl
{
  template<typename...>
  struct TypeList;

  /**
   * Implementation of a TypeList's At operation. This operation finds the type 
   * in position idx of the TypeList.
   * 
   * @tparam This  the vector
   * @tparam idx   index
   */
  template<typename This, size_t idx> // general declaration
  struct __TypeListAtImpl;

  // 1st specialisation: usual case -> drop current Head of the TypeList and do 
  //                                   recursive call with idx-1
  template<typename Head, typename... Tail, size_t idx>
  struct __TypeListAtImpl<TypeList<Head, Tail...>, idx>
  {
    static_assert(sizeof... (Tail) >= idx, "Index out of bounds!");
    using Result = typename __TypeListAtImpl<TypeList<Tail...>, idx-1>::Result;
  };

  // 2nd operation: reached target element (idx=0) -> current Head is the Result
  template<typename Head, typename... Tail>
  struct __TypeListAtImpl<TypeList<Head, Tail...>, 0>
  {
    using Result = Head;
  };

  template<>
  struct TypeList<>
  {
    using Size    = IntegralConstant<size_t, 0>;
    using MaxSize = IntegralConstant<size_t, -1>;
    using Empty   = TrueType;
    template<typename T>
    using PushBack  = TypeList<T>;
    template<typename T>
    using PushFront = TypeList<T>;
  };

  template<typename Head, typename... Tail>
  struct TypeList<Head, Tail...>
  {
    using This      = TypeList<Head,Tail...>;
    using Size      = IntegralConstant<size_t, 1 + sizeof... (Tail)>;
    using MaxSize   = IntegralConstant<size_t, -1>;
    using Empty     = FalseType;
    template<size_t n>
    using At        = typename __TypeListAtImpl<This, n>::Result;
    using Front     = At<0>;
    using Back      = At<Size()-1>;
    template<typename T>
    using PushBack  = TypeList<Head, Tail..., T>;
    template<typename T>
    using PushFront = TypeList<T, Head, Tail...>;
  };
} // namespace lunacy

} // namespace mpl