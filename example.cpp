#include "silentvmt/vmt.hpp"
#include <iostream>

/* unique_ptr for handling the silent_vmt instance */
std::unique_ptr<silent_vmt>g_silentVmt;

/* the class that we will be "shadowing" */
class test {
public:
    virtual auto test_function() -> void {
        std::cout << "this is the original function called" << std::endl;
    }
};

auto hooked_function() -> void {
    std::cout << "hooked func called" << std::endl;

    /* return the original function (test::test_function) */
    return g_silentVmt->call_original<void>(0);
}

int main()
{
    /* create a new instance of the "test" class */
    auto class_instance = new test();

    /* convert the "test" class instance pointer to a uintptr_t pointer */
    auto ptr = (std::uintptr_t*)(class_instance);

    /* create a new instance of the "silent_vmt" class and pass the pointer to the "test" class instance */
    g_silentVmt = std::make_unique<silent_vmt>(ptr);

    /* hook the "test_function" in the "test" class (the function index is 0) and redirect it to "hooked_function" */
    g_silentVmt->hook(0, (std::uintptr_t)hooked_function);

    /* call the actual function; instead of only printing "this is the original function called," it should also print "hooked func called" */
    class_instance->test_function();

    /* alternatively, if you want to directly call the original function, you can do this */
    g_silentVmt->call_original<void>(0);

    /* or print the original function address? */
    std::cout << "original function addr: " << std::hex << std::showbase << g_silentVmt->get_original(0) << std::endl;
}


