# Wireless-Sensor-Network_Hust_20221
Project for Wireless Sensor Network class in HUST 20221
## Cấu hình Edge
- Tải Docker về máy:  
Có nhiều lựa chọn để có thể cấu hình Thingsboard Edge trên máy tính ở đây nhóm lựa chọn sử dụng Docker for Windows
Các lựa chọn khác có thể tham khảo:
https://thingsboard.io/docs/user-guide/install/edge/installation-options/
- Chạy Thingsboard Edge trên máy theo file cấu hình sử dụng lệnh trên terminal theo hướng dẫn sau: https://thingsboard.io/docs/user-guide/install/edge/docker-windows/ 
- Truy nhập vào Thingsboard Edge sử dụng địa chỉ IP của máy mà docker chạy trên máy đó và sử dụng địa chỉ đó để kết nối Gateway
- Tạo Device trên Edge sẽ đồng bộ hóa với Cloud và copy ACCESS TOKEN của Device đó để đưa vào parameter của HTTP request

Tạo Device theo hướng dẫn: https://thingsboard.io/docs/edge/getting-started/
## Triển khai trên Thingsboard Cloud
- Sau khi tạo Device trên Edge thì sẽ được đồng bộ lên Cloud
- Tạo Rule chain để tạo và xóa cảnh báo khi thông số vượt ngưỡng https://thingsboard.io/docs/user-guide/rule-engine-2-0/tutorials/create-clear-alarms/
- Tạo Dashboard và cấu hình Widget để hiển thị và điều khiển: https://thingsboard.io/docs/user-guide/contribution/widgets-development/

Cấu hình bản tin để gửi lệnh theo RPC ở phần Advanced của Control Widget 
