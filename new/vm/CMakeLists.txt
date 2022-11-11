
set(sources
    src/Vm.c
    src/main.c
)

add_executable(vm ${sources})
target_include_directories(vm PRIVATE include)
