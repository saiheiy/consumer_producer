#include <SessionManager.h>
#include <InputProcessor.h>
#include <Application.h>


int main(){
    SessionManager m_sessionManager;
    InputProcessor m_inputProcessor(m_sessionManager);

    Application app(m_sessionManager, m_inputProcessor);
    app.run();
    return 0;
}
