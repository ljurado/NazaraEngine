// Copyright (C) 2012 R�mi B�ges
// This file is part of the "Nazara Engine - DynaTerrain"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/DynaTerrain/Config.hpp>
#if NAZARA_DYNATERRAIN_MEMORYLEAKTRACKER || defined(NAZARA_DEBUG)
#include <Nazara/Core/Debug/MemoryLeakTracker.hpp>
#include <new>

void* operator new(std::size_t size)
{
	return NzMemoryManager::Allocate(size, false);
}

void* operator new[](std::size_t size)
{
	return NzMemoryManager::Allocate(size, true);
}

void operator delete(void* pointer) noexcept
{
	NzMemoryManager::Free(pointer, false);
}

void operator delete[](void* pointer) noexcept
{
	NzMemoryManager::Free(pointer, true);
}
#endif
