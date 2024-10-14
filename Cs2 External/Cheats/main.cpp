#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <d3d11.h>
#include <Overlay/Overlay.hpp>
#include <Functions/Console.hpp>
#include <Interfaces/Loader.hpp>
#include <Memory/Memory.hpp>
#include <Memory/Handle.hpp>
#include <Overlay/ExeConfig.hpp>

HANDLE Memory::ProcessHandle = NULL;

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show)
{
    if (CS2::ProcID < 0)
    {
        ShowErrorBox(L"Process cs2.exe not found!");
    }

    if (FileExists("settings.json"))
    {
        LoadSettings("settings.json");
    }
    if (Flags::g_showConsole)
    {
        CreateConsoleWindow(L"Console");
        ShowTitle();
    }
    if (Flags::g_showWarningBox)
    {
        ShowWarningBox(L"We don't recommend using cheats. Use at your own risk.\nUsing cheats can get you banned.");
    }

    HANDLE SteamHandle = GetProcessHandle(L"steam.exe");
    if (!SteamHandle)
        return 1;

    Memory::ProcessHandle = GetCS2HandleFrom(SteamHandle);
    if (!Memory::ProcessHandle)
        return 1;

    HWND window = InitializeWindow(instance, cmd_show);
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* device_context = nullptr;
    IDXGISwapChain* swap_chain = nullptr;
    ID3D11RenderTargetView* render_target_view = nullptr;

    if (!InitializeDirectX(window, &device, &device_context, &swap_chain, &render_target_view))
        return 1;

    InitializeImGui(window, device, device_context);
    updater.UpdateOffsets();
    RunMainLoop(window, device_context, swap_chain, render_target_view);  // Main game loop
    CleanUp(swap_chain, device, device_context, render_target_view, window, {});

    return 0;
}
