//
//  LuaUtils.h
//  Chilli Source
//  Created by Scott Downie on 13/08/2014.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2014 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#ifndef _CHILLISOURCE_LUA_BASE_LUAUTILS_H_
#define _CHILLISOURCE_LUA_BASE_LUAUTILS_H_

#include <ChilliSource/ChilliSource.h>

extern "C"
{
#include <lua/lua.h>
#include <lua/lauxlib.h>
}

#include <tuple>

namespace ChilliSource
{
    namespace Lua
    {
        namespace LuaUtils
        {
            //---------------------------------------------------------
            /// Push the value to the Lua VM stack. This is specialised
            /// for each supported value type and will assert if
            /// unsupported type is used.
            ///
            /// @author S Downie
            ///
            /// @param Lua VM
            /// @param Value
            //---------------------------------------------------------
            template <typename TArg> void PushValueToVM(lua_State* in_vm, TArg in_arg)
            {
                static_assert(std::is_pointer<TArg>::value, "Lua type not supported");
            }
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, bool in_arg);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, s32 in_arg);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, u32 in_arg);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, f32 in_arg);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, f64 in_arg);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, std::string in_arg);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> void PushValueToVM(lua_State* in_vm, const char* in_arg);
            //---------------------------------------------------------
            /// Pop the value from the top of the Lua VM stack. This is specialised
            /// for each supported value type and will assert if
            /// unsupported type is used.
            ///
            /// @author S Downie
            ///
            /// @param Lua VM
            ///
            /// @return Value
            //---------------------------------------------------------
            template <typename TResult> TResult PopValueFromVM(lua_State* in_vm)
            {
                static_assert(std::is_pointer<TResult>::value, "Lua type not supported");
                return TResult();
            }
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> bool PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> s32 PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> u32 PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> f32 PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> f64 PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> std::string PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            //---------------------------------------------------------
            template <> const char* PopValueFromVM(lua_State* in_vm);
            //---------------------------------------------------------
            /// Template container for a tuple Index
            ///
            /// @author S Downie
            //---------------------------------------------------------
            template <size_t> struct TupleIndex { };
            //---------------------------------------------------------
            /// Specialised function to terminate recursion when
            /// index is zero.
            ///
            /// @author S Downie
            ///
            /// @param Lua VM
            /// @param Tuple
            /// @param Index 0
            //---------------------------------------------------------
            template <typename TTupleType> void PushAllToVM(lua_State* in_vm, const TTupleType& tuple, TupleIndex<0>)
            {
                
            }
            //---------------------------------------------------------
            /// Helper function for iterating the tuple and pushing
            /// all values to the Lua VM using recursion and starting
            /// at the given index
            ///
            /// @author S Downie
            ///
            /// @param Lua VM
            /// @param Tuple
            /// @param Index to push from
            //---------------------------------------------------------
            template <typename TTupleType, size_t N> void PushAllToVM(lua_State* in_vm, const TTupleType& tuple, TupleIndex<N>)
            {
                PushAllToVM(in_vm, tuple, TupleIndex<N-1>());
                PushValueToVM(in_vm, std::get<N-1>(tuple));
            }
            //---------------------------------------------------------
            /// Helper function for iterating the tuple and pushing
            /// all values to the Lua VM using recursion.
            ///
            /// @author S Downie
            ///
            /// @param Lua VM
            /// @param Tuple
            //---------------------------------------------------------
            template <typename TTupleType> void PushAllToVM(lua_State* in_vm, const TTupleType& tuple)
            {
                PushAllToVM(in_vm, tuple, TupleIndex<std::tuple_size<TTupleType>::value>());
            }
        }
    }
}

#endif
