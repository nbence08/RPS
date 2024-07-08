set(COMMON_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	${CMAKE_CURRENT_LIST_DIR}/gamelogic.hpp
	${CMAKE_CURRENT_LIST_DIR}/gamelogic.cpp
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${COMMON_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
