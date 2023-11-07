#include <iostream>
#include <string>
#include <curl/curl.h>
#include "./protobuf/gtfs-realtime.pb.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace transit_realtime;

std::vector<std::unordered_map<std::string, std::string>> parseCSV(const std::string& filePath) {
    std::vector<std::unordered_map<std::string, std::string>> data;

    // Open the CSV file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return data;
    }

    // Read and parse the header row to get column names
    std::string header;
    if (std::getline(file, header)) {
        std::istringstream headerStream(header);
        std::vector<std::string> columnNames;
        std::string column;
        while (std::getline(headerStream, column, ',')) {
            columnNames.push_back(column);
        }

        // Read and parse data rows
        std::string line;
        while (std::getline(file, line)) {
            std::unordered_map<std::string, std::string> rowData;
            std::istringstream lineStream(line);
            size_t columnIndex = 0;
            std::string cell;
            while (std::getline(lineStream, cell, ',')) {
                if (columnIndex < columnNames.size()) {
                    rowData[columnNames[columnIndex]] = cell;
                }
                columnIndex++;
            }
            data.push_back(rowData);
        }
    } else {
        std::cerr << "Failed to read the header row." << std::endl;
    }

    // Close the file
    file.close();

    return data;
}

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

    std::vector<std::string> endpoints{"vehiclePositions", "tripUpdates"};

    // Set the target URL
    std::string url = "https://api.stm.info/pub/od/gtfs-rt/ic/v2/" + endpoints.at(0);

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

    std::string outputFilePath("./output.txt");

    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open file: " << outputFilePath << std::endl;
        return 1;
    }
    outputFile << response.DebugString() << std::endl;

    auto routeData = parseCSV("../stm_data/routes.txt");

    return 0;
}
