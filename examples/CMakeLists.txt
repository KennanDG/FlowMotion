add_executable(flowmotion_basic_example
    basic_pipeline.cpp
)

target_link_libraries(
    flowmotion_basic_example
    PRIVATE
        FlowMotion::flowmotion
)
