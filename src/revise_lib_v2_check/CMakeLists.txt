add_library(ReviseLibV2Check MODULE "")
target_compile_options(ReviseLibV2Check PRIVATE -fno-rtti)
target_include_directories(ReviseLibV2Check
    PRIVATE
        ${CLANG_INCLUDE_DIRS}
        ${LLVM_INCLUDE_DIRS}
)
target_sources(ReviseLibV2Check PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ReviseLibV2APICheck.cpp)
