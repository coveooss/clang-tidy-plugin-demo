add_library(ReviseLibV2Sample MODULE "")
target_compile_options(ReviseLibV2Sample PRIVATE -fno-rtti)
target_include_directories(ReviseLibV2Sample
    PRIVATE
        ${CLANG_INCLUDE_DIRS}
        ${LLVM_INCLUDE_DIRS}
)
target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example1.cpp)
target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example2.cpp)
#target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example2-after.cpp)
target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example3.cpp)
#target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example3-after.cpp)
target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example4.cpp)
#target_sources(ReviseLibV2Sample PRIVATE ${CMAKE_CURRENT_LIST_DIR}/example4-after.cpp)
