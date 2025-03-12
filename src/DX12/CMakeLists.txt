IF (NOT MyFG_BUILD_DX12)
    RETURN()
ENDIF ()

ADD_TARGET(
        MODE STATIC
        SOURCE
        "${PROJECT_SOURCE_DIR}/include/MyFG/DX12"
        LIB
        My::MyFG_core
        My::MyDX12_core
)