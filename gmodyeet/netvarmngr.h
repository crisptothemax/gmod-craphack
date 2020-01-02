#pragma once
#include "Client.h"
#include <fstream>
#include <iostream>

class INetVarManager
{
public:
	INetVarManager(IBaseClient* pBaseClientDLL) {
		// pBaseClientDLL is basically your VClient018 interface. GetAllClasses is index 8. It returns a pointer to the first ClientClass
		pClientClassHead = pBaseClientDLL->GetAllClasses();
	}
	int GetOffset(const char* szTable, const char* szProp) {
		// Loops through ClientClasses by setting pClass = pClass->m_pNext at the iteration as long as pClass is not nullptr
		for (ClientClass* pClass = pClientClassHead; pClass; pClass = pClass->pNextClass) {
			// If it doesn't have a RecvTable then skip this iteration
			if (!pClass->Table) continue;
			RecvTable* pTable = pClass->Table;
			// Check if RecvTable name matches the one inputed, if not then skip this iteration
			if (strcmp(pTable->m_pNetTableName, szTable)) continue;
			// Loop through all props in the table. m_nProps is the number of RecvProps in the table. Note that the prefix is m_n, NOT m_p
			for (int i = 0; i < pTable->m_nProps; i++) {
				// Get a pointer to the current RecvProp
				RecvProp* pProp = &pTable->m_pProps[i];
				// If the prop's name matches the one inputed then return it's offset
				if (!strcmp(pProp->m_pVarName, szProp)) {
					// int GetOffset() const { return m_Offset; } OR just make all private variables public ¯\_(?)_/¯
					return pProp->GetOffset();
				}
			}
		}
		return 0;
	}
	const char* GetDataTypeFromEnum(int nEnum) {
		// There's an enum that stores the data type of the prop. It's useful. Haven't found a more "elegant" way to translate it to a string
		switch (nEnum) {
		case DPT_Int:
			return "int";
		case DPT_Float:
			return "float";
		case DPT_Vector:
			return "Vector";
		case DPT_VectorXY:
			return "Vector2";
		case DPT_String:
			return "const char*";
		default:
			return "void";
		}
	}

	void Dump() {
		std::ofstream o;
		o.open("netvardump.txt");

		o << std::hex;

		printf("dumping netvars..\n");

		// This function logs every RecvTable and every RecvProp. Starts off the same as the GetOffset function
		for (ClientClass* pClass = pClientClassHead; pClass; pClass = pClass->pNextClass) {
			// Because there's specific table we want to get there's no need to strcmp the name of the table
			if (!pClass->Table) continue;
			RecvTable* pTable = pClass->Table;
			for (int i = 0; i < pTable->m_nProps; i++) {
				RecvProp* pProp = &pTable->m_pProps[i];
				if (!pProp) continue;
				// This logs the RecvProp in the following style: NETVAR(void, baseclass, "DT_ExampleTable", "baseclass")
				o << GetDataTypeFromEnum(pProp->m_RecvType) << " - " << pTable->m_pNetTableName << " - " << pProp->m_pVarName << " = 0x" << GetOffset(pTable->m_pNetTableName, pProp->m_pVarName) << std::endl;
				//printf("NETVAR(%s, %s, \"%s\", \"%s\")\n", GetDataTypeFromEnum(pProp->m_RecvType), pProp->m_pVarName, pTable->m_pNetTableName, pProp->m_pVarName);
			}
		}

		o.close();
		printf("dumped netvars!\n");
	}
private:
	ClientClass* pClientClassHead;
};