add_library(bearlib SHARED IMPORTED GLOBAL)


math(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

if(WIN32)
	if(BITNESS EQUAL "32")
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/BearLibTerminal/Windows32/BearLibTerminal.dll")
		set_target_properties(bearlib PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/Dependencies/BearLibTerminal/Windows32/BearLibTerminal.lib")
	else()
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/BearLibTerminal/Windows64/BearLibTerminal.dll")
		set_target_properties(bearlib PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/Dependencies/BearLibTerminal/Windows64/BearLibTerminal.lib")
	endif()
elseif(LINUX)
if(BITNESS EQUAL "32")
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/BearLibTerminal/Linux32/libBearLibTerminal.so")
	else()
		set_target_properties(bearlib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/BearLibTerminal/Linux64/libBearLibTerminal.so")
	endif()
else()
message(FATAL_ERROR "Unsupported Platform")
endif()

set(DEP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/include")

target_include_directories(bearlib INTERFACE ${DEP_INCLUDE_DIR})

add_library(hashMap STATIC map.c)
target_include_directories(hashMap PUBLIC ${DEP_INCLUDE_DIR})

add_library(xml STATIC xml.c)
target_include_directories(xml PUBLIC ${DEP_INCLUDE_DIR})
target_include_directories(xml PRIVATE "${CMAKE_SOURCE_DIR}/Source")

add_library(re STATIC re.c)
target_include_directories(re PUBLIC ${DEP_INCLUDE_DIR})

add_library(jsmn STATIC jsmn.c)
target_include_directories(jsmn PUBLIC ${DEP_INCLUDE_DIR})