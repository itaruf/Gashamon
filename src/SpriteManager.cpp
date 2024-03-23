#include "SpriteManager.hpp"

std::shared_ptr<Sprite> SpriteManager::Get(const std::string& name) const
{
	auto it = m_sprites.find(name);
	if (it == m_sprites.end())
		return {}; //< Syntaxe pour construire l'objet par défaut sans avoir besoin de retaper le type, équivalent de return std::shared_ptr<Sprite>();
	return it->second;
}

void SpriteManager::Purge()
{
	for (auto it = m_sprites.begin(); it != m_sprites.end();)
	{
		const auto& sprite = it->second;
		if (sprite.use_count() > 1)
			++it;
		else
			it = m_sprites.erase(it);
	}
}

void SpriteManager::Register(std::string name, std::shared_ptr<Sprite> sprite)
{
	m_sprites.insert_or_assign(std::move(name), std::move(sprite));
	// équivalent moins beau: m_sprites[std::move(name)] = std::move(sprite);
}

std::unordered_map<std::string, std::shared_ptr<Sprite>>& SpriteManager::GetMap() {
	return (m_sprites);
}
