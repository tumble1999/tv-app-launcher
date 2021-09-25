set(NAME tal)
file(GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_executable(${NAME}
	WIN32
	${SRC}
)



target_link_libraries(${NAME}
	${LTV_LIBS}
	# ltv
)
