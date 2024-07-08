set(CLIENT_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	${CMAKE_CURRENT_LIST_DIR}/client.hpp
	${CMAKE_CURRENT_LIST_DIR}/client.cpp
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${CLIENT_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
