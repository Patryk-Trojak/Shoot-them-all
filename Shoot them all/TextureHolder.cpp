#include "TextureHolder.h"



TextureHolder::TextureHolder()
{
	TextureHolder::loadTexture("missingTexture", ".\\Textures\\MissingTexture.jpg");
}


TextureHolder::~TextureHolder()
{
}

void TextureHolder::loadTexture(const std::string& id, const std::string& filepath)
{
	std::unique_ptr < sf::Texture > texture = std::make_unique< sf::Texture >();
	texture->loadFromFile(filepath);
	textureMap.insert(std::pair < std::string, std::unique_ptr <sf::Texture> >(id, std::move(texture)));
}

sf::Texture* TextureHolder::getPointerToTexture(const std::string& id) const
{
	auto found = textureMap.find(id);
	if (found != textureMap.end())
	{
		return found->second.get();
	}
	else
	{
		return textureMap.at("missingTexture").get();
	}
}

sf::Texture& TextureHolder::getTexture(const std::string& id) const
{
	auto found = textureMap.find(id);
	if (found != textureMap.end())
	{
		return *found->second;
	}
	else
	{
		std::cout << "Texture: " << id << "doesnt exist." << std::endl;
		return *textureMap.at("missingTexture");
	}
}
