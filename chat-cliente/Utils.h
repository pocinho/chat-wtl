#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "stdafx.h"

void SubstituirEmWString(std::wstring& original, const std::wstring& procurar, const std::wstring& substituir)
{
	size_t pos = 0;
	while ((pos = original.find(procurar, pos)) != std::string::npos)
	{
		original.replace(pos, procurar.length(), substituir);
		pos += substituir.length();
	}
}

#endif // !UTILS_H



