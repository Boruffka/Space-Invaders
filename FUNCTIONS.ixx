
module;

import CONSTANTS;
import <concepts>;
import <filesystem>;
import <thread>;

import <iostream>;
import <string>;
import <chrono>;
import <ctime>;
import <fstream>;
import <mutex>;

export module FUNCTIONS;
import <SFML/Graphics.hpp>;
import <SFML/System.hpp>;

export namespace FUNCTIONS 
{
	template <typename T>
	requires std::integral <T> || std::floating_point<T>
	T clamp(T& value, T min, T max)
	{
		if (value > max)
		{
			value = max;
			return max;
		}
		if (value < min)
		{
			value = min;
			return min;
		}

		return value;
	}

	void loadTexture(sf::RectangleShape& sprite, const sf::Texture& texture)
	{
		sprite.setTexture(&texture);
		sprite.setSize(sf::Vector2f(
			static_cast<float>(texture.getSize().x),
			static_cast<float>(texture.getSize().y)
		));
	}

	std::mutex logMutex;
	bool logText(const std::string& text = " ")
	{
		std::filesystem::path logPath = LOG_FILE_PATH;
		try {
			std::lock_guard<std::mutex> lock(logMutex);

			if (!logPath.parent_path().empty() && !std::filesystem::exists(logPath.parent_path()))
			{
				std::filesystem::create_directories(logPath.parent_path());
			}

			std::ofstream logFile(logPath, std::ios::app);
			if (!logFile) 
			{
				std::cout << "Failed to open log file: " << logPath << "\n";
				return false;
			}

			std::cout << text << "\n";
			logFile << text << "\n";

			return true;
		}
		catch (const std::exception& e) {
			std::cout << "Exception appending to log: " << e.what() << "\n";
			return false;
		}
	}

	void debugLog(const std::string& text)
	{
		std::thread([text]() {
			logText(text);
			}).detach();
	}
}



