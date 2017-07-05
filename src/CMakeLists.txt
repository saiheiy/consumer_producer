cmake_minimum_required(VERSION 3.7)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp Application.cpp Application.h StdinStringProcessor.cpp StdinStringProcessor.h Constants.h SessionManager.cpp SessionManager.h TestSession.cpp TestSession.h conpro_types.h SynchronizedQueue.cpp SynchronizedQueue.h ISession.h IMessageProcessor.h IParser.h IParsedType.h TestParser.h TestParsedType.h IRequestServer.h TestRequestServer.h)


add_executable(conpro ${SOURCE_FILES})



# set the path to the library folder
link_directories(/Users/saiheiyeung/git/producer_consumer/install/bde/lib)

# link the libraries to the executable
target_link_libraries (conpro
        /Users/saiheiyeung/git/consumer_producer/install/bde/lib/libbsl.a
        /Users/saiheiyeung/git/consumer_producer/install/bde/lib/libbdl.a
        )

include_directories(
        .
        /Users/saiheiyeung/git/consumer_producer/install/bde/include/bsl
        /Users/saiheiyeung/git/consumer_producer/install/bde/include/bdl
)