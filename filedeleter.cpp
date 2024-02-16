#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

// Function to check if a given file is related to video games
bool isVideoGameFile(const fs::path& filePath) {
    static const std::vector<std::string> videoGameExtensions = {".exe", ".dll", ".iso", ".rom"};

    // Check if the file extension is in the list of video game extensions
    std::string extension = filePath.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return std::find(videoGameExtensions.begin(), videoGameExtensions.end(), extension) != videoGameExtensions.end();
}

// Function to delete files from the desktop recursively
void deleteDesktopFiles(const fs::path& directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            deleteDesktopFiles(entry.path()); // Recursive call for directories
        } else if (!isVideoGameFile(entry.path())) {
            fs::remove(entry.path()); // Delete the file if it's not related to video games
        }
    }
}

int main() {
    const fs::path desktopPath = fs::path(getenv("USERPROFILE")) / "Desktop";

    try {
        deleteDesktopFiles(desktopPath);
        std::cout << "All files except video game files deleted from the desktop." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}