set(NAME tv-app-launcher)
file( GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_executable(${NAME}
	${SRC}
)