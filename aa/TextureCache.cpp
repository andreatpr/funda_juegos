#include "TextureCache.h"
#include "ImageLoader.h"
TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath)
{
	/*map<string, GLTexture>::iterator mit = textureMap.find(texturePath);*/
	auto mit = textureMap.find(texturePath);
	if (mit == textureMap.end()) {
		GLTexture texture = ImageLoader::loadPng(texturePath);
		//op1
		/*pair<string, GLTexture> newPair(texturePath, texture);
		textureMap.insert(newPair);*/
		//op2
		textureMap[texturePath] = texture;
		return texture;
	}
	return mit->second;
}
