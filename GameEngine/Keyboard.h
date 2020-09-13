#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
#define EVENT Keyboard::Event

	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			code(0u)
		{}
		Event(Type type, unsigned char code) noexcept
			:
			type(type),
			code(code)
		{}
		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}
		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}
	};
	
	public:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator = (const Keyboard&) = delete;

		// key event stuff
		bool KeyIsPressed(unsigned char KeyCode)const noexcept;
		Event ReadKey() noexcept;
		bool KeyIsEmpty() const noexcept;
		void FlushKey() noexcept;
		char ReadChar() noexcept;
		bool CharIsEmpty() const noexcept;
		void FlushChar() noexcept;
		void Flush() noexcept;

		// this is for autorepeating of keys being held down

		void EnableAutoRepeat() noexcept;
		void DisableAutoRepeat() noexcept;
		bool AutorepeatIsEnabled() const noexcept;

private:
	void OnKeyPressed(unsigned char KeyCode) noexcept;
	void OnKeyReleased(unsigned char KeyCode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template <typename t>
	static void TrimBuffer(std::queue<t>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};

template<typename t>
inline void Keyboard::TrimBuffer(std::queue<t>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}
