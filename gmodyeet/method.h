#pragma once

template<typename out, class type>
inline out method(size_t index, type* self)  noexcept
{
	return reinterpret_cast<out>((*reinterpret_cast<void***>(self))[index]);
}