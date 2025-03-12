ADD_TARGET(
        MODE STATIC
        SOURCE
        "${PROJECT_SOURCE_DIR}/include/MyFG"
        INC
        "${PROJECT_SOURCE_DIR}/include"
        LIB
        My::MyGraphviz_core
)