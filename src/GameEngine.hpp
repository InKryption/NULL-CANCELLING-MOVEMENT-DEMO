#ifndef __INK__APPBASE_STRUCT__HEADER_FILE_
#define __INK__APPBASE_STRUCT__HEADER_FILE_

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include <vector>
#include <unordered_map>

#include <iterator>
#include <memory>

/*
Include this file inside any child class of "GameEngine" after defining "GAMESTATE", as a macro function
taking in the name of another macro function, listing out the names of all desired gamestates as parameters to the
macro function name.

Example:
#define GAMESTATE(v) v(MainMenu) v(OptionsMenu) v(MainGame)

	!Note: This will be undefined automatically right after including the file.

This will add the following functionalities to the child class:

	* enum class GAMESTATE {...};
		A scoped enum called 'GAMESTATE' containing all the listed Gamestates.
			Example: enum class GAMESTATE { MainMenu, OptionsMenu, MainGame };
	
	* <GAMESTATE FUNCTIONS>
		A declaration of a member function for each declared GAMESTATE enum value, of the same name.
			Example:
				void MainMenu();
				void OptionsMenu();
				void MainGame();
	
	! REMEMBER: For each gamestate declared in 'GAMESTATES', a member function of the same name must be `defined` - not declared, as that is done
	automatically when this header is included after defining GAMESTATES.
	
	* GAMESTATE CurrentGameState;
		A variable of type GAMESTATE called 'CurrentGameState' which is used in the next listed function.
	
	* void Start();
		A function which will loop continuously so long as the bool 'Running' (from the GameEngine struct) is true,
		performing a switch statement to check the value of 'CurrentGameState', and run the matching function.
			Example:
				void Start() {
					while (Running) {
						switch (CurrentState) {
							case GAMESTATE::MainMenu: MainMenu(); break;
							case GAMESTATE::OptionsMenu: OptionsMenu(); break;
							case GAMESTATE::MainGame: MainGame(); break;
						}
					}
				}
	
	* bool CheckActive(GAMESTATE GameState);
		A function which returns true if: (CurrentGameState == GameState && Running). This is convenient for using 'main while loops' within the
		game state functions.
	
*/

#ifndef GAMESTATES

namespace ink {
	
	struct GameEngine:
	public Subsystem,
	public Screen,
	public FPSManager
	{
		bool Running = false;
		
		SDL_Event Event; // General event structure
		PhysicalKeyboard Keyboard; // Physical Keyboard state
		Mouse Mouse; // Mouse State
		
		// Called once on initialization
		virtual void GameInit() = 0;
		
		// Called to initialize the game engine
		void init(const Subsystem::Config& subsys_config, const Window::Config& win_config, const Renderer::Config& rend_config)
		{
			if (Running) return;
			Running = true;
			Subsystem::init(subsys_config);
			Screen::init(win_config, rend_config);
			GameInit();
		}
		
		class Object;
		class ObjectManager;
		
		// Generic Object ABI class. Should be managed within either a ObjectManager, or an inheriting type.
		class Object
		{
			public:
			virtual ~Object() {}
			virtual void Draw(ObjectManager* parent, GameEngine* ths) const = 0;
			virtual void Update(ObjectManager* parent, GameEngine* ths) = 0;
		};
		
		// Object Manager class. Allows two way interaction between itself and its managed objects. 
		// Deriving classes per-context for using it as an interface for context-specific variables is not a bad idea.
		// It features a dynamic render queue; those at the "top" of the render queue are rendered first - index 0 is considered the 'last'
		// priority. Objects can have their priority modified through function calls, using an efficient, redundant internal
		// data structure for indexing and queueing renders.
		struct ObjectManager
		{
			typedef std::unique_ptr<Object> ManagedObject;
			typedef ManagedObject::pointer ObjectPtr;
			
			size_t ObjectCount() const
			{ return ObjectHash.size(); }
			
			// Returns an iterator based on position in the RenderQueue
			std::vector<ObjectPtr>::const_iterator ObjectIterator() const
			{ return RenderQueue.begin(); }
			
			// Returns the theoretical iterator that would come after the last element in the iterator returned by ObjectIterator()
			std::vector<ObjectPtr>::const_iterator ObjectIterEnd() const
			{ return RenderQueue.end(); }
			
			// Add an object to the manager.
			void AddObject(ObjectPtr obj)
			{
				size_t index = ObjectHash.size();
				ObjectHash.emplace(index, std::pair(obj, index));
				IndexAccess.emplace(GetObject(index), index);
				RenderQueue.push_back(GetObject(index));
			}
			
			// Set the object at specified index to be rendered at zDestination, pushing other objects up or down the queue as necessary.
			template<typename T>
			void ChangeObjectZ(T index, size_t zDestination)
			{
				static_assert( std::is_convertible<T, size_t>::value, "Member function template<typename T> ObjectManager::ChangeObjectZ must be templated with type convertible to size_t.\n" );
				ChangeLayerZ(ObjectHash[static_cast<size_t>(index)].second, zDestination); ObjectHash[static_cast<size_t>(index)].second = zDestination;
			}
			
			// Set the object z index at layerIndex to be rendered at zDestination, pushing other objects up or down the queue as necessary.
			void ChangeLayerZ(size_t layerIndex, size_t zDestination)
			{
				auto elem = RenderQueue[layerIndex];
				signed short dir = (layerIndex < zDestination) - (layerIndex > zDestination);
				for (size_t i=layerIndex; i!=zDestination; i+=dir)
				RenderQueue[i] = RenderQueue[i+dir];
				RenderQueue[zDestination] = elem;
			}
			
			// Get object at specified index
			template<typename T>
			ObjectPtr GetObject(T index)
			{
				static_assert( std::is_convertible<T, size_t>::value, "Member function template<typename T> ObjectManager::GetObject must be templated with type convertible to size_t.\n" );
				return ObjectHash[static_cast<size_t>(index)].first.get(); }
			
			// Get object at specified zIndex
			ObjectPtr GetLayer(size_t zIndex)
			{ return RenderQueue[zIndex]; }
			
			// For objects that need access to their own index.
			size_t GetIndexOf(ObjectPtr objAddr)
			{ return IndexAccess[objAddr]; }
			
			// For objects that need to know where they are in the rendering queue.
			size_t GetLayerOf(ObjectPtr objAddr)
			{ return ObjectHash[GetIndexOf(objAddr)].second; }
			
			// Update all managed objects
			void Update(GameEngine* ths)
			{ for (auto& obj : ObjectHash) obj.second.first->Update(this, ths); }
			
			// Draw all managed objects to the GameEngine screen
			void Draw(GameEngine* ths)
			{ for ( auto obj = RenderQueue.rbegin(); obj != RenderQueue.rend(); obj++ ) (*obj)->Draw(this, ths); }
			
			private:
			std::vector<ObjectPtr> RenderQueue;
			std::unordered_map<ObjectPtr, size_t> IndexAccess;
			std::unordered_map< size_t , std::pair<ManagedObject, size_t> > ObjectHash;
		};
		
		// Struct that I'm essentially using to emulate a namespace within GameEngine
		struct DEFAULT {
			// Solid Color
			static inline const Color
				Black{0, 0, 0, 255},
				Grey{127, 127, 127, 255},
				White{255, 255, 255, 255},
				
				Red{255, 0, 0, 255},
				Yellow{255, 255, 0, 255},
				Green{0, 255, 0, 255},
				Cyan{0, 255, 255, 255},
				Blue{0, 0, 255, 255},
				Magenta{255, 0, 255, 255}
			;
		};
		
	};
	
}

#endif
#endif


#if defined(GAMESTATE)

#define _PROTECT(v) v

#define ADD_COMMA(v) v,
#define DECL_VOID_FUNC(name) void name();
#define RUN_GAMESTATE(GameState) case GAMESTATE::GameState: GameState(); break;

enum class _PROTECT(GAMESTATE) { GAMESTATE(ADD_COMMA) } CurrentGameState;
GAMESTATE(DECL_VOID_FUNC)
// Called to start the game itself
void Start() { while (Running) switch (CurrentGameState) { GAMESTATE(RUN_GAMESTATE) } }

bool CheckActive(GAMESTATE GameState) { return (GameState == CurrentGameState) && Running; }

#undef RUN_GAMESTATE
#undef DECL_VOID_FUNC
#undef ADD_COMMA

#undef _PROTECT
#undef GAMESTATES

#endif