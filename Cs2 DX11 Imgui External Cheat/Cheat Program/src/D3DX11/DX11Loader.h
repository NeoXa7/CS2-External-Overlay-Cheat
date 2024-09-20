#pragma once
#include <D3DX11tex.h>

namespace D3DX11_Loader
{
	inline ID3D11ShaderResourceView* ImageResource = nullptr;

	inline bool LoadImageByMemory(ID3D11Device* device,
		unsigned char* image,
		size_t image_size,
		ID3D11ShaderResourceView** result)
	{
		D3DX11_IMAGE_LOAD_INFO information;
		ID3DX11ThreadPump* thread = nullptr;

		auto hres = D3DX11CreateShaderResourceViewFromMemory(device, image, image_size, &information, thread, result, 0);
		return (hres == S_OK);
	}
}