#include <curl/curl.h>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

// Callback function to handle data received from the server
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

std::string getTimezoneOffset(const std::string &apiUrl) {
  CURL *curl = nullptr;
  CURLcode res = CURL_LAST;
  std::string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl != nullptr) {
    curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
      curl_easy_cleanup(curl);
      curl_global_cleanup();
      return "";
    }
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return readBuffer;
}

int main() {
  // Example API URL (WorldTimeAPI for the current time and timezone)
  std::string apiUrl = "http://worldtimeapi.org/api/ip";

  std::string response = getTimezoneOffset(apiUrl);
  if (response.empty()) {
    std::cerr << "Failed to get a response from the API" << std::endl;
    return 1;
  }

  rapidjson::Document document;
  if (document.Parse(response.c_str()).HasParseError()) {
    std::cerr << "JSON parsing error: "
              << rapidjson::GetParseError_En(document.GetParseError())
              << std::endl;
    return 1;
  }

  if (document.HasMember("utc_offset") && document["utc_offset"].IsString()) {
    std::string offset = document["utc_offset"].GetString();
    std::cout << "Timezone offset: " << offset << std::endl;
  } else {
    std::cerr << "Invalid or missing 'utc_offset' field in JSON response"
              << std::endl;
    return 1;
  }

  return 0;
}
