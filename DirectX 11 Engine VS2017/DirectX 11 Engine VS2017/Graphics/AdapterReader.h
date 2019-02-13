#pragma once
#include "../Utils/ErrorLogger.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <vector> 


class AdapterData
{
public:
	AdapterData(IDXGIAdapter * pAdapter);
	IDXGIAdapter * pAdapter = nullptr;
	DXGI_ADAPTER_DESC description;
};

//========================
// Get all avaliable graphic card
//========================
class AdapterReader
{
public:
	static std::vector<AdapterData> GetAdapters();
private:
	static std::vector<AdapterData> adapters;
};