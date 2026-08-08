// 1. 对当前文件夹中显示的文件和目录进行自动排序（a-z）
// 2. 为自动排序后的结果添加序号（1-n）

#include <filesystem>
#include <iostream>
#include <map>
#include <string>

namespace fs = std::filesystem;

int main() {
  std::string path = "./";
  std::map<std::string, uintmax_t> file_list;

  std::cout << "Sorting..." << std::endl;

  try {
    if (fs::exists(path) && fs::is_directory(path)) {
      for (const auto &entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry)) {
          file_list[entry.path().filename().string()] = fs::file_size(entry);
        };
      }
      std::cout << "Sorting..." << std::endl;
      for (auto it = file_list.begin(); it != file_list.end(); ++it) {
        std::cout << "[File]: " << it->first << " \t [Size]: " << it->second
                  << " bytes" << std::endl;
      }
    }
  } catch (const fs::filesystem_error &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
