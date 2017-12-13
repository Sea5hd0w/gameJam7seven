#include "Sprites.h"

#include "LibraryCommunication.h"

#include "View.h"

map<string, tuple<SDL_Texture*, int>> Sprites::sprites;

Sprites::Sprites()
{
}


Sprites::~Sprites()
{
}

SDL_Texture* Sprites::addSprite(string path)
{
	if (Sprites::sprites.find(path) == Sprites::sprites.end())
	{
		SDL_Texture* sprite = SDL_CreateTextureFromSurface(View::renderer, SDL_LoadBMP(path.c_str()));
		if (sprite != NULL)
		{
			Sprites::sprites.insert(std::pair<string, tuple<SDL_Texture*, int>>(path, make_tuple(sprite, 0)));
		}
	}
	else
	{
		get<1>(Sprites::sprites.find(path)->second) = get<1>(Sprites::sprites.find(path)->second) + 1;
	}

	return get<0>(Sprites::sprites.find(path)->second);
}

void Sprites::deleteSprite(string path)
{
	if (Sprites::sprites.find(path) != Sprites::sprites.end())
	{
		if (get<1>(Sprites::sprites.find(path)->second) == 1)
		{
			SDL_DestroyTexture(get<0>(Sprites::sprites.find(path)->second));
			Sprites::sprites.erase(path);
			des("Sprite : [" + path + "] Delete");
		}
		else
		{
			get<1>(Sprites::sprites.find(path)->second) = get<1>(Sprites::sprites.find(path)->second) - 1;
		}
	}
}

int Sprites::getNbrSprites()
{
	return Sprites::sprites.size();
}
