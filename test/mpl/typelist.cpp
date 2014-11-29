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

#include <mpl/typelist.hpp>

using namespace lunacy;
using namespace mpl;

using IntList = TypeList<IntegralConstant<int, 1>, 
                         IntegralConstant<int, 2>, 
                         IntegralConstant<int, 3>, 
                         IntegralConstant<int, 4>>;
using EmptyList = TypeList<>;

static_assert(EmptyList::Empty(), "");
static_assert(!IntList::Empty(), "");

static_assert(EmptyList::Size() == 0, "");
static_assert(IntList::Size() == 4, "");

static_assert(IntList::At<1>() == 2, "");
static_assert(IntList::At<2>() == 3, "");
static_assert(IntList::Front() == 1, "");
static_assert(IntList::Back() == 4, "");
static_assert(IntList::PushBack<IntegralConstant<int, 5>>::Back() == 5, "");
