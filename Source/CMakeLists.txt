

add_executable(rl main.c parser.c)
target_link_libraries(rl bearlib)

get_target_property(LIB_LOCATION bearlib IMPORTED_LOCATION)

add_custom_command(TARGET rl POST_BUILD
	COMMENT "Copying Bearlibterminal"# Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${LIB_LOCATION}"      # <--this is in-file
        $<TARGET_FILE_DIR:rl>)