// sol2

// The MIT License (MIT)

// Copyright (c) 2013-2022 Rapptz, ThePhD and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SOL_COMPATIBILITY_HPP
#define SOL_COMPATIBILITY_HPP

// The various pieces of the compatibility layer
// comes from https://github.com/keplerproject/lua-compat-5.3
// but has been modified in many places for use with sol and luajit,
// though the core abstractions remain the same

#include <sol/version.hpp>
#include <sol/compatibility/lua_version.hpp>

#ifdef SOL_LUAU

typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);
typedef int (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);

#define lua_pushcclosure(L, fn, n) \
  (lua_pushcclosurek((L), (fn), NULL, (n), NULL))

#define lua_pushcfunction(L, f) \
   (lua_pushcclosurek((L), (f), NULL, 0, NULL))

#define luaL_loadbuffer(L,s,sz,n)	luaL_loadbufferx(L,s,sz,n,NULL)

#define lua_error(L) (lua_error(L), 0)
#define luaL_error(L, fmt, ...) (luaL_errorL(L, fmt, ##__VA_ARGS__), 0)


#define lua_getinfo(L, what, ar) \
  (lua_getinfo((L), 1, what, (ar)))

#define lua_getstack(L, level, ar) \
  (lua_getinfo((L), "s", (ar)))

#define LUA_ERRFILE     (LUA_ERRERR+1)

inline int luaL_ref (lua_State *L, int t) {
    return -1; // TODO
}

void luaL_unref (lua_State *L, int t, int ref) {
    // TODO
}

inline lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf) {
    return NULL; // TODO
}

inline int luaopen_package (lua_State *L) {
    // TODO
}

inline int luaopen_io (lua_State *L) {
    // TODO
}

#define LUA_FILEHANDLE		"FILE*"

// #define lua_getinfo(L, what, ar) \
//   (lua_getinfo((L), 1, (what), (ar)))

#endif // SOL_LUAU

#if SOL_IS_ON(SOL_USE_COMPATIBILITY_LAYER)

// clang-format off
#if SOL_IS_ON(SOL_USING_CXX_LUA) || SOL_IS_ON(SOL_USING_CXX_LUAJIT)
	#ifndef COMPAT53_LUA_CPP
		#define COMPAT53_LUA_CPP 1
	#endif // Build Lua Compat layer as C++
#endif
	#ifndef COMPAT53_INCLUDE_SOURCE
		#define COMPAT53_INCLUDE_SOURCE 1
	#endif // Build Compat Layer Inline
	#include <sol/compatibility/compat-5.3.h>
	#include <sol/compatibility/compat-5.4.h>
#endif
// clang-format on

#endif // SOL_COMPATIBILITY_HPP
