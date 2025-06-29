
module;

import <map>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;

export module assetManager;


export class AssetManager
{
public:
	AssetManager() {}

	~AssetManager() {}

	void LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	sf::Texture& GetTexture(std::string name)
	{
		return this->_textures.at(name);
	}

	void LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.openFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font& GetFont(std::string name)
	{
		return this->_fonts.at(name);
	}

	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};