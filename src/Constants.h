//
// Created by Sai Hei Yeung on 6/24/17.
//

#ifndef SRC_CONSTANTS_H
#define SRC_CONSTANTS_H


namespace Constants {
    //InputProcessor configs
    static const int IP_MIN_THREADS = 2;
    static const int IP_MAX_THREADS = 10;
    static const int IP_MAX_IDLETIME = 5000;  //in milliseconds

    //SessionManager configs
    static const int SM_MIN_THREADS = 2;
    static const int SM_MAX_THREADS = 20;
    static const int SM_MAX_IDLETIME = 5000;  //in milliseconds

    static const char *TEST_CLIENTID1 = "test1";
}


#endif //SRC_CONSTANTS_H
