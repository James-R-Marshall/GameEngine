#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char KeyCode) const noexcept
{
	return keystates[KeyCode];
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		EVENT e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

char Keyboard::ReadChar() noexcept
{
	if (!charbuffer.empty())
	{
	unsigned char charcode = charbuffer.front();
	charbuffer.pop();
	return charcode;
	}
	return '0';
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void Keyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutoRepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char KeyCode) noexcept
{
	keystates[KeyCode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, KeyCode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(unsigned char KeyCode) noexcept
{
	keystates[KeyCode] = false;
	keybuffer.push(EVENT(EVENT::Type::Release, KeyCode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}