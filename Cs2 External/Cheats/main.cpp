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

    Memory::ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CS2::ProcID);
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

    MSG msg{};
    while (Flags::IsRunning)
    {
      //  std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) Flags::IsRunning = false;
        }

        if (!Flags::IsRunning) break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (Flags::IsVisible)
        {
            LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
            exStyle &= ~WS_EX_TRANSPARENT; // remove WS_EX_TRANSPARENT
            exStyle &= ~WS_EX_LAYERED; // remove WS_EX_TRANSPARENT
            SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
        }
        else
        {
            LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
            exStyle |= WS_EX_TRANSPARENT; // add WS_EX_TRANSPARENT
            exStyle |= WS_EX_LAYERED; // add WS_EX_TRANSPARENT
            SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
        }

        if (CS2::ProcID > 0)
        {
            player.UpdateLocalPlayer();
            game.UpdateGameVars();

            CHEATS::ProcessCheatInputs();
            CHEATS::InitializeBasicCheats();

            RenderMenu();
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep for 1 ms		

            if (!PM.IsProcessRunning(CS2::ProcID))
            {
                Flags::IsRunning = false;
            }
        }

        ImGui::Render();
        const float color[4]{ 0.f, 0.f, 0.f, 0.f };
        device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
        device_context->ClearRenderTargetView(render_target_view, color);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        swap_chain->Present(0U, 0U);
    }
    
    CleanUp(swap_chain, device, device_context, render_target_view, window, {});

    return 0;
}
