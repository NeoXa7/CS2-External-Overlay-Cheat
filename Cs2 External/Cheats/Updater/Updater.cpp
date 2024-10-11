#include <Updater/Updater.h>

bool Updater::FileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

bool Updater::DownloadFile(const std::string& url, const std::string& fileName) {
    HINTERNET hInternet, hConnect;

    hInternet = InternetOpen(L"Updater", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << " [Updater] InternetOpen failed." << std::endl;
        return false;
    }

    hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        std::cerr << " [Updater] InternetOpenUrlA failed." << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        std::cerr << " [Updater] Failed to create local file." << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return false;
    }

    char buffer[4096];
    DWORD bytesRead;

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        outFile.write(buffer, bytesRead);
    }

    outFile.close();
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return true;
}

bool Updater::GetLastCommitInfo(string api, json& commit) {
    HINTERNET hInternet, hConnect;

    hInternet = InternetOpen(L"Updater", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        return false;
    }

    hConnect = InternetOpenUrlA(hInternet, api.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return false;
    }

    char buffer[4096];
    DWORD bytesRead;
    std::string commitData;

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        commitData.append(buffer, bytesRead);
    }

    json data;
    try {
        data = json::parse(commitData);
    }
    catch (const std::exception& e) {
        std::cout << " [Updater] Failed to parse JSON response from GitHub" << std::endl;
        return false;
    }

    if (data.empty())
        return false;

    if (data.is_array()) {
        json last_commit = data[0];
        json last_commit_author = last_commit["commit"]["author"];
        commit = last_commit_author;
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return true;
}

