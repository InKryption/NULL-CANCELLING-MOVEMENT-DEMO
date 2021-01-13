#include "main.hpp"


struct NCM_DEMO:
public ink::GameEngine
{
	
	#define GAMESTATE(v) v(main)
	#include "GameEngine.hpp"
	
	void GameInit() override
	{
		
	}
	
	void HandleEvents()
	{
		while (SDL_PollEvent(&Event)!=0) switch(Event.type)
		{
			case SDL_QUIT: Running = false; break;
		}
		Mouse.Update();
	}
	
	struct {
		bool Right = 0, Left = 0;
		
		void Update(ink::PhysicalKeyboard& kb)
		{
			bool	pRight = RightBHeld,
				pLeft = LeftBHeld
			;
			
			RightBHeld = kb[SDL_SCANCODE_D];
			LeftBHeld = kb[SDL_SCANCODE_A];
			
			RightBPressed = RightBHeld && !pRight;
			LeftBPressed = LeftBHeld && !pLeft;
			
			Right = RightBHeld && !LeftBPressed && (RightBPressed || Right);
			Left = LeftBHeld && !RightBPressed && (LeftBPressed || Left);
			
			bool specialCheck = (!Right && !Left) && (RightBHeld || LeftBHeld);
			Right = specialCheck + !specialCheck * Right;
			Left = specialCheck + !specialCheck * Left;
			
			/*
			Mathematical formula for null cancelling movement:
				* Required variables:
				- 'Key1' or K1, 'Key2' or K2 (the command booleans representing the null cancelling keys)
				
				- K1Held, K2Held (Booleans indicating whether the respective key is being actively held)
				
				- K1Pressed, K2Pressed (Booleans indicating whether the respective key has been pressed - single tick)
				
				- prevK1, prevK2 (Booleans indicating the state of K1Held and K2Held, respectively, in the previous iteration)
				
				- SpecialCheck (Boolean that tests for a particular case of key input that interferes with smooth transition of null cancelling movement)
				
				* Process:
				1.	prevK1 = K1Held,
					prevK2 = K2Held
					
				2.	K1Held = GetKeyDown(<key code>),
					K2Held = GetKeyDown(<key code>)
					
				3.	K1Pressed = K1Held && !prevK1,
					K2Pressed = K2Held && !prevK2
				
				4.	K1 = K1Held && !K2Pressed && (K1Pressed || K1),
					K2 = K2Held && !K1Pressed && (K2Pressed || K2)
				
				5.1	SpecialCheck = (!K1 && !K2) && (K1Held || K2Held)
				5.2	K1 = SpecialCheck + !SpecialCheck * K1,
					K2 = SpecialCheck + !SpecialCheck * K2
			*/
		}
		
		private:
		bool RightBHeld, LeftBHeld;
		bool RightBPressed, LeftBPressed;
		bool RightBReleased, LeftBReleased;
	} Command;
	
	struct MovingRect:
	public Object
	{
		ink::Rect<int> rect{0, 500, 100, 100};
		void Draw(ObjectManager* parent, GameEngine* _engine) const override
		{
			_engine->SetDrawColor(DEFAULT::Green); _engine->DrawRect(rect, true);
		}
		
		void Update(ObjectManager* parent, GameEngine* _engine) override
		{
			auto engine = static_cast<NCM_DEMO*>(_engine);
			rect.pos += 6 * ink::V2D<int>{ -engine->Command.Left + engine->Command.Right };
		}
	};
	
};

void NCM_DEMO::main()
{
	
	ObjectManager ObjManager;
		ObjManager.AddObject( new MovingRect );
	
	while ( CheckActive( GAMESTATE::main ) )
	{
		CaptureStartFrame();
		HandleEvents();
		Command.Update(Keyboard);
		
		SetDrawColor(DEFAULT::White); Clear();
		
		ObjManager.Update(this);
		ObjManager.Draw(this);
		
		RenderPresent();
		CaptureEndFrame();
	}
	
}

int main(int argc, char* argv[])
{
	NCM_DEMO Demo; {
		ink::Subsystem::Config subsys_config;
		
		ink::Window::Config win_config;
			win_config.width_percentage = 75;
			win_config.height_percentage = 75;
			win_config.title = "NULL CANCELLING MOVEMENT DEMO";
		
		ink::Renderer::Config rend_config;
			rend_config.Flag.ACCELERATED = true;
		
		Demo.init(subsys_config, win_config, rend_config);
	}
	Demo.Start();
	
	return 0;
}
