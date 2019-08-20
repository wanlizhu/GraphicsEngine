#pragma once

#include "EngineConfig.h"
#include "NonCopyable.h"
#include <any>
#include <memory>
#include <string>
#include <list>
#include <unordered_map>
#include <functional>

struct GLFWwindow;

namespace ZHU
{
	struct InputModifiers
	{
		bool Ctrl = false;
		bool Shift = false;
		bool Alt = false;
	};
	
	struct KeyboardEvent
	{
		enum class EType 
		{
			Down,
			Up,
			Char,
		};
		
		EType Type;
		char Key;
		InputModifiers Mods;
		uint32_t CodePoint = 0;
	};
	
	struct MouseEvent
	{
		enum class EType 
		{
			LeftDown,
			LeftUp,
			MiddleDown,
			MiddleUp,
			RightDown,
			RightUp,
			Move,
			Wheel,
		};
		
		EType Type;
		InputModifiers Mods;
		std::array<int, 2> Position;
		std::array<int, 2> WheelDelta;
	};
	
    class GS_API Window : public std::enable_shared_from_this<Window>,
                          public NonCopyable
    {
    public:
		using SharedPtr = std::shared_ptr<Window>;
		using UniquePtr = std::unique_ptr<Window>;
		using MSG_ID = uint32_t;
		using HWINDOW = void*;
		using MSG_FUNC = std::function<void(HWINDOW, uint32_t, uint32_t)>;
		struct Desc 
		{
			std::string Title = "Untitled";
			std::array<int, 2> Position = { -1 };
			std::array<int, 2> Size = { -1 };
			bool IsFullScreen = false;
			bool IsResizable = true;
			bool AcceptDropFiles = true;
		};
		class ICallbacks
		{
		public:
			virtual void OnCreate() = 0;
			virtual void OnDestroy() = 0;
			virtual void OnResize(int width, int height) = 0;
			virtual void OnRender() = 0;
			virtual void OnKeyboardEvent(const KeyboardEvent& event) = 0;
			virtual void OnMouseEvent(const MouseEvent& event) = 0;
			virtual void OnDropFile(const std::string& path) = 0;
		};

        static std::array<int, 2> DefaultPos();
        static std::array<int, 2> DefaultSize();
		static SharedPtr Create(const WindowDesc& desc, ICallbacks* callbacks);

		void SetCallbacks(ICallbacks* callbacks);
        void SetTitle(const std::string& title);
        void SetFullScreen(bool enabled = true) ;
        void SetSize(int width, int height);
        void MoveTo(int x, int y);
        void MessageLoop();
		void SetMessageHook(MSG_ID msg, const MSG_FUNC& func);
        void Hide();
        void Show();
        void Destroy();

        std::string GetTitle() const;
        std::array<int, 2> GetPosition() const;
        std::array<int, 2> GetSize() const;
        
    protected:
        static void Initialize();

    private:
        GLFWwindow* mpWindow = nullptr;
		ICallbacks* mpCallbacks = nullptr;
		std::unordered_map<MSG_ID, MSG_FUNC> mMessageHooks;
    };
      
}