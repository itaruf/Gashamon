#pragma once

#include "Sprite.hpp"
#include <string>
#include <unordered_map>
#include <iostream>

class SpriteManager
{
	public:
		SpriteManager() = default;
		SpriteManager(const SpriteManager&) = default;
		SpriteManager(SpriteManager&&) noexcept = default;
		~SpriteManager() = default;

		std::shared_ptr<Sprite> Get(const std::string& name) const;

		void Purge();

		void Register(std::string name, std::shared_ptr<Sprite> sprite);

		SpriteManager& operator=(const SpriteManager&) = delete;
		SpriteManager& operator=(SpriteManager&&) = default;

		std::unordered_map<std::string, std::shared_ptr<Sprite>>& GetMap();

	private:
		std::unordered_map<std::string, std::shared_ptr<Sprite>> m_sprites;

};