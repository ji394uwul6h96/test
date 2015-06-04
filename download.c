#include <stdio.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>
#include <string.h>
//小葉笨
//呵呵

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t written = fwrite(ptr, size, nmemb, stream);

	return written;
}
int main(int argc, const char *argv[])
{
	if(argc < 3) {

		printf("Useage : ./download <url> <outputfile>!\n");
		return -1;	
	}
	else {
	
        CURL *curl = NULL;
        FILE *fp = NULL;
        CURLcode res;
        
        char url[1024];// = "http://211.72.227.245/iBeaconWeb/Asset.do?act=getAsset&id=370";
        char outfilename[FILENAME_MAX];
        strcpy(url, argv[1]);
        sprintf(outfilename, "./%s", argv[2]);
        curl = curl_easy_init();
        
        if(curl) {
            
            fp = fopen(outfilename, "wb");
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            
            long res_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res_code);
            if (!((res_code == 200 || res_code == 201) && res != CURLE_ABORTED_BY_CALLBACK))
            {
                printf("!!! Response code: %ld\n", res_code);
                return -1;
            }
            
            curl_easy_cleanup(curl);
            fclose(fp);
        }
    }
	return 0;
}
