/*
	Copyright(c) 2024 Devon Artmeier

	Permission to use, copy, modify, and /or distribute this software
	for any purpose with or without fee is hereby granted.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
	WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIE
	WARRANTIES OF MERCHANTABILITY AND FITNESS.IN NO EVENT SHALL THE
	AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
	DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
	PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
	TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
	PERFORMANCE OF THIS SOFTWARE.
*/

#include "shared.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Usage: sonic_cd_file_tool -r [region] -i [ip] -s [sp] -p [patches] [folder]" << std::endl << std::endl <<
		             "           -r [region]  - Region setting (Japan/USA/Europe)" << std::endl <<
		             "           -i [ip]      - Initial program file" << std::endl <<
		             "           -s [sp]      - System program file" << std::endl <<
		             "           -p [patches] - Patches folder" << std::endl <<
		             "           [folder]     - Folder to scan" << std::endl << std::endl;
		return -1;
	}

	try {
		std::string region;
		std::string ip;
		std::string sp;
		std::string patches;
		std::string folder;

		for (int i = 1; i < argc; i++) {
			if (CheckArgument(argc, argv, i, "r")) {
				if (!region.empty()) {
					throw std::runtime_error("Region setting already defined.");
				}
				region = argv[i];
				continue;
			}

			if (CheckArgument(argc, argv, i, "i")) {
				if (!ip.empty()) {
					throw std::runtime_error("Initial program file already defined.");
				}
				ip = argv[i];
				continue;
			}

			if (CheckArgument(argc, argv, i, "s")) {
				if (!sp.empty()) {
					throw std::runtime_error("System program file already defined.");
				}
				sp = argv[i];
				continue;
			}

			if (CheckArgument(argc, argv, i, "p")) {
				if (!patches.empty()) {
					throw std::runtime_error("Patches folder already defined.");
				}
				patches = argv[i];
				continue;
			}

			if (!folder.empty()) {
				throw std::runtime_error("Folder already defined.");
			}
			folder = argv[i];
		}

		if (ip.empty()) {
			throw std::runtime_error("Initial program file not defined.");
		}
		if (sp.empty()) {
			throw std::runtime_error("System program file not defined.");
		}
		if (patches.empty()) {
			throw std::runtime_error("Patches folder not defined.");
		}
		if (folder.empty()) {
			throw std::runtime_error("Scan folder not defined.");
		}

		if (!std::filesystem::exists(ip)) {
			throw std::runtime_error(("\"" + ip + "\" does not exist.").c_str());
		}
		if (!std::filesystem::exists(sp)) {
			throw std::runtime_error(("\"" + sp + "\" does not exist.").c_str());
		}
		if (!std::filesystem::exists(patches)) {
			throw std::runtime_error(("\"" + patches + "\" does not exist.").c_str());
		}
		if (!std::filesystem::exists(folder)) {
			throw std::runtime_error(("\"" + folder + "\" does not exist.").c_str());
		}

		if (region.empty()) {
			throw std::runtime_error("Region setting not defined.");
		} else if (StringToLower(region).compare("japan") == 0) {
			ProcessFilesJapan(ip, sp, patches, folder);
		} else if (StringToLower(region).compare("usa") == 0) {
			ProcessFilesUsa(ip, sp, patches, folder);
		} else if (StringToLower(region).compare("europe") == 0) {
			ProcessFilesEurope(ip, sp, patches, folder);
		} else {
			throw std::runtime_error(("Invalid region setting \"" + region + "\".").c_str());
		}
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}
