#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <string>


template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

void DIR(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();

			auto file_date = std::filesystem::last_write_time(entry);
			std::time_t cftime = to_time_t(file_date);
			std::string time = ctime(&cftime);
			time.pop_back(); 

			std::uintmax_t size;
			std::string file_size;
			if (std::filesystem::exists(entry) && std::filesystem::is_regular_file(entry))
			{
				size = std::filesystem::file_size(entry);
				file_size = std::to_string(size);
			}
			else
			{
				file_size = "";
			}
				
			std::string file_dir = "";
			if (std::filesystem::exists(entry) && std::filesystem::is_directory(entry))
				file_dir = "<DIR>";

			std::cout << time << std::setw(8) << std::right << file_dir <<
				std::setw(10) << std::right << file_size << " " << file_name << std::endl;
		}
	}
}

int main()
{
	DIR(std::filesystem::current_path());

	return 0;
}