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

void ProcessFiles(const std::string& ip, const std::string& sp, const unsigned long ip_crc32, const unsigned long sp_crc32, const std::string& folder,
                  const std::string& patches_path, const FileHash* file_hashes, const size_t file_hash_count)
{
	unsigned char* file_data = nullptr;
	size_t         file_size = 0;

	ReadFileData(ip, file_data, file_size);
	if (CalcCrc32(file_data, file_size) != ip_crc32) {
		std::cout << "Initial program file has differences." << std::endl;
	}
	delete[] file_data;

	ReadFileData(sp, file_data, file_size);
	if (CalcCrc32(file_data, file_size) != sp_crc32) {
		std::cout << "System program file has differences." << std::endl;
	}
	delete[] file_data;

	Patches patches;

	
	if (!std::filesystem::exists(patches_path)) {
		std::cout << "\"" + patches_path + "\" does not exist." << std::endl;
	} else {
		for (const auto& patch_entry : std::filesystem::directory_iterator(patches_path)) {
			std::string patch_file = patch_entry.path().filename().string();
		
			for (const auto& file_entry : std::filesystem::directory_iterator(folder)) {
				std::string file_name   = file_entry.path().filename().string();
				size_t      name_length = file_name.length();

				if (StringStartsWith(patch_file, file_name) && patch_file.length() > name_length && patch_file[name_length] == '.') {
					std::string patch_address = patch_file.substr(++name_length);
					size_t      separator     = patch_address.find('.', name_length);
					if (separator != std::string::npos) {
						patch_address = patch_address.substr(separator + 1);
					}

					Patch patch = { patches_path + "/" + patch_file, std::stoull(patch_address, nullptr, 16) };
					if (patches.find(file_name) != patches.end()) {
						patches[file_name].push_back(patch);
					} else {
						patches[file_name] = { patch };
					}
				}
			}
		}
	}

	for (const auto& file_entry : std::filesystem::directory_iterator(folder)) {
		std::string file_name = file_entry.path().filename().string();
		ReadFileData(file_entry.path().string(), file_data, file_size);

		bool found = false;
		for (int i = 0; i < file_hash_count; i++) {
			if (file_name.compare(file_hashes[i].file) == 0) {
				unsigned long crc32 = CalcCrc32(file_data, file_size);
				found = true;

				for (const auto& file_patch : patches) {
					if (file_patch.first.compare(file_name) == 0) {
						for (const auto& patch : file_patch.second) {
							std::ifstream patch_file(patch.file, std::ios::in | std::ios::binary);

							patch_file.seekg(0, std::ios_base::end);
							size_t patch_size = patch_file.tellg();
							patch_file.seekg(0, std::ios_base::beg);

							if (patch_size <= file_size - patch.address) {
								patch_file.read(reinterpret_cast<char*>(file_data + patch.address), patch_size);
							}
						}
						break;
					}
				}
				unsigned long crc32_patched = CalcCrc32(file_data, file_size);

				if (crc32_patched != file_hashes[i].crc32) {
					std::cout << "\"" << file_name << "\" has differences." << std::endl;
				} else if (crc32 != crc32_patched) {
					std::ofstream file_write(file_entry.path().string(), std::ios::out | std::ios::binary);
					if (!file_write.is_open()) {
						std::cout << "Failed to open \"" << file_entry.path().string() << "\" for writing." << std::endl;
					} else {
						file_write.write(reinterpret_cast<char*>(file_data), file_size);
						std::cout << "Patched \"" << file_name << "\"." << std::endl;
					}
				}
				break;
			}
		}

		if (!found) {
			std::cout << "\"" << file_name << "\" is not from Sonic CD." << std::endl;
		}
		delete[] file_data;
	}
}