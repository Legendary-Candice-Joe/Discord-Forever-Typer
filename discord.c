#include <stdio.h>
#include "include/curl/curl.h"
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int end(){
    printf("\nCommand should look like:\nPoo.exe <Channel ID> <Discord Token>\n");
    return 1;
}

int main(int argc, char** argv){
    // need to make this check not suck ass.
    unsigned char queueEnd = 0;
    if(argc != 3)
        queueEnd = 1;
    if((argv[1] && (strlen(argv[1]) < 16 || strlen(argv[1]) > 20)) || !argv[1]){
        printf("Invalid Channel ID\n");
        queueEnd = 1;
    }
    if(argc != 3 || (argv[2] && strlen(argv[2]) < 10) || !argv[2]){
        printf("Invalid or missing token\n");
        queueEnd = 1;
    }
    if(queueEnd) return end();

    // basic setup garbage.
    // yes this is stolen from the demo.
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    struct curl_slist* dog = 0;

    int8_t len = strlen(argv[1]);
    int8_t l2n = strlen(argv[2]);

    // there is a more elegant way but I'm tired so f**k it.
    char*  fullString = malloc(36 + len + 8);
    strcpy(fullString       , "https://discord.com/api/v9/channels/");
    strcpy(fullString+36    , argv[1]);
    strcpy(fullString+36+len, "/typing");
    // I don't think this manual 0 is needed, but I want it here still.
    fullString[36+len+7] = '\0';

    char*  tokenString = malloc(16 + l2n);
    strcpy(tokenString   , "Authorization: ");
    strcpy(tokenString+15, argv[2]);
    tokenString[15+l2n] = '\0';

    //////////////////////////////////////////////

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fullString);

        // this sucks
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
        curl_easy_setopt(curl, CURLOPT_POST, 3L);

        dog = curl_slist_append(dog, tokenString);
        dog = curl_slist_append(dog, "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:109.0) Gecko/20100101 Firefox/114.0");
        ////                            ^^^^ user agent is so appearently we have a less likely chance of being banned.
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, dog);

        while(1){
            printf("Performing\n");
            // don't bother reporting the error
            res = curl_easy_perform(curl);
            if(res != CURLE_OK)
                printf("Error (lol)\n");

            // wait for 9 seconds.
            struct timespec h;
            h.tv_sec  = 9;
            h.tv_nsec = 9 * 1000000;
            nanosleep(&h, &h);
        }

        // clean up code not really needed as it kinda never gets used.
        curl_slist_free_all(dog);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}