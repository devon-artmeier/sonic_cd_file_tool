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

#ifndef PATCH_HPP
#define PATCH_HPP

struct FileHash
{
	const char*   file;
	unsigned long crc32;
};

struct Patch
{
	std::string        file;
	unsigned long long address;
};

typedef std::unordered_map<std::string, std::vector<Patch>> Patches;
typedef std::unordered_map<std::string, unsigned char*>     FileData;

extern void ProcessFiles      (const std::string& ip, const std::string& sp, const unsigned long ip_crc32, const unsigned long sp_crc32, const std::string& folder,
                               const std::string& patches_path, const FileHash* file_hashes, const size_t file_hash_count);
extern void ProcessFilesJapan (const std::string& ip, const std::string& sp, const std::string& patches, const std::string& folder);
extern void ProcessFilesUsa   (const std::string& ip, const std::string& sp, const std::string& patches, const std::string& folder);
extern void ProcessFilesEurope(const std::string& ip, const std::string& sp, const std::string& patches, const std::string& folder);

#endif // PATCH_HPP
