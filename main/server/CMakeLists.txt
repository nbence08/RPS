set(SERVER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	${CMAKE_CURRENT_LIST_DIR}/server.hpp
	${CMAKE_CURRENT_LIST_DIR}/server.cpp
	${CMAKE_CURRENT_LIST_DIR}/scoreboard.hpp
	${CMAKE_CURRENT_LIST_DIR}/scoreboard.cpp
	${CMAKE_CURRENT_LIST_DIR}/connection.hpp
	${CMAKE_CURRENT_LIST_DIR}/connection.cpp
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${SERVER_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
