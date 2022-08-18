#pragma once
#include "BaseComponent.h"
#include "HelperStructs.h"

namespace dae
{
	class Texture2D;
}

struct SDL_Texture;
class TextureComponent : public BaseComponent
{
public:
	TextureComponent(const std::string& filepath, int amountOfCols = 1, int amountOfRows = 1);
	TextureComponent(SDL_Texture* pTexture, int amountOfCols = 1, int amountOfRows = 1);

	TextureComponent(const TextureComponent&) = delete;
	TextureComponent& operator=(const TextureComponent&) = delete;
	TextureComponent(TextureComponent&&) = delete;
	TextureComponent& operator=(TextureComponent&&) = delete;
	~TextureComponent();

	void SetIsFlipped(bool value) { m_IsFlipped = value; }
	bool GetIsFlipped()const { return m_IsFlipped; }

	dae::Texture2D* GetTexture()const { return m_pTexture; }
	void SetTexture(const std::string& filename);

	void SetDestinationRectDimensions(const Vector2& dst);
	Rect GetDestinationRect()const;
	void SetSourceRect(const Rect& src);
	Rect GetSourceRect()const;

	void CalculateSourceRect(int imagePartIndex);
	void CalculateSourceRect(int col, int row);

	int GetTextureWidth()const { return m_Width; };
	int GetTextureHeight()const { return m_Height; };

	int GetImagePartWidth()const { return m_Width / m_AmountOfCols; };
	int GetImagePartHeight()const { return m_Height / m_AmountOfRows; };


	void UpdateTexture();
private:
	dae::Texture2D* m_pTexture;
	Rect m_DestinationRect{};
	Rect m_SourceRect{};

	int m_Width{};
	int m_Height{};

	int m_AmountOfRows{ 1 };
	int m_AmountOfCols{ 1 };

	bool m_IsFlipped{ false };
	bool m_IsInChargeOfDeletion{ false };

	void CalculateDimension();
};

