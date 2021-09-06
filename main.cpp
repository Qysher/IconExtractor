#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <Windows.h>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	if (argc == 0) return -1;

	for (int o = 1; o < argc; o++) {
		string arg = string(argv[o]);
		fs::path currentPath = fs::path(arg);
		if (currentPath.has_parent_path()) {
			string parentPath = currentPath.parent_path().string();
			string programName = currentPath.filename().string();
			string outputPath = "output\\" + programName;
			//cout << "programName: " << programName << endl;
			system(string("mkdir \"" + outputPath + "\"").c_str());
			//cout << string("iconsext.exe /save \"" + currentPath.string() + "\" \"output\\" + programName + "\" -icons") << endl;
			system(string("iconsext.exe /save \"" + currentPath.string() + "\" \"output\\" + programName + "\" -icons").c_str());

			vector<string> fileList;

			for (const fs::directory_entry& entry : fs::directory_iterator(outputPath)) {
				string fileName = entry.path().string();
				fileList.push_back(fileName);
			}

			for (string fileName : fileList) {
				//cout << "fileName: " << fileName << endl;
				system(string("ffmpeg.exe -i \"" + fileName + "\" \"" + fileName + ".png\"").c_str());
				system(string("del " + fileName).c_str());
			}
		}
	}

	return 0;
}