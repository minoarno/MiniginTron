#include "MiniginPCH.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"

TextureComponent::TextureComponent(const std::string& filepath, int amountOfCols, int amountOfRows)
	: BaseComponent{}
	, m_pTexture{nullptr}
	, m_AmountOfCols{amountOfCols}
	, m_AmountOfRows{amountOfRows}
	, m_IsInChargeOfDeletion{ false }
{
	SetTexture(filepath);
}

TextureComponent::TextureComponent(SDL_Texture* pTexture, int amountOfCols, int amountOfRows)
	: BaseComponent{}
	, m_pTexture{ new dae::Texture2D{pTexture} }
	, m_IsInChargeOfDeletion{ true }
	, m_AmountOfCols{ amountOfCols }
	, m_AmountOfRows{ amountOfRows }
{
	CalculateDimension();
}

TextureComponent::~TextureComponent()
{
	if (m_IsInChargeOfDeletion)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	CalculateDimension();
}

void TextureComponent::SetDestinationRectDimensions(const Vector2& dst)
{
	m_DestinationRect.w = dst.x;
	m_DestinationRect.h = dst.y;
}

Rect TextureComponent::GetDestinationRect() const
{
	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	return Rect{int(pos.x),int(pos.y) ,m_DestinationRect.w,m_DestinationRect.h};
}

void TextureComponent::SetSourceRect(const Rect& src)
{
	m_SourceRect = src;
}

Rect TextureComponent::GetSourceRect() const
{
	return m_SourceRect;
}

void TextureComponent::CalculateSourceRect(int imagePartIndex)
{
	int colIndex{ imagePartIndex % m_AmountOfCols };
	int rowIndex{ imagePartIndex / m_AmountOfCols };

	CalculateSourceRect(colIndex, rowIndex);
}

void TextureComponent::CalculateSourceRect(int col, int row)
{
	int widthPart{ m_Width / m_AmountOfCols };
	int heightPart{ m_Height / m_AmountOfRows };

	m_SourceRect = Rect{ col * widthPart,row * heightPart,widthPart,heightPart };
}

void TextureComponent::CalculateDimension()
{
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
}
