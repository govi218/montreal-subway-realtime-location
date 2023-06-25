#include <iostream>
#include <string>
#include <curl/curl.h>
#include "./protobuf/gtfs-realtime.proto3.pb.h"

using namespace MontrealSubwayRealtimeLocation;

// Callback function to write the HTTP response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t total_size = size * nmemb;
    response->append((char*)contents, total_size);
    return total_size;
}

int main() {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a CURL handle
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl" << std::endl;
        return 1;
    }

    // Set the target URL
    std::string url = "https://api.stm.info/pub/od/gtfs-rt/ic/v2/tripUpdates";

    // Set the request headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "accept: application/x-protobuf");
    headers = curl_slist_append(headers, "apiKey: l76925aaec843544ffb6c2cfe56de5e97e");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Set the request options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    std::string response_data;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    // Perform the HTTP GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to perform HTTP GET request: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        curl_global_cleanup();
        return 1;
    }

    // Cleanup libcurl
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    // Deserialize the protobuf response message
   FeedMessage response;
    if (!response.ParseFromString(response_data)) {
        std::cerr << "Failed to parse response protobuf" << std::endl;
        return 1;
    }

    // Display the response message
    std::cout << response.DebugString() << std::endl;

    return 0;
}
