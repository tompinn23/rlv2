
set(LUA_SRC src/lapi.c
			src/lauxlib.c
			src/lbaselib.c
			src/lbitlib.c
			src/lcode.c
			src/lcorolib.c
			src/lctype.c
			src/ldblib.c
			src/ldebug.c
			src/ldo.c
			src/ldump.c
			src/lfunc.c
			src/lgc.c
			src/linit.c
			src/liolib.c
			src/llex.c
			src/lmathlib.c
			src/lmem.c
			src/loadlib.c
			src/lobject.c
			src/lopcodes.c
			src/loslib.c
			src/lparser.c
			src/lstate.c
			src/lstring.c
			src/lstrlib.c
			src/ltable.c
			src/ltablib.c
			src/ltm.c
			src/lundump.c
			src/lutf8lib.c
			src/lvm.c
			src/lzio.c )

add_library (lualib SHARED ${LUA_SRC})
target_compile_definitions ( lualib PRIVATE _CRT_SECURE_NO_WARNINGS LUA_BUILD_AS_DLL )
set_target_properties ( lualib PROPERTIES OUTPUT_NAME lua LINKER_LANGUAGE C)
target_include_directories(lualib PUBLIC "${CMAKE_SOURCE_DIR}/Dependencies/Lua/src")

