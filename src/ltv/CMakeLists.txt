set(NAME ltv)
file( GLOB_RECURSE SRC
	"*.cpp"
	"*.c"
)

add_library(${NAME}
	${SRC}
)



target_link_libraries(${NAME}
${LTV_LIBS}
)
