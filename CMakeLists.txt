file(GLOB_RECURSE files src/*)

#COMPILE MAIN
add_executable(
        main
        ${files}
)

