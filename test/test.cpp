#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <config.h>
#include <gx_face_api.h>
//using namespace std;
//
using namespace glasssix::face;
int main() {

    //config *x = new config();
    gx_face_api* _api = new gx_face_api();
    delete _api;
    //_api->gx_detect(nullptr);
    getchar();
    return 0;

}
