include("/home/dragomir/dev/Drago2D/Drago2D/build/drago2dTargets.cmake")
            set_property(
                TARGET drago2d
                APPEND PROPERTY
                    INTERFACE_INCLUDE_DIRECTORIES "/home/dragomir/dev/Drago2D/Drago2D"
            )
            add_compile_options("-std=c++17")