#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// 用于接收 HTTP 响应数据
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    // 对话历史（线性表）
    std::vector<std::pair<std::string, std::string>> dialogueHistory;

    // 用户输入
    std::string userInput;
    std::cout << "请输入你的问题: ";
    std::getline(std::cin, userInput);

    // 构造请求 JSON
    json requestJson;
    requestJson["model"] = "deepseek-chat";
    requestJson["messages"] = {
        { {"role", "system"}, {"content", "你是一个数据结构小助手"} },
        { {"role", "user"}, {"content", userInput} }
    };
    requestJson["max_tokens"] = 150;
    requestJson["temperature"] = 0.7;

    // DeepSeek API 地址（指导书提供）
    std::string url = "http://8.134.223.251:3000/v1/chat/completions";
    std::string apiKey = "sk-1KPKwgb3R3zvesdO498d81C41c2b444a8a01B3FeB512121b"; // 在实验指导书中会给

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());

        std::string requestData = requestJson.dump();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() 失败: " << curl_easy_strerror(res) << std::endl;
        } else {
            // 解析返回 JSON
            json responseJson = json::parse(readBuffer);
            std::string assistantReply = responseJson["choices"][0]["message"]["content"];
            std::cout << "助手回复: " << assistantReply << std::endl;

            // 存储到对话历史
            dialogueHistory.push_back({userInput, assistantReply});
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
