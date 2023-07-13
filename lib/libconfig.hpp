#pragma once

#define _LIBCONFIG_VERBOSE_

#ifdef _LIBCONFIG_VERBOSE_
#include <iostream>
#endif

#include <Windows.h>
#include <dpapi.h>

#include <filesystem>
#include <array>
#include <string>

#pragma comment(lib, "crypt32.lib")

typedef unsigned char BYTE;

namespace libconfig
{
	constexpr unsigned short current_version = 1;
	constexpr unsigned long epoch = 1688594400; //TODO
	const std::array<char, 6> config_signature = { 0x00, 0x69, 0x42, 0x00, 0x02, 0x03 };

	namespace multiplatform {
		namespace windows {
			bool read_file(std::filesystem::path path, BYTE* data, size_t bufLength);
			bool write_file(std::filesystem::path path, BYTE* data, size_t bufLength);
			bool get_file_length(std::filesystem::path path, size_t* lpBufLength);
		}

		bool get_file_length(std::filesystem::path path, size_t* lpBufLength);
		bool read_file(std::filesystem::path path, BYTE* data, size_t bufLength);
		bool write_file(std::filesystem::path path, BYTE* data, size_t bufLength);
	}

	namespace logger {
		static void log(std::string error) {
#ifdef _LIBCONFIG_VERBOSE_
			std::cerr << error << std::endl;
#endif
		}
	}
	struct ConfigurationHeader {
		char magic[6]; //0x00 0x69 0x42 0x00 0x02 0x03
		unsigned short version;
		unsigned long stamp;
		unsigned long buf_size;
		unsigned long data_offset;
	};

	template <typename T>
	class ConfigurationLoader {

	private:
		T m_data;
		std::string m_project_name;
	public:
		ConfigurationLoader(std::string project_name) {
			this->m_project_name = project_name;
			this->m_data = { 0 };
		}

		std::filesystem::path get_file_path() {
			char* env;
			unsigned long long size;
			_dupenv_s(&env, &size, "LOCALAPPDATA");

			return std::filesystem::path(env) / this->m_project_name / "config.bin";
		}

		std::tuple<BYTE*, unsigned long long> uncipher_data(BYTE* buffer, size_t bufLength) {
			DATA_BLOB in;

			in.pbData = buffer;
			in.cbData = (DWORD)bufLength;

			DATA_BLOB out = { 0 };

			bool success = CryptUnprotectData(&in, nullptr, nullptr, nullptr, NULL, NULL, &out);
			if (!success) {
				return { nullptr, 0 };
			}

			return { out.pbData, (size_t)out.cbData };
		}

		std::tuple<BYTE*, unsigned long long> cipher_data(BYTE* buffer, size_t bufLength) {

			DATA_BLOB blob;
			blob.pbData = buffer;
			blob.cbData = (DWORD)bufLength;

			DATA_BLOB out;

			bool cryptSuccess = CryptProtectData(&blob, NULL, NULL, NULL, NULL, CRYPTPROTECT_LOCAL_MACHINE, &out);

			if (!cryptSuccess) {
				return { nullptr, 0 };
			}

			return { out.pbData, (size_t)out.cbData };
		}

		T* data() {
			return &this->m_data;
		}

		bool exists() {
			std::filesystem::path config_path = this->get_file_path();

			return std::filesystem::exists(config_path);
		}

		bool initialize(T data) {
			if (this->exists()) {
				logger::log("file already exists, cant initialize");
				return false;
			}

			this->m_data = data;

			return write();
		}

		bool write() {
			size_t dataLength = sizeof(ConfigurationHeader) + sizeof(T);
			BYTE* buffer = new BYTE[dataLength];

			ConfigurationHeader header;
			header.version = current_version;
			header.stamp = epoch;
			header.buf_size = (unsigned long)sizeof(T);
			header.data_offset = offsetof(ConfigurationHeader, data_offset) + sizeof(header.data_offset);
			memcpy(&header.magic, (const void*)config_signature.data(), config_signature.size());
			memcpy(buffer, &header, sizeof(header));
			memcpy(buffer + sizeof(header), this->data(), sizeof(T));

			auto [out, cryptedDataLength] = this->cipher_data(buffer, dataLength);

			bool success = libconfig::multiplatform::write_file(this->get_file_path(), out, cryptedDataLength);

			if (!success) {
				logger::log("failed to write file");
			}

			delete[] buffer;

			return success;
		}


		bool read() {
			if (!this->exists()) {
				logger::log("file does not exists");
				return false;
			}

			std::filesystem::path file_path = this->get_file_path();

			size_t fileLength;

			if (!libconfig::multiplatform::get_file_length(file_path, &fileLength)) {
				logger::log("failed to get file length");
				return false;
			}

			BYTE* buffer = new BYTE[fileLength];

			if (!libconfig::multiplatform::read_file(file_path, buffer, fileLength)) {
				logger::log("failed to read file");
				return false;
			}

			auto [cipherBuffer, cipherBufLength] = this->uncipher_data(buffer, fileLength);

			if (!cipherBuffer)
			{
				logger::log("failed to uncipher data");
				return false;
			}

			ConfigurationHeader* header = (ConfigurationHeader*)cipherBuffer;

			for (unsigned int i = 0; i < (unsigned int)config_signature.size(); i++) {
				if (header->magic[i] != config_signature[i]) {
					logger::log("signature mismatch");
					return false;
				}
			}

			unsigned long dataSize = header->buf_size;

			T* data = (T*)(cipherBuffer + header->data_offset);

			this->m_data = *data;

			return true;
		}
	};

}