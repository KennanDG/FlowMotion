add_executable(flowmotion_tests
    test_pipeline.cpp
)

target_link_libraries(
    flowmotion_tests
    PRIVATE
        FlowMotion::flowmotion
)

add_test(
    NAME flowmotion_tests
    COMMAND flowmotion_tests
)
