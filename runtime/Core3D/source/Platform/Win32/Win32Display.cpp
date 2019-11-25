#include "Wanlix/Platform/Win32/Win32Display.h"
#include <codecvt>

namespace Wanlix
{
    thread_local static std::vector<IDisplay::UniquePtr>* gDisplayListRef = nullptr;
    static BOOL CALLBACK Win32MonitorEnumProc(
        HMONITOR monitor,
        HDC hDC,
        LPRECT rect,
        LPARAM data
    )
    {
        if (gDisplayListRef)
        {
            gDisplayListRef->push_back(Win32Display::Create(monitor));
            return TRUE;
        }
        return FALSE;
    }

    std::vector<IDisplay::UniquePtr> IDisplay::List()
    {
        std::vector<IDisplay::UniquePtr> displayList;

        gDisplayListRef = &displayList;
        ::EnumDisplayMonitors(nullptr, nullptr, Win32MonitorEnumProc, 0);
        gDisplayListRef = nullptr;

        return displayList;
    }

    IDisplay::UniquePtr IDisplay::Primary()
    {
        auto monitor = MonitorFromPoint({}, MONITOR_DEFAULTTOPRIMARY);
        return Win32Display::Create(monitor);
    }

    Win32Display::UniquePtr Win32Display::Create(HMONITOR monitor)
    {
        return std::unique_ptr<Win32Display>(new Win32Display(monitor));
    }

    Win32Display::Win32Display(HMONITOR monitor)
        : mMonitor(monitor)
    {}

    bool Win32Display::IsPrimary() const
    {
        MONITORINFO info;
        GetInfo(info);
        return ((info.dwFlags & MONITORINFOF_PRIMARY) != 0);
    }

    std::string Win32Display::GetDeviceName() const
    {
        MONITORINFOEX infoEx;
        GetInfo(infoEx);
        #ifdef UNICODE
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
        return conv.to_bytes(infoEx.szDevice);
        #else
        return std::string(infoEx.szDevice);
        #endif
    }

    Offset Win32Display::GetOffset() const
    {
        MONITORINFO info;
        GetInfo(info);
        return 
        {
            static_cast<int32_t>(info.rcMonitor.left),
            static_cast<int32_t>(info.rcMonitor.top),
        };
    }

    bool Win32Display::ResetDisplayMode()
    {
        // Get display device name
        MONITORINFOEX infoEx;
        GetInfo(infoEx);

        // Change settings for this display to default
        auto result = ChangeDisplaySettingsEx(infoEx.szDevice, nullptr, nullptr, 0, nullptr);

        return (result == DISP_CHANGE_SUCCESSFUL);
    }

    static void Convert(DEVMODE& dst, const DisplayModeDescriptor& src)
    {
        dst.dmPelsWidth = static_cast<DWORD>(src.resolution.width);
        dst.dmPelsHeight = static_cast<DWORD>(src.resolution.height);
        dst.dmDisplayFrequency = static_cast<DWORD>(src.refreshRate);
    }

    bool Win32Display::SetDisplayMode(const DisplayModeDescriptor& displayModeDesc)
    {
        // Get display device name
        MONITORINFOEX infoEx;
        GetInfo(infoEx);

        // Change settings for this display
        DEVMODE devMode = {};
        {
            devMode.dmSize = sizeof(devMode);
            devMode.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY);
            Convert(devMode, displayModeDesc);
        }
        auto result = ChangeDisplaySettingsEx(infoEx.szDevice, &devMode, nullptr, CDS_FULLSCREEN, nullptr);

        return (result == DISP_CHANGE_SUCCESSFUL);
    }

    static void Convert(DisplayModeDescriptor& dst, const DEVMODE& src)
    {
        dst.resolution.width = static_cast<std::uint32_t>(src.dmPelsWidth);
        dst.resolution.height = static_cast<std::uint32_t>(src.dmPelsHeight);
        dst.refreshRate = static_cast<std::uint32_t>(src.dmDisplayFrequency);
    }

    DisplayModeDescriptor Win32Display::GetDisplayMode() const
    {
        // Get display device name
        MONITORINFOEX infoEx;
        GetInfo(infoEx);

        // Get current display settings
        DEVMODE devMode;
        devMode.dmSize = sizeof(devMode);

        if (EnumDisplaySettings(infoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode) != FALSE)
        {
            DisplayModeDescriptor displayModeDesc;
            Convert(displayModeDesc, devMode);
            return displayModeDesc;
        }

        return {};
    }

    std::vector<DisplayModeDescriptor> Win32Display::GetSupportedDisplayModes() const
    {
        std::vector<DisplayModeDescriptor> displayModeDescs;

        // Get display device name
        MONITORINFOEX infoEx;
        GetInfo(infoEx);

        // Enumerate all display settings for this display
        const DWORD fieldBits = (DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY);

        DEVMODE devMode;
        devMode.dmSize = sizeof(devMode);

        for (DWORD modeNum = 0; EnumDisplaySettings(infoEx.szDevice, modeNum, &devMode) != FALSE; ++modeNum)
        {
            // Only enumerate display settings where the width, height, and frequency fields have been initialized
            if ((devMode.dmFields & fieldBits) == fieldBits)
            {
                DisplayModeDescriptor outputDesc;
                Convert(outputDesc, devMode);
                displayModeDescs.push_back(outputDesc);
            }
        }

        // Sort final display mode list and remove duplciate entries
        FinalizeDisplayModes(displayModeDescs);

        return displayModeDescs;
    }

    void Win32Display::GetInfo(MONITORINFO& info) const
    {
        info.cbSize = sizeof(info);
        GetMonitorInfo(mMonitor, &info);
    }

    void Win32Display::GetInfo(MONITORINFOEX& info) const
    {
        info.cbSize = sizeof(info);
        GetMonitorInfo(mMonitor, &info);
    }
}