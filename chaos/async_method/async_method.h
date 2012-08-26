/*
 * Copyright 2012, Yunjie Lu.  All rights reserved.
 * https://github.com/lyjdamzwf/chaos
 *
 * Use of this source code is governed by a BSD-style
 * license that can be found in the License file.
 */

#ifndef _CHAOS_ASYNC_METHOD_H_
#define _CHAOS_ASYNC_METHOD_H_

/*! 
 *  @file           async_method.h
 *  @author         yunjie.lu
 *  @email          lyjdamzwf@gmail.com
 *  @weibo          http://weibo.com/crazyprogramerlyj
 *  @date           2012.3.17
 *  @brief          async method interface
 *  @last changed
 *
 */

#include <stdlib.h>
#include <stdint.h>

#include <iostream>

#include <chaos/utility/utility_inc.h>

#include <chaos/async_method/async_method_base.h>
#include <chaos/async_method/async_method_bind_func.h>
#include <chaos/async_method/async_method_bind_obj.h>

namespace chaos
{

namespace async_method
{

using namespace std;

#define BIND_FUNC_ENTRY(num) \
template <typename F BIND_NAME_LIST_##num(typename A)> \
static async_method_t bind_func(F f_ BIND_ARG_LIST_##num) \
{ \
    async_method_base_t* async_method_ptr = \
    new async_method_bind_func_##num##_t<F BIND_NAME_LIST_##num(A)>( \
                                f_ BIND_NEW_CTOR_LIST_##num \
                                                                   ); \
    async_method_t async_method(async_method_ptr); \
    return async_method; \
}

#define BIND_OBJ_ENTRY(num) \
template <typename F, typename CLS_TYPE BIND_NAME_LIST_##num(typename A)> \
static async_method_t bind_memfunc(CLS_TYPE obj_, F f_ BIND_ARG_LIST_##num) \
{ \
    async_method_base_t* async_method_ptr = \
    new async_method_bind_obj_##num##_t<CLS_TYPE, F BIND_NAME_LIST_##num(A)>( \
                                obj_, f_ BIND_NEW_CTOR_LIST_##num \
                                                                            ); \
    async_method_t async_method(async_method_ptr); \
    return async_method; \
}

//! yunjie: bind接口的参数不能使用const T&类型, 如果传入的是函数指针将编译错误
class async_method_t
{
public:
    //! ---------------------- yunjie: bind static function begin ---------------------- 
    BIND_FUNC_ENTRY(0)
    BIND_FUNC_ENTRY(1)
    BIND_FUNC_ENTRY(2)
    BIND_FUNC_ENTRY(3)
    BIND_FUNC_ENTRY(4)
    BIND_FUNC_ENTRY(5)
    BIND_FUNC_ENTRY(6)
    BIND_FUNC_ENTRY(7)
    BIND_FUNC_ENTRY(8)
    BIND_FUNC_ENTRY(9)
    //! ---------------------- yunjie: bind static function end ---------------------- 




    //! ---------------------- yunjie: bind object function begin ---------------------- 
    BIND_OBJ_ENTRY(0)
    BIND_OBJ_ENTRY(1)
    BIND_OBJ_ENTRY(2)
    BIND_OBJ_ENTRY(3)
    BIND_OBJ_ENTRY(4)
    BIND_OBJ_ENTRY(5)
    BIND_OBJ_ENTRY(6)
    BIND_OBJ_ENTRY(7)
    BIND_OBJ_ENTRY(8)
    BIND_OBJ_ENTRY(9)
    //! ---------------------- yunjie: bind object function end ---------------------- 


public:
    async_method_t()
        : m_async_method_base_ptr(NULL)
    {
    }

    async_method_t(async_method_base_t* ptr_)
        : m_async_method_base_ptr(ptr_)
    {
    }

    async_method_t(const async_method_t& rhs_)
    {
        m_async_method_base_ptr = rhs_.m_async_method_base_ptr;
    }

    void operator=(const async_method_t& method_)
    {
        m_async_method_base_ptr = method_.m_async_method_base_ptr;
    }

    void operator()()
    {
        if (NULL != m_async_method_base_ptr)
        {
            m_async_method_base_ptr->exec();
        }
    }

    void release()
    {
        if (NULL != m_async_method_base_ptr)
        {
            SAFE_DELETE(m_async_method_base_ptr);
        }
    }

private:
    async_method_base_t*    m_async_method_base_ptr;
};


}

}

#endif //! _CHAOS_ASYNC_METHOD_H_

