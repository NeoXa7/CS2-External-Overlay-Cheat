#pragma once
#include <Globals/Includes.hpp>

VOID ShowErrorBox(const std::wstring& errorMessage, const std::wstring& errorTitle = L"Error")
{
    MessageBoxW(nullptr, errorMessage.c_str(), errorTitle.c_str(), MB_ICONERROR | MB_OK);
}

INT ShowWarningBox(const std::wstring& warningMessage, const std::wstring& warningTitle = L"Warning")
{
    int result = MessageBoxW(nullptr, warningMessage.c_str(), warningTitle.c_str(), MB_ICONWARNING | MB_OK);
    return result;
}

VOID ShowMessage(const std::wstring& message, const std::wstring& messageTitle = L"Info")
{
    std::thread([message, messageTitle]() {
        MessageBoxW(nullptr, message.c_str(), messageTitle.c_str(), MB_ICONWARNING | MB_OK);
        }).detach();
}