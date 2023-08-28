#include "vmt.hpp"

silent_vmt::silent_vmt(std::uintptr_t* ptr, size_t sz) {
	if (ptr == nullptr)
	   throw std::invalid_argument("ptr cannot be null bru");

	/* store the original vtable */
	m_originalTable = *(std::uintptr_t**)ptr;

	/* i wanted to do this just incase if someone wanted to manually specify the vmt size */
	if (!sz)
           sz = get_count();

	/* alloc a new "copy" of the vtable, this is where the "shadowing" starts (+ 1 because we need somewhere to store the ptr to the orig vmt) */
        m_copiedTable = new std::uintptr_t[sz + 1];

	/* copy the original vmt into the new vtable */
	std::memcpy(&m_copiedTable[1], m_originalTable, sz * sizeof(std::uintptr_t));

	/* update the instance's vmt ptr to our new "shadow" / "copy" */
	*ptr = (std::uintptr_t)&m_copiedTable[1];

}

auto silent_vmt::hook(int idx, std::uintptr_t hook) -> bool {
	auto original_function = m_originalTable[idx];
	if (!original_function)
		return false;

	m_originalFunctions.insert( { idx, original_function } );
	m_copiedTable[idx + 1] = hook;

	return true;
}

auto silent_vmt::get_count() -> int {
	int retval = 0;
	while (m_originalTable[retval] != 0)
		retval++;

	return retval;
}
