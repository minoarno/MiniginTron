#include "MiniginPCH.h"
#include "InputManager.h"
#include <XInput.h>
#include <Windows.h>
#include "Command.h"
#include <map>

struct InputStruct
{
public:
	Command* pOnPressDown = nullptr;
	Command* pOnHold = nullptr;
	Command* pOnRelease = nullptr;
	bool wasPressedDownPreviousFrame = false;

	InputStruct() {};
	~InputStruct() 
	{
		delete pOnPressDown;
		pOnPressDown = nullptr;

		delete pOnHold;
		pOnHold = nullptr;

		delete pOnRelease;
		pOnRelease = nullptr;
	}
};

struct PlayerButton
{
	ControllerButton button;
	DWORD playerID;
};
bool operator==(const PlayerButton& lhs, const PlayerButton& rhs)
{
	return lhs.button == rhs.button && lhs.playerID == rhs.playerID;
}
bool operator<(const PlayerButton& lhs, const PlayerButton& rhs)
{
	return lhs.button < rhs.button || (lhs.button == rhs.button && lhs.playerID < rhs.playerID);
}
bool operator>(const PlayerButton& lhs, const PlayerButton& rhs)
{
	return lhs.button > rhs.button || (lhs.button == rhs.button && lhs.playerID > rhs.playerID);
}

class InputManager::XInputManager
{
public:
	bool ProcessInput();
	bool IsPressed(ControllerButton button, DWORD playerID) const;

	void AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID = 0);
	void AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID = 0);

	void CleanUp();
private:
	std::map<PlayerButton, InputStruct*> m_ControllerCommands;

	XINPUT_STATE m_pCurrentState{};
	bool m_DidInputGet = false;
};

bool InputManager::XInputManager::ProcessInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_pCurrentState, sizeof(XINPUT_STATE));
		XInputGetState(i, &m_pCurrentState);

		if (!IsPressed(ControllerButton(m_pCurrentState.Gamepad.wButtons), i))
		{
			for (auto& c : m_ControllerCommands)
			{
				if (c.second->wasPressedDownPreviousFrame == true)
				{
					c.second->wasPressedDownPreviousFrame = false;
					if (c.second->pOnRelease != nullptr)
					{
						c.second->pOnRelease->Execute();
						
					}
				}
			}
		}
	}


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool InputManager::XInputManager::IsPressed(ControllerButton button, DWORD playerID) const
{
	// todo: return whether the given button is pressed or not.

	if (m_ControllerCommands.find(PlayerButton{ button,playerID }) != m_ControllerCommands.end())
	{
		const bool previousState = m_ControllerCommands.at(PlayerButton{ button,playerID })->wasPressedDownPreviousFrame;
		if (previousState == false)
		{
			m_ControllerCommands.at(PlayerButton{ button,playerID })->wasPressedDownPreviousFrame = true;
			if (m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnPressDown != nullptr)
			{
				m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnPressDown->Execute();
			}
		}
		else
		{
			if (m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnHold != nullptr)
			{
				m_ControllerCommands.at(PlayerButton{ button,playerID })->pOnHold->Execute();
			}
		}
		return true;
	}
	return false;

	//switch (button)
	//{
	//case ControllerButton::ButtonA:
	//	return m_pCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	//case ControllerButton::ButtonB:
	//	return m_pCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	//case ControllerButton::ButtonX:
	//	return m_pCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	//case ControllerButton::ButtonY:
	//	return m_pCurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	//default: return false;
	//}
}

void InputManager::XInputManager::AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	auto button = PlayerButton{ controllerButton,playerID };
	if (m_ControllerCommands.find(button) == m_ControllerCommands.end())
	{
		InputStruct* inputStruct = new InputStruct{};
		inputStruct->pOnPressDown = command;
		m_ControllerCommands.emplace(button, inputStruct);
	}
	else
	{
		m_ControllerCommands[button]->pOnPressDown = command;
	}
}

void InputManager::XInputManager::AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	auto button = PlayerButton{ controllerButton,playerID };
	if (m_ControllerCommands.find(PlayerButton{ controllerButton,playerID }) == m_ControllerCommands.end())
	{
		InputStruct* inputStruct = new InputStruct{};
		inputStruct->pOnHold = command;
		m_ControllerCommands.emplace(button, inputStruct);
	}
	else
	{
		m_ControllerCommands[button]->pOnHold = command;
	}
}

void InputManager::XInputManager::AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	auto button = PlayerButton{ controllerButton,playerID };
	if (m_ControllerCommands.find(PlayerButton{ controllerButton,playerID }) == m_ControllerCommands.end())
	{
		InputStruct* inputStruct = new InputStruct{};
		inputStruct->pOnRelease = command;
		m_ControllerCommands.emplace(button, inputStruct);
	}
	else
	{
		m_ControllerCommands[button]->pOnRelease = command;
	}
}

void InputManager::XInputManager::CleanUp()
{
	for (auto& p : m_ControllerCommands)
	{
		delete p.second;
		p.second = nullptr;
	}
	m_ControllerCommands.clear();
}

InputManager::InputManager()
	:pimpl{ std::make_unique<XInputManager>() }
{
}

InputManager::~InputManager() = default;

bool InputManager::ProcessInput()
{
	return pimpl->ProcessInput();
}

bool InputManager::IsPressed(ControllerButton button, DWORD playerID) const
{
	return pimpl->IsPressed(button, playerID);
}

void InputManager::AddOnPressDown(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnPressDown(controllerButton, command, playerID);
}

void InputManager::AddOnHold(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnHold(controllerButton, command, playerID);
}

void InputManager::AddOnRelease(ControllerButton controllerButton, Command* command, DWORD playerID)
{
	pimpl->AddOnRelease(controllerButton, command, playerID);
}

void InputManager::CleanUp()
{
	pimpl->CleanUp();
}
