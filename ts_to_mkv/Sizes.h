#pragma once
#include <ostream>
#include <array>
#include <string>
#include <cmath>
#include <iomanip>

namespace Size {
	struct Size_t {
		Size_t(const uint16_t base, const std::array<std::wstring, 6>& size_strings, uintmax_t size = 0)
			: m_base(base), m_size_strings(size_strings), m_size(size) {}

		size_t get_power_of_size() const {
			if (m_size == 0) return 0;
			size_t i = 0;
			for (; i < m_size_strings.size(); ++i) {
				if (m_size < std::pow(m_base, i + 1))
					break;
			}
			return i;
		}

		const uint16_t m_base;
		const std::array<std::wstring, 6>& m_size_strings;
		uintmax_t m_size;

		friend std::wostream& operator<<(std::wostream& out, const Size_t& obj);		
	};

	struct Bytes : public Size_t {
		const static inline std::array<std::wstring, 6> size_strings = {
			L"B",L"KB",L"MB",L"GB",L"TB",L"PB"
		};
		Bytes(uintmax_t size = 0) : Size_t(1'000, size_strings, size) {};
	};

	struct Bits : public Size_t {
		const static inline std::array<std::wstring, 6> size_strings = {
			L"b",L"KiB",L"MiB",L"GiB",L"TiB",L"PiB"
		};
		Bits(uintmax_t size = 0) : Size_t(1'024, size_strings, size) {};
	};

	std::wostream& operator<<(std::wostream& out, const Size_t& obj) {
		size_t i = obj.get_power_of_size();
		float size = obj.m_size / std::pow(obj.m_base, i);
		const auto prev_iosflags = std::cout.flags();
		const auto prev_precision = std::cout.precision();
		out << std::setiosflags(std::ios::fixed) << std::setprecision(2)
			<< size
			<< std::setiosflags(prev_iosflags) << std::setprecision(prev_precision)
			<< " " << obj.m_size_strings[i];
		return out;
	}
}

