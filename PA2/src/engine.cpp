
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize(char** shaders)
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, shaders))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  char input = 's';  
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      input = Keyboard() | Mouse();
      if(input) break;
    }

    // Update and render the graphics
    m_graphics->Update(m_DT,input);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

char Engine::Mouse()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
    return '\0';
  }
  else if (m_event.type == SDL_MOUSEBUTTONDOWN){
    if(m_event.button.button == SDL_BUTTON_LEFT){
      return 'a';
    }
    if(m_event.button.button == SDL_BUTTON_RIGHT){
      return 's';
    }
  }
  return '\0';
}

char Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
    return '\0';
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    switch(m_event.key.keysym.sym){
      case SDLK_ESCAPE:
        m_running = false;
	break;
      case SDLK_a:
	return 'a';
	break;
      case SDLK_s:
	return 's';
	break;
      case SDLK_d:
        return 'd';
	break;
      case SDLK_f:
	return 'f';
	break;
      case SDLK_g:
        return 'g';
	break;
      case SDLK_h:
	return 'h';
	break;
      default:
	return '\0';
	break;
      }
  }
}
unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
