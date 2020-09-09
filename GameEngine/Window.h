#include "ModifiedWindow.h"


// This is the Windows wrapper so we dont need to keep messing with the window api to deal with making a window

class window
{
private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
	};

};