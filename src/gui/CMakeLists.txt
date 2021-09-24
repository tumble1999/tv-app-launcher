set(NAME tal)
file( GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_executable(${NAME}
	${SRC}
)



target_link_libraries(${NAME}
${TAL_LIBS}
)
