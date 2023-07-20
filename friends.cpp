#include <curl/curl.h>
#include <iostream>
using namespace std;
int main()
{
    //"http://parsamabani.pythonanywhere.com/reminder/check/?student_id=401521327"
    CURL *curl=curl_easy_init();
    CURLcode res;
    char k[14]= {"912259739"};
    if (curl)
    {
        //string s = "http://parsamabani.pythonanywhere.com/reminder/call/?student_id=401521327&phone_number=" + k ;
        char link[1000];
        snprintf(link, 1000, "http://parsamabani.pythonanywhere.com/reminder/call/?student_id=401521327&phone_number=%s", k);
        curl_easy_setopt(curl, CURLOPT_URL, link);
        res = curl_easy_perform(curl);
        //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        //cout << s;
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