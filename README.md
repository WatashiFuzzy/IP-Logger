# IP Logger in C++

Một ứng dụng máy chủ dòng lệnh (console) đơn giản được viết bằng C++ để ghi lại địa chỉ IP công khai.
Dự án này rất phù hợp cho những người muốn tìm hiểu cách hoạt động của một máy chủ HTTP cơ bản, cách xử lý request và ghi tệp trong C++.

> **⚠️ CẢNH BÁO QUAN TRỌNG**
>
> - **CHỈ SỬ DỤNG VỚI SỰ ĐỒNG Ý:** Công cụ này được tạo ra cho mục đích học tập. Chỉ sử dụng với những người đã biết và đồng ý cho phép bạn lấy IP của họ.
> - **VI PHẠM QUYỀN RIÊNG TƯ:** Lạm dụng công cụ này là hành vi xâm phạm quyền riêng tư và có thể là bất hợp pháp.
> - **MIỄN TRỪ TRÁCH NHIỆM:** Tác giả không chịu trách nhiệm cho bất kỳ hành vi sai trái nào khi sử dụng công cụ này.

## Tính năng

- Ghi lại địa chỉ IP Công khai (IPv4 & IPv6).
- Ghi lại thời gian truy cập chính xác.
- Tự động chuyển hướng người dùng đến một trang web khác.
- Chạy dưới dạng một ứng dụng console đơn giản.
- Sử dụng `ngrok` để đưa máy chủ nội bộ ra ngoài Internet.

## Cách chạy

#### 1. Chuẩn bị

- Cài đặt một trình biên dịch C++ (ví dụ: `g++`).
- Tải về tệp `httplib.h` từ [repo chính thức](https://github.com/yhirose/cpp-httplib/blob/master/httplib.h).
- Tải về và cài đặt `ngrok` từ [trang chủ](https://ngrok.com/download).
- Tạo một tệp `server.cpp` với mã nguồn của dự án.

#### 2. Biên dịch mã nguồn

Sử dụng `g++` để biên dịch chương trình. Mở terminal trong thư mục dự án và chạy:
```bash
g++ server.cpp -o ip_logger -pthread -std=c++17
```
### 3. Chạy chương trình ( Yêu cầu: 2 cửa sổ terminal )
 - Cửa sổ 1: Khởi chạy máy chủ
   ``` bash
   ./ip_logger
   ```
 - Cửa sổ 2: Chạy ngrok
   ```bash
   ngrok http 8080
   ```
 ### 4. Gửi liên kết 
 - Sao chép liên kết `Forwarding` từ `ngrok` ( ví dụ: `https://abcd-1234.ngrok-free.app` ).
 - Gửi liên kết này cho người bạn đã đồng ý thử nghiệm.
 ### Giao diện & Kết quả 
 - Giao diện dòng lệnh khi chạy:
   ``` bash
   $ ./ip_logger
    C++ IP Logger server starting on port 8080...
    Listening on [http://0.0.0.0:8080](http://0.0.0.0:8080)
     Logging: IP: 203.0.113.75 | Time: 2025-06-15 19:35:10
   ```
  - Nội dung tệp ips.log được tạo ra:
    ``` bash
    IP: 203.0.113.75 | Time: 2025-06-15 19:35:10
    IP: 2001:db8:85a3::8a2e:370:7334 | Time: 2025-06-15 19:36:02
    ```
 ### Điểm nổi bật về mã nguồn
  - Sử dụng thư viện `#include "httplib.h"` để tạo một máy chủ HTTP đa nền tảng một cách đơn giản.
  - Dùng `svr.Get("/", ...) `để định nghĩa một hàm xử lý các request `GET `đến máy chủ.
  - Lấy IP của khách truy cập thông qua `req.remote_addr` và header` X-Forwarded-For`.
  - Dùng `std::ofstream` để mở và ghi thông tin vào tệp tin log.
  - Chuyển hướng người dùng bằng `res.set_redirect("https://google.com")`.
