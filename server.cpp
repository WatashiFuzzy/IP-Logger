#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "httplib.h"

// Hàm để lấy thời gian hiện tại dưới dạng chuỗi
std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

int main() {
    // Khởi tạo máy chủ từ thư viện httplib
    httplib::Server svr;

    // Định nghĩa hành vi cho đường dẫn gốc "/"
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        std::string ip_address;
        
        // Khi dùng proxy như ngrok, IP thật nằm trong header
        if (req.has_header("X-Forwarded-For")) {
            ip_address = req.get_header_value("X-Forwarded-For");
        } else {
            ip_address = req.remote_addr;
        }

        std::string timestamp = get_current_time();
        std::string log_entry = "IP: " + ip_address + " | Time: " + timestamp + "\n";
        
        // In ra console để theo dõi
        std::cout << "Logging: " << log_entry;

        // Mở file và ghi log
        std::ofstream log_file("ips_cpp.log", std::ios::app);
        if (log_file.is_open()) {
            log_file << log_entry;
            log_file.close();
        }

        // Thiết lập phản hồi chuyển hướng (302 Found)
        res.set_redirect("https://www.google.com");
    });

    int port = 8080;
    std::cout << "Server starting on port " << port << "..." << std::endl;
    
    // Lắng nghe kết nối trên cổng 8080
    // "0.0.0.0" có nghĩa là lắng nghe trên tất cả các giao diện mạng
    svr.listen("0.0.0.0", port);

    return 0;
}
