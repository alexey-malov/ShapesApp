#pragma once

class Texture;
class Font;

enum class TexturesID
{
	Icon,
	BackgroundFirst,
	BackgroundSecond,
};

enum class FontsID
{
	Main,
};

template <typename Resource, typename Identifier> class CResourceHolder;
typedef CResourceHolder<sf::Texture, TexturesID> TextureHolder;
typedef CResourceHolder<sf::Font, FontsID> FontHolder;