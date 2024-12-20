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

static const FileHash file_hashes[] = {
	{ "ABS.TXT",      0xB45563C8 },
	{ "ATTACK.BIN",   0x4FC04719 },
	{ "ATTACK.MMD",   0x6FD5B665 },
	{ "BADEND.BIN",   0xD9337E36 },
	{ "BADEND.STM",   0x2D1723BD },
	{ "BIB.TXT",      0x2F6016F7 },
	{ "BRAMINIT.MMD", 0x9CA8CF4F },
	{ "BRAMMAIN.MMD", 0xE238B04F },
	{ "BRAMSUB.BIN",  0x8A0183E4 },
	{ "COME__.MMD",   0xB872B5C1 },
	{ "CPY.TXT",      0xB4AD0BDF },
	{ "DEMO11A.MMD",  0x50835D3B },
	{ "DEMO43C.MMD",  0x651CDC6C },
	{ "DEMO82A.MMD",  0xB53DEB6F },
	{ "DUMMY0.MMD",   0x38DDB6C9 },
	{ "DUMMY1.MMD",   0xE130FD8B },
	{ "DUMMY2.MMD",   0xC392EB8B },
	{ "DUMMY3.MMD",   0x937D41ED },
	{ "DUMMY4.MMD",   0xCD59D361 },
	{ "DUMMY5.MMD",   0x1A6E2CCA },
	{ "DUMMY6.MMD",   0x1A6E2CCA },
	{ "DUMMY7.MMD",   0x1A6E2CCA },
	{ "DUMMY8.MMD",   0x1A6E2CCA },
	{ "DUMMY9.MMD",   0x1A6E2CCA },
	{ "ENDING.MMD",   0xECBF68B1 },
	{ "GOODEND.BIN",  0xAFB6E590 },
	{ "GOODEND.STM",  0xE09BAF5C },
	{ "IPX___.MMD",   0xBB818F8F },
	{ "MDINIT.MMD",   0x5A081D10 },
	{ "NISI.MMD",     0xAC77FE53 },
	{ "OPEN_M.MMD",   0x2D182CC7 },
	{ "OPEN_S.BIN",   0x7165F3B9 },
	{ "OPN.STM",      0x09489D1C },
	{ "PLANET_D.BIN", 0x4D1278B1 },
	{ "PLANET_M.MMD", 0x911B092B },
	{ "PLANET_S.BIN", 0xFBD3DF11 },
	{ "PTEST.BIN",    0x15824E19 },
	{ "PTEST.MMD",    0x10A74611 },
	{ "PTEST.STM",    0xD29A3745 },
	{ "R11A__.MMD",   0xDC319AB2 },
	{ "R11B__.MMD",   0xBBA8D60C },
	{ "R11C__.MMD",   0x4415E7BD },
	{ "R11D__.MMD",   0xD65790B9 },
	{ "R12A__.MMD",   0x1C8853D8 },
	{ "R12B__.MMD",   0xEE0EBF79 },
	{ "R12C__.MMD",   0x3D9139DB },
	{ "R12D__.MMD",   0xD439D921 },
	{ "R13C__.MMD",   0xBA325B6A },
	{ "R13D__.MMD",   0x2F2D987B },
	{ "R31A__.MMD",   0x2F1542AF },
	{ "R31B__.MMD",   0xDA9CEF12 },
	{ "R31C__.MMD",   0x0666034C },
	{ "R31D__.MMD",   0xFD6F0095 },
	{ "R32A__.MMD",   0xC195DA57 },
	{ "R32B__.MMD",   0x7CECC32D },
	{ "R32C__.MMD",   0x538148DD },
	{ "R32D__.MMD",   0x31B0D6FA },
	{ "R33C__.MMD",   0x79791351 },
	{ "R33D__.MMD",   0x1D104F88 },
	{ "R41A__.MMD",   0x4C32F52D },
	{ "R41B__.MMD",   0xDCC2653E },
	{ "R41C__.MMD",   0x4CA861AA },
	{ "R41D__.MMD",   0xD3D8097F },
	{ "R42A__.MMD",   0xE2860B31 },
	{ "R42B__.MMD",   0xEE631CE2 },
	{ "R42C__.MMD",   0x69093B5E },
	{ "R42D__.MMD",   0xCF4D9E71 },
	{ "R43C__.MMD",   0x6C963E83 },
	{ "R43D__.MMD",   0x383CE14E },
	{ "R51A__.MMD",   0xBDC114E4 },
	{ "R51B__.MMD",   0xD58FD05F },
	{ "R51C__.MMD",   0x25AED238 },
	{ "R51D__.MMD",   0x6F509290 },
	{ "R52A__.MMD",   0x9C89518F },
	{ "R52B__.MMD",   0xCDB32B37 },
	{ "R52C__.MMD",   0x77634319 },
	{ "R52D__.MMD",   0xC4B23BA1 },
	{ "R53C__.MMD",   0xEE02DFFC },
	{ "R53D__.MMD",   0xEC452254 },
	{ "R61A__.MMD",   0x067C1A39 },
	{ "R61B__.MMD",   0x6D83996B },
	{ "R61C__.MMD",   0x2F01C8AD },
	{ "R61D__.MMD",   0xCDCE8D20 },
	{ "R62A__.MMD",   0xBD3F10AA },
	{ "R62B__.MMD",   0x05CA1DE5 },
	{ "R62C__.MMD",   0x26CD249E },
	{ "R62D__.MMD",   0x73EEB6E3 },
	{ "R63C__.MMD",   0xD56AD9CB },
	{ "R63D__.MMD",   0xD8AB624D },
	{ "R71A__.MMD",   0xAA0850C9 },
	{ "R71B__.MMD",   0x9B4EB26F },
	{ "R71C__.MMD",   0x27F28BCA },
	{ "R71D__.MMD",   0x90A8AC0B },
	{ "R72A__.MMD",   0x3A6400F9 },
	{ "R72B__.MMD",   0xDDA1F6C4 },
	{ "R72C__.MMD",   0xB1A27A03 },
	{ "R72D__.MMD",   0x3DCECD91 },
	{ "R73C__.MMD",   0x3EC4E1C9 },
	{ "R73D__.MMD",   0xE7638EE0 },
	{ "R81A__.MMD",   0x306E1B19 },
	{ "R81B__.MMD",   0x0A036342 },
	{ "R81C__.MMD",   0x249EE705 },
	{ "R81D__.MMD",   0xEF199293 },
	{ "R82A__.MMD",   0xE1DC12FE },
	{ "R82B__.MMD",   0xF1F1D50E },
	{ "R82C__.MMD",   0xBE2C7FFA },
	{ "R82D__.MMD",   0xB412188B },
	{ "R83C__.MMD",   0x7ACAB8DB },
	{ "R83D__.MMD",   0x883D7602 },
	{ "SNCBNK1B.BIN", 0x00AE686F },
	{ "SNCBNK3B.BIN", 0xF5997045 },
	{ "SNCBNK4B.BIN", 0x7350C0E5 },
	{ "SNCBNK5B.BIN", 0xE5D9F7DA },
	{ "SNCBNK6B.BIN", 0x943910A7 },
	{ "SNCBNK7B.BIN", 0x9704B43B },
	{ "SNCBNK8B.BIN", 0x53E611F0 },
	{ "SNCBNKB1.BIN", 0x736A03D5 },
	{ "SNCBNKB2.BIN", 0x9AF2C404 },
	{ "SOSEL_.MMD",   0x6305D309 },
	{ "SPEEND.MMD",   0xA134FDC5 },
	{ "SPMM__.MMD",   0x06CBB814 },
	{ "SPSS__.BIN",   0x9CD1FA5F },
	{ "SPX___.BIN",   0x50B7CA08 },
	{ "STSEL_.MMD",   0x16B57E37 },
	{ "THANKS_D.BIN", 0x99C0CB76 },
	{ "THANKS_M.MMD", 0x2108C368 },
	{ "THANKS_S.BIN", 0x363AC58C },
	{ "TITLEM.MMD",   0x73AB422E },
	{ "TITLES.BIN",   0x264E1733 },
	{ "VM____.MMD",   0xA46AE170 },
	{ "WARP__.MMD",   0xF1293A31 }
};

void ProcessFilesEurope(const std::string& ip, const std::string& sp, const std::string& patches, const std::string& folder)
{
	ProcessFiles(ip, sp, 0x0C5C4BB7, 0xC2051A81, folder, patches + "/europe", file_hashes, sizeof(file_hashes) / sizeof(FileHash));
}