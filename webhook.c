/* Written by tornadus */
#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
    CURL* curl;
    CURLcode res;
    curl_mime* mime;
    curl_mimepart* part;

    char whurl[256];
    char filename[64];

    printf("Enter webhook URL (max 255 chars): ");
    scanf_s("%255s", whurl, (unsigned)_countof(whurl));

    printf("Enter filename (max 63 chars): ");
    scanf_s("%63s", filename, (unsigned)_countof(filename));

    struct curl_slist* file_headers = NULL;
    
    file_headers = curl_slist_append(file_headers, "Content-Type: application/octet-stream");

    curl = curl_easy_init();
    if (curl) {
        mime = curl_mime_init(curl);
        
        part = curl_mime_addpart(mime);
        curl_mime_filedata(part, filename);
        curl_mime_name(part, "file");
        curl_mime_filename(part, filename);
        curl_mime_headers(part, file_headers, 1);
        
        curl_easy_setopt(curl, CURLOPT_URL, whurl);
        curl_easy_setopt(curl , CURLOPT_MIMEPOST, mime);
            
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "Request error: %s\n",
                curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    return 0;
}
