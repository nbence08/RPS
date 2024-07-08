set(CURRENT_TARGET RockPaperScissors)

add_executable(${CURRENT_TARGET})

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${PRIMARY_INCLUDE_DIR}
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${RPS_ROOT_DIR}/BuildFunctions.cmake
)

# message(${SCRAM_ROOT_DIR}/lib)
# message(${SCRAM_ROOT_DIR}/lib/Debug)
target_link_directories(${CURRENT_TARGET} PRIVATE ${RPS_ROOT_DIR}/lib)
target_link_directories(${CURRENT_TARGET} PRIVATE ${RPS_ROOT_DIR}/lib/Debug)
target_link_directories(${CURRENT_TARGET} PRIVATE ${RPS_ROOT_DIR}/lib/Release)
target_link_directories(${CURRENT_TARGET} PRIVATE ${RPS_ROOT_DIR}/bin)
target_link_directories(${CURRENT_TARGET} PRIVATE ${RPS_ROOT_DIR}/bin/Debug)
target_link_directories(${CURRENT_TARGET} PRIVATE ${RPS_ROOT_DIR}/bin/Release)
target_link_libraries(${CURRENT_TARGET} PRIVATE )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/client)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/server)

set(MAIN_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
	
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_sources(${CURRENT_TARGET}
	PRIVATE
	${MAIN_SOURCES}
)

target_include_directories(${CURRENT_TARGET}
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
 )

 groupSources()
