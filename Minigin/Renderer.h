#pragma once
#include "Singleton.h"

class TextureComponent;
namespace dae
{
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const TextureComponent* pTexture, const int x, const int y) const;
		void RenderTexture(const TextureComponent* pTexture, const int x, const int y, const int width, const int height) const;
		void RenderTexture(const TextureComponent* pTexture, const SDL_Rect& srcRect, const int x, const int y) const;
		void RenderTexture(const TextureComponent* pTexture, const SDL_Rect& srcRect, const int x, const int y, const int width, const int height) const;
		void RenderTexture(const TextureComponent* pTexture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

