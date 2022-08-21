#pragma once
#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "Transform.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		ME_CORE_ERROR("SDL_CreateRenderer Error: ");
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	//imgui initialize
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	//Imgui destroy
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const TextureComponent* pTexture, const int x, const int y, float angle) const
{
	RenderTexture(pTexture, x, y, pTexture->GetTextureWidth(), pTexture->GetTextureHeight(), angle);
}

void dae::Renderer::RenderTexture(const TextureComponent* pTexture, const int x, const int y, const int width, const int height, float angle) const
{
	SDL_Rect dst{x,y,width,height};
	SDL_Point center{ int(x + width * .5f), int(y + height * .5f) };

	if (pTexture->GetIsFlipped())
	{
		SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetTexture()->GetSDLTexture(), nullptr, &dst, double(angle), &center, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetTexture()->GetSDLTexture(), nullptr, &dst, double(angle), &center, SDL_FLIP_NONE);
	}
}

void dae::Renderer::RenderTexture(const TextureComponent* pTexture, const SDL_Rect& srcRect, const int x, const int y, float angle) const
{
	RenderTexture(pTexture, srcRect,x, y, pTexture->GetTextureWidth(), pTexture->GetTextureHeight(), angle);
}

void dae::Renderer::RenderTexture(const TextureComponent* pTexture, const SDL_Rect& srcRect, const int x, const int y, const int width, const int height, float angle) const
{
	SDL_Rect dst{x,y,width,height};

	SDL_Point center{ int(x + width * .5f), int(y + height * .5f) };
	if (pTexture->GetIsFlipped())
	{
		SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetTexture()->GetSDLTexture(), &srcRect, &dst, angle, &center, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		SDL_RenderCopyEx(GetSDLRenderer(), pTexture->GetTexture()->GetSDLTexture(), &srcRect, &dst, angle, &center, SDL_FLIP_NONE);
	}

}

void dae::Renderer::RenderTexture(const TextureComponent* pTexture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, float angle) const
{
	RenderTexture(pTexture, srcRect, dstRect.x, dstRect.y, dstRect.w, dstRect.h,angle);
}
