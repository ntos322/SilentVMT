#pragma once
#include <string>
#include <unordered_map>

/* for throw */
#include <stdexcept>

/* for std::function */
#include <functional>

class silent_vmt {
private:

	struct {

	/* a map to store the original functions
         * key: the index of the function in the vmt
         * value: addr of the orig function
        */
	std::unordered_map<int, std::uintptr_t>m_originalFunctions;

        /* a ptr to the original virtual method table (vmt) instance */
        std::uintptr_t* m_originalTable;

        /* the "shadowed" table */
        std::uintptr_t* m_copiedTable;

	};

public:

    /**
     * constructor for the silent_vmt class.
     *
     * @param ptr: a ptr to the instance of the class whose vmt is to be hooked.
     * this is used to create and set up the shadow vmt for the specified instance ptr
    */
    silent_vmt(std::uintptr_t* ptr, size_t sz = 0);

    /**
     * get the number of functions in the virtual table.
     * 
     * this func counts and returns the num of valid function ptrs
     * @return int the number of functions in the vmt
    */
    auto get_count() -> int;

    /**
     * hooks a func in the vmt at the specified index
     * @return true if successful, false otherwise
    */
    auto hook(int idx, std::uintptr_t hook) -> bool;

    /**
     * if you for some reason dont want to directly call the function with "call_original", you can get the address without calling the actual function
     * @return the orig func addr
    */
    auto get_original(int idx) -> std::uintptr_t {
        return m_originalFunctions[idx];
    }

    /**
     * call the original function by index
     * @return the original functions retval
    */
    template <typename T, typename ...arguments>
    auto call_original(int idx, arguments... args) -> T {
        auto addr = m_originalFunctions[idx];
        std::function<T(arguments...)> original_function = reinterpret_cast<T(*)(arguments...)>(addr);
        return original_function(args...);
    }

};
