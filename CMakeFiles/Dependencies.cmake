include(FetchContent)

function(addExternalDependency name url tag)
    FetchContent_Declare(
        ${name}
        GIT_REPOSITORY ${url}
        GIT_TAG ${tag}
    )
    FetchContent_MakeAvailable(${name})
    list(APPEND ${PROJECT_NAME}_LIBRARIES ${name})
endfunction()

addExternalDependency(
    FlockFlow
    https://github.com/TL044CN/FlockFlow.git
    v1.0.3
)

addExternalDependency(
    DoveDispatch
    https://github.com/TL044CN/DoveDispatch.git
    v1.0.5
)
