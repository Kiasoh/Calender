#include <curl/curl.h>
#include <iostream>
using namespace std;
int main()
{
    //"http://parsamabani.pythonanywhere.com/reminder/check/?student_id=401521327"
    CURL *curl=curl_easy_init();
    CURLcode res;
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://parsamabani.pythonanywhere.com/reminder/check/?student_id=401521327");
        res = curl_easy_perform(curl);
        //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if(res == CURLE_OK) {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            cout << endl << response_code << endl;
        }
        //cout << response_code;
        curl_easy_cleanup(curl);
        
    }
    //cout << endl << response_code << endl;

    
    
}